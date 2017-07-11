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
//! \file   solutions/instaspin_foc/src/proj_lab10e.c
//! \brief Flying start project
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

//! \defgroup PROJ_LAB10e PROJ_LAB10e
//@{

//! \defgroup PROJ_LAB10e_OVERVIEW Project Overview
//!
//! Flying Start (Rotor already moving)
//!
// **************************************************************************
// the includes

// system includes
#include <math.h>
#include "main.h"

#ifdef FLASH
#pragma CODE_SECTION(mainISR,"ramfuncs");
#endif

// Include header files used in the main function


// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   5
#define USER_BREAK_TIME     10
#define MOTO_UP_TIME        50 //1s
#define MOTO_DOWN_TIME      50

#define WAIT_ISR_CYCLE      1
#define WAIT_SECOND         5

#define POINT_B_VALUE 15000000
#define POINT_C_VALUE 15719000

#define HIGHSPEED_RUN  _IQ(1.645)
#define NEG_HIGHSPEED_RUN _IQ(-1.645)


#define BASESPEED_RUN  _IQ(0.5)
#define NEG_BASESPEED_RUN _IQ(-0.5)

#define SPEED_CONDITION1 _IQ(-0.48) //180rpm
#define SPEED_CONDITION2 _IQ(-0.52)
#define SPEED_CONDITION3 _IQ(0.52)

#define MAXACCEL  _IQ(80)
// min value 14837800 14925000
// max value 15380000 15820000

// **************************************************************************
// the globals

BRAKE_Obj   myBrake;
BRAKE_Handle Brakehandle;



uint_least16_t gCounter_updateGlobals = 0;

bool Flag_Latch_softwareUpdate = true;

CTRL_Handle ctrlHandle;

#ifdef CSM_ENABLE
#pragma DATA_SECTION(halHandle,"rom_accessed_data");
#endif
HAL_Handle halHandle;

PROCTRL_Obj MyProcessCtrl;
PROCTRL_Handle proctrlHandle;
volatile uint16_t  MotoRun_time = 0;
volatile uint16_t  ISR_CYSLE = 0;

PCA955x_Handle pca955xHandle;
PCA955x_Obj pca9555;

LDC161x_Handle ldc161xHandle_a;
LDC161x_Handle ldc161xHandle_b;

LDC161x_Obj Ldc1612_A;
LDC161x_Obj Ldc1612_B;

OLED_Handle oledHandle;
OLED_Obj OLED;

DECODER_Handle QPdecHandle;
DECODER_Obj QPdecoder;

 uint32_t DispData;
volatile bool pca955x_Int_Flag;

#ifdef CSM_ENABLE
#pragma DATA_SECTION(gUserParams,"rom_accessed_data");
#endif
USER_Params gUserParams;

HAL_PwmData_t gPwmData = {_IQ(0.0), _IQ(0.0), _IQ(0.0)};

HAL_AdcData_t gAdcData;

HAL_DacData_t gDacData;

_iq gMaxCurrentSlope = _IQ(0.0);

#ifdef FAST_ROM_V1p6
CTRL_Obj *controller_obj;
#else
#ifdef CSM_ENABLE
#pragma DATA_SECTION(ctrl,"rom_accessed_data");
#endif
CTRL_Obj ctrl;				//v1p7 format
#endif

uint16_t gLEDcnt = 0;
uint16_t BrakeCnt = 0;
bool brake_enable = false;


volatile MOTOR_Vars_t gMotorVars = MOTOR_Vars_INIT;


#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;

#ifdef CSM_ENABLE
extern uint16_t *econst_start, *econst_end, *econst_ram_load;
extern uint16_t *switch_start, *switch_end, *switch_ram_load;
#endif
#endif

SVGENCURRENT_Obj svgencurrent;
SVGENCURRENT_Handle svgencurrentHandle;
SVGENCURRENT_MeasureShunt_e measurableShuntThisCycle;

// define Flying Start (FS) variables
FS_Obj fs;
FS_Handle fsHandle;

// define CPU time
CPU_TIME_Obj     cpu_time;
CPU_TIME_Handle  cpu_timeHandle;


// set the offset, default value of 1 microsecond
int16_t gCmpOffset = (int16_t)(1.0 * USER_SYSTEM_FREQ_MHz);

MATH_vec3 gIavg = {_IQ(0.0), _IQ(0.0), _IQ(0.0)};
uint16_t gIavg_shift = 1;
MATH_vec3 gPwmData_prev = {_IQ(0.0), _IQ(0.0), _IQ(0.0)};

#ifdef DRV8301_SPI
// Watch window interface to the 8301 SPI
DRV_SPI_8301_Vars_t gDrvSpi8301Vars;
#endif

#ifdef DRV8305_SPI
// Watch window interface to the 8305 SPI
DRV_SPI_8305_Vars_t gDrvSpi8305Vars;
#endif

_iq gFlux_pu_to_Wb_sf;

_iq gFlux_pu_to_VpHz_sf;

_iq gTorque_Ls_Id_Iq_pu_to_Nm_sf;

_iq gTorque_Flux_Iq_pu_to_Nm_sf;

// **************************************************************************
// the functions
void PROCTRL_run(PROCTRL_Handle handle);

