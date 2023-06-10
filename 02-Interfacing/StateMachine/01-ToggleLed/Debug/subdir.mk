################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BlinkLed.c \
../DIO_Lcfg.c \
../DIO_Program.c \
../TIMER_Program.c 

OBJS += \
./BlinkLed.o \
./DIO_Lcfg.o \
./DIO_Program.o \
./TIMER_Program.o 

C_DEPS += \
./BlinkLed.d \
./DIO_Lcfg.d \
./DIO_Program.d \
./TIMER_Program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


