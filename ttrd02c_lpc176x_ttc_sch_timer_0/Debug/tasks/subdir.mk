################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tasks/heartbeat_1769_003-0_c02b.c \
../tasks/watchdog_1769_003-0_c02a.c 

OBJS += \
./tasks/heartbeat_1769_003-0_c02b.o \
./tasks/watchdog_1769_003-0_c02a.o 

C_DEPS += \
./tasks/heartbeat_1769_003-0_c02b.d \
./tasks/watchdog_1769_003-0_c02a.d 


# Each subdirectory must supply rules for building sources it contributes
tasks/%.o: ../tasks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__REDLIB__ -D__CODE_RED -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


