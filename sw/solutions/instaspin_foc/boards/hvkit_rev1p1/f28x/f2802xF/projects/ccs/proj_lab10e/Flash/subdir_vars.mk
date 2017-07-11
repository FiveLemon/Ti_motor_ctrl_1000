################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
D:/Foc/my_motor/sw/ide/ccs/cmd/f2802x/F28027F.cmd 

LIB_SRCS += \
D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_IQ_ROMSymbols.lib \
D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_ONLY_ROMSymbols.lib \
D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_RTS_ROMSymbols.lib \
D:/Foc/my_motor/sw/modules/iqmath/lib/f28x/32b/IQmath.lib \
D:/Foc/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/fast_public.lib 

ASM_SRCS += \
D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm \
D:/Foc/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm 

C_SRCS += \
D:/Foc/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c \
D:/Foc/my_motor/sw/modules/brake/src/brake.c \
D:/Foc/my_motor/sw/modules/clarke/src/32b/clarke.c \
D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c \
D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c \
D:/Foc/my_motor/sw/modules/cpu_time/src/32b/cpu_time.c \
D:/Foc/my_motor/sw/modules/ctrl/src/32b/ctrl.c \
D:/Foc/my_motor/sw/drivers/drvic/decoder.c \
D:/Foc/my_motor/sw/modules/filter/src/32b/filter_fo.c \
D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c \
D:/Foc/my_motor/sw/modules/flyingStart/src/32b/flyingStart.c \
D:/Foc/my_motor/sw/modules/fw/src/32b/fw.c \
D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c \
D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c \
D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c \
D:/Foc/my_motor/sw/modules/ipark/src/32b/ipark.c \
D:/Foc/my_motor/sw/drivers/drvic/ldc1612.c \
D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c \
D:/Foc/my_motor/sw/modules/offset/src/32b/offset.c \
D:/Foc/my_motor/sw/drivers/drvic/oled/oled.c \
D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c \
D:/Foc/my_motor/sw/modules/park/src/32b/park.c \
D:/Foc/my_motor/sw/drivers/drvic/pca9555.c \
D:/Foc/my_motor/sw/modules/pid/src/32b/pid.c \
D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c \
D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c \
D:/Foc/my_motor/sw/drivers/drvic/process_ctrl.c \
D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab10e.c \
D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c \
D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c \
D:/Foc/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c \
D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen.c \
D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen_current.c \
D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c \
D:/Foc/my_motor/sw/modules/traj/src/32b/traj.c \
D:/Foc/my_motor/sw/modules/user/src/32b/user.c \
D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c 

OBJS += \
./CodeStartBranch.obj \
./adc.obj \
./brake.obj \
./clarke.obj \
./clk.obj \
./cpu.obj \
./cpu_time.obj \
./ctrl.obj \
./decoder.obj \
./filter_fo.obj \
./flash.obj \
./flyingStart.obj \
./fw.obj \
./gpio.obj \
./hal.obj \
./i2c.obj \
./ipark.obj \
./ldc1612.obj \
./memCopy.obj \
./offset.obj \
./oled.obj \
./osc.obj \
./park.obj \
./pca9555.obj \
./pid.obj \
./pie.obj \
./pll.obj \
./process_ctrl.obj \
./proj_lab10e.obj \
./pwm.obj \
./pwr.obj \
./spi.obj \
./svgen.obj \
./svgen_current.obj \
./timer.obj \
./traj.obj \
./usDelay.obj \
./user.obj \
./wdog.obj 

ASM_DEPS += \
./CodeStartBranch.pp \
./usDelay.pp 

C_DEPS += \
./adc.pp \
./brake.pp \
./clarke.pp \
./clk.pp \
./cpu.pp \
./cpu_time.pp \
./ctrl.pp \
./decoder.pp \
./filter_fo.pp \
./flash.pp \
./flyingStart.pp \
./fw.pp \
./gpio.pp \
./hal.pp \
./i2c.pp \
./ipark.pp \
./ldc1612.pp \
./memCopy.pp \
./offset.pp \
./oled.pp \
./osc.pp \
./park.pp \
./pca9555.pp \
./pid.pp \
./pie.pp \
./pll.pp \
./process_ctrl.pp \
./proj_lab10e.pp \
./pwm.pp \
./pwr.pp \
./spi.pp \
./svgen.pp \
./svgen_current.pp \
./timer.pp \
./traj.pp \
./user.pp \
./wdog.pp 

