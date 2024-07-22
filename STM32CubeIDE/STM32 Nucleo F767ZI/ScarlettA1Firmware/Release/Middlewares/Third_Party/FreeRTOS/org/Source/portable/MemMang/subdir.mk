################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.o Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.su Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/%.c Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu18 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/Config" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/OS" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/SEGGER/SEGGER" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS_V2" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Projects/GitHub/S-car-lett-A1-Firmware/STM32CubeIDE/STM32 Nucleo F767ZI/ScarlettA1Firmware/Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.d ./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.o ./Middlewares/Third_Party/FreeRTOS/org/Source/portable/MemMang/heap_4.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-MemMang

