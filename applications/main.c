/*
 * Copyright (c) 2021 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   Fan YANG        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "led.h"
#include "sdcard.h"
#include "usbh_common.h"
#include "hpm_gpio_drv.h"
#include "enetdev.h"


int main(void)
{
    led_init();
    usbh_common_init();
    enetdev_init();

    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 3);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 3, 1);

    rt_thread_mdelay(2000);

    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 5);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 5, 1);
    rt_thread_mdelay(500);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 5, 0);
    // sdcard_init();

    return 0;
}



