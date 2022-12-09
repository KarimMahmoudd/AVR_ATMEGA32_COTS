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
CLCD3.lss \

FLASH_IMAGE += \
CLCD3.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: CLCD3.elf secondary-outputs

# Tool invocations
CLCD3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CLCD3.map -mmcu=atmega32 -o "CLCD3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CLCD3.lss: CLCD3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CLCD3.elf  >"CLCD3.lss"
	@echo 'Finished building: $@'
	@echo ' '

CLCD3.hex: CLCD3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex CLCD3.elf  "CLCD3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CLCD3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 CLCD3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CLCD3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
