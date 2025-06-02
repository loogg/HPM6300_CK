
#include <lwip/netif.h>
#include <lwip/netifapi.h>
#include <lwip/inet.h>
#include <netdev.h>


#define DBG_TAG    "enetdev"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define ENETDEV_NAME "E0"

static struct netdev *enetdev = NULL;

int enetdev_init(void) {
    enetdev = netdev_get_by_name(ENETDEV_NAME);
    if (enetdev == NULL) {
        LOG_E("Failed to get network device: %s", ENETDEV_NAME);
        return -1;
    }

    netdev_dhcp_enabled(enetdev, RT_FALSE);

    ip_addr_t ipaddr, netmask, gw;
    IP4_ADDR(&ipaddr, 192, 168, 2, 32);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gw, 192, 168, 2, 1);

    netdev_set_ipaddr(enetdev, &ipaddr);
    netdev_set_netmask(enetdev, &netmask);
    netdev_set_gw(enetdev, &gw);

    return 0;
}