C_DEPS__QUOTED += \
"adc.pp" \
"brake.pp" \
"clarke.pp" \
"clk.pp" \
"cpu.pp" \
"cpu_time.pp" \
"ctrl.pp" \
"decoder.pp" \
"filter_fo.pp" \
"flash.pp" \
"flyingStart.pp" \
"fw.pp" \
"gpio.pp" \
"hal.pp" \
"i2c.pp" \
"ipark.pp" \
"ldc1612.pp" \
"memCopy.pp" \
"offset.pp" \
"oled.pp" \
"osc.pp" \
"park.pp" \
"pca9555.pp" \
"pid.pp" \
"pie.pp" \
"pll.pp" \
"process_ctrl.pp" \
"proj_lab10e.pp" \
"pwm.pp" \
"pwr.pp" \
"spi.pp" \
"svgen.pp" \
"svgen_current.pp" \
"timer.pp" \
"traj.pp" \
"user.pp" \
"wdog.pp" 

OBJS__QUOTED += \
"CodeStartBranch.obj" \
"adc.obj" \
"brake.obj" \
"clarke.obj" \
"clk.obj" \
"cpu.obj" \
"cpu_time.obj" \
"ctrl.obj" \
"decoder.obj" \
"filter_fo.obj" \
"flash.obj" \
"flyingStart.obj" \
"fw.obj" \
"gpio.obj" \
"hal.obj" \
"i2c.obj" \
"ipark.obj" \
"ldc1612.obj" \
"memCopy.obj" \
"offset.obj" \
"oled.obj" \
"osc.obj" \
"park.obj" \
"pca9555.obj" \
"pid.obj" \
"pie.obj" \
"pll.obj" \
"process_ctrl.obj" \
"proj_lab10e.obj" \
"pwm.obj" \
"pwr.obj" \
"spi.obj" \
"svgen.obj" \
"svgen_current.obj" \
"timer.obj" \
"traj.obj" \
"usDelay.obj" \
"user.obj" \
"wdog.obj" 

ASM_DEPS__QUOTED += \
"CodeStartBranch.pp" \
"usDelay.pp" 

ASM_SRCS__QUOTED += \
"D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm" \
"D:/Foc/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm" 

C_SRCS__QUOTED += \
"D:/Foc/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c" \
"D:/Foc/my_motor/sw/modules/brake/src/brake.c" \
"D:/Foc/my_motor/sw/modules/clarke/src/32b/clarke.c" \
"D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c" \
"D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c" \
"D:/Foc/my_motor/sw/modules/cpu_time/src/32b/cpu_time.c" \
"D:/Foc/my_motor/sw/modules/ctrl/src/32b/ctrl.c" \
"D:/Foc/my_motor/sw/drivers/drvic/decoder.c" \
"D:/Foc/my_motor/sw/modules/filter/src/32b/filter_fo.c" \
"D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c" \
"D:/Foc/my_motor/sw/modules/flyingStart/src/32b/flyingStart.c" \
"D:/Foc/my_motor/sw/modules/fw/src/32b/fw.c" \
"D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c" \
"D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c" \
"D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c" \
"D:/Foc/my_motor/sw/modules/ipark/src/32b/ipark.c" \
"D:/Foc/my_motor/sw/drivers/drvic/ldc1612.c" \
"D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c" \
"D:/Foc/my_motor/sw/modules/offset/src/32b/offset.c" \
"D:/Foc/my_motor/sw/drivers/drvic/oled/oled.c" \
"D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c" \
"D:/Foc/my_motor/sw/modules/park/src/32b/park.c" \
"D:/Foc/my_motor/sw/drivers/drvic/pca9555.c" \
"D:/Foc/my_motor/sw/modules/pid/src/32b/pid.c" \
"D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c" \
"D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c" \
"D:/Foc/my_motor/sw/drivers/drvic/process_ctrl.c" \
"D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab10e.c" \
"D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c" \
"D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c" \
"D:/Foc/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c" \
"D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen.c" \
"D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen_current.c" \
"D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c" \
"D:/Foc/my_motor/sw/modules/traj/src/32b/traj.c" \
"D:/Foc/my_motor/sw/modules/user/src/32b/user.c" \
"D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c" 


