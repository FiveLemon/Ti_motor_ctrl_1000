
#ifndef _EXPERT_PID_H_
#define _EXPERT_PID_H_

// **************************************************************************
// the includes

//modules
#include "sw/modules/iqmath/src/32b/IQmathLib.h"
#include "sw/modules/types/src/types.h"


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the typedefs

//! \brief Defines the PID controller object
//!
typedef struct _EXP_PID_Obj_
{
  _iq Kp;                     //!< the proportional gain for the PID controller
  _iq Ki;                     //!< the integral gain for the PID controller
  _iq Kd;                     //!< the derivative gain for the PID controller

  _iq preError;                //e(k-1) 
  _iq preDetError;             //delta e(k-1)

  _iq Ui;                     //!< the integrator start value for the PID controller

  _iq refValue;               //!< the reference input value
  _iq fbackValue;             //!< the feedback input value

  _iq errorBoundary1;
  _iq errorBoundary2;

  _iq outMin;                 //!< the minimum output value allowed for the PID controller
  _iq outMax;                 //!< the maximum output value allowed for the PID controller

} _EXP_PID_Obj; 


//! \brief Defines the PID handle
//!
typedef struct _EXP_PID_Obj_ *EXP_PID_Handle;

static inline _iq PID_getFbackValue(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->fbackValue);
} // end of PID_getFbackValue() function


static inline void PID_getGains(PID_Handle handle,_iq *pKp,_iq *pKi,_iq *pKd)
{
  PID_Obj *obj = (PID_Obj *)handle;

  *pKp = obj->Kp;
  *pKi = obj->Ki;
  *pKd = obj->Kd;

  return;
} // end of PID_getGains() function

static inline _iq PID_getKd(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->Kd);
} // end of PID_getKd() function


//! \brief     Gets the integral gain in the PID controller
//! \param[in] handle  The PID controller handle
//! \return    The integral gain in the PID controller
static inline _iq PID_getKi(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->Ki);
} // end of PID_getKi() function


//! \brief     Gets the proportional gain in the PID controller
//! \param[in] handle  The PID controller handle
//! \return    The proportional gain in the PID controller
static inline _iq PID_getKp(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->Kp);
} // end of PID_getKp() function

static inline void PID_getMinMax(PID_Handle handle,_iq *pOutMin,_iq *pOutMax)
{
  PID_Obj *obj = (PID_Obj *)handle;

  *pOutMin = obj->outMin;
  *pOutMax = obj->outMax;

  return;
} // end of PID_getMinMax() function

static inline _iq PID_getOutMax(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->outMax);
} // end of PID_getOutMax() function

static inline _iq PID_getOutMin(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->outMin);
} // end of PID_getOutMin() function

static inline _iq PID_getRefValue(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->refValue);
} // end of PID_getRefValue() function

static inline _iq PID_getUi(PID_Handle handle)
{
  PID_Obj *obj = (PID_Obj *)handle;

  return(obj->Ui);
} // end of PID_getUi() function

extern PID_Handle PID_init(void *pMemory,const size_t numBytes);

static inline void EXP_PID_run(EXP_PID_Handle handle,const _iq refValue,const _iq fbackValue,_iq *pOutValue)
{
  EXP_PID_Obj *obj = (EXP_PID_Obj *)handle;

  _iq Error;
  _iq Up,Ui;
  _iq curDetError;
  _iq absError;
  _iq Gain;
  _iq Atten;
  _iq result;

  Error = refValue - fbackValue;
  curDetError = Error - obj->preError;
  
  absError = _IQabs(Error); 
  result = _IQmpy(obj->Kp,Error);   // Compute the proportional
  Ui = 0;

// expert rule
  if( absError > obj->errorBoundary1) //rule 1 open control
  {
    Up = result;
  }

  if((Error > 0 && curDetError > 0)||(Error < 0 && curDetError < 0)||(curDetError == 0))
  { //rule 2
    if(absError > obj->errorBoundary2)
	{
	  Gain = _IQ(1.2);
	  Up = _IQmpy(result, Gain);
	}
	else
	{
	  //Gain = _IQ(1.0); 
	  //Up = _IQmpy(result, Gain);
	  Up = result;
	}

  }

  if((Error < 0 && curDetError > 0) || (Error > 0 && curDetError < 0))
  { 
    if((curDetError > 0 && preDetError > 0) || (curDetError < 0 && preDetError < 0))
    { //rule 3 balance output not change
      Up = _IQmpy(obj->preError, obj->Kp); // use previous value
    }
	if((curDetError > 0 && preDetError < 0) || (curDetError < 0 && preDetError > 0))
	{ // rule 4 error in pole
      if(absError > obj->errorBoundary2)
	  { //strong control
		Gain = _IQ(1.618);
        Up = _IQmpy(Gain,result);
	  }
	  else
	  {
		Atten = _IQ(0.618);
        Up = _IQmpy(Atten,result);
	  }
	}
  }

  if(Error == 0)
  {
    Up = _IQmpy(obj->preError, obj->Kp); //use previous value
  }

  if(absError <= _IQ(0.003)) //add integral reduce error
  {
	Ui = obj->Ui;
	Up = result;
    Ui = _IQsat(Ui + _IQmpy(obj->Ki,Up),obj->outMax,obj->outMin);
  }


  obj->preError = Error; 
  obj->preDetError = curDetError; 
  obj->Ui = Ui;
  obj->refValue = refValue;
  obj->fbackValue = fbackValue;

  *pOutValue = _IQsat(Up + Ui,obj->outMax,obj->outMin);          // Saturate the output

  return;
} // end of EXP_PID_run() function


static inline void PID_setGains(PID_Handle handle,const _iq Kp,const _iq Ki,const _iq Kd)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->Kp = Kp;
  obj->Ki = Ki;
  obj->Kd = Kd;

  return;
} // end of PID_setGains() function

static inline void PID_setKd(PID_Handle handle,const _iq Kd)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->Kd = Kd;

  return;
} // end of PID_setKd() function


static inline void PID_setKi(PID_Handle handle,const _iq Ki)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->Ki = Ki;

  return;
} // end of PID_setKi() function


static inline void PID_setKp(PID_Handle handle,const _iq Kp)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->Kp = Kp;

  return;
} // end of PID_setKp() function


static inline void PID_setMinMax(PID_Handle handle,const _iq outMin,const _iq outMax)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->outMin = outMin;
  obj->outMax = outMax;

  return;
} // end of PID_setMinMax() function

static inline void PID_setOutMax(PID_Handle handle,const _iq outMax)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->outMax = outMax;

  return;
} // end of PID_setOutMax() function


static inline void PID_setOutMin(PID_Handle handle,const _iq outMin)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->outMin = outMin;

  return;
} // end of PID_setOutMin() function

static inline void PID_setBoundary(PID_Handle handle,const _iq Boundary)
{

} // end of EXP_PID_setBoundary()



static inline void PID_setRefValue(PID_Handle handle,const _iq refValue)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->refValue = refValue;

  return;
} // end of PID_setRefValue() function

static inline void PID_setUi(PID_Handle handle,const _iq Ui)
{
  PID_Obj *obj = (PID_Obj *)handle;

  obj->Ui = Ui;

  return;
} // end of PID_setUi() function




#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif //end of _EXP_PID_H_ definition

