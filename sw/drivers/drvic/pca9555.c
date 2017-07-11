/*************************************************************************
    > File Name: pca9555.c
    > Author: 
    > Mail: 
    > Created Time: Sat 08 Jul 2017 09:30:21 AM CST
 ************************************************************************/

#include "sw/drivers/drvic/pca9555.h"

PCA955x_Handle PCA955x_Init(void *pMemory,const size_t numBytes)
{
  PCA955x_Handle handle;
  
  if(numBytes < sizeof(PCA955x_Obj))
     return ((PCA955x_Handle)NULL);
  
  handle = (PCA955x_Handle)pMemory;

  PCA955x_resetRxTimeOut(handle);
  PCA955x_resetTxTimeOut(handle);

  return(handle);
}

void PCA955x_setI2cHandle(PCA955x_Handle handle, I2C_Handle i2cHandle)
{
  PCA955x_Obj *obj = (PCA955x_Obj *)handle;

  obj->i2cHandle = i2cHandle;

  return;
}

void PCA955x_WrData(PCA955x_Handle handle, PCA955x_RegName_e RegName, uint16_t data)
{
    PCA955x_Obj *obj = (PCA955x_Obj *)handle;
    static volatile uint16_t WaitTimeOut;

    while(I2C_isMasterBusy(obj->i2cHandle))
        I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);


    // Send Address
    I2C_setMasterSlaveAddr(obj->i2cHandle, PCA955X_SLAVE_ADDR);
    I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x02);
    I2C_enable(obj->i2cHandle);

    // Send Data1
    I2C_putData(obj->i2cHandle, ((uint16_t)RegName));
     
    // Wait Tx register Ready
    WaitTimeOut = 0;
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy
            && (WaitTimeOut < 0x1fff))
    {
       if(++WaitTimeOut > 0x1ffe)
       {
          obj->TxTimeOut = true;
          return;
       }
    }

    I2C_putData(obj->i2cHandle, data);

    // Wait The data Transmit
    WaitTimeOut = 0;
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop
            && (WaitTimeOut < 0x1fff))
    {
       if(++WaitTimeOut > 0x1ffe)
       {
          obj->TxTimeOut = true;
          return;
       }

    }

    return;
}

uint16_t PCA955x_RdData(PCA955x_Handle handle, PCA955x_RegName_e RegName)
{
    PCA955x_Obj *obj = (PCA955x_Obj *)handle;
    static volatile uint16_t WaitTimeOut;
    uint16_t pcaData;

    while(I2C_isMasterBusy(obj->i2cHandle))
            I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);

    I2C_setMasterSlaveAddr(obj->i2cHandle, PCA955X_SLAVE_ADDR);
    I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x01);
    I2C_enable(obj->i2cHandle);

    I2C_putData(obj->i2cHandle, (uint16_t)(RegName));

    WaitTimeOut = 0;
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy
            && (WaitTimeOut < 0x1fff))
    {
       if(++WaitTimeOut > 0x1ffe)
       {
          obj->TxTimeOut = true;
          return 0;
       }

    }
    
    WaitTimeOut = 0;
    while(I2C_isMasterBusy(obj->i2cHandle) && (WaitTimeOut < 0x1fff))
    {
       if(++WaitTimeOut > 0x1ffe)
       {
          obj->TxTimeOut = true;
          return 0;
       }

    }

    I2C_setMasterSlaveAddr(obj->i2cHandle, PCA955X_SLAVE_ADDR);
    I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_RX, I2C_BitCount_8_Bits,0x01);
    I2C_enable(obj->i2cHandle);

    WaitTimeOut = 0;
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Rx_Rdy) != I2C_Status_Rx_Rdy
            && (WaitTimeOut < 0x1fff))
    {
      if(++WaitTimeOut > 0x1ffe)
       {
          obj->RxTimeOut = true;
          return 0;
       }

    }

    pcaData = I2C_getData(obj->i2cHandle);
   
    WaitTimeOut = 0;
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop
            && (WaitTimeOut < 0x1fff))
    {
       if(++WaitTimeOut > 0x1ffe)
       {
          obj->RxTimeOut = true;
          return 0;
       }

    }

    return pcaData;

}

//void PCA955x_setStatus(PCA955x_Handle handle, PCA955x_StatusFlag_e status)
//{
//
//
//
//
//
//}
//
//void PCA955x_getStatus(PCA955x_Handle handle)
//{
//
//
//
//
//}

void PCA955x_Configure(PCA955x_Handle handle, PCA955x_PortNum_e PortNum, uint16_t Config)
{

  PCA955x_RegName_e pcaRegName;
  if(PortNum == PCA955x_PortNum_Port0)
    pcaRegName = PCA955x_RegName_Port0_Config;
  else
    pcaRegName = PCA955x_RegName_Port1_Config;

  PCA955x_WrData(handle, pcaRegName, Config);

  return;
}

void PCA955x_WriteCommand(PCA955x_Handle handle, PCA955x_PortNum_e PortNum, uint16_t Command)
{
  PCA955x_RegName_e pcaRegName;
  
  if(PortNum == PCA955x_PortNum_Port0)
    pcaRegName = PCA955x_RegName_Port0_OUT;
  else
    pcaRegName = PCA955x_RegName_Port1_OUT;

  PCA955x_WrData(handle, pcaRegName, Command);

  return;
}

uint16_t PCA955x_ReadStatus(PCA955x_Handle handle, PCA955x_PortNum_e PortNum)
{
  
  PCA955x_RegName_e pcaRegName;
  uint16_t pcaRegData;

  if(PortNum == PCA955x_PortNum_Port0)
    pcaRegName = PCA955x_RegName_Port0_IN;
  else
    pcaRegName = PCA955x_RegName_Port1_IN;

  pcaRegData = PCA955x_RdData(handle, pcaRegName);

  return pcaRegData;

}



