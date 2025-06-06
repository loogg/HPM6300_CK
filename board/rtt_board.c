/*
 * Copyright (c) 2021 - 2022 hpmicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "rtt_board.h"
#include "hpm_uart_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtthread.h>
#include "hpm_dma_mgr.h"
#include "hpm_rtt_os_tick.h"
#include "hpm_l1c_drv.h"

extern int rt_hw_uart_init(void);

void rtt_os_tick_clock(void)
{
#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
    clock_add_to_group(BOARD_OS_TIMER_CLK_NAME, 0);
#else
    clock_add_to_group(clock_mchtmr0, 0);
#endif
}

static void rtt_board_print_clock_freq(void)
{
    rt_kprintf("==============================\n");
    rt_kprintf(" %s clock summary\n", BOARD_NAME);
    rt_kprintf("==============================\n");
    rt_kprintf("cpu0:\t\t %luHz\n", clock_get_frequency(clock_cpu0));
    rt_kprintf("axi:\t\t %luHz\n", clock_get_frequency(clock_axi));
    rt_kprintf("ahb:\t\t %luHz\n", clock_get_frequency(clock_ahb));
    rt_kprintf("mchtmr0:\t %luHz\n", clock_get_frequency(clock_mchtmr0));
    rt_kprintf("xpi0:\t\t %luHz\n", clock_get_frequency(clock_xpi0));
    rt_kprintf("xpi1:\t\t %luHz\n", clock_get_frequency(clock_xpi1));
    rt_kprintf("femc:\t\t %luHz\n", clock_get_frequency(clock_femc));
    rt_kprintf("pll0clk0:\t\t %luHz\n", clock_get_frequency(clk_pll0clk0));
    rt_kprintf("pll0clk1:\t\t %luHz\n", clock_get_frequency(clk_pll0clk1));
    rt_kprintf("pll0clk2:\t\t %luHz\n", clock_get_frequency(clk_pll0clk2));
    rt_kprintf("pll1clk0:\t\t %luHz\n", clock_get_frequency(clk_pll1clk0));
    rt_kprintf("pll1clk1:\t\t %luHz\n", clock_get_frequency(clk_pll1clk1));
    rt_kprintf("pll2clk0:\t\t %luHz\n", clock_get_frequency(clk_pll2clk0));
    rt_kprintf("pll2clk1:\t\t %luHz\n", clock_get_frequency(clk_pll2clk1));
    rt_kprintf("==============================\n");
}

void rtt_board_init(void)
{
    rtt_os_tick_clock();
    board_init_clock();
    // board_init_console();
    board_init_pmp();

    dma_mgr_init();

    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

    /* Configure the OS Tick */
    os_tick_config();

    /* Initialize the UART driver first, because later driver initialization may require the rt_kprintf */
    rt_hw_uart_init();

    /* Set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rtt_board_print_clock_freq();
}

void app_init_led_pins(void)
{
    gpio_set_pin_output(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN);
    gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, BOARD_LED_OFF_LEVEL);
}

void app_led_write(uint32_t index, bool state)
{
   gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, state);
}


void BOARD_LED_write(uint32_t index, bool state)
{
    switch (index)
    {
    case 0:
        gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, state);
        break;
    default:
        /* Suppress the toolchain warnings */
        break;
    }
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(BOARD_APP_UART_BASE, *str++);
    }
}

void app_init_usb_pins(void)
{
    board_init_usb(HPM_USB0);
}

void rt_hw_cpu_reset(void)
{
    HPM_PPOR->RESET_ENABLE = (1UL << 31);
    HPM_PPOR->RESET_HOT &= ~(1UL << 31);
    HPM_PPOR->RESET_COLD |= (1UL << 31);

    HPM_PPOR->SOFTWARE_RESET = 1000U;
    while(1) {

    }
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset the board);

#ifdef RT_USING_CACHE
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH) {
        l1c_dc_flush((uint32_t)addr, size);
    } else {
        l1c_dc_invalidate((uint32_t)addr, size);
    }
}
#endif

uint32_t rtt_board_init_adc16_clock(ADC16_Type *ptr, bool clk_src_ahb)
{
    uint32_t freq = 0;

    if (ptr == HPM_ADC0) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@160MHz by default)*/
            clock_set_adc_source(clock_adc0, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll0_clk1 divided by 2 (@166MHz by default) */
            clock_set_adc_source(clock_adc0, clk_adc_src_ana0);
            clock_set_source_divider(clock_ana0, clk_src_pll0_clk1, 2U);
        }
        clock_add_to_group(clock_adc0, 0);
        freq = clock_get_frequency(clock_adc0);
    } else if (ptr == HPM_ADC1) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@160MHz by default)*/
            clock_set_adc_source(clock_adc1, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@166MHz by default) */
            clock_set_adc_source(clock_adc1, clk_adc_src_ana1);
            clock_set_source_divider(clock_ana1, clk_src_pll0_clk1, 2U);
        }
        clock_add_to_group(clock_adc1, 0);
        freq = clock_get_frequency(clock_adc1);
    } else if (ptr == HPM_ADC2) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@160MHz by default)*/
            clock_set_adc_source(clock_adc2, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@166MHz by default) */
            clock_set_adc_source(clock_adc2, clk_adc_src_ana2);
            clock_set_source_divider(clock_ana2, clk_src_pll0_clk1, 2U);
        }
        clock_add_to_group(clock_adc2, 0);
        freq = clock_get_frequency(clock_adc2);
    }

    return freq;
}

uint32_t rtt_board_init_i2s_clock(I2S_Type *ptr)
{
    if (ptr == HPM_I2S0) {
        clock_add_to_group(clock_i2s0, 0);
        return clock_get_frequency(clock_i2s0);
    } else if (ptr == HPM_I2S1) {
        clock_add_to_group(clock_i2s1, 0);
        return clock_get_frequency(clock_i2s1);
    } else {
        return 0;
    }
}

uint32_t rtt_board_init_pwm_clock(PWM_Type *ptr)
{
    uint32_t freq = 0;
    (void) ptr;
    return freq;
}

