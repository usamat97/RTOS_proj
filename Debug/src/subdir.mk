################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/StdPeriph_Driver/inc" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Third-Party/SEGGER/SEGGER" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Third-Party/SEGGER/OS" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Third-Party/SEGGER/Config" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Config" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/Third-Party/FreeRTOS/org/Source/include" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/inc" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/CMSIS/device" -I"/home/usamat980/workspace/RTOS-Project/STM32_HelloWorld/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


