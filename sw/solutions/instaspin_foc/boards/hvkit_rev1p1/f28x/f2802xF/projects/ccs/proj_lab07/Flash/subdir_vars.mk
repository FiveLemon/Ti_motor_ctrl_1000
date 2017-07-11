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
D:/Foc/my_motor/sw/modules/clarke/src/32b/clarke.c \
D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c \
D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c \
D:/Foc/my_motor/sw/modules/cpu_usage/src/32b/cpu_usage.c \
D:/Foc/my_motor/sw/modules/ctrl/src/32b/ctrl.c \
D:/Foc/my_motor/sw/modules/fem/src/32b/fem.c \
D:/Foc/my_motor/sw/modules/filter/src/32b/filter_fo.c \
D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c \
D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c \
D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c \
D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c \
D:/Foc/my_motor/sw/modules/ipark/src/32b/ipark.c \
D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c \
D:/Foc/my_motor/sw/modules/offset/src/32b/offset.c \
D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c \
D:/Foc/my_motor/sw/modules/park/src/32b/park.c \
D:/Foc/my_motor/sw/modules/pid/src/32b/pid.c \
D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c \
D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c \
D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab07.c \
D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c \
D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c \
D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen.c \
D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c \
D:/Foc/my_motor/sw/modules/traj/src/32b/traj.c \
D:/Foc/my_motor/sw/modules/user/src/32b/user.c \
D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c 

OBJS += \
./CodeStartBranch.obj \
./adc.obj \
./clarke.obj \
./clk.obj \
./cpu.obj \
./cpu_usage.obj \
./ctrl.obj \
./fem.obj \
./filter_fo.obj \
./flash.obj \
./gpio.obj \
./hal.obj \
./i2c.obj \
./ipark.obj \
./memCopy.obj \
./offset.obj \
./osc.obj \
./park.obj \
./pid.obj \
./pie.obj \
./pll.obj \
./proj_lab07.obj \
./pwm.obj \
./pwr.obj \
./svgen.obj \
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
./clarke.pp \
./clk.pp \
./cpu.pp \
./cpu_usage.pp \
./ctrl.pp \
./fem.pp \
./filter_fo.pp \
./flash.pp \
./gpio.pp \
./hal.pp \
./i2c.pp \
./ipark.pp \
./memCopy.pp \
./offset.pp \
./osc.pp \
./park.pp \
./pid.pp \
./pie.pp \
./pll.pp \
./proj_lab07.pp \
./pwm.pp \
./pwr.pp \
./svgen.pp \
./timer.pp \
./traj.pp \
./user.pp \
./wdog.pp 

C_DEPS__QUOTED += \
"adc.pp" \
"clarke.pp" \
"clk.pp" \
"cpu.pp" \
"cpu_usage.pp" \
"ctrl.pp" \
"fem.pp" \
"filter_fo.pp" \
"flash.pp" \
"gpio.pp" \
"hal.pp" \
"i2c.pp" \
"ipark.pp" \
"memCopy.pp" \
"offset.pp" \
"osc.pp" \
"park.pp" \
"pid.pp" \
"pie.pp" \
"pll.pp" \
"proj_lab07.pp" \
"pwm.pp" \
"pwr.pp" \
"svgen.pp" \
"timer.pp" \
"traj.pp" \
"user.pp" \
"wdog.pp" 

OBJS__QUOTED += \
"CodeStartBranch.obj" \
"adc.obj" \
"clarke.obj" \
"clk.obj" \
"cpu.obj" \
"cpu_usage.obj" \
"ctrl.obj" \
"fem.obj" \
"filter_fo.obj" \
"flash.obj" \
"gpio.obj" \
"hal.obj" \
"i2c.obj" \
"ipark.obj" \
"memCopy.obj" \
"offset.obj" \
"osc.obj" \
"park.obj" \
"pid.obj" \
"pie.obj" \
"pll.obj" \
"proj_lab07.obj" \
"pwm.obj" \
"pwr.obj" \
"svgen.obj" \
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
"D:/Foc/my_motor/sw/modules/clarke/src/32b/clarke.c" \
"D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c" \
"D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c" \
"D:/Foc/my_motor/sw/modules/cpu_usage/src/32b/cpu_usage.c" \
"D:/Foc/my_motor/sw/modules/ctrl/src/32b/ctrl.c" \
"D:/Foc/my_motor/sw/modules/fem/src/32b/fem.c" \
"D:/Foc/my_motor/sw/modules/filter/src/32b/filter_fo.c" \
"D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c" \
"D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c" \
"D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c" \
"D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c" \
"D:/Foc/my_motor/sw/modules/ipark/src/32b/ipark.c" \
"D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c" \
"D:/Foc/my_motor/sw/modules/offset/src/32b/offset.c" \
"D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c" \
"D:/Foc/my_motor/sw/modules/park/src/32b/park.c" \
"D:/Foc/my_motor/sw/modules/pid/src/32b/pid.c" \
"D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c" \
"D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c" \
"D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab07.c" \
"D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c" \
"D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c" \
"D:/Foc/my_motor/sw/modules/svgen/src/32b/svgen.c" \
"D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c" \
"D:/Foc/my_motor/sw/modules/traj/src/32b/traj.c" \
"D:/Foc/my_motor/sw/modules/user/src/32b/user.c" \
"D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c" 


