/*************************************************************************
	> File Name: decoder.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Jul 2017 03:33:33 PM CST
 ************************************************************************/

#ifndef _DECODER_H
#define _DECODER_H


// drivers
#include "sw/drivers/spi/src/32b/f28x/f2806x/spi.h"
#include "sw/drivers/gpio/src/32b/f28x/f2806x/gpio.h"



#ifdef __cplusplus 
extern "C" { 
#endif     


typedef enum
{
  DECODER_enable = 0x00,
  DECODER_disable = 0x01

} DECODER_Status_e;

typedef enum
{
   DECODER_CycReg = 0x0,
   DECODER_PosReg = 0xf
} DECODER_RegName_e;



typedef struct _DECODER_Vars_t_
{
  uint16_t   Pos_Reg;
  uint16_t   Cyc_Reg;

} DECODER_Vars_t;


typedef struct _DECODER_Obj_
{
  SPI_Handle       spiHandle;
  GPIO_Handle      gpioHandle;

  GPIO_Number_e    gpioNumber;
  bool             RxTimeOut;

} DECODER_Obj;

typedef struct _DECODER_Obj_ *DECODER_Handle;


uint16_t DECODER_readSpi(DECODER_Handle handle, const DECODER_RegName_e regName);
void DECODER_setSpiHandle(DECODER_Handle handle, SPI_Handle spiHandle);
void DECODER_setGpioHandle(DECODER_Handle handle, GPIO_Handle gpioHandle);
void DECODER_setGpioNumber(DECODER_Handle handle,GPIO_Number_e gpioNumber);
DECODER_Handle DECODER_Init(void *pMemory,const size_t numBytes);
//void DECODER_enableCPLD(DECODER_Handle handle, DECODER_Status_e);
void DECODER_readReg(DECODER_Handle handle, uint32_t *RegData);

static inline void DECODER_resetRxTimeout(DECODER_Handle handle)
{
  DECODER_Obj *obj = (DECODER_Obj *)handle;

  obj->RxTimeOut = false;

  return;
}





#ifdef __cplusplus 
} 
#endif // extern "C"

#endif
