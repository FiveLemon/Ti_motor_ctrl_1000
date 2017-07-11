################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CodeStartBranch.obj: D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

adc.obj: D:/Foc/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

clarke.obj: D:/Foc/my_motor/sw/modules/clarke/src/32b/clarke.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="clarke.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

clk.obj: D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="clk.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpu.obj: D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ctrl.obj: D:/Foc/my_motor/sw/modules/ctrl/src/32b/ctrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="ctrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

filter_fo.obj: D:/Foc/my_motor/sw/modules/filter/src/32b/filter_fo.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="filter_fo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

flash.obj: D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="flash.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio.obj: D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

graph.obj: D:/Foc/my_motor/sw/modules/diagnostic/graph/src/32b/graph.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="graph.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal.obj: D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="hal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c.obj: D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="i2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ipark.obj: D:/Foc/my_motor/sw/modules/ipark/src/32b/ipark.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="ipark.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

memCopy.obj: D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="memCopy.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

offset.obj: D:/Foc/my_motor/sw/modules/offset/src/32b/offset.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="offset.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

osc.obj: D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="osc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

park.obj: D:/Foc/my_motor/sw/modules/park/src/32b/park.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="park.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pid.obj: D:/Foc/my_motor/sw/modules/pid/src/32b/pid.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pid.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pie.obj: D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pie.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pll.obj: D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pll.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

proj_lab05h.obj: D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab05h.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="proj_lab05h.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwm.obj: D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pwm.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwr.obj: D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pwr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi.obj: D:/Foc/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="spi.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

svgen.obj: D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="svgen.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

svgen_current.obj: D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen_current.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="svgen_current.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

traj.obj: D:/Foc/my_motor/sw/modules/traj/src/32b/traj.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="traj.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usDelay.obj: D:/Foc/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

user.obj: D:/Foc/my_motor/sw/modules/user/src/32b/user.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="user.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

wdog.obj: D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt -O2 --include_path="D:/Foc/my_motor/sw/modules/hal/boards/drv8312kit_revD/f28x/f2802x/src/" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/Foc/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="D:/Foc/my_motor" -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="wdog.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


