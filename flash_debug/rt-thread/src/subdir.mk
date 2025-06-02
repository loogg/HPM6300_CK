################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/src/clock.c \
../rt-thread/src/components.c \
../rt-thread/src/idle.c \
../rt-thread/src/ipc.c \
../rt-thread/src/irq.c \
../rt-thread/src/kservice.c \
../rt-thread/src/mem.c \
../rt-thread/src/mempool.c \
../rt-thread/src/object.c \
../rt-thread/src/scheduler_up.c \
../rt-thread/src/thread.c \
../rt-thread/src/timer.c 

OBJS += \
./rt-thread/src/clock.o \
./rt-thread/src/components.o \
./rt-thread/src/idle.o \
./rt-thread/src/ipc.o \
./rt-thread/src/irq.o \
./rt-thread/src/kservice.o \
./rt-thread/src/mem.o \
./rt-thread/src/mempool.o \
./rt-thread/src/object.o \
./rt-thread/src/scheduler_up.o \
./rt-thread/src/thread.o \
./rt-thread/src/timer.o 

C_DEPS += \
./rt-thread/src/clock.d \
./rt-thread/src/components.d \
./rt-thread/src/idle.d \
./rt-thread/src/ipc.d \
./rt-thread/src/irq.d \
./rt-thread/src/kservice.d \
./rt-thread/src/mem.d \
./rt-thread/src/mempool.d \
./rt-thread/src/object.d \
./rt-thread/src/scheduler_up.d \
./rt-thread/src/thread.d \
./rt-thread/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/src/%.o: ../rt-thread/src/%.c
	riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-strict-align -mno-save-restore -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -gdwarf-2 -DDEBUG -DUSE_NONVECTOR_MODE=1 -DFLASH_XIP=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -I"D:\Learning\HPM\workspace\HPM6300_CK" -I"D:\Learning\HPM\workspace\HPM6300_CK\applications" -I"D:\Learning\HPM\workspace\HPM6300_CK\board" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\drivers" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\arch\riscv\l1c" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\arch" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\debug_console" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\dma_mgr" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\enet_phy\rtl8201" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\enet_phy" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\touch" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\components\usb" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\drivers\inc" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\soc\HPM6300\HPM6360\boot" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\soc\HPM6300\HPM6360" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\soc\HPM6300\ip" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\utils" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\misc\rtt_interrupt_util" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\misc\rtt_os_tick" -I"D:\Learning\HPM\workspace\HPM6300_CK\modules\enet" -I"D:\Learning\HPM\workspace\HPM6300_CK\modules\led" -I"D:\Learning\HPM\workspace\HPM6300_CK\modules\sdcard" -I"D:\Learning\HPM\workspace\HPM6300_CK\modules\usb_config" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\adb" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\audio" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\cdc" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\dfu" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\hid" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\hub" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\midi" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\msc" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\vendor\net" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\vendor\serial" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\vendor\wifi" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\video" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\class\wireless" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\common" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3\core" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\CherryUSB-v1.4.3" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\netutils-latest\ntp" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\porting\inc\bsp" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\porting\inc\hal" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\porting\inc\rtos" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\inc" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\resources\clm\COMPONENT_43438" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\resources\firmware\COMPONENT_43438" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\resources\nvram\COMPONENT_43438\COMPONENT_AW-CU427-P" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\resources\resource_imp" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\src\bus_protocols" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\src\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver\WiFi_Host_Driver\src" -I"D:\Learning\HPM\workspace\HPM6300_CK\packages\wifi-host-driver-latest\wifi-host-driver" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\dfs\dfs_v1\filesystems\devfs" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\dfs\dfs_v1\filesystems\elmfat" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\dfs\dfs_v1\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\drivers\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\drivers\wlan" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\finsh" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\compilers\common\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\compilers\newlib" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\posix\io\epoll" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\posix\io\eventfd" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\posix\io\poll" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\posix\io\stdio" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\libc\posix\ipc" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\lwip\lwip-2.1.2\src\include\netif" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\lwip\lwip-2.1.2\src\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\lwip\port" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\netdev\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\sal\impl" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\sal\include\dfs_net" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\sal\include\socket\sys_socket" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\sal\include\socket" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\net\sal\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\components\utilities\ulog" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\include" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\libcpu\risc-v\common" -I"D:\Learning\HPM\workspace\HPM6300_CK\startup\HPM6360" -include"D:\Learning\HPM\workspace\HPM6300_CK\rtconfig_preinc.h" -std=gnu11 -ffunction-sections -fdata-sections -fno-common   -mcmodel=medlow -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

