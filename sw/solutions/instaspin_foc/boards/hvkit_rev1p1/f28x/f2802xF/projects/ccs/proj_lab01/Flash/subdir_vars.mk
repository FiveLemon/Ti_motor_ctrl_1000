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
D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c \
D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c \
D:/Foc/my_motor/sw/drivers/drvic/decoder.c \
D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c \
D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c \
D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c \
D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c \
D:/Foc/my_motor/sw/drivers/drvic/ldc1612.c \
D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c \
D:/Foc/my_motor/sw/drivers/drvic/oled/oled.c \
D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c \
D:/Foc/my_motor/sw/drivers/drvic/pca9555.c \
D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c \
D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c \
D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab01.c \
D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c \
D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c \
D:/Foc/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c \
D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c \
D:/Foc/my_motor/sw/modules/user/src/32b/user.c \
D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c 

OBJS += \
./CodeStartBranch.obj \
./adc.obj \
./clk.obj \
./cpu.obj \
./decoder.obj \
./flash.obj \
./gpio.obj \
./hal.obj \
./i2c.obj \
./ldc1612.obj \
./memCopy.obj \
./oled.obj \
./osc.obj \
./pca9555.obj \
./pie.obj \
./pll.obj \
./proj_lab01.obj \
./pwm.obj \
./pwr.obj \
./spi.obj \
./timer.obj \
./usDelay.obj \
./user.obj \
./wdog.obj 

ASM_DEPS += \
./CodeStartBranch.pp \
./usDelay.pp 

C_DEPS += \
./adc.pp \
./clk.pp \
./cpu.pp \
./decoder.pp \
./flash.pp \
./gpio.pp \
./hal.pp \
./i2c.pp \
./ldc1612.pp \
./memCopy.pp \
./oled.pp \
./osc.pp \
./pca9555.pp \
./pie.pp \
./pll.pp \
./proj_lab01.pp \
./pwm.pp \
./pwr.pp \
./spi.pp \
./timer.pp \
./user.pp \
./wdog.pp 

C_DEPS__QUOTED += \
"adc.pp" \
"clk.pp" \
"cpu.pp" \
"decoder.pp" \
"flash.pp" \
"gpio.pp" \
"hal.pp" \
"i2c.pp" \
"ldc1612.pp" \
"memCopy.pp" \
"oled.pp" \
"osc.pp" \
"pca9555.pp" \
"pie.pp" \
"pll.pp" \
"proj_lab01.pp" \
"pwm.pp" \
"pwr.pp" \
"spi.pp" \
"timer.pp" \
"user.pp" \
"wdog.pp" 

OBJS__QUOTED += \
"CodeStartBranch.obj" \
"adc.obj" \
"clk.obj" \
"cpu.obj" \
"decoder.obj" \
"flash.obj" \
"gpio.obj" \
"hal.obj" \
"i2c.obj" \
"ldc1612.obj" \
"memCopy.obj" \
"oled.obj" \
"osc.obj" \
"pca9555.obj" \
"pie.obj" \
"pll.obj" \
"proj_lab01.obj" \
"pwm.obj" \
"pwr.obj" \
"spi.obj" \
"timer.obj" \
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
"D:/Foc/my_motor/sw/drivers/clk/src/32b/f28x/f2802x/clk.c" \
"D:/Foc/my_motor/sw/drivers/cpu/src/32b/f28x/f2802x/cpu.c" \
"D:/Foc/my_motor/sw/drivers/drvic/decoder.c" \
"D:/Foc/my_motor/sw/drivers/flash/src/32b/f28x/f2802x/flash.c" \
"D:/Foc/my_motor/sw/drivers/gpio/src/32b/f28x/f2802x/gpio.c" \
"D:/Foc/my_motor/sw/modules/hal/boards/hvkit_rev1p1/f28x/f2802x/src/hal.c" \
"D:/Foc/my_motor/sw/drivers/i2c/src/32b/f28x/f2802x/i2c.c" \
"D:/Foc/my_motor/sw/drivers/drvic/ldc1612.c" \
"D:/Foc/my_motor/sw/modules/memCopy/src/memCopy.c" \
"D:/Foc/my_motor/sw/drivers/drvic/oled/oled.c" \
"D:/Foc/my_motor/sw/drivers/osc/src/32b/f28x/f2802x/osc.c" \
"D:/Foc/my_motor/sw/drivers/drvic/pca9555.c" \
"D:/Foc/my_motor/sw/drivers/pie/src/32b/f28x/f2802x/pie.c" \
"D:/Foc/my_motor/sw/drivers/pll/src/32b/f28x/f2802x/pll.c" \
"D:/Foc/my_motor/sw/solutions/instaspin_foc/src/proj_lab01.c" \
"D:/Foc/my_motor/sw/drivers/pwm/src/32b/f28x/f2802x/pwm.c" \
"D:/Foc/my_motor/sw/drivers/pwr/src/32b/f28x/f2802x/pwr.c" \
"D:/Foc/my_motor/sw/drivers/spi/src/32b/f28x/f2802x/spi.c" \
"D:/Foc/my_motor/sw/drivers/timer/src/32b/f28x/f2802x/timer.c" \
"D:/Foc/my_motor/sw/modules/user/src/32b/user.c" \
"D:/Foc/my_motor/sw/drivers/wdog/src/32b/f28x/f2802x/wdog.c" 


