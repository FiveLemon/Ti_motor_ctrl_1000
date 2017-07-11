################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
/home/wmj/Documents/my_motor/sw/ide/ccs/cmd/f2802x/F28027F.cmd 

LIB_SRCS += \
/home/wmj/Documents/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_IQ_ROMSymbols.lib \
/home/wmj/Documents/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_ONLY_ROMSymbols.lib \
/home/wmj/Documents/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/2802xRevB_Fast_RTS_ROMSymbols.lib \
/home/wmj/Documents/my_motor/sw/modules/iqmath/lib/f28x/32b/IQmath.lib \
/home/wmj/Documents/my_motor/sw/modules/fast/lib/32b/f28x/f2802x/fast_public.lib 

ASM_SRCS += \
/home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm \
/home/wmj/Documents/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm 

C_SRCS += \
/home/wmj/Documents/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c \
/home/wmj/Documents/my_motor/sw/modules/angle_gen/src/32b/angle_gen.c \
/home/wmj/Documents/my_motor/sw/modules/clarke/src/32b/clarke.c \
/home/wmj/Documents/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c \
/home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c \
/home/wmj/Documents/my_motor/sw/modules/cpu_time/src/32b/cpu_time.c \
/home/wmj/Documents/my_motor/sw/modules/ctrl/src/32b/ctrl.c \
/home/wmj/Documents/my_motor/sw/modules/datalog/src/32b/datalog.c \
/home/wmj/Documents/my_motor/sw/modules/filter/src/32b/filter_fo.c \
/home/wmj/Documents/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c \
/home/wmj/Documents/my_motor/sw/modules/fw/src/32b/fw.c \
/home/wmj/Documents/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c \
/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c \
/home/wmj/Documents/my_motor/sw/modules/ipark/src/32b/ipark.c \
/home/wmj/Documents/my_motor/sw/modules/memCopy/src/memCopy.c \
/home/wmj/Documents/my_motor/sw/modules/offset/src/32b/offset.c \
/home/wmj/Documents/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c \
/home/wmj/Documents/my_motor/sw/modules/park/src/32b/park.c \
/home/wmj/Documents/my_motor/sw/modules/pid/src/32b/pid.c \
/home/wmj/Documents/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c \
/home/wmj/Documents/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c \
/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/src/proj_lab01b.c \
/home/wmj/Documents/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c \
/home/wmj/Documents/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c \
/home/wmj/Documents/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c \
/home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen.c \
/home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen_current.c \
/home/wmj/Documents/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c \
/home/wmj/Documents/my_motor/sw/modules/traj/src/32b/traj.c \
/home/wmj/Documents/my_motor/sw/modules/user/src/32b/user.c \
/home/wmj/Documents/my_motor/sw/modules/vs_freq/src/32b/vs_freq.c \
/home/wmj/Documents/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c 

OBJS += \
./CodeStartBranch.obj \
./adc.obj \
./angle_gen.obj \
./clarke.obj \
./clk.obj \
./cpu.obj \
./cpu_time.obj \
./ctrl.obj \
./datalog.obj \
./filter_fo.obj \
./flash.obj \
./fw.obj \
./gpio.obj \
./hal.obj \
./ipark.obj \
./memCopy.obj \
./offset.obj \
./osc.obj \
./park.obj \
./pid.obj \
./pie.obj \
./pll.obj \
./proj_lab01b.obj \
./pwm.obj \
./pwr.obj \
./spi.obj \
./svgen.obj \
./svgen_current.obj \
./timer.obj \
./traj.obj \
./usDelay.obj \
./user.obj \
./vs_freq.obj \
./wdog.obj 

ASM_DEPS += \
./CodeStartBranch.d \
./usDelay.d 

C_DEPS += \
./adc.d \
./angle_gen.d \
./clarke.d \
./clk.d \
./cpu.d \
./cpu_time.d \
./ctrl.d \
./datalog.d \
./filter_fo.d \
./flash.d \
./fw.d \
./gpio.d \
./hal.d \
./ipark.d \
./memCopy.d \
./offset.d \
./osc.d \
./park.d \
./pid.d \
./pie.d \
./pll.d \
./proj_lab01b.d \
./pwm.d \
./pwr.d \
./spi.d \
./svgen.d \
./svgen_current.d \
./timer.d \
./traj.d \
./user.d \
./vs_freq.d \
./wdog.d 

