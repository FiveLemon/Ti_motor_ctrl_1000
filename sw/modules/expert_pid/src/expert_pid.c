
#include "sw/modules/pid/src/32b/pid.h"


// **************************************************************************
// the functions

_EXP_PID_Handle EXP_PID_init(void *pMemory,const size_t numBytes)
{
  EXP_PID_Handle handle;


  if(numBytes < sizeof(EXP_PID_Obj))
    return((EXP_PID_Handle)NULL);

  // assign the handle
  handle = (EXP_PID_Handle)pMemory;

  // set some defaults
  PID_setUi(handle,_IQ(0.0));
  PID_setRefValue(handle,_IQ(0.0));
  PID_setFbackValue(handle,_IQ(0.0));


  return(handle);
} // end of PID_init() function

