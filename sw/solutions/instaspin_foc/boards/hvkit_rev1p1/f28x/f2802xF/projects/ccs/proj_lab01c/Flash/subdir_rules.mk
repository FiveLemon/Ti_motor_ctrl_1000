################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CodeStartBranch.obj: /home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="CodeStartBranch.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

adc.obj: /home/wmj/Documents/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="adc.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

angle_gen.obj: /home/wmj/Documents/my_motor/sw/modules/angle_gen/src/32b/angle_gen.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="angle_gen.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

clarke.obj: /home/wmj/Documents/my_motor/sw/modules/clarke/src/32b/clarke.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="clarke.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

clk.obj: /home/wmj/Documents/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="clk.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

cpu.obj: /home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

cpu_time.obj: /home/wmj/Documents/my_motor/sw/modules/cpu_time/src/32b/cpu_time.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu_time.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

ctrl.obj: /home/wmj/Documents/my_motor/sw/modules/ctrl/src/32b/ctrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="ctrl.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

datalog.obj: /home/wmj/Documents/my_motor/sw/modules/datalog/src/32b/datalog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="datalog.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

filter_fo.obj: /home/wmj/Documents/my_motor/sw/modules/filter/src/32b/filter_fo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="filter_fo.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

flash.obj: /home/wmj/Documents/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="flash.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

fw.obj: /home/wmj/Documents/my_motor/sw/modules/fw/src/32b/fw.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="fw.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

gpio.obj: /home/wmj/Documents/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="gpio.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

hal.obj: /home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="hal.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

ipark.obj: /home/wmj/Documents/my_motor/sw/modules/ipark/src/32b/ipark.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="ipark.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

memCopy.obj: /home/wmj/Documents/my_motor/sw/modules/memCopy/src/memCopy.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="memCopy.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

offset.obj: /home/wmj/Documents/my_motor/sw/modules/offset/src/32b/offset.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="offset.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

osc.obj: /home/wmj/Documents/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="osc.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

park.obj: /home/wmj/Documents/my_motor/sw/modules/park/src/32b/park.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="park.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pid.obj: /home/wmj/Documents/my_motor/sw/modules/pid/src/32b/pid.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pid.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pie.obj: /home/wmj/Documents/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pie.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pll.obj: /home/wmj/Documents/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pll.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

proj_lab01c.obj: /home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/src/proj_lab01c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="proj_lab01c.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pwm.obj: /home/wmj/Documents/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pwm.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pwr.obj: /home/wmj/Documents/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="pwr.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

spi.obj: /home/wmj/Documents/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="spi.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

svgen.obj: /home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="svgen.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

svgen_current.obj: /home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen_current.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="svgen_current.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: /home/wmj/Documents/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="timer.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

traj.obj: /home/wmj/Documents/my_motor/sw/modules/traj/src/32b/traj.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="traj.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

usDelay.obj: /home/wmj/Documents/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="usDelay.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

user.obj: /home/wmj/Documents/my_motor/sw/modules/user/src/32b/user.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="user.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

vs_freq.obj: /home/wmj/Documents/my_motor/sw/modules/vs_freq/src/32b/vs_freq.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="vs_freq.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

wdog.obj: /home/wmj/Documents/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/" --include_path="/mnt/eda_tools/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/boards/hvkit_rev1p1/f28x/f2802xF/src" --include_path="/home/wmj/Documents/my_motor" --advice:performance=all -g --define=FLASH --define=FAST_ROM_V1p7 --define=F2802xF --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="wdog.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


