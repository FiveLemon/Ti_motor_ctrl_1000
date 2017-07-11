/*************************************************************************
	> File Name: process_ctrl.h
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Jul 2017 09:36:34 AM CST
 ************************************************************************/

#ifndef _PROCESS_CTRL_H
#define _PROCESS_CTRL_H

#include "sw/drivers/drvic/ldc1612.h"
#include "sw/drivers/drvic/oled/oled.h"
#include "sw/drivers/drvic/decoder.h"
#include "sw/drivers/drvic/pca9555.h"
#include "hal.h"
#include "sw/solutions/instaspin_foc/src/main.h"
#include <math.h>


#ifdef __cplusplus
extern "C" { 
#endif


#define USE_OLED
#define USE_LDC161x_0x2A


typedef enum
{
  PROCTRL_State_IDLE = 0,
  PROCTRL_State_EditLow,
  PROCTRL_State_EditHigh,
  PROCTRL_State_EditReturn,
  PROCTRL_State_NormalLow,
  PROCTRL_State_NormHiSped,
  PROCTRL_State_NormDecle,
  PROCTRL_State_NormSlow,
  PROCTRL_State_NormAccele,
  PROCTRL_State_NormSate,
  PROCTRL_State_NormReturn,
  PROCTRL_State_NormSlow2,
  PROCTRL_State_NormStop

} PROCTRL_State_e;
//
//
//typedef struct _PROCTRL_Moto_Massage_t
//{
//  
//
//
//}







typedef struct _PROCTRL_Obj_
{
 HAL_Handle        halHandle;

  //PCA955x_Handle    pca955xHandle;
  //PCA955x_Obj       pca9555;

  //LDC161x_Handle    ldc161xHandle_a;
  //LDC161x_Obj       ldc1612_a;

  //LDC161x_Handle    ldc161xHandle_b;
  //LDC161x_Obj       ldc1612_b;

  //OLED_Handle       oledHandle;
  //OLED_Obj          OLED;

  //DECODER_Handle    QPdecHandle;
  //DECODER_Obj       QPdecoder;

  uint32_t          LDC_HighPointData;
  uint32_t          LDC_LowPointData;

  PROCTRL_State_e   Cur_State; 
  bool              SENSOR0_ON;
  bool              SENSOR1_ON;
  bool              EMG_STOP;
  bool              ldcGetGoal;
  bool              ldc_high_recoded;
  bool              ldc_low_recoded;

  bool              ldc_touch_top;
  bool              ldc_touch_buttom;

  bool              moto_up_flag;
  bool              moto_down_flag;
  bool              set_high_speed;
  bool              set_high_accel;
  bool              arrive_point_B;
  bool              wait_time;
  bool              wait_second;
  bool              arrive_point_C;
  bool              set_stop_flag;
  bool              edit_mode_flag;

} PROCTRL_Obj;

typedef struct _PROCTRL_Obj_ *PROCTRL_Handle;



PROCTRL_Handle PROCTRL_init(void *pMemory,const size_t numBytes);
void PROCTRL_setHalHandle(PROCTRL_Handle handle, HAL_Handle hal_handle);
void PROCTRL_setParams(PROCTRL_Handle handle);
//void PROCTRL_run(PROCTRL_Handle handle, MOTOR_Vars_t *pMotorVars);

















#ifdef __cplusplus 
}
#endif


#endif