C_DEPS__QUOTED += \
"adc.d" \
"angle_gen.d" \
"clarke.d" \
"clk.d" \
"cpu.d" \
"cpu_time.d" \
"ctrl.d" \
"datalog.d" \
"filter_fo.d" \
"flash.d" \
"fw.d" \
"gpio.d" \
"hal.d" \
"ipark.d" \
"memCopy.d" \
"offset.d" \
"osc.d" \
"park.d" \
"pid.d" \
"pie.d" \
"pll.d" \
"proj_lab01b.d" \
"pwm.d" \
"pwr.d" \
"spi.d" \
"svgen.d" \
"svgen_current.d" \
"timer.d" \
"traj.d" \
"user.d" \
"vs_freq.d" \
"wdog.d" 

OBJS__QUOTED += \
"CodeStartBranch.obj" \
"adc.obj" \
"angle_gen.obj" \
"clarke.obj" \
"clk.obj" \
"cpu.obj" \
"cpu_time.obj" \
"ctrl.obj" \
"datalog.obj" \
"filter_fo.obj" \
"flash.obj" \
"fw.obj" \
"gpio.obj" \
"hal.obj" \
"ipark.obj" \
"memCopy.obj" \
"offset.obj" \
"osc.obj" \
"park.obj" \
"pid.obj" \
"pie.obj" \
"pll.obj" \
"proj_lab01b.obj" \
"pwm.obj" \
"pwr.obj" \
"spi.obj" \
"svgen.obj" \
"svgen_current.obj" \
"timer.obj" \
"traj.obj" \
"usDelay.obj" \
"user.obj" \
"vs_freq.obj" \
"wdog.obj" 

ASM_DEPS__QUOTED += \
"CodeStartBranch.d" \
"usDelay.d" 

ASM_SRCS__QUOTED += \
"/home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/CodeStartBranch.asm" \
"/home/wmj/Documents/my_motor/sw/modules/usDelay/src/32b/f28x/usDelay.asm" 

C_SRCS__QUOTED += \
"/home/wmj/Documents/my_motor/sw/drivers/adc/src/32b/f28x/f2802x/adc.c" \
"/home/wmj/Documents/my_motor/sw/modules/angle_gen/src/32b/angle_gen.c" \
"/home/wmj/Documents/my_motor/sw/modules/clarke/src/32b/clarke.c" \
"/home/wmj/Documents/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c" \
"/home/wmj/Documents/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c" \
"/home/wmj/Documents/my_motor/sw/modules/cpu_time/src/32b/cpu_time.c" \
"/home/wmj/Documents/my_motor/sw/modules/ctrl/src/32b/ctrl.c" \
"/home/wmj/Documents/my_motor/sw/modules/datalog/src/32b/datalog.c" \
"/home/wmj/Documents/my_motor/sw/modules/filter/src/32b/filter_fo.c" \
"/home/wmj/Documents/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c" \
"/home/wmj/Documents/my_motor/sw/modules/fw/src/32b/fw.c" \
"/home/wmj/Documents/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c" \
"/home/wmj/Documents/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c" \
"/home/wmj/Documents/my_motor/sw/modules/ipark/src/32b/ipark.c" \
"/home/wmj/Documents/my_motor/sw/modules/memCopy/src/memCopy.c" \
"/home/wmj/Documents/my_motor/sw/modules/offset/src/32b/offset.c" \
"/home/wmj/Documents/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c" \
"/home/wmj/Documents/my_motor/sw/modules/park/src/32b/park.c" \
"/home/wmj/Documents/my_motor/sw/modules/pid/src/32b/pid.c" \
"/home/wmj/Documents/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c" \
"/home/wmj/Documents/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c" \
"/home/wmj/Documents/my_motor/sw/solutions/instaspin_foc/src/proj_lab01b.c" \
"/home/wmj/Documents/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c" \
"/home/wmj/Documents/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c" \
"/home/wmj/Documents/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c" \
"/home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen.c" \
"/home/wmj/Documents/my_motor/sw/modules/svgen/src/32b/svgen_current.c" \
"/home/wmj/Documents/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c" \
"/home/wmj/Documents/my_motor/sw/modules/traj/src/32b/traj.c" \
"/home/wmj/Documents/my_motor/sw/modules/user/src/32b/user.c" \
"/home/wmj/Documents/my_motor/sw/modules/vs_freq/src/32b/vs_freq.c" \
"/home/wmj/Documents/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c" 


