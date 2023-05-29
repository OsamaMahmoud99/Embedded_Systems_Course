################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Digital_Clock.lss \

FLASH_IMAGE += \
Digital_Clock.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Digital_Clock.elf secondary-outputs

# Tool invocations
Digital_Clock.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Digital_Clock.map -mmcu=atmega32 -o "Digital_Clock.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Digital_Clock.lss: Digital_Clock.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Digital_Clock.elf  >"Digital_Clock.lss"
	@echo 'Finished building: $@'
	@echo ' '

Digital_Clock.hex: Digital_Clock.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Digital_Clock.elf  "Digital_Clock.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Digital_Clock.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Digital_Clock.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Digital_Clock.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
