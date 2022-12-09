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
BIG_ASS.lss \

FLASH_IMAGE += \
BIG_ASS.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: BIG_ASS.elf secondary-outputs

# Tool invocations
BIG_ASS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BIG_ASS.map -mmcu=atmega32 -o "BIG_ASS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BIG_ASS.lss: BIG_ASS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BIG_ASS.elf  >"BIG_ASS.lss"
	@echo 'Finished building: $@'
	@echo ' '

BIG_ASS.hex: BIG_ASS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BIG_ASS.elf  "BIG_ASS.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BIG_ASS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BIG_ASS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BIG_ASS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
