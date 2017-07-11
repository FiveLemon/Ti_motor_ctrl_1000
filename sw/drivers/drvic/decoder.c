/*************************************************************************
	> File Name: decoder.c
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Jul 2017 03:33:24 PM CST
 ************************************************************************/

#include "sw/drivers/drvic/decoder.h"


DECODER_Handle DECODER_Init(void *pMemory,const size_t numBytes)
{
  DECODER_Handle handle;
  
  if(numBytes < sizeof(DECODER_Obj))
    return((DECODER_Handle)NULL);

  // assign the handle
  handle = (DECODER_Handle)pMemory;

  DECODER_resetRxTimeout(handle);

   return (handle);
} // end of DECODER_Init() function

uint16_t DECODER_readSpi(DECODER_Handle handle, const DECODER_RegName_e regName)
{
  DECODER_Obj *obj = (DECODER_Obj *)handle;
  volatile uint16_t readWord;
  static volatile uint16_t WaitTimeOut = 0;
  volatile uint16_t ctrlWord;
  volatile SPI_FifoStatus_e RxFifoCnt = SPI_FifoStatus_Empty;

// reset the Rx fifo pointer to zero
  SPI_resetRxFifo(obj->spiHandle); 
  SPI_enableRxFifo(obj->spiHandle);
  
  ctrlWord = (uint16_t)regName;
  SPI_write(obj->spiHandle,ctrlWord);

  // wait for one words to populate the RX fifo, or a wait timeout will occur
  while((RxFifoCnt < SPI_FifoStatus_1_Word) && (WaitTimeOut < 0xffff))
  {
    RxFifoCnt = SPI_getRxFifoStatus(obj->spiHandle);
    
    if(++WaitTimeOut > 0xfffe)
    {
       obj->RxTimeOut = true;
    }
  }

  // Read data
  readWord = SPI_readEmu(obj->spiHandle);

  return readWord;

}

void DECODER_setSpiHandle(DECODER_Handle handle, SPI_Handle spiHandle)
{
  DECODER_Obj *obj = (DECODER_Obj *)handle;

  // initialize the serial peripheral interface object 
  obj->spiHandle = spiHandle;
  
  return;
}

void DECODER_setGpioHandle(DECODER_Handle handle, GPIO_Handle gpioHandle)
{
  DECODER_Obj *obj = (DECODER_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioHandle = gpioHandle; 
  
  return;
}

void DECODER_setGpioNumber(DECODER_Handle handle,GPIO_Number_e gpioNumber)
{
  DECODER_Obj *obj = (DECODER_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioNumber = gpioNumber;

  return;
} // end of DECODER_setGpioNumber() function 

void DECODER_readReg(DECODER_Handle handle, uint32_t *RegData)
{
  //DECODER_Obj *obj = (DECODER_Obj *)handle;
  volatile DECODER_RegName_e drvRegName;

  union
  {
	  uint32_t       data_uint;
	  DECODER_Vars_t drvRegData;
  } drvData_u;

  drvData_u.data_uint =0;

  drvRegName = DECODER_CycReg;
  drvData_u.drvRegData.Cyc_Reg = DECODER_readSpi(handle, drvRegName) & 0xff;
  drvRegName = DECODER_PosReg;
  drvData_u.drvRegData.Pos_Reg = DECODER_readSpi(handle, drvRegName);


  *RegData = drvData_u.data_uint;

  return;
}








