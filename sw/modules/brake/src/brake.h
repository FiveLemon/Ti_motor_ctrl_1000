
#ifndef _BRAKE_H_
#define _BRAKE_H_

// the includes

#include "sw/modules/iqmath/src/32b/IQmathLib.h"
#include "sw/modules/math/src/32b/math.h"
#include "sw/modules/types/src/types.h"
#include "sw/modules/pid/src/32b/pid.h"

#include "hal_obj.h"

#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines


// **************************************************************************
// the typedefs

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

	PID_Handle           pidHandle_Ibrake;      //!< the handle for the I brake PID controller
	PID_Obj              pid_Ibrake;            //!< the Ibrake PID controller object
	//MOTOR_Params         motorParams;           //!< the motor parameters

	  _iq                Kp_Ibrake;             //!< the desired Kp_Id value
	  _iq                Ki_Ibrake;             //!< the desired Kp_Id value
	  _iq                Kd_Ibrake;             //!< the desired Kd_Id value

	  _iq                Ibrake_ref;            //!< the speed reference, pu
	  _iq                Ibrake_fbk;
	  MATH_vec2          AdcValue_I;

	  _iq                Ibrake_out;
	  _iq                Irated;
	  _iq                current_rate;

	  BRAKE_Type_e       brake_type;
	  uint_least16_t     counter_current;       //!< the isr counter
	  bool               flag_enableBrake;      //!< a flag to enable the brake
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



inline void Brake_run_online(BRAKE_Handle handle,const HAL_AdcData_t *pAdcData,HAL_PwmData_t *pPwmData)
{
	BRAKE_Obj *obj = (BRAKE_Obj *)handle;
	  //_iq   Ibrake_fbk;
	  //_iq   brake;
	  MATH_vec3 pT; //point to pwm duty
	  _iq refValue = obj->Ibrake_ref;
	  //_iq Ki_Ibrake;
      _iq adc_temp;

	  adc_temp = pAdcData->I.value[0];
	  obj->Ibrake_fbk = adc_temp;

      //fbackValue = BRAKE_getFeedbak_in_pu(handle);

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


BRAKE_Handle Brake_init(void *pMemory,const size_t numBytes);
void Brake_run(BRAKE_Handle handle,HAL_Handle halHandle,
	   	const HAL_AdcData_t *pAdcData,
		HAL_PwmData_t *pPwmData);

void Brake_setGains(BRAKE_Handle handle, const _iq Kp,const _iq Ki,const _iq Kd);

void Brake_Setup(BRAKE_Handle handle);





#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _AFSEL_H_ definition
