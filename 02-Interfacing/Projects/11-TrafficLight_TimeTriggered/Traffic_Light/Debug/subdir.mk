################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Lcfg.c \
../DIO_Program.c \
../LED.c \
../SSD.c \
../STTS_program.c \
../TIME.c \
../TIMER_Program.c \
../Timer_Service.c \
../main.c 

OBJS += \
./DIO_Lcfg.o \
./DIO_Program.o \
./LED.o \
./SSD.o \
./STTS_program.o \
./TIME.o \
./TIMER_Program.o \
./Timer_Service.o \
./main.o 

C_DEPS += \
./DIO_Lcfg.d \
./DIO_Program.d \
./LED.d \
./SSD.d \
./STTS_program.d \
./TIME.d \
./TIMER_Program.d \
./Timer_Service.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


