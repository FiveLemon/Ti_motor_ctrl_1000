/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//! \file   solutions/instaspin_foc/src/proj_lab01.c
//! \brief CPU and Inverter Set-up and introduction to interfacing to the ROM library
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

//! \defgroup PROJ_LAB01 PROJ_LAB01
//@{

//! \defgroup PROJ_LAB01_OVERVIEW Project Overview
//!
//! CPU and Inverter Set-up and introduction to interfacing to the ROM library
//!

//
// **************************************************************************
// the includes

// system includes
#include <math.h>


// modules
#include "sw/modules/math/src/32b/math.h"
#include "sw/modules/memCopy/src/memCopy.h"
#include "sw/drivers/drvic/ldc1612.h"
#include "sw/drivers/drvic/oled/oled.h"
#include "sw/drivers/drvic/decoder.h"
#include "sw/drivers/drvic/pca9555.h"
//#include "sw/drivers/drvic/oled/bmp.h"
// drivers


// platforms
#include "main.h"


// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   50

// **************************************************************************
// the globals

uint_least32_t gLEDcnt = 0;                   // Counter used to divide down the ISR rate for visually blinking an LED

#ifdef CSM_ENABLE
#pragma DATA_SECTION(halHandle,"rom_accessed_data");
#endif
HAL_Handle halHandle;                         // Handle to the Inverter hardware abstraction layer

PCA955x_Handle pca955xHandle;
PCA955x_Obj pca9555;

LDC161x_Handle ldc161xHandle;
LDC161x_Obj Ldc1612;

OLED_Handle oledHandle;
OLED_Obj OLED;

DECODER_Handle QPdecHandle;
DECODER_Obj QPdecoder;

unsigned char dataxx[7]= "AHH...";
uint32_t DispData;

uint16_t data;

#ifdef CSM_ENABLE
#pragma DATA_SECTION(gUserParams,"rom_accessed_data");
#endif
USER_Params gUserParams;                      // Contains the user.h settings

HAL_PwmData_t gPwmData = {0,0,0};             // Contains PWM duty cycles in global Q format

HAL_AdcData_t gAdcData = {0,0,0,0,0,0,0};     // Contains Current and Voltage ADC readings in global Q format

volatile MOTOR_Vars_t gMotorVars = MOTOR_Vars_INIT;

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;

#ifdef CSM_ENABLE
extern uint16_t *econst_start, *econst_end, *econst_ram_load;
extern uint16_t *switch_start, *switch_end, *switch_ram_load;
#endif
#endif


#ifdef DRV8301_SPI
// Watch window interface to the 8301 SPI
DRV_SPI_8301_Vars_t gDrvSpi8301Vars;
#endif

#ifdef DRV8305_SPI
// Watch window interface to the 8305 SPI
DRV_SPI_8305_Vars_t gDrvSpi8305Vars;
#endif

// **************************************************************************
// the functions

