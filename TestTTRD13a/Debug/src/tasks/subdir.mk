################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tasks/heartbeat_1769_003-0_c02a.c \
../src/tasks/menu_1769_003-0_c13a.c \
../src/tasks/spi_7_seg_display_1769_003-0_c13a.c \
../src/tasks/switch_ea-sw3_1769_003-0_c13a.c \
../src/tasks/watchdog_1769_003-0_c02a.c 

OBJS += \
./src/tasks/heartbeat_1769_003-0_c02a.o \
./src/tasks/menu_1769_003-0_c13a.o \
./src/tasks/spi_7_seg_display_1769_003-0_c13a.o \
./src/tasks/switch_ea-sw3_1769_003-0_c13a.o \
./src/tasks/watchdog_1769_003-0_c02a.o 

C_DEPS += \
./src/tasks/heartbeat_1769_003-0_c02a.d \
./src/tasks/menu_1769_003-0_c13a.d \
./src/tasks/spi_7_seg_display_1769_003-0_c13a.d \
./src/tasks/switch_ea-sw3_1769_003-0_c13a.d \
./src/tasks/watchdog_1769_003-0_c02a.d 


# Each subdirectory must supply rules for building sources it contributes
src/tasks/%.o: ../src/tasks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"D:\Santiago\Universidad\PPS\Workspaces\Pruebas\TestTTRD13a\inc" -I"D:\Santiago\Universidad\PPS\Workspaces\Pruebas\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