//
void main(void)
{
  uint_least8_t estNumber = 0;

#ifdef FAST_ROM_V1p6
  uint_least8_t ctrlNumber = 0;
#endif

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

  Brakehandle = Brake_init(&myBrake, sizeof(myBrake));

  proctrlHandle = PROCTRL_init(&MyProcessCtrl,sizeof(MyProcessCtrl));
  PROCTRL_setHalHandle(proctrlHandle, halHandle);

  proctrlHandle->moto_down_flag = false;
  proctrlHandle->moto_up_flag = false;
  proctrlHandle->EMG_STOP = false;
  proctrlHandle->SENSOR0_ON = false;
  proctrlHandle->SENSOR1_ON = false;
  proctrlHandle->ldc_high_recoded = false;
  proctrlHandle->ldc_low_recoded = false;
  proctrlHandle->ldc_touch_buttom = false;
  proctrlHandle->ldc_touch_top = false;
  proctrlHandle->edit_mode_flag = true;
  //PROCTRL_setParams(proctrlHandle);

  pca955xHandle = PCA955x_Init(&pca9555,sizeof(pca9555));
  PCA955x_setI2cHandle(pca955xHandle,halHandle->i2cHandle);

  // initialize the ldc sensor and oled displayer
  ldc161xHandle_a = LDC1612_init(&Ldc1612_A, sizeof(Ldc1612_A));

  LDC161x_setI2cHandle(ldc161xHandle_a,halHandle->i2cHandle);
  LDC161x_setGpioHandle(ldc161xHandle_a,halHandle->gpioHandle);
  LDC161x_setSensorSerial(ldc161xHandle_a->ldcHandle,LDC161x_Slave_Addr0);

  ldc161xHandle_b = LDC1612_init(&Ldc1612_B, sizeof(Ldc1612_B));
  LDC161x_setI2cHandle(ldc161xHandle_b,halHandle->i2cHandle);
  LDC161x_setGpioHandle(ldc161xHandle_b,halHandle->gpioHandle);
  LDC161x_setSensorSerial(ldc161xHandle_b->ldcHandle,LDC161x_Slave_Addr1);

  oledHandle = OLED_Init(&OLED, sizeof(OLED));
  OLED_setI2cHandle(oledHandle,halHandle->i2cHandle);

  QPdecHandle = DECODER_Init(&QPdecoder,sizeof(QPdecoder));
  DECODER_setSpiHandle(QPdecHandle,halHandle->spiAHandle);


  // check for errors in user parameters
  USER_checkForErrors(&gUserParams);

//  gMotorVars.Flag_enableUserParams = false;

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


  PCA955x_Configure(pca955xHandle, PCA955x_PortNum_Port0, 0x00);
  PCA955x_Configure(pca955xHandle, PCA955x_PortNum_Port1, 0xff);
  PCA955x_WriteCommand(pca955xHandle, PCA955x_PortNum_Port0, 0x50);
  PCA955x_WriteCommand(pca955xHandle, PCA955x_PortNum_Port0, 0xac);

 // OLED_RegInit(oledHandle);
 // OLED_Clear(oledHandle);


  LDC161x_ResetSensor(ldc161xHandle_a);
  LDC161x_setRcount(ldc161xHandle_a->ldcHandle, 0x0, 0xffff);
  LDC161x_writeRcount(ldc161xHandle_a,LDC161x_ChNum_CH0);
  LDC161x_setSettleCnt(ldc161xHandle_a->ldcHandle, 0x0, 0x000a);
  LDC161x_writeSettleCnt(ldc161xHandle_a,LDC161x_ChNum_CH0);
  LDC161x_setClkDivs(ldc161xHandle_a->ldcHandle,0x0, 0x1001);
  LDC161x_writeClkDivs(ldc161xHandle_a,LDC161x_ChNum_CH0);
  LDC161x_setConfig(ldc161xHandle_a->ldcHandle,0x1c01);
  LDC161x_writeConfig(ldc161xHandle_a);
  LDC161x_setMuxConfig(ldc161xHandle_a->ldcHandle,0x020c);
  LDC161x_writeMuxConfig(ldc161xHandle_a);

  
  Brake_Setup(Brakehandle);

  // initialize the controller
#ifdef FAST_ROM_V1p6
  ctrlHandle = CTRL_initCtrl(ctrlNumber, estNumber);  		//v1p6 format (06xF and 06xM devices)
#else
  ctrlHandle = CTRL_initCtrl(estNumber,&ctrl,sizeof(ctrl));	//v1p7 format default
#endif

  {
    CTRL_Version version;

    // get the version number
    CTRL_getVersion(ctrlHandle,&version);

    gMotorVars.CtrlVersion = version;
  }

  // set the default controller parameters
  CTRL_setParams(ctrlHandle,&gUserParams);

  // Initialize and setup the 100% SVM generator
  svgencurrentHandle = SVGENCURRENT_init(&svgencurrent,sizeof(svgencurrent));

  // setup svgen current
  {
    float_t minWidth_microseconds = 2.0;
    uint16_t minWidth_counts = (uint16_t)(minWidth_microseconds * USER_SYSTEM_FREQ_MHz);
    float_t fdutyLimit = 0.5-(2.0*minWidth_microseconds*USER_PWM_FREQ_kHz*0.001);
    _iq dutyLimit = _IQ(fdutyLimit);

    SVGENCURRENT_setMinWidth(svgencurrentHandle, minWidth_counts);
    SVGENCURRENT_setIgnoreShunt(svgencurrentHandle, use_all);
    SVGENCURRENT_setMode(svgencurrentHandle,all_phase_measurable);
    SVGENCURRENT_setVlimit(svgencurrentHandle,dutyLimit);
  }


  // Initialize Flying Start (FS)
  fsHandle = FS_init(&fs,sizeof(fs));

  // Disable Flying Start (FS)
  FS_setFlag_enableFs(fsHandle, false);

  // Clear Flying Start(FS) check time count
  FS_clearCntCheckTime(fsHandle);

  // Set Flying Start(FS) minimum transition speed
  FS_setSpeedFsMin_krpm(fsHandle, ctrlHandle, FS_SPEED_MIN);

  // set Flying Start(FS) maximum check time
  FS_setMaxCheckTime(fsHandle, FS_MAX_CHECK_TIME);

  gMotorVars.Flag_enableSpeedCtrl = true;		// enable speed close loop control
  gMotorVars.Flag_enableFlyingStart = true;		// enable Flying Start

  // initialize the CPU usage module
  cpu_timeHandle = CPU_TIME_init(&cpu_time,sizeof(cpu_time));
  CPU_TIME_setParams(cpu_timeHandle, PWM_getPeriod(halHandle->pwmHandle[0]));

  // set overmodulation to maximum value
  gMotorVars.OverModulation = _IQ(MATH_TWO_OVER_THREE);

  #ifndef F2802xF
  // set DAC parameters
  HAL_setDacParameters(halHandle, &gDacData);
  #endif

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


  // enable DC bus compensation
  CTRL_setFlag_enableDcBusComp(ctrlHandle, true);


  // compute scaling factors for flux and torque calculations
  gFlux_pu_to_Wb_sf = USER_computeFlux_pu_to_Wb_sf();
  gFlux_pu_to_VpHz_sf = USER_computeFlux_pu_to_VpHz_sf();
  gTorque_Ls_Id_Iq_pu_to_Nm_sf = USER_computeTorque_Ls_Id_Iq_pu_to_Nm_sf();
  gTorque_Flux_Iq_pu_to_Nm_sf = USER_computeTorque_Flux_Iq_pu_to_Nm_sf();

  // Below two lines code for Flash Testing, need to be commented
  gMotorVars.Flag_enableSys = true;
  gMotorVars.Flag_enablePowerWarp = true;
//  gMotorVars.Flag_enableRun = true;

  for(;;)
  {
    // Waiting for enable system flag to be set
    while(!(gMotorVars.Flag_enableSys));

    // Enable the Library internal PI.  Iq is referenced by the speed PI now
    CTRL_setFlag_enableSpeedCtrl(ctrlHandle, true);

    // loop while the enable system flag is true
    while(gMotorVars.Flag_enableSys)
      {
        CTRL_Obj *obj = (CTRL_Obj *)ctrlHandle;

        // increment counters
        gCounter_updateGlobals++;

        // enable/disable the use of motor parameters being loaded from user.h
        CTRL_setFlag_enableUserMotorParams(ctrlHandle,gMotorVars.Flag_enableUserParams);

        // enable/disable Rs recalibration during motor startup
        EST_setFlag_enableRsRecalc(obj->estHandle,gMotorVars.Flag_enableRsRecalc);

        // enable/disable automatic calculation of bias values
        CTRL_setFlag_enableOffset(ctrlHandle,gMotorVars.Flag_enableOffsetcalc);


        // HAL_setGpioHigh(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
         LDC161x_readChData(ldc161xHandle_a,LDC161x_ChNum_CH0);
         LDC161x_KalmanFilter(ldc161xHandle_a,LDC161x_ChNum_CH0,&DispData);

        // OLED_setPos(oledHandle,0,0);
         //OLED_ShowNum(oledHandle, OLED_FontSize_16, DispData, 0x9);

         if(pca955x_Int_Flag)
         {

         if((PCA955x_ReadStatus(pca955xHandle,PCA955x_PortNum_Port1) & PCA955x_StatusFlag_SENSOR0) == PCA955x_StatusFlag_SENSOR0)
         {
         	proctrlHandle->SENSOR0_ON = false;
         }
         else
         {

         	proctrlHandle->SENSOR0_ON = true;
         }
         if((PCA955x_ReadStatus(pca955xHandle,PCA955x_PortNum_Port1) & PCA955x_StatusFlag_SENSOR1) == PCA955x_StatusFlag_SENSOR1)
         {
            proctrlHandle->SENSOR1_ON = false;
         }
         else
            proctrlHandle->SENSOR1_ON = true;
         if((PCA955x_ReadStatus(pca955xHandle,PCA955x_PortNum_Port1) & PCA955x_StatusFlag_EMERG_STP) == PCA955x_StatusFlag_EMERG_STP)
         {
         	//OLED_setPos(oledHandle,0,4);
         	//OLED_ShowNum(oledHandle, OLED_FontSize_16, 0x1, 0x1);
         	proctrlHandle->EMG_STOP = true;
         }
         else
         {
         	//OLED_setPos(oledHandle,0,4);
         	//OLED_ShowNum(oledHandle, OLED_FontSize_16, 0x0, 1);
         	proctrlHandle->EMG_STOP = false;
         }

         }


     //    if(DispData <= 14829000)
      //   {
     //    	MyProcessCtrl.ldc_touch_buttom = true;
      //   }
    //     if(DispData >= 15729000)
    //     {
    //     	MyProcessCtrl.ldc_touch_top = true;
    //     }



        // Control motor Start or Stop with Flying Start
        motor_RunCtrl(ctrlHandle);
        PROCTRL_run(proctrlHandle);

        if(CTRL_isError(ctrlHandle))
          {
            // set the enable controller flag to false
            CTRL_setFlag_enableCtrl(ctrlHandle,false);

            // set the enable system flag to false
            gMotorVars.Flag_enableSys = false;

            // disable the PWM
            HAL_disablePwm(halHandle);
          }
        else
          {
            // update the controller state
            bool flag_ctrlStateChanged = CTRL_updateState(ctrlHandle);

            // enable or disable the control
            CTRL_setFlag_enableCtrl(ctrlHandle, gMotorVars.Flag_Run_Identify);

            if(flag_ctrlStateChanged)
              {
                CTRL_State_e ctrlState = CTRL_getState(ctrlHandle);

                if(ctrlState == CTRL_State_OffLine)
                  {
                    // enable the PWM
                    HAL_enablePwm(halHandle);
                  }
                else if(ctrlState == CTRL_State_OnLine)
                  {
                    if(gMotorVars.Flag_enableOffsetcalc == true)
                    {
                      // update the ADC bias values
                      HAL_updateAdcBias(halHandle);
                    }
                    else
                    {
                      // set the current bias
                      HAL_setBias(halHandle,HAL_SensorType_Current,0,_IQ(I_A_offset));
                      HAL_setBias(halHandle,HAL_SensorType_Current,1,_IQ(I_B_offset));
                      HAL_setBias(halHandle,HAL_SensorType_Current,2,_IQ(I_C_offset));

                      // set the voltage bias
                      HAL_setBias(halHandle,HAL_SensorType_Voltage,0,_IQ(V_A_offset));
                      HAL_setBias(halHandle,HAL_SensorType_Voltage,1,_IQ(V_B_offset));
                      HAL_setBias(halHandle,HAL_SensorType_Voltage,2,_IQ(V_C_offset));
                    }

                    // Return the bias value for currents
                    gMotorVars.I_bias.value[0] = HAL_getBias(halHandle,HAL_SensorType_Current,0);
                    gMotorVars.I_bias.value[1] = HAL_getBias(halHandle,HAL_SensorType_Current,1);
                    gMotorVars.I_bias.value[2] = HAL_getBias(halHandle,HAL_SensorType_Current,2);

                    // Return the bias value for voltages
                    gMotorVars.V_bias.value[0] = HAL_getBias(halHandle,HAL_SensorType_Voltage,0);
                    gMotorVars.V_bias.value[1] = HAL_getBias(halHandle,HAL_SensorType_Voltage,1);
                    gMotorVars.V_bias.value[2] = HAL_getBias(halHandle,HAL_SensorType_Voltage,2);

//                    // enable the PWM
//                    HAL_enablePwm(halHandle);
                  }
                else if(ctrlState == CTRL_State_Idle)
                  {
                    // disable the PWM
                    HAL_disablePwm(halHandle);
                    gMotorVars.Flag_Run_Identify = false;
                  }

                if((CTRL_getFlag_enableUserMotorParams(ctrlHandle) == true) &&
                  (ctrlState > CTRL_State_Idle) &&
                  (gMotorVars.CtrlVersion.minor == 6))
                  {
                    // call this function to fix 1p6
                    USER_softwareUpdate1p6(ctrlHandle);
                  }
              }
          }


        if(EST_isMotorIdentified(obj->estHandle))
          {
            _iq Id_squared_pu = _IQmpy(CTRL_getId_ref_pu(ctrlHandle),CTRL_getId_ref_pu(ctrlHandle));


            //Set the maximum current controller output for the Iq and Id current controllers to enable
            //over-modulation.
            //An input into the SVM above 1/SQRT(3) = 0.5774 is in the over-modulation region.  An input of 0.5774 is where
            //the crest of the sinewave touches the 100% duty cycle.  At an input of 2/3, the SVM generator
            //produces a trapezoidal waveform touching every corner of the hexagon
            CTRL_setMaxVsMag_pu(ctrlHandle,gMotorVars.OverModulation);

            // set the current ramp
            EST_setMaxCurrentSlope_pu(obj->estHandle,gMaxCurrentSlope);
            gMotorVars.Flag_MotorIdentified = true;

            // set the speed reference
            CTRL_setSpd_ref_krpm(ctrlHandle,gMotorVars.SpeedRef_krpm);

            // set the speed acceleration
            CTRL_setMaxAccel_pu(ctrlHandle,_IQmpy(MAX_ACCEL_KRPMPS_SF,gMotorVars.MaxAccel_krpmps));

            // set the Id reference
            CTRL_setId_ref_pu(ctrlHandle, _IQmpy(gMotorVars.IdRef_A, _IQ(1.0/USER_IQ_FULL_SCALE_CURRENT_A)));

            if(Flag_Latch_softwareUpdate)
            {
              Flag_Latch_softwareUpdate = false;

              USER_calcPIgains(ctrlHandle);

              // initialize the watch window kp and ki current values with pre-calculated values
              gMotorVars.Kp_Idq = CTRL_getKp(ctrlHandle,CTRL_Type_PID_Id);
              gMotorVars.Ki_Idq = CTRL_getKi(ctrlHandle,CTRL_Type_PID_Id);
            }

          }
        else
          {
            Flag_Latch_softwareUpdate = true;

            // initialize the watch window kp and ki values with pre-calculated values
            gMotorVars.Kp_spd = CTRL_getKp(ctrlHandle,CTRL_Type_PID_spd);
            gMotorVars.Ki_spd = CTRL_getKi(ctrlHandle,CTRL_Type_PID_spd);


            // the estimator sets the maximum current slope during identification
            gMaxCurrentSlope = EST_getMaxCurrentSlope_pu(obj->estHandle);
          }


        // when appropriate, update the global variables
        if(gCounter_updateGlobals >= NUM_MAIN_TICKS_FOR_GLOBAL_VARIABLE_UPDATE)
          {
            // reset the counter
            gCounter_updateGlobals = 0;

            updateGlobalVariables_motor(ctrlHandle);
          }


        // update Kp and Ki gains
        updateKpKiGains(ctrlHandle);

        // enable/disable the forced angle
        EST_setFlag_enableForceAngle(obj->estHandle,gMotorVars.Flag_enableForceAngle);

        // enable or disable power warp
        CTRL_setFlag_enablePowerWarp(ctrlHandle,gMotorVars.Flag_enablePowerWarp);

#ifdef DRV8301_SPI
        HAL_writeDrvData(halHandle,&gDrvSpi8301Vars);

        HAL_readDrvData(halHandle,&gDrvSpi8301Vars);
#endif
#ifdef DRV8305_SPI
        HAL_writeDrvData(halHandle,&gDrvSpi8305Vars);

        HAL_readDrvData(halHandle,&gDrvSpi8305Vars);
#endif
      } // end of while(gFlag_enableSys) loop


    // disable the PWM
    HAL_disablePwm(halHandle);

    // set the default controller parameters (Reset the control to re-identify the motor)
    CTRL_setParams(ctrlHandle,&gUserParams);
    gMotorVars.Flag_Run_Identify = false;

  } // end of for(;;) loop

} // end of main() function

