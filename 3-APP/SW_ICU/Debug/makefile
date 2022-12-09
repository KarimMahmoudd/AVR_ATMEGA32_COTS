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
SW_ICU.lss \

FLASH_IMAGE += \
SW_ICU.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SW_ICU.elf secondary-outputs

# Tool invocations
SW_ICU.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SW_ICU.map -mmcu=atmega32 -o "SW_ICU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SW_ICU.lss: SW_ICU.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SW_ICU.elf  >"SW_ICU.lss"
	@echo 'Finished building: $@'
	@echo ' '

SW_ICU.hex: SW_ICU.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SW_ICU.elf  "SW_ICU.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SW_ICU.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SW_ICU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SW_ICU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
