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
DC_MOTOR.lss \

FLASH_IMAGE += \
DC_MOTOR.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: DC_MOTOR.elf secondary-outputs

# Tool invocations
DC_MOTOR.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,DC_MOTOR.map -mmcu=atmega32 -o "DC_MOTOR.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

DC_MOTOR.lss: DC_MOTOR.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S DC_MOTOR.elf  >"DC_MOTOR.lss"
	@echo 'Finished building: $@'
	@echo ' '

DC_MOTOR.hex: DC_MOTOR.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex DC_MOTOR.elf  "DC_MOTOR.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: DC_MOTOR.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 DC_MOTOR.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) DC_MOTOR.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