// mainISR
interrupt void mainISR(void)
{
  // read the timer 1 value and update the CPU usage module
  uint32_t timer1Cnt = HAL_readTimerCnt(halHandle,2);
  CPU_TIME_updateCnts(cpu_timeHandle,timer1Cnt);

//  SVGENCURRENT_MeasureShunt_e measurableShuntThisCycle = SVGENCURRENT_getMode(svgencurrentHandle);
  measurableShuntThisCycle = SVGENCURRENT_getMode(svgencurrentHandle);

  // toggle status LED
  if(++gLEDcnt >= (uint_least32_t)(USER_ISR_FREQ_Hz / LED_BLINK_FREQ_Hz))
  {

    //HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
    gLEDcnt = 0;
	if(brake_enable)
	{
      BrakeCnt++;
	}
    if(BrakeCnt>= (USER_BREAK_TIME))
	{
      brake_enable = false;
	  BrakeCnt = 0; 
	}
    MotoRun_time++;


  }

  // acknowledge the ADC interrupt
  HAL_acqAdcInt(halHandle,ADC_IntNumber_1);

  // convert the ADC data
  HAL_readAdcData(halHandle,&gAdcData);

  // run the current reconstruction algorithm
  SVGENCURRENT_RunRegenCurrent(svgencurrentHandle, (MATH_vec3 *)(gAdcData.I.value));

  gIavg.value[0] += (gAdcData.I.value[0] - gIavg.value[0])>>gIavg_shift;
  gIavg.value[1] += (gAdcData.I.value[1] - gIavg.value[1])>>gIavg_shift;
  gIavg.value[2] += (gAdcData.I.value[2] - gIavg.value[2])>>gIavg_shift;

  if(measurableShuntThisCycle > two_phase_measurable)
  {
	  gAdcData.I.value[0] = gIavg.value[0];
	  gAdcData.I.value[1] = gIavg.value[1];
	  gAdcData.I.value[2] = gIavg.value[2];
  }

  // run the flying start
  FS_run(ctrlHandle, fsHandle);

  // run the controller
  CTRL_run(ctrlHandle,halHandle,&gAdcData,&gPwmData);

  // run the PWM compensation and current ignore algorithm
  SVGENCURRENT_compPwmData(svgencurrentHandle,&(gPwmData.Tabc),&gPwmData_prev);


  if(gMotorVars.Flag_RunState == false)
  {
	if(brake_enable)
    {
	 // gPwmData.Tabc.value[0] = _IQ(0.15);
	 // gPwmData.Tabc.value[1] = _IQ(0.0);
	 // gPwmData.Tabc.value[2] = _IQ(-0.15);
      Brake_run(Brakehandle,halHandle,&gAdcData,&gPwmData);
    }
	else
	{
	  gPwmData.Tabc.value[0] = _IQ(0.0);
	  gPwmData.Tabc.value[1] = _IQ(0.0);
	  gPwmData.Tabc.value[2] = _IQ(0.0);
	// disable the PWM
	  HAL_disablePwm(halHandle);

	}
  }

  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);

  {
    SVGENCURRENT_IgnoreShunt_e ignoreShuntNextCycle = SVGENCURRENT_getIgnoreShunt(svgencurrentHandle);
    SVGENCURRENT_VmidShunt_e midVolShunt = SVGENCURRENT_getVmid(svgencurrentHandle);

    // Set trigger point in the middle of the low side pulse
    HAL_setTrigger(halHandle,ignoreShuntNextCycle,midVolShunt);
  }

  // setup the controller
  CTRL_setup(ctrlHandle);

  // get the estimator angle and frequency values
  gMotorVars.angle_est_pu = EST_getAngle_pu(ctrlHandle->estHandle);
  gMotorVars.speed_est_pu = EST_getFm_pu(ctrlHandle->estHandle);

  _iq Iq_pu = CTRL_getIq_in_pu(ctrlHandle);

  #ifndef F2802xF
  // connect inputs of the PWMDAC module.
  gDacData.value[0] = gAdcData.I.value[0];
  gDacData.value[1] = Iq_pu;
  gDacData.value[2] = gMotorVars.speed_est_pu;
  gDacData.value[3] = gMotorVars.angle_est_pu;

  HAL_writeDacData(halHandle,&gDacData);
  #endif

  // read the timer 1 value and update the CPU usage module
  timer1Cnt = HAL_readTimerCnt(halHandle,2);
  CPU_TIME_run(cpu_timeHandle,timer1Cnt);

  ISR_CYSLE++;

  //check the PCA9555 INT
  if(GPIO_read(halHandle->gpioHandle,(GPIO_Number_7)))
  {
	 pca955x_Int_Flag = false;
  }
  else
  {
	  pca955x_Int_Flag = true;
  }


  return;
} // end of mainISR() function


