################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/HPM6360/toolchains/gcc/port_gcc.S \
../startup/HPM6360/toolchains/gcc/start.S 

O_SRCS += \
../startup/HPM6360/toolchains/gcc/port_gcc.o \
../startup/HPM6360/toolchains/gcc/start.o 

OBJS += \
./startup/HPM6360/toolchains/gcc/port_gcc.o \
./startup/HPM6360/toolchains/gcc/start.o 

S_UPPER_DEPS += \
./startup/HPM6360/toolchains/gcc/port_gcc.d \
./startup/HPM6360/toolchains/gcc/start.d 


# Each subdirectory must supply rules for building sources it contributes
startup/HPM6360/toolchains/gcc/%.o: ../startup/HPM6360/toolchains/gcc/%.S
	riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-strict-align -mno-save-restore -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -gdwarf-2 -x assembler-with-cpp -I"D:\Learning\HPM\workspace\HPM6300_CK" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\soc\HPM6300\ip" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\soc\HPM6300\HPM6360" -I"D:\Learning\HPM\workspace\HPM6300_CK\rt-thread\libcpu\risc-v\common" -I"D:\Learning\HPM\workspace\HPM6300_CK\libraries\hpm_sdk\arch" -I"D:\Learning\HPM\workspace\HPM6300_CK\startup\HPM6360" -ffunction-sections -fdata-sections -fno-common -mcmodel=medlow -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

