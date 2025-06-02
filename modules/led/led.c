#include <rtthread.h>
#include "board.h"
#include "hpm_gpio_drv.h"
#include "hpm_gpiom_drv.h"

#define DBG_TAG    "led"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void _hw_init_pins(void) {
    HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_SOC_PZ_02;
    HPM_IOC->PAD[IOC_PAD_PZ02].FUNC_CTL  = IOC_PZ02_FUNC_CTL_GPIO_Z_02;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOZ, 2, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOZ, 2);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOZ, 2, 1);

    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_GPIO_C_08;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOC, 8, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 8);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 8, 1);

    HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_GPIO_C_09;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOC, 9, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 9);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 9, 1);

    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PC10_FUNC_CTL_GPIO_C_10;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOC, 10, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 10);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 10, 1);

    HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PC11_FUNC_CTL_GPIO_C_11;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOC, 11, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOC, 11);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOC, 11, 1);

    HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PA24_FUNC_CTL_GPIO_A_24;

    gpiom_set_pin_controller(HPM_GPIOM, GPIOM_ASSIGN_GPIOA, 24, gpiom_soc_gpio0);
    gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOA, 24);
    gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOA, 24, 1);
}

static uint32_t _led_pins[] = {
    IOC_PAD_PA24,
    IOC_PAD_PC11,
    IOC_PAD_PC10,
    IOC_PAD_PC09,
    IOC_PAD_PC08,
    IOC_PAD_PZ02,
};

static void led_entry(void *parameter) {
    while (1) {
        for (int i = 0; i < sizeof(_led_pins) / sizeof(_led_pins[0]); i++) {
            gpio_toggle_pin(HPM_GPIO0, GPIO_GET_PORT_INDEX(_led_pins[i]), GPIO_GET_PIN_INDEX(_led_pins[i]));
            rt_thread_mdelay(500);
        }
    }
}

int led_init(void) {
    _hw_init_pins();

    rt_thread_t tid = rt_thread_create("led", led_entry, NULL, 2048, 25, 10);
    if (tid == NULL) {
        LOG_E("Failed to create led thread");
        return -1;
    }
    rt_thread_startup(tid);

    return 0;
}