void updateGlobalVariables_motor(CTRL_Handle handle)
{
  CTRL_Obj *obj = (CTRL_Obj *)handle;

  // get the speed estimate
  gMotorVars.Speed_krpm = EST_getSpeed_krpm(obj->estHandle);

  // get the real time speed reference coming out of the speed trajectory generator
  gMotorVars.SpeedTraj_krpm = _IQmpy(CTRL_getSpd_int_ref_pu(handle),EST_get_pu_to_krpm_sf(obj->estHandle));

  // get the torque estimate
  gMotorVars.Torque_Nm = USER_computeTorque_Nm(handle, gTorque_Flux_Iq_pu_to_Nm_sf, gTorque_Ls_Id_Iq_pu_to_Nm_sf);

  // get the magnetizing current
  gMotorVars.MagnCurr_A = EST_getIdRated(obj->estHandle);

  // get the rotor resistance
  gMotorVars.Rr_Ohm = EST_getRr_Ohm(obj->estHandle);

  // get the stator resistance
  gMotorVars.Rs_Ohm = EST_getRs_Ohm(obj->estHandle);

  // get the stator inductance in the direct coordinate direction
  gMotorVars.Lsd_H = EST_getLs_d_H(obj->estHandle);

  // get the stator inductance in the quadrature coordinate direction
  gMotorVars.Lsq_H = EST_getLs_q_H(obj->estHandle);

  // get the flux in V/Hz in floating point
  gMotorVars.Flux_VpHz = EST_getFlux_VpHz(obj->estHandle);

  // get the flux in Wb in fixed point
  gMotorVars.Flux_Wb = USER_computeFlux(handle, gFlux_pu_to_Wb_sf);

  // get the controller state
  gMotorVars.CtrlState = CTRL_getState(handle);

  // get the estimator state
  gMotorVars.EstState = EST_getState(obj->estHandle);

  // read Vd and Vq vectors per units
  gMotorVars.Vd = CTRL_getVd_out_pu(ctrlHandle);
  gMotorVars.Vq = CTRL_getVq_out_pu(ctrlHandle);

  // calculate vector Vs in per units
  gMotorVars.Vs = _IQsqrt(_IQmpy(gMotorVars.Vd, gMotorVars.Vd) + _IQmpy(gMotorVars.Vq, gMotorVars.Vq));

  // read Id and Iq vectors in amps
  gMotorVars.Id_A = _IQmpy(CTRL_getId_in_pu(ctrlHandle), _IQ(USER_IQ_FULL_SCALE_CURRENT_A));
  gMotorVars.Iq_A = _IQmpy(CTRL_getIq_in_pu(ctrlHandle), _IQ(USER_IQ_FULL_SCALE_CURRENT_A));

  // calculate vector Is in amps
  gMotorVars.Is_A = _IQsqrt(_IQmpy(gMotorVars.Id_A, gMotorVars.Id_A) + _IQmpy(gMotorVars.Iq_A, gMotorVars.Iq_A));

  // Get the DC buss voltage
  gMotorVars.VdcBus_kV = _IQmpy(gAdcData.dcBus,_IQ(USER_IQ_FULL_SCALE_VOLTAGE_V/1000.0));

  return;
} // end of updateGlobalVariables_motor() function