void main(void)
{
  // Only used if running from FLASH
  // Note that the variable FLASH is defined by the project
  #ifdef FLASH
  // Copy time critical code and Flash setup code to RAM
  // The RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
  // symbols are created by the linker. Refer to the linker files.
  memCopy((uint16_t *)&RamfuncsLoadStart,(uint16_t *)&RamfuncsLoadEnd,(uint16_t *)&RamfuncsRunStart);

  #ifdef CSM_ENABLE
    //copy .econst to unsecure RAM
    if(*econst_end - *econst_start)
      {
        memCopy((uint16_t *)&econst_start,(uint16_t *)&econst_end,(uint16_t *)&econst_ram_load);
      }

    //copy .switch ot unsecure RAM
    if(*switch_end - *switch_start)
      {
        memCopy((uint16_t *)&switch_start,(uint16_t *)&switch_end,(uint16_t *)&switch_ram_load);
      }
  #endif
  #endif

  // initialize the hardware abstraction layer
  halHandle = HAL_init(&hal,sizeof(hal));

  pca955xHandle = PCA955x_Init(&pca9555,sizeof(pca9555));
  PCA955x_setI2cHandle(pca955xHandle,halHandle->i2cHandle);

  ldc161xHandle = LDC1612_init(&Ldc1612, sizeof(Ldc1612));
  LDC161x_setI2cHandle(ldc161xHandle,halHandle->i2cHandle);
  LDC161x_setGpioHandle(ldc161xHandle,halHandle->gpioHandle);
  LDC161x_setSensorSerial(ldc161xHandle->ldcHandle,LDC161x_Slave_Addr0);

  oledHandle = OLED_Init(&OLED, sizeof(OLED));
  OLED_setI2cHandle(oledHandle,halHandle->i2cHandle);

  QPdecHandle = DECODER_Init(&QPdecoder,sizeof(QPdecoder));
  DECODER_setSpiHandle(QPdecHandle,halHandle->spiAHandle);

  // check for errors in user parameters
  USER_checkForErrors(&gUserParams);

  // store user parameter error in global variable
  gMotorVars.UserErrorCode = USER_getErrorCode(&gUserParams);

  // do not allow code execution if there is a user parameter error
  if(gMotorVars.UserErrorCode != USER_ErrorCode_NoError)
    {
      for(;;)
        {
          gMotorVars.Flag_enableSys = false;
        }
    }

  // initialize the user parameters
  USER_setParams(&gUserParams);

  // set the hardware abstraction layer parameters
  HAL_setParams(halHandle,&gUserParams);

#ifdef LAUNCHPAD
  // Setup GPIOs 0 and 1 as outputs for use in project lab1 only.
  // This is specific to the launchpad because its LEDs are also used by the PWM channels.
  HAL_setupLaunchPadGpio0and1(halHandle);
#endif





  //configure the Pac9555 for init
  //HAL_I2c_Pca9555_WrData(halHandle,0x06,0x00);
  PCA955x_Configure(pca955xHandle, PCA955x_PortNum_Port0, 0x00);

  //getData[1] = 0x0f | HAL_I2c_Pca9555_RdData(halHandle,0x01);
  //HAL_I2c_Pca9555_WrData(halHandle,0x02,0x50);
  PCA955x_WriteCommand(pca955xHandle, PCA955x_PortNum_Port0, 0x50);
  PCA955x_WriteCommand(pca955xHandle, PCA955x_PortNum_Port0, 0xac);
  //HAL_I2c_Pca9555_WrData(halHandle,0x02,0x5c);


  OLED_RegInit(oledHandle);
  OLED_Clear(oledHandle);

  LDC161x_ResetSensor(ldc161xHandle);
  LDC161x_setRcount(ldc161xHandle->ldcHandle, 0x0, 0xffff);
  LDC161x_writeRcount(ldc161xHandle,LDC161x_ChNum_CH0);
  LDC161x_setSettleCnt(ldc161xHandle->ldcHandle, 0x0, 0x000a);
  LDC161x_writeSettleCnt(ldc161xHandle,LDC161x_ChNum_CH0);
  LDC161x_setClkDivs(ldc161xHandle->ldcHandle,0x0, 0x1001);
  LDC161x_writeClkDivs(ldc161xHandle,LDC161x_ChNum_CH0);
  LDC161x_setConfig(ldc161xHandle->ldcHandle,0x1c01);
  LDC161x_writeConfig(ldc161xHandle);
  LDC161x_setMuxConfig(ldc161xHandle->ldcHandle,0x020c);
  LDC161x_writeMuxConfig(ldc161xHandle);

  // setup faults
  HAL_setupFaults(halHandle);


  // initialize the interrupt vector table
  HAL_initIntVectorTable(halHandle);


  // enable the ADC interrupts
  HAL_enableAdcInts(halHandle);


  // enable global interrupts
  HAL_enableGlobalInts(halHandle);


  // enable debug interrupts
  HAL_enableDebugInt(halHandle);

  // disable the PWM
  HAL_disablePwm(halHandle);


#ifdef DRV8301_SPI
  // turn on the DRV8301 if present
  HAL_enableDrv(halHandle);
  // initialize the DRV8301 interface
  HAL_setupDrvSpi(halHandle,&gDrvSpi8301Vars);
#endif

#ifdef DRV8305_SPI
  // turn on the DRV8305 if present
  HAL_enableDrv(halHandle);
  // initialize the DRV8305 interface
  HAL_setupDrvSpi(halHandle,&gDrvSpi8305Vars);
#endif



  // For ever loop
  while(true)
	  {
	  //data = LDC161x_readI2c(ldc161xHandle, LDC161x_RegName_DEVICE_ID);
	  //



	  };

} // end of main() function


interrupt void mainISR(void)
{

  // toggle status LED
  if(++gLEDcnt >= (uint_least32_t)(USER_ISR_FREQ_Hz / LED_BLINK_FREQ_Hz))
  {
    //HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
    gLEDcnt = 0;
//	data = LDC161x_readI2c(ldc161xHandle, LDC161x_RegName_MANUFACTURER_ID);
//    LDC161x_readRcount(ldc161xHandle,LDC161x_ChNum_CH0);
//    LDC161x_readConfig(ldc161xHandle);
//    LDC161x_readStatus(ldc161xHandle);
    LDC161x_readChData(ldc161xHandle,LDC161x_ChNum_CH0);
    LDC161x_KalmanFilter(ldc161xHandle,LDC161x_ChNum_CH0,&DispData);
    OLED_setPos(oledHandle,0,0);
    OLED_ShowNum(oledHandle, OLED_FontSize_16, DispData, 0x9);
    DECODER_readReg(QPdecHandle,&DispData);
    OLED_setPos(oledHandle,0,2);
    OLED_ShowNum(oledHandle, OLED_FontSize_16, DispData, 0x10);


  }


  // acknowledge the ADC interrupt
  HAL_acqAdcInt(halHandle,ADC_IntNumber_1);


  // convert the ADC data
  HAL_readAdcData(halHandle,&gAdcData);

  //HAL_I2c_Pca9555_WrData(halHandle,0x02,0x5c);
  // ADC processing and pwm result code goes here



  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function


//@} //defgroup
// end of file




