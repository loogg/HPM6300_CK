#include <rtthread.h>
#include <dfs_fs.h>
#include "board.h"

#define DBG_TAG "sdcard"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SDCARD_SDXC_BASE   HPM_SDXC0
#define SDCARD_DEVICE_NAME "sd0"
#define SDCARD_MOUNT_POINT "/"

void rt_hw_mmcsd_change(SDXC_Type *ptr);

typedef struct _sd_handler {
    // 有符号数，0表示未挂载，1表示挂载成功，-1表示挂载失败
    int8_t mounted;
} sd_handler_t;

sd_handler_t sd_handler;

static int _sdcard_mount(void) {
    int       rc = -1;
    rt_base_t level;

    rt_device_t device = rt_device_find(SDCARD_DEVICE_NAME);
    if (device == NULL) {
        mmcsd_wait_cd_changed(0);
        rt_hw_mmcsd_change(SDCARD_SDXC_BASE);
        mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
        device = rt_device_find(SDCARD_DEVICE_NAME);
    }
    if (device != RT_NULL) {
        if (dfs_mount(SDCARD_DEVICE_NAME, SDCARD_MOUNT_POINT, "elm", 0, 0) == RT_EOK) { rc = 0; }
    }

    if (rc != 0) {
        LOG_W("sd card mount to '%s' failed!", SDCARD_MOUNT_POINT);
        level              = rt_hw_interrupt_disable();
        sd_handler.mounted = -1;
        rt_hw_interrupt_enable(level);
    } else {
        LOG_I("sd card mount to '%s'", SDCARD_MOUNT_POINT);

        level              = rt_hw_interrupt_disable();
        sd_handler.mounted = 1;
        rt_hw_interrupt_enable(level);
    }

    return rc;
}

static int _sdcard_unmount(void) {
    int       rc = 0;
    rt_base_t level;

    rt_thread_mdelay(200);
    dfs_unmount(SDCARD_MOUNT_POINT);
    LOG_I("Unmount '%s'", SDCARD_MOUNT_POINT);

    level              = rt_hw_interrupt_disable();
    sd_handler.mounted = 0;
    rt_hw_interrupt_enable(level);

    mmcsd_wait_cd_changed(0);
    rt_hw_mmcsd_change(SDCARD_SDXC_BASE);
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);

    return rc;
}

static void sd_mount_thread(void *parameter) {
    rt_thread_mdelay(1000);
    while (1) {
        rt_thread_mdelay(200);

        if (!board_sd_detect_card(SDCARD_SDXC_BASE)) {
            if (sd_handler.mounted == 1) {
                LOG_W("SD card removed");
                _sdcard_unmount();
            }
        } else {
            if (sd_handler.mounted != 1) {
                LOG_I("SD card inserted");
                _sdcard_mount();
            }
        }
    }
}

int sdcard_check_mount(void) {
    int       ret = -1;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret   = sd_handler.mounted;
    rt_hw_interrupt_enable(level);

    return ret;
}

int sdcard_init(void) {
    rt_memset(&sd_handler, 0, sizeof(sd_handler));

    init_sdxc_cd_pin(SDCARD_SDXC_BASE, false); // 设置 SD 卡检测引脚为 GPIO 模式

    rt_thread_t tid = rt_thread_create("sd_mount", sd_mount_thread, RT_NULL, 4096, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL) {
        rt_thread_startup(tid);
    } else {
        LOG_E("create sd_mount thread err!");
    }

    return RT_EOK;
}
