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
ICU_HW.lss \

FLASH_IMAGE += \
ICU_HW.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ICU_HW.elf secondary-outputs

# Tool invocations
ICU_HW.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ICU_HW.map -mmcu=atmega32 -o "ICU_HW.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ICU_HW.lss: ICU_HW.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ICU_HW.elf  >"ICU_HW.lss"
	@echo 'Finished building: $@'
	@echo ' '

ICU_HW.hex: ICU_HW.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ICU_HW.elf  "ICU_HW.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ICU_HW.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ICU_HW.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ICU_HW.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
