################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_IQ_ROMSymbols.lib" \
"D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_ONLY_ROMSymbols.lib" \
"D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_RTS_ROMSymbols.lib" \
"D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/fast_public.lib" \
"D:/Foc/my_motor/sw/modules/iqmath/lib/f28x/32b/IQmath.lib" \
"./wdog.obj" \
"./user.obj" \
"./usDelay.obj" \
"./traj.obj" \
"./timer.obj" \
"./svgen_current.obj" \
"./svgen.obj" \
"./spi.obj" \
"./pwr.obj" \
"./pwm.obj" \
"./proj_lab10e.obj" \
"./process_ctrl.obj" \
"./pll.obj" \
"./pie.obj" \
"./pid.obj" \
"./pca9555.obj" \
"./park.obj" \
"./osc.obj" \
"./oled.obj" \
"./offset.obj" \
"./memCopy.obj" \
"./ldc1612.obj" \
"./ipark.obj" \
"./i2c.obj" \
"./hal.obj" \
"./gpio.obj" \
"./fw.obj" \
"./flyingStart.obj" \
"./flash.obj" \
"./filter_fo.obj" \
"./decoder.obj" \
"./ctrl.obj" \
"./cpu_time.obj" \
"./cpu.obj" \
"./clk.obj" \
"./clarke.obj" \
"./brake.obj" \
"./adc.obj" \
"./CodeStartBranch.obj" \
"D:/Foc/my_motor/sw/ide/ccs/cmd/f2802x/F28027F.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
proj_lab10e.out \

EXE_OUTPUTS__QUOTED += \
"proj_lab10e.out" \

BIN_OUTPUTS += \
proj_lab10e.hex \

BIN_OUTPUTS__QUOTED += \
"proj_lab10e.hex" \


# All Target
all: proj_lab10e.out

# Tool invocations
proj_lab10e.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing -z -m"proj_lab10e.map" --stack_size=0x200 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --reread_libs --priority --disable_auto_rts --diag_suppress=16002 --xml_link_info="proj_lab10e_linkInfo.xml" --rom_model -o "proj_lab10e.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

proj_lab10e.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "proj_lab10e.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "adc.pp" "brake.pp" "clarke.pp" "clk.pp" "cpu.pp" "cpu_time.pp" "ctrl.pp" "decoder.pp" "filter_fo.pp" "flash.pp" "flyingStart.pp" "fw.pp" "gpio.pp" "hal.pp" "i2c.pp" "ipark.pp" "ldc1612.pp" "memCopy.pp" "offset.pp" "oled.pp" "osc.pp" "park.pp" "pca9555.pp" "pid.pp" "pie.pp" "pll.pp" "process_ctrl.pp" "proj_lab10e.pp" "pwm.pp" "pwr.pp" "spi.pp" "svgen.pp" "svgen_current.pp" "timer.pp" "traj.pp" "user.pp" "wdog.pp" 
	-$(RM) "CodeStartBranch.obj" "adc.obj" "brake.obj" "clarke.obj" "clk.obj" "cpu.obj" "cpu_time.obj" "ctrl.obj" "decoder.obj" "filter_fo.obj" "flash.obj" "flyingStart.obj" "fw.obj" "gpio.obj" "hal.obj" "i2c.obj" "ipark.obj" "ldc1612.obj" "memCopy.obj" "offset.obj" "oled.obj" "osc.obj" "park.obj" "pca9555.obj" "pid.obj" "pie.obj" "pll.obj" "process_ctrl.obj" "proj_lab10e.obj" "pwm.obj" "pwr.obj" "spi.obj" "svgen.obj" "svgen_current.obj" "timer.obj" "traj.obj" "usDelay.obj" "user.obj" "wdog.obj" 
	-$(RM) "CodeStartBranch.pp" "usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

