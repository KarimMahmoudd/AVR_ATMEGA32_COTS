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
BUZZER.lss \

FLASH_IMAGE += \
BUZZER.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: BUZZER.elf secondary-outputs

# Tool invocations
BUZZER.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BUZZER.map -mmcu=atmega32 -o "BUZZER.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BUZZER.lss: BUZZER.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BUZZER.elf  >"BUZZER.lss"
	@echo 'Finished building: $@'
	@echo ' '

BUZZER.hex: BUZZER.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BUZZER.elf  "BUZZER.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BUZZER.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BUZZER.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BUZZER.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
