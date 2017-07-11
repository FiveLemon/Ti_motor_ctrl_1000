/*************************************************************************
	> File Name: process_ctrl.c
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Jul 2017 09:35:56 AM CST
 ************************************************************************/


#include "sw/drivers/drvic/process_ctrl.h"




PROCTRL_Handle PROCTRL_init(void *pMemory,const size_t numBytes)
{

   PROCTRL_Handle handle;
   
   if(numBytes < sizeof(PROCTRL_Obj))
     return ((PROCTRL_Handle)NULL);

   handle = (PROCTRL_Handle)pMemory;

   return (handle);

}

void PROCTRL_setHalHandle(PROCTRL_Handle handle, HAL_Handle halHandle)
{
  PROCTRL_Obj *obj = (PROCTRL_Obj *)handle;

  obj->halHandle = halHandle;

  return;
}

/*

void PROCTRL_setParams(PROCTRL_Handle handle)
{

  PROCTRL_Obj *obj = (PROCTRL_Obj *)handle;

  obj->pca955xHandle = PCA955x_Init(&(obj->pca9555),sizeof(obj->pca9555));
  PCA955x_setI2cHandle(obj->pca955xHandle,obj->halHandle->i2cHandle);
  PCA955x_Configure(obj->pca955xHandle, PCA955x_PortNum_Port0, 0x00);
  PCA955x_Configure(obj->pca955xHandle, PCA955x_PortNum_Port1, 0xff);
  PCA955x_WriteCommand(obj->pca955xHandle, PCA955x_PortNum_Port0, 0x50);
  PCA955x_WriteCommand(obj->pca955xHandle, PCA955x_PortNum_Port0, 0x5c);

#ifdef USE_DECODER

  obj->QPdecHandle = DECODER_Init(&(obj->QPdecoder),sizeof(obj->QPdecoder));
  DECODER_setSpiHandle(obj->QPdecHandle,obj->halHandle->spiAHandle);

#endif

  // initialize the ldc sensor and oled displayer


#ifdef USE_LDC161x_0x2A

  obj->ldc161xHandle_a = LDC1612_init(&(obj->ldc1612_a), sizeof(obj->ldc1612_a));
  LDC161x_setI2cHandle(obj->ldc161xHandle_a, obj->halHandle->i2cHandle);
  LDC161x_setGpioHandle(obj->ldc161xHandle_a, obj->halHandle->gpioHandle);
  LDC161x_setSensorSerial(obj->ldc161xHandle_a->ldcHandle, LDC161x_Slave_Addr0);

  LDC161x_ResetSensor(obj->ldc161xHandle_a);
  LDC161x_setRcount(obj->ldc161xHandle_a->ldcHandle, 0x0, 0xffff);
  LDC161x_setSettleCnt(obj->ldc161xHandle_a->ldcHandle, 0x0, 0x000a);
  LDC161x_setClkDivs(obj->ldc161xHandle_a->ldcHandle, 0x0, 0x1001);
  LDC161x_setConfig(obj->ldc161xHandle_a->ldcHandle, 0x1c01);
  LDC161x_setMuxConfig(obj->ldc161xHandle_a->ldcHandle, 0x020c);
  
  LDC161x_writeRcount(obj->ldc161xHandle_a, LDC161x_ChNum_CH0);
  LDC161x_writeSettleCnt(obj->ldc161xHandle_a, LDC161x_ChNum_CH0);
  LDC161x_writeClkDivs(obj->ldc161xHandle_a, LDC161x_ChNum_CH0);
  LDC161x_writeConfig(obj->ldc161xHandle_a);
  LDC161x_writeMuxConfig(obj->ldc161xHandle_a);

#endif

#ifdef USE_LDC161x_0x2B

  obj->ldc161xHandle_b = LDC1612_init(&(obj->ldc1612_b), sizeof(obj->ldc1612_b));
  LDC161x_setI2cHandle(obj->ldc161xHandle_b, obj->halHandle->i2cHandle);
  LDC161x_setGpioHandle(obj->ldc161xHandle_b, obj->halHandle->gpioHandle);
  LDC161x_setSensorSerial(obj->ldc161xHandle_b->ldcHandle, LDC161x_Slave_Addr1);

  LDC161x_ResetSensor(obj->ldc161xHandle_b);
  LDC161x_setRcount(obj->ldc161xHandle_b->ldcHandle, 0x0, 0xffff);
  LDC161x_setSettleCnt(obj->ldc161xHandle_b->ldcHandle, 0x0, 0x000a);
  LDC161x_setClkDivs(obj->ldc161xHandle_b->ldcHandle,0x0, 0x1001);
  LDC161x_setConfig(obj->ldc161xHandle_b->ldcHandle, 0x1c01);
  LDC161x_setMuxConfig(obj->ldc161xHandle_b->ldcHandle, 0x020c);
  
  LDC161x_writeRcount(obj->ldc161xHandle_b, LDC161x_ChNum_CH0);
  LDC161x_writeSettleCnt(obj->ldc161xHandle_b, LDC161x_ChNum_CH0);
  LDC161x_writeClkDivs(obj->ldc161xHandle_b, LDC161x_ChNum_CH0);
  LDC161x_writeConfig(obj->ldc161xHandle_b);
  LDC161x_writeMuxConfig(obj->ldc161xHandle_b);

#endif

#ifdef USE_OLED

  obj->oledHandle = OLED_Init(&(obj->OLED), sizeof(obj->OLED));
  OLED_setI2cHandle(obj->oledHandle, obj->halHandle->i2cHandle);

  OLED_RegInit(obj->oledHandle);
  OLED_Clear(obj->oledHandle);

#endif

}

*/






























