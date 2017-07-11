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


// drivers


// platforms
#include "main.h"




// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   5

typedef enum
{
   BRAKE_Type_Current = 0,
   BRAKE_Type_voltage

}BRAKE_Type_e;

typedef enum {
	BRAKE_State_Error=0,           //!< the controller error state
	BRAKE_State_Idle,              //!< the controller idle state
	BRAKE_State_OffLine,           //!< the controller offline state
	BRAKE_State_OnLine,            //!< the controller online state
	BRAKE_numStates                //!< the number of controller states
} BRAKE_State_e;

typedef struct _BRAKE_Obj_
{

	BRAKE_State_e        state;

	PID_Handle           pidHandle_Ibrake;                 //!< the handle for the I brake PID controller
	PID_Obj              pid_Ibrake;                       //!< the Ibrake PID controller object
	//MOTOR_Params         motorParams;                      //!< the motor parameters

	  _iq                Kp_Ibrake;                        //!< the desired Kp_Id value
	  _iq                Ki_Ibrake;                        //!< the desired Kp_Id value
	  _iq                Kd_Ibrake;                        //!< the desired Kd_Id value

	  _iq                Ibrake_ref;                      //!< the speed reference, pu
	  _iq                Ibrake_fbk;
	  MATH_vec2          AdcValue_I;

	  _iq                Ibrake_out;
	  _iq                Irated;
	  _iq                current_rate;

	  BRAKE_Type_e       brake_type;
	  uint_least16_t     counter_current;                 //!< the isr counter
	  bool               flag_enableBrake;                //!< a flag to enable the brake
      bool               flag_enableOffset;

} BRAKE_Obj;

typedef struct _BRAKE_Obj_ *BRAKE_Handle;




inline _iq *Brake_getIbrake_out_addr(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	return(&(obj->Ibrake_out));
}

inline _iq BRAKE_getFeedbak_in_pu(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	return(obj->Ibrake_fbk);
}


static inline void BRAKE_setKp(BRAKE_Handle handle,const float_t Kp)
{
  BRAKE_Obj *obj = (BRAKE_Obj *)handle;
  obj->Kp_Ibrake = Kp;
  return;
}

static inline void BRAKE_setKi(BRAKE_Handle handle,const float_t Ki)
{
  BRAKE_Obj *obj = (BRAKE_Obj *)handle;
  obj->Ki_Ibrake = Ki;
  return;
}

static inline void BRAKE_setKd(BRAKE_Handle handle,const float_t Kd)
{
  BRAKE_Obj *obj = (BRAKE_Obj *)handle;
  obj->Kd_Ibrake = Kd;
  return;
}


BRAKE_Handle Brake_init(void *pMemory,const size_t numBytes)
{

	BRAKE_Handle BrakeHandle;

    if(numBytes < sizeof(BRAKE_Obj))
    return((BRAKE_Handle)NULL);

    // assign the handle
    BrakeHandle = (BRAKE_Handle)pMemory;

    BrakeHandle->pidHandle_Ibrake = PID_init(&(BrakeHandle->pid_Ibrake),sizeof(BrakeHandle->pid_Ibrake));

    return (BrakeHandle);
}


inline void Brake_run_online(BRAKE_Handle handle,const HAL_AdcData_t *pAdcData,HAL_PwmData_t *pPwmData)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	  //_iq   Ibrake_fbk;
	  //_iq   brake;
	  MATH_vec3 pT; //point to pwm duty
	  _iq refValue = obj->Ibrake_ref;
	  _iq fbackValue;
	  //_iq Kp_Ibrake;
	  //_iq Ki_Ibrake;
      _iq adc_temp;

	  adc_temp = pAdcData->I.value[0];
	  obj->Ibrake_fbk = adc_temp;

      fbackValue = BRAKE_getFeedbak_in_pu(handle);

	  PID_setMinMax(obj->pidHandle_Ibrake,_IQ(-0.9),_IQ(0.9));

	  // set the Brake controller gains
	  PID_run(obj->pidHandle_Ibrake, refValue, adc_temp, Brake_getIbrake_out_addr(handle));


	  pT.value[0] = (obj->Ibrake_out);
	  pT.value[1] = -(obj->Ibrake_out);
	  pT.value[2] = _IQ(0.0);

	  pPwmData->Tabc = pT;
}

inline void Brake_setCurrent_rate_pu(BRAKE_Handle handle,const _iq motor_Irated)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	obj->Irated	= motor_Irated;
	return;
}

inline void Brake_setCurrent_ref_pu(BRAKE_Handle handle,const _iq brake_ref_pu)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	obj->Ibrake_ref = brake_ref_pu;

	return;
}

inline void Brake_setCurrent_Rate(BRAKE_Handle handle,const _iq current_rate_pu)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	obj->current_rate = current_rate_pu;

	return;
}

inline void Brake_setBrake_Type(BRAKE_Handle  handle,const BRAKE_Type_e brake_type)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	obj->brake_type = brake_type;
	return;
}

inline void Brake_setFlag_enableBrake(BRAKE_Handle handle,const bool state)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	obj->flag_enableBrake = state;
	return;
}


inline void Brake_setFlag_enableOffset(BRAKE_Handle handle,const bool state)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;

    obj->flag_enableOffset = state;

  return;
} // end of Brake_setFlag_enableOffset() function

