#include <rtthread.h>
#include <stdint.h>
#include <board.h>
#include "rtt_board.h"
#include "usbh_core.h"

int usbh_common_init(void) {
    app_init_usb_pins();

    intc_set_irq_priority(CONFIG_HPM_USBH_IRQn, 2);
    usbh_initialize(0, CONFIG_HPM_USBH_BASE);

    return 0;
}
