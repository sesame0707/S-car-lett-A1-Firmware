################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
SEGGER/OS/%.o SEGGER/OS/%.su SEGGER/OS/%.cyclo: ../SEGGER/OS/%.c SEGGER/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/Config" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/OS" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/SEGGER" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS_V2" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SEGGER-2f-OS

clean-SEGGER-2f-OS:
	-$(RM) ./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.cyclo ./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d ./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o ./SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-SEGGER-2f-OS

