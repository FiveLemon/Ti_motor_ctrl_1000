#include "sw/modules/brake/src/brake.h"
#include "hal.h"
#include "user.h"



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
	//_iq current_sf;
	_iq ref_current;


	  Ki = _IQ(0.001);
	  Kp = _IQ(1.0);
      Kd = _IQ(0.0);
      //current_sf = _IQ(USER_CURRENT_SF);
      Motor_Rated_I = _IQ(0.25);

      Brake_setCurrent_rate_pu(handle,Motor_Rated_I);
      Brake_setCurrent_Rate(handle, _IQ(0.75));

      //current_A = _IQmpy(obj->Irated , current_sf);

      ref_current = _IQmpy(Motor_Rated_I, obj->current_rate);

	  Brake_setCurrent_ref_pu(handle, ref_current);

	  Brake_setGains(handle,Kp,Ki,Kd);
	  PID_setGains(obj->pidHandle_Ibrake, Kp,Ki,Kd);
    return;
}



