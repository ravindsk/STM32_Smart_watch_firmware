################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DEV_Config.c \
../Src/GUI_Paint.c \
../Src/LCD_1inch28.c \
../Src/LCD_1inch28_test.c \
../Src/display_driver.c \
../Src/font12.c \
../Src/font16.c \
../Src/font20.c \
../Src/font24.c \
../Src/font8.c \
../Src/fpu.c \
../Src/i2c.c \
../Src/image.c \
../Src/main.c \
../Src/max30102.c \
../Src/max30102_lib.c \
../Src/pulse_ox_display.c \
../Src/pulse_oximetry_lib.c \
../Src/rtc.c \
../Src/spi.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timebase.c \
../Src/uart.c 

OBJS += \
./Src/DEV_Config.o \
./Src/GUI_Paint.o \
./Src/LCD_1inch28.o \
./Src/LCD_1inch28_test.o \
./Src/display_driver.o \
./Src/font12.o \
./Src/font16.o \
./Src/font20.o \
./Src/font24.o \
./Src/font8.o \
./Src/fpu.o \
./Src/i2c.o \
./Src/image.o \
./Src/main.o \
./Src/max30102.o \
./Src/max30102_lib.o \
./Src/pulse_ox_display.o \
./Src/pulse_oximetry_lib.o \
./Src/rtc.o \
./Src/spi.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timebase.o \
./Src/uart.o 

C_DEPS += \
./Src/DEV_Config.d \
./Src/GUI_Paint.d \
./Src/LCD_1inch28.d \
./Src/LCD_1inch28_test.d \
./Src/display_driver.d \
./Src/font12.d \
./Src/font16.d \
./Src/font20.d \
./Src/font24.d \
./Src/font8.d \
./Src/fpu.d \
./Src/i2c.d \
./Src/image.d \
./Src/main.d \
./Src/max30102.d \
./Src/max30102_lib.d \
./Src/pulse_ox_display.d \
./Src/pulse_oximetry_lib.d \
./Src/rtc.d \
./Src/spi.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timebase.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"../$(ProjDirPath)/F4_chip_headers/CMSIS/Include" -I"../$(ProjDirPath)/F4_chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/DEV_Config.cyclo ./Src/DEV_Config.d ./Src/DEV_Config.o ./Src/DEV_Config.su ./Src/GUI_Paint.cyclo ./Src/GUI_Paint.d ./Src/GUI_Paint.o ./Src/GUI_Paint.su ./Src/LCD_1inch28.cyclo ./Src/LCD_1inch28.d ./Src/LCD_1inch28.o ./Src/LCD_1inch28.su ./Src/LCD_1inch28_test.cyclo ./Src/LCD_1inch28_test.d ./Src/LCD_1inch28_test.o ./Src/LCD_1inch28_test.su ./Src/display_driver.cyclo ./Src/display_driver.d ./Src/display_driver.o ./Src/display_driver.su ./Src/font12.cyclo ./Src/font12.d ./Src/font12.o ./Src/font12.su ./Src/font16.cyclo ./Src/font16.d ./Src/font16.o ./Src/font16.su ./Src/font20.cyclo ./Src/font20.d ./Src/font20.o ./Src/font20.su ./Src/font24.cyclo ./Src/font24.d ./Src/font24.o ./Src/font24.su ./Src/font8.cyclo ./Src/font8.d ./Src/font8.o ./Src/font8.su ./Src/fpu.cyclo ./Src/fpu.d ./Src/fpu.o ./Src/fpu.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/image.cyclo ./Src/image.d ./Src/image.o ./Src/image.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/max30102.cyclo ./Src/max30102.d ./Src/max30102.o ./Src/max30102.su ./Src/max30102_lib.cyclo ./Src/max30102_lib.d ./Src/max30102_lib.o ./Src/max30102_lib.su ./Src/pulse_ox_display.cyclo ./Src/pulse_ox_display.d ./Src/pulse_ox_display.o ./Src/pulse_ox_display.su ./Src/pulse_oximetry_lib.cyclo ./Src/pulse_oximetry_lib.d ./Src/pulse_oximetry_lib.o ./Src/pulse_oximetry_lib.su ./Src/rtc.cyclo ./Src/rtc.d ./Src/rtc.o ./Src/rtc.su ./Src/spi.cyclo ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timebase.cyclo ./Src/timebase.d ./Src/timebase.o ./Src/timebase.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

