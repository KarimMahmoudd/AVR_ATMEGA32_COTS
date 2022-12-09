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
DIOAss2.lss \

FLASH_IMAGE += \
DIOAss2.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: DIOAss2.elf secondary-outputs

# Tool invocations
DIOAss2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,DIOAss2.map -mmcu=atmega32 -o "DIOAss2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

DIOAss2.lss: DIOAss2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S DIOAss2.elf  >"DIOAss2.lss"
	@echo 'Finished building: $@'
	@echo ' '

DIOAss2.hex: DIOAss2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex DIOAss2.elf  "DIOAss2.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: DIOAss2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 DIOAss2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) DIOAss2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