void updateKpKiGains(CTRL_Handle handle)
{
  if((gMotorVars.CtrlState == CTRL_State_OnLine) && (gMotorVars.Flag_MotorIdentified == true) && (Flag_Latch_softwareUpdate == false))
    {
      // set the kp and ki speed values from the watch window
      CTRL_setKp(handle,CTRL_Type_PID_spd,gMotorVars.Kp_spd);
      CTRL_setKi(handle,CTRL_Type_PID_spd,gMotorVars.Ki_spd);

      // set the kp and ki current values for Id and Iq from the watch window
      CTRL_setKp(handle,CTRL_Type_PID_Id,gMotorVars.Kp_Idq);
      CTRL_setKi(handle,CTRL_Type_PID_Id,gMotorVars.Ki_Idq);
      CTRL_setKp(handle,CTRL_Type_PID_Iq,gMotorVars.Kp_Idq);
      CTRL_setKi(handle,CTRL_Type_PID_Iq,gMotorVars.Ki_Idq);
	}

  return;
} // end of updateKpKiGains() function

// Control motor running
void motor_RunCtrl(CTRL_Handle handle)
{
  CTRL_Obj *obj = (CTRL_Obj *)handle;
  bool flag_enableSpeedCtrl;

  gMotorVars.Flag_Run_Identify = true;

  if(gMotorVars.Flag_enableRun)		// Stop to Start
  {
	 gMotorVars.SpeedRef_krpm = gMotorVars.SpeedSet_krpm;

		if(gMotorVars.Flag_RunState == false)
		{
			FS_setFlag_enableFs(fsHandle, gMotorVars.Flag_enableFlyingStart);

			FS_reset(fsHandle);

			gMotorVars.Flag_RunState = true;

			PID_setUi(obj->pidHandle_spd, _IQ(0.0));
			PID_setUi(obj->pidHandle_Id, _IQ(0.0));
			PID_setUi(obj->pidHandle_Iq, _IQ(0.0));

			CTRL_setId_ref_pu(handle, _IQ(0.0));
			CTRL_setIq_ref_pu(handle, _IQ(0.0));
			CTRL_setSpd_out_pu(handle, _IQ(0.0));

			CTRL_setFlag_enableCurrentCtrl(handle,true);

			gPwmData.Tabc.value[0] = _IQ(0.0);
			gPwmData.Tabc.value[1] = _IQ(0.0);
			gPwmData.Tabc.value[2] = _IQ(0.0);

			// write the PWM compare values
			HAL_writePwmData(halHandle,&gPwmData);

			// enable the PWM
			HAL_enablePwm(halHandle);
		}

		flag_enableSpeedCtrl = (gMotorVars.Flag_enableSpeedCtrl) & (FS_getFlag_SpeedCtrl(fsHandle));
   }
   else
	{
	   if(gMotorVars.Flag_RunState == true)  // Run to Stop
      {
       	FS_setFlag_enableFs(fsHandle, false);

       	gMotorVars.Flag_RunState = false;
       	gMotorVars.SpeedRef_krpm = _IQ(0.0);

		brake_enable = true;
       	// disable the PWM
		
       	//HAL_disablePwm(halHandle);

       	flag_enableSpeedCtrl = false;

       	PID_setUi(obj->pidHandle_spd, _IQ(0.0));
       	PID_setUi(obj->pidHandle_Id, _IQ(0.0));
       	PID_setUi(obj->pidHandle_Iq, _IQ(0.0));

       	gPwmData.Tabc.value[0] = _IQ(0.0);
       	gPwmData.Tabc.value[1] = _IQ(0.0);
       	gPwmData.Tabc.value[2] = _IQ(0.0);

       	CTRL_setId_ref_pu(handle, _IQ(0.0));
       	CTRL_setIq_ref_pu(handle, _IQ(0.0));


       	CTRL_setFlag_enableCurrentCtrl(handle,false);
      }

  }
  // enable/disable the Library internal PI.  Iq is referenced by the speed PI now
  CTRL_setFlag_enableSpeedCtrl(handle,flag_enableSpeedCtrl);
}