inline _iq Brake_getRefValue_pu(BRAKE_Handle handle,const BRAKE_Type_e BrakeType)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
    _iq ref = _IQ(0.0);

  if(BrakeType == BRAKE_Type_Current)
    {
      ref = PID_getRefValue(obj->pidHandle_Ibrake);
    }
  else if(BrakeType == BRAKE_Type_voltage)
    {
      ;//ref = PID_getRefValue(obj->pidHandle_Id);
    }


  return(ref);
} // end of Brake_getRefValue_pu() function

inline BRAKE_State_e Brake_getState(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;

  return(obj->state);
} // end of Brake_getState() function


inline bool Brake_getFlag_enableCtrl(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;

  return(obj->flag_enableBrake);
} // end of Brake_getFlag_enableCtrl() function


inline bool Brake_getFlag_enableOffset(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;

  return(obj->flag_enableOffset);
} // end of Brake_getFlag_enableOffset() function


void Brake_run(BRAKE_Handle handle,HAL_Handle halHandle,
        const HAL_AdcData_t *pAdcData,
        HAL_PwmData_t *pPwmData)
{

    if(Brake_getFlag_enableCtrl(handle))
    {
	  Brake_run_online(handle,pAdcData,pPwmData);
    }

}



void Brake_setGains(BRAKE_Handle handle, const _iq Kp,const _iq Ki,const _iq Kd)
{

  BRAKE_setKp(handle,Kp);
  BRAKE_setKi(handle,Ki);
  BRAKE_setKd(handle,Kd);

  return;
} // end of Brake_setGains() function



void Brake_Setup(BRAKE_Handle handle)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;

	_iq Kp,Ki,Kd;
	_iq Motor_Rated_I;
	_iq current_sf;
	_iq ref_current;
	_iq current_A;


	  Ki = _IQ(0.001);
	  Kp = _IQ(1.0);
      Kd = _IQ(0.0);
      current_sf = _IQ(USER_CURRENT_SF);
      Motor_Rated_I = _IQ(USER_MOTO_RATED_CURRENT);

      Brake_setCurrent_rate_pu(handle,Motor_Rated_I);
      Brake_setCurrent_Rate(handle, _IQ(0.75));

      current_A = _IQmpy(obj->Irated , current_sf);

      ref_current = _IQmpy(Motor_Rated_I, obj->current_rate);

	  Brake_setCurrent_ref_pu(handle, ref_current);

	  Brake_setGains(handle,Kp,Ki,Kd);
	  PID_setGains(obj->pidHandle_Ibrake, Kp,Ki,Kd);
    return;
}








// **************************************************************************
// the globals

uint_least32_t gLEDcnt = 0;                   // Counter used to divide down the ISR rate for visually blinking an LED

HAL_Handle halHandle;                         // Handle to the Inverter hardware abstraction layer

BRAKE_Obj   myBrake;

BRAKE_Handle Brakehandle;

USER_Params gUserParams;                      // Contains the user.h settings

HAL_PwmData_t gPwmData = {0,0,0};             // Contains PWM duty cycles in global Q format

HAL_AdcData_t gAdcData = {0,0,0,0,0,0,0};     // Contains Current and Voltage ADC readings in global Q format

volatile MOTOR_Vars_t gMotorVars = MOTOR_Vars_INIT;

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;
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
  #endif

  // initialize the hardware abstraction layer
  halHandle = HAL_init(&hal,sizeof(hal));

  Brakehandle = Brake_init(&myBrake, sizeof(myBrake));

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
  Brake_Setup(Brakehandle);

#ifdef LAUNCHPAD
  // Setup GPIOs 0 and 1 as outputs for use in project lab1 only.
  // This is specific to the launchpad because its LEDs are also used by the PWM channels.
  HAL_setupLaunchPadGpio0and1(halHandle);
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


  //configure the Pac9555 for init
  HAL_I2c_Pca9555_WrData(halHandle,0x06,0x00);
  //getData[1] = 0x0f | HAL_I2c_Pca9555_RdData(halHandle,0x01);
  HAL_I2c_Pca9555_WrData(halHandle,0x02,0x58);
  HAL_I2c_Pca9555_WrData(halHandle,0x02,0x5c);

  // disable the PWM
  //HAL_disablePwm(halHandle);
  HAL_enablePwm(halHandle);

  // For ever loop
  while(true);

} // end of main() function


interrupt void mainISR(void)
{
  // toggle status LED
  if(gLEDcnt++ > (uint_least32_t)(USER_ISR_FREQ_Hz / LED_BLINK_FREQ_Hz))
  {
    //HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
    gLEDcnt = 0;
  }



  // acknowledge the ADC interrupt
  HAL_acqAdcInt(halHandle,ADC_IntNumber_1);


  // convert the ADC data
  HAL_readAdcData(halHandle,&gAdcData);


  // ADC processing and pwm result code goes here
  //gPwmData.Tabc.value[0]= _IQ(0.0);
  //gPwmData.Tabc.value[1]= _IQ(0.3);
  //gPwmData.Tabc.value[2]= _IQ(-0.3);
  Brake_run(Brakehandle,halHandle,&gAdcData,&gPwmData);


  // write the PWM compare values
  HAL_writePwmData(halHandle,&gPwmData);


  return;
} // end of mainISR() function










//@} //defgroup
// end of file