inline PROCTRL_State_e PROCTRL_getCurState(PROCTRL_Handle handle)
{
   PROCTRL_Obj *Obj = (PROCTRL_Obj *)handle;
   PROCTRL_State_e CurrentState;

   CurrentState = Obj-> Cur_State;

   return (CurrentState);

}

inline PROCTRL_setNxtState(PROCTRL_Handle handle, PROCTRL_State_e Nxt_State)
{
   PROCTRL_Obj *Obj = (PROCTRL_Obj *)handle;

   Obj-> Cur_State = Nxt_State;

   return;
}


void PROCTRL_run(PROCTRL_Handle handle)
{
  PROCTRL_Obj *obj = (PROCTRL_Obj *)handle;
  PROCTRL_State_e Ctrl_State;

  Ctrl_State = PROCTRL_getCurState(handle);

  switch(Ctrl_State)
  {

      case PROCTRL_State_IDLE:
               if(gMotorVars.Flag_RunState == true)
               {
            	 gMotorVars.SpeedSet_krpm = NEG_BASESPEED_RUN;
            	 gMotorVars.MaxAccel_krpmps = MAXACCEL;
 	        	 obj->LDC_HighPointData = DispData;
             	 //obj->ldc_high_recoded = true;
            	 MotoRun_time = 0;
            	 //reset all flag
            	 obj->moto_up_flag = false;
            	 obj->moto_down_flag = false;
            	 obj->set_high_speed = false;
            	 obj->set_high_accel = false;
            	 obj->arrive_point_B = false;
            	 obj->wait_time = false;
            	 obj->wait_second = false;
            	 obj->arrive_point_C = false;
            	 obj->set_stop_flag = false;

            	 if(obj->edit_mode_flag)
            	 {
            	   gMotorVars.SpeedSet_krpm = NEG_HIGHSPEED_RUN;
                   MotoRun_time = 0;
            	   PROCTRL_setNxtState(handle, PROCTRL_State_NormAccele);
            	 }

            	 else
            	 {
                    PROCTRL_setNxtState(handle, PROCTRL_State_EditReturn);
            	 }
               }
               else
               {
            	 if(obj->SENSOR0_ON)
            	    gMotorVars.Flag_enableRun = true;
                 PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);
               }
           break;
      case PROCTRL_State_EditLow: //edit mode recoder the ldc1612 parameter1
    	        if(proctrlHandle->EMG_STOP)
    	        {

                    PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
    	        }
    	        else if(gMotorVars.Flag_RunState == true) //
                {
    	         if(obj->moto_up_flag)
    	         {
                 	 obj->LDC_LowPointData = DispData;
                 	 //obj->ldc_low_recoded = true;
                     gMotorVars.SpeedSet_krpm = BASESPEED_RUN;
                     MotoRun_time = 0;
                     PROCTRL_setNxtState(handle, PROCTRL_State_EditHigh);
    	         }
    	         else
    	         {
					if(MotoRun_time > MOTO_UP_TIME)
					{
						obj->moto_up_flag = true;
					}
    	        	 PROCTRL_setNxtState(handle, PROCTRL_State_EditLow);
    	         }
                }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);


           break;
      case PROCTRL_State_EditHigh: //edit mode recoder the ldc1612 parameter2
          if(proctrlHandle->EMG_STOP)
          {

            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
                else if(gMotorVars.Flag_RunState == true)
                {

                  if(obj->moto_down_flag)
                  {

                    MotoRun_time = 0;
                	PROCTRL_setNxtState(handle, PROCTRL_State_EditReturn);
                  }
                  else
                  {
  	        	     if(MotoRun_time < MOTO_DOWN_TIME)
  	        	     {obj->moto_down_flag = true;}
                     PROCTRL_setNxtState(handle, PROCTRL_State_EditHigh);
                  }
                }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_EditReturn: //recover the ldc1612 parameter
          if(proctrlHandle->EMG_STOP)
          {

            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->SENSOR0_ON)
                {
        	    // Obj->LDC_LowPointData = DispData;

                 gMotorVars.SpeedSet_krpm = NEG_BASESPEED_RUN;
                // gMotorVars.MaxAccel_krpmps = _IQ(12);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormalLow);
                }
        	  else
                 PROCTRL_setNxtState(handle, PROCTRL_State_EditReturn);
          }
          else if(gMotorVars.Flag_RunState == false)
          {
              PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);
          }

           break;
      case PROCTRL_State_NormalLow: //set motor low speed run xx second
          if(proctrlHandle->EMG_STOP)
          {

            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->set_high_speed)
                {
                 gMotorVars.SpeedSet_krpm = NEG_HIGHSPEED_RUN;
                // gMotorVars.MaxAccel_krpmps = _IQ(12);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormHiSped);
                }
        	  else
        	  {
        		 if(gMotorVars.Speed_krpm <= SPEED_CONDITION1)
        		 {
        			 obj->set_high_speed = true;
        		 }
        		 PROCTRL_setNxtState(handle, PROCTRL_State_NormalLow);
        	  }
          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormHiSped: //set motor high speed run xx second
          if(proctrlHandle->EMG_STOP)
          {
           //gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->arrive_point_B)
                {
                 gMotorVars.SpeedSet_krpm = NEG_BASESPEED_RUN;
                 //gMotorVars.MaxAccel_krpmps = _IQ(2);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormDecle);
                }
        	  else
        	  {
                 if(DispData < POINT_B_VALUE)
                 {obj->arrive_point_B = true;}
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormHiSped);
        	  }
          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormDecle:  // motor decelerate the accelerate in A rpm/s^2
          if(proctrlHandle->EMG_STOP)
          {
            //gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->wait_time)
                {
                 gMotorVars.SpeedSet_krpm = NEG_BASESPEED_RUN;
                 //gMotorVars.MaxAccel_krpmps = _IQ(2);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormSlow);
                 ISR_CYSLE = 0;
                }
        	  else
        	  {
        		  if(gMotorVars.Speed_krpm >= SPEED_CONDITION2)
        		  {obj->wait_time = true;}
        		  PROCTRL_setNxtState(handle, PROCTRL_State_NormDecle);
        	  }
          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormSlow:  // motor run in 200rpm speed wait sensor
          if(proctrlHandle->EMG_STOP)
          {
            //gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->set_high_accel)
                {
                 gMotorVars.SpeedSet_krpm = NEG_HIGHSPEED_RUN;
                 //gMotorVars.MaxAccel_krpmps = _IQ(12);
                 MotoRun_time = 0;
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormAccele);
                }
        	  else
        	  {
        		  if(ISR_CYSLE > WAIT_ISR_CYCLE)
        	      {
        		    obj->set_high_accel =true;
        	      }
        		  PROCTRL_setNxtState(handle, PROCTRL_State_NormSlow);
               }

          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormAccele: //motor accelerate the accelerate in B rpm/s^2
          if(proctrlHandle->EMG_STOP)
          {
            //gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->wait_second)
                {
                 gMotorVars.SpeedSet_krpm = HIGHSPEED_RUN;
                 //gMotorVars.MaxAccel_krpmps = _IQ(12);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormReturn);

                }
        	  else
        	  {
        		  if(MotoRun_time > (LED_BLINK_FREQ_Hz * WAIT_SECOND))
        		  {obj->wait_second = true;}
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormAccele);
        	  }
          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormSate: // motor locked-rotor (stable torque)
          if(proctrlHandle->EMG_STOP)
          {
           // gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
              ;
          }
          else if(gMotorVars.Flag_RunState == false)
              PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormReturn: // motor return the origal point in C rpm
          if(proctrlHandle->EMG_STOP)
          {
           // gMotorVars.MaxAccel_krpmps = _IQ(2);
            PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
          }
          else if(gMotorVars.Flag_RunState == true)
          {
        	  if(obj->arrive_point_C)
                {
                 gMotorVars.SpeedSet_krpm = NEG_BASESPEED_RUN;
               //  gMotorVars.MaxAccel_krpmps = _IQ(15);
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormSlow2);

                }
        	  else
        	  {
                  if(DispData > POINT_C_VALUE)
                  {
                 	 obj->arrive_point_C = true;
                  }
                PROCTRL_setNxtState(handle, PROCTRL_State_NormReturn);
        	  }
          }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormSlow2: // motor run in 200rpm speed wait sensor
                if(proctrlHandle->EMG_STOP)
                  {
                   // gMotorVars.MaxAccel_krpmps = _IQ(2);
                    PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
                  }
                else if(gMotorVars.Flag_RunState == true)
                {
                	if(obj->set_stop_flag)
                    {
                     gMotorVars.SpeedSet_krpm = BASESPEED_RUN;
                  //   gMotorVars.MaxAccel_krpmps = _IQ(2);
                     PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);

                    }
                	else
                	{
                	  if(gMotorVars.Speed_krpm <= SPEED_CONDITION3)
                	  {obj->set_stop_flag = true;}
                	  PROCTRL_setNxtState(handle, PROCTRL_State_NormSlow2);
                	}
                }
                else if(gMotorVars.Flag_RunState == false)
                  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);

           break;
      case PROCTRL_State_NormStop: //motor stop
                if(gMotorVars.Flag_RunState == true)
                {
                 gMotorVars.SpeedSet_krpm = _IQ(0.0);
              // gMotorVars.MaxAccel_krpmps = _IQ(2);
                 gMotorVars.Flag_enableRun = false;
                 PROCTRL_setNxtState(handle, PROCTRL_State_NormStop);
                }
                else
                {
                  obj->edit_mode_flag = false;
                  if(brake_enable == false)
                  {

                    PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);
                  }
                }
           break;
      default:  PROCTRL_setNxtState(handle, PROCTRL_State_IDLE);
           break;

    }

   return;

}



//@} //defgroup
// end of file



