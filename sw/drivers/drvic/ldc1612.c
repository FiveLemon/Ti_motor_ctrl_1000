
#include <math.h>


// drivers
#include "sw/drivers/drvic/ldc1612.h"



// **************************************************************************
// the function prototypes
//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeI2c(LDC161x_Handle handle, const LDC161x_RegName_e regName,const uint16_t data)
{
   LDC161x_Obj *obj = (LDC161x_Obj *)handle;
   uint16_t     WriteWord;
   static volatile uint16_t WaitTimeOut;

   while(I2C_isMasterBusy(obj->i2cHandle))
       I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);

   if(obj->RxTimeOut == true || obj->TxTimeOut == true) 
   {
      return;
   }

   //Send slave Address
   I2C_setMasterSlaveAddr(obj->i2cHandle, (uint16_t)(obj->ldc161x.LdcSerial));
   I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x03);
   I2C_enable(obj->i2cHandle);

   // Send register address
   I2C_putData(obj->i2cHandle, regName);

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

   WriteWord = data >> 8;
   I2C_putData(obj->i2cHandle, WriteWord);

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
  
   WriteWord = data & 0x00ff;
   I2C_putData(obj->i2cHandle, WriteWord);
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

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
uint16_t LDC161x_readI2c(LDC161x_Handle handle,const LDC161x_RegName_e regName)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  static volatile uint16_t WaitTimeOut;
  volatile uint16_t readWord;

  while(I2C_isMasterBusy(obj->i2cHandle))
    I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);  

   if(obj->RxTimeOut == true || obj->TxTimeOut == true) 
   {
      return ((uint16_t)NULL);
   }

  I2C_setMasterSlaveAddr(obj->i2cHandle, obj->ldc161x.LdcSerial);
  I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x01);
  I2C_enable(obj->i2cHandle);
  I2C_putData(obj->i2cHandle, regName);
  
  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy
           && (WaitTimeOut < 0x1fff))
   {
       if(++WaitTimeOut > 0x1ffe)
       {
         obj->TxTimeOut = true;
         return ((uint16_t)NULL);
       }
   }
  
  WaitTimeOut = 0;
  while(I2C_isMasterBusy(obj->i2cHandle)
           && (WaitTimeOut < 0x1fff))
   {
       if(++WaitTimeOut > 0x1ffe)
       {
         obj->TxTimeOut = true;
         return ((uint16_t)NULL);
       }
   }

  I2C_setMasterSlaveAddr(obj->i2cHandle, obj->ldc161x.LdcSerial);
  I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_RX, I2C_BitCount_8_Bits,0x02);
  I2C_enable(obj->i2cHandle);

  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Rx_Rdy) != I2C_Status_Rx_Rdy
           && (WaitTimeOut < 0x1fff))
   {
       if(++WaitTimeOut > 0x1ffe)
       {
         obj->RxTimeOut = true;
         return ((uint16_t)NULL);
       }
   }

  readWord = I2C_getData(obj->i2cHandle);
  readWord <<= 8;

  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Rx_Rdy) != I2C_Status_Rx_Rdy
           && (WaitTimeOut < 0x1fff))
   {
       if(++WaitTimeOut > 0x1ffe)
       {
         obj->RxTimeOut = true;
         return  ((uint16_t)NULL);
       }
   }

  readWord |= I2C_getData(obj->i2cHandle);

  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop
           && (WaitTimeOut < 0x1fff))
   {
       if(++WaitTimeOut > 0x1ffe)
       {
         obj->RxTimeOut = true;
         return  ((uint16_t)NULL);
       }
   }

  return readWord;

} // end of the LDC161x_readI2c() functions



//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readChData(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName1;
  LDC161x_RegName_e  drvRegName2;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName1 = LDC161x_RegName_Ch0DataLSB;
        drvRegName2 = LDC161x_RegName_Ch0DataMSB;
        ChNum = 0x00;                   
    break;
    case LDC161x_ChNum_CH1: drvRegName1 = LDC161x_RegName_Ch1DataLSB;
        drvRegName2 = LDC161x_RegName_Ch1DataMSB;
        ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName1 = LDC161x_RegName_Ch2DataLSB;
        drvRegName2 = LDC161x_RegName_Ch2DataMSB;
        ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName1 = LDC161x_RegName_Ch3DataLSB;
        drvRegName2 = LDC161x_RegName_Ch3DataMSB;
        ChNum = 0x03;                   
      break;
    default: break;
  }

  drvDataNew = LDC161x_readI2c(handle,drvRegName1);
  LDC161x_setChData_LSB(obj->ldcHandle, ChNum, drvDataNew);
  drvDataNew = LDC161x_readI2c(handle,drvRegName2);
  LDC161x_setChData_MSB(obj->ldcHandle, ChNum, drvDataNew);

  return;
} // end of the LDC161x_readChData() functions


//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readRcount(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0Rcount;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1Rcount;
                            ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2Rcount;
                            ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3Rcount;
                            ChNum = 0x03;                   
      break;
    default: break;
  }

  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setRcount(obj->ldcHandle, ChNum, drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readOffset(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0Offset;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1Offset;
                            ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2Offset;
                            ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3Offset;
                            ChNum = 0x03;                   
      break;
    default: break;
  }

  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setOffset(obj->ldcHandle, ChNum, drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readSettleCnt(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0SettleCnt;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1SettleCnt;
                            ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2SettleCnt;
                            ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3SettleCnt;
                            ChNum = 0x03;                   
      break;
    default: break;
  }

  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setSettleCnt(obj->ldcHandle, ChNum, drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readClkDivs(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0ClkDiv;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1ClkDiv;
                            ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2ClkDiv;
                            ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3ClkDiv;
                            ChNum = 0x03;                   
      break;
    default: break;
  }

  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setClkDivs(obj->ldcHandle, ChNum, drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readStatus(LDC161x_Handle handle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  
  drvRegName = LDC161x_RegName_STATUS;
  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setStatus(obj->ldcHandle,drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readErrors(LDC161x_Handle handle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;
  
  drvRegName = LDC161x_RegName_ERROR_CONFIG;
  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setErrors(obj->ldcHandle,drvDataNew);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_readConfig(LDC161x_Handle handle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataNew;
  LDC161x_RegName_e  drvRegName;

  drvRegName = LDC161x_RegName_CONFIG;
  drvDataNew = LDC161x_readI2c(handle,drvRegName);
  LDC161x_setConfig(obj->ldcHandle,drvDataNew);
  
  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeRcount(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0Rcount;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1Rcount;
                            ChNum = 0x01;                   
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2Rcount;
                            ChNum = 0x02;                   
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3Rcount;
                            ChNum = 0x03;                   
      break;
    default: break;
  }
  
  LDC161x_getRcount(obj->ldcHandle, ChNum, &drvDataGet);
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);
  
  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeOffset(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0Offset;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1Offset;
                            ChNum = 0x01;                  
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2Offset;
                            ChNum = 0x02;                 
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3Offset;
                            ChNum = 0x03;                   
      break;
    default: break;
  }
  
  LDC161x_getOffset(obj->ldcHandle, ChNum, &drvDataGet);
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);
  
  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeSettleCnt(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0SettleCnt;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1SettleCnt;
                            ChNum = 0x01;                  
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2SettleCnt;
                            ChNum = 0x02;                 
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3SettleCnt;
                            ChNum = 0x03;                   
      break;
    default: break;
  }
  
  LDC161x_getSettleCnt(obj->ldcHandle, ChNum, &drvDataGet);
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);
  
  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeClkDivs(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;
  uint16_t ChNum;
  
  switch(ChannelNum)
  {
    case LDC161x_ChNum_CH0: drvRegName = LDC161x_RegName_Ch0ClkDiv;
                            ChNum = 0x00;                   
      break;
    case LDC161x_ChNum_CH1: drvRegName = LDC161x_RegName_Ch1ClkDiv;
                            ChNum = 0x01;                  
      break;
    case LDC161x_ChNum_CH2: drvRegName = LDC161x_RegName_Ch2ClkDiv;
                            ChNum = 0x02;                 
      break;
    case LDC161x_ChNum_CH3: drvRegName = LDC161x_RegName_Ch3ClkDiv;
                            ChNum = 0x03;                   
      break;
    default: break;
  }
  
  LDC161x_getClkDivs(obj->ldcHandle, ChNum, &drvDataGet);
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);
  
  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeConfig(LDC161x_Handle handle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;

  drvRegName = LDC161x_RegName_CONFIG;
  LDC161x_getConfig(obj->ldcHandle, &drvDataGet);
  drvDataGet |= 0x0001;
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_writeMuxConfig(LDC161x_Handle handle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;
  uint16_t drvDataGet;
  LDC161x_RegName_e  drvRegName;

  drvRegName = LDC161x_RegName_MUX_CONFIG;
  LDC161x_getConfig(obj->ldcHandle, &drvDataGet);
  drvDataGet |= 0x0208;
  LDC161x_writeI2c(handle, drvRegName, drvDataGet);

  return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_ResetSensor(LDC161x_Handle handle)
{
  // LDC161x_Obj *obj = (LDC161x_Obj *)handle;
   uint16_t drvDataGet; 
   LDC161x_RegName_e  drvRegName;
   
   drvRegName = LDC161x_RegName_RESET_DEV; 
   drvDataGet = LDC161x_RESET_MASK;
   LDC161x_writeI2c(handle,  drvRegName, drvDataGet); 

   return;
}

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setChData_MSB(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  switch(Channel)
  {
  case 0:
      obj->LdcChData.CH0_DATA.MSB.ERR_UR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_UR_BIT);
      obj->LdcChData.CH0_DATA.MSB.ERR_OR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_OR_BIT);
      obj->LdcChData.CH0_DATA.MSB.ERR_WD = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_WD_BIT);
      obj->LdcChData.CH0_DATA.MSB.ERR_AE = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_AE_BIT);
      obj->LdcChData.CH0_DATA.MSB.DAT_MB = LDC161x_DATA_MASK & drvData;
    break;
  case 1:
      obj->LdcChData.CH1_DATA.MSB.ERR_UR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_UR_BIT);
      obj->LdcChData.CH1_DATA.MSB.ERR_OR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_OR_BIT);
      obj->LdcChData.CH1_DATA.MSB.ERR_WD = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_WD_BIT);
      obj->LdcChData.CH1_DATA.MSB.ERR_AE = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_AE_BIT);
      obj->LdcChData.CH1_DATA.MSB.DAT_MB = LDC161x_DATA_MASK & drvData;
    break;
  case 2:
      obj->LdcChData.CH2_DATA.MSB.ERR_UR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_UR_BIT);
      obj->LdcChData.CH2_DATA.MSB.ERR_OR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_OR_BIT);
      obj->LdcChData.CH2_DATA.MSB.ERR_WD = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_WD_BIT);
      obj->LdcChData.CH2_DATA.MSB.ERR_AE = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_AE_BIT);
      obj->LdcChData.CH2_DATA.MSB.DAT_MB = LDC161x_DATA_MASK & drvData;
    break;
  case 3:
      obj->LdcChData.CH3_DATA.MSB.ERR_UR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_UR_BIT);
      obj->LdcChData.CH3_DATA.MSB.ERR_OR = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_OR_BIT);
      obj->LdcChData.CH3_DATA.MSB.ERR_WD = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_WD_BIT);
      obj->LdcChData.CH3_DATA.MSB.ERR_AE = (bool)(drvData & (uint16_t)LDC161x_DataFlag_ERR_AE_BIT);
      obj->LdcChData.CH3_DATA.MSB.DAT_MB = LDC161x_DATA_MASK & drvData;
    break;
  default: break;

  }

 return;   
} //end of the LDC161x_setChData_MSB() functions


//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setChData_LSB(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  switch(Channel)
  {
    case 0:  obj->LdcChData.CH0_DATA.LSB = drvData;   break;
    case 1:  obj->LdcChData.CH1_DATA.LSB = drvData;   break;
    case 2:  obj->LdcChData.CH2_DATA.LSB = drvData;   break;
    case 3:  obj->LdcChData.CH3_DATA.LSB = drvData;   break;
  default: break;
  }
  return;
} // end of the LDC161x_setChData_LSB() functions

//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setRcount(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  switch(Channel)
  {
    case 0:  obj->LdcRcount.RCOUNT_CH0 = drvData; break;
    case 1:  obj->LdcRcount.RCOUNT_CH1 = drvData; break;
    case 2:  obj->LdcRcount.RCOUNT_CH2 = drvData; break;
    case 3:  obj->LdcRcount.RCOUNT_CH3 = drvData; break;
    default: break;
  }
  return;
} // end of the LDC161x_setRcount() functions


//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setOffset(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  switch(Channel)
  {
    case 0:  obj->LdcOffset.OFFSET_CH0 = drvData; break;
    case 1:  obj->LdcOffset.OFFSET_CH1 = drvData; break;
    case 2:  obj->LdcOffset.OFFSET_CH2 = drvData; break;
    case 3:  obj->LdcOffset.OFFSET_CH3 = drvData; break;
    default: break;
  }
  return;
} // end of the LDC161x_setRcount() functions


//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setSettleCnt(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  switch(Channel)
  {
    case 0:  obj->LdcSettleCnt.SETTLECOUNT_CH0 = drvData; break;
    case 1:  obj->LdcSettleCnt.SETTLECOUNT_CH1 = drvData; break;
    case 2:  obj->LdcSettleCnt.SETTLECOUNT_CH2 = drvData; break;
    case 3:  obj->LdcSettleCnt.SETTLECOUNT_CH3 = drvData; break;
    default: break;
  }
  return;
} // end of the LDC161x_setRcount() functions


//
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void LDC161x_setClkDivs(LDC_Handle handle,const uint16_t Channel, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  switch(Channel)
  {
    case 0:  
         obj->LdcClkDiv.CLK_DIVS_CH0.FREF_DIVIDER = (drvData & LDC161x_FREF_DIV_MASK);
         obj->LdcClkDiv.CLK_DIVS_CH0.FIN_DIVIDER = (drvData & LDC161x_FIN_DIV_MASK)>>12;  
       break;
    case 1:
         obj->LdcClkDiv.CLK_DIVS_CH1.FREF_DIVIDER = (drvData & LDC161x_FREF_DIV_MASK);
         obj->LdcClkDiv.CLK_DIVS_CH1.FIN_DIVIDER = (drvData & LDC161x_FIN_DIV_MASK)>>12;
       break;
    case 2:
         obj->LdcClkDiv.CLK_DIVS_CH2.FREF_DIVIDER = (drvData & LDC161x_FREF_DIV_MASK);
         obj->LdcClkDiv.CLK_DIVS_CH2.FIN_DIVIDER = (drvData & LDC161x_FIN_DIV_MASK)>>12;
       break;
    case 3:
         obj->LdcClkDiv.CLK_DIVS_CH3.FREF_DIVIDER = (drvData & LDC161x_FREF_DIV_MASK);
         obj->LdcClkDiv.CLK_DIVS_CH3.FIN_DIVIDER = (drvData & LDC161x_FIN_DIV_MASK)>>12;
       break;
  default: break;
  }
  return;
} // end of the LDC161x_setRcount() functions

void LDC161x_setStatus(LDC_Handle handle,uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

  obj->LdcStatus.UNRDCONV_CH3 = (bool)(drvData & (uint16_t)(LDC161x_StatusType_CH3_UNRDCONV));
  obj->LdcStatus.UNRDCONV_CH2 = (bool)(drvData & (uint16_t)(LDC161x_StatusType_CH2_UNRDCONV));
  obj->LdcStatus.UNRDCONV_CH1 = (bool)(drvData & (uint16_t)(LDC161x_StatusType_CH1_UNRDCONV));
  obj->LdcStatus.UNRDCONV_CH0 = (bool)(drvData & (uint16_t)(LDC161x_StatusType_CH0_UNRDCONV));
  obj->LdcStatus.DRDY         = (bool)(drvData & (uint16_t)(LDC161x_StatusType_DRDY));
  obj->LdcStatus.ERR_ZC       = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_ZC));
  obj->LdcStatus.ERR_ALE      = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_ALE));
  obj->LdcStatus.ERR_AHE      = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_AHE));
  obj->LdcStatus.ERR_WD       = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_WD));
  obj->LdcStatus.ERR_OR       = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_OR));
  obj->LdcStatus.ERR_UR       = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_UR));
  obj->LdcStatus.ERR_CHAN_0   = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_CHAN0));
  obj->LdcStatus.ERR_CHAN_1   = (bool)(drvData & (uint16_t)(LDC161x_StatusType_ERR_CHAN1));

  return;
}

void LDC161x_setErrors(LDC_Handle handle,uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  
  obj->LdcError.UR_ERR2OUT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_UR_ERR2OUT));
  obj->LdcError.OR_ERR2OUT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_OR_ERR2OUT));
  obj->LdcError.WD_ERR2OUT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_WD_ERR2OUT));
  obj->LdcError.AH_ERR2OUT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_AH_ERR2OUT));
  obj->LdcError.AL_ERR2OUT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_AL_ERR2OUT));
  obj->LdcError.UR_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_UR_ERR2INT));
  obj->LdcError.OR_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_OR_ERR2INT));
  obj->LdcError.WD_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_WD_ERR2INT));
  obj->LdcError.AH_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_AH_ERR2INT));
  obj->LdcError.AL_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_FAL_ERR2IN));
  obj->LdcError.ZC_ERR2INT = (bool)(drvData & (uint16_t)(LDC161x_FaultType_ZC_ERR2INT));
  obj->LdcError.DRDY_2INT  = (bool)(drvData & (uint16_t)(LDC161x_FaultType_DRDY_2INT));

  return;
}

void LDC161x_setConfig(LDC_Handle handle, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  
  obj->LdcConfig.ACTIVE_CHAN_0    = (bool)(drvData & (uint16_t)(LDC161x_Config_ACTIVE_CHAN_0));
  obj->LdcConfig.ACTIVE_CHAN_1    = (bool)(drvData & (uint16_t)(LDC161x_Config_ACTIVE_CHAN_1));
  obj->LdcConfig.SLEEP_MODE_EN    = (bool)(drvData & (uint16_t)(LDC161x_Config_SLEEP_MODE_EN));
  obj->LdcConfig.RP_OVERRIDE_EN   = (bool)(drvData & (uint16_t)(LDC161x_Config_RP_OVERRIDE_EN));
  obj->LdcConfig.SENSOR_ACTV_SEL  = (bool)(drvData & (uint16_t)(LDC161x_Config_SENSOR_ACTV_SEL));
  obj->LdcConfig.AUTO_AMP_DIS     = (bool)(drvData & (uint16_t)(LDC161x_Config_AUTO_AMP_DIS));
  obj->LdcConfig.REF_CLK_SRC      = (bool)(drvData & (uint16_t)(LDC161x_Config_REF_CLK_SRC));
  obj->LdcConfig.INTB_DIS         = (bool)(drvData & (uint16_t)(LDC161x_Config_INTB_DIS));
  obj->LdcConfig.HIGH_CURRENT_DRV = (bool)(drvData & (uint16_t)(LDC161x_Config_HIGH_CURRENT_DRV));

  return;
}

void LDC161x_setMuxConfig(LDC_Handle handle, uint16_t drvData)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
 
  obj->LdcMuxConf.AUTOSCAN_EN = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_AUTOSCAN_EN)); 
  obj->LdcMuxConf.RR_SEQUENCE_0 = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_RR_SEQUENCE_0));
  obj->LdcMuxConf.RR_SEQUENCE_1 = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_RR_SEQUENCE_1));
  obj->LdcMuxConf.DEGLITCH_0 = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_DEGLITCH_0));
  obj->LdcMuxConf.DEGLITCH_1 = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_DEGLITCH_1));
  obj->LdcMuxConf.DEGLITCH_2 = (bool)(drvData & (uint16_t)(LDC161x_MuxConfig_DEGLITCH_2));

  return;
}

void LDC161x_getMuxConfig(LDC_Handle handle, uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;
  if(obj->LdcMuxConf.AUTOSCAN_EN)
    drvData |= (uint16_t)(LDC161x_MuxConfig_AUTOSCAN_EN);
  if(obj->LdcMuxConf.RR_SEQUENCE_0)
    drvData |= (uint16_t)(LDC161x_MuxConfig_RR_SEQUENCE_0);
  if(obj->LdcMuxConf.RR_SEQUENCE_1)
    drvData |= (uint16_t)(LDC161x_MuxConfig_RR_SEQUENCE_1);
  if(obj->LdcMuxConf.DEGLITCH_0)
    drvData |= (uint16_t)(LDC161x_MuxConfig_DEGLITCH_0);
  if(obj->LdcMuxConf.DEGLITCH_1)
    drvData |= (uint16_t)(LDC161x_MuxConfig_DEGLITCH_1);
  if(obj->LdcMuxConf.DEGLITCH_2)
    drvData |= (uint16_t)(LDC161x_MuxConfig_DEGLITCH_2);
  
  *drvDataGet = drvData;

  return;
}

void LDC161x_getConfig(LDC_Handle handle,uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;
  if(obj->LdcConfig.ACTIVE_CHAN_0)
    drvData |= (uint16_t)(LDC161x_Config_ACTIVE_CHAN_0);
  if(obj->LdcConfig.ACTIVE_CHAN_1)
    drvData |= (uint16_t)(LDC161x_Config_ACTIVE_CHAN_1);
  if(obj->LdcConfig.SLEEP_MODE_EN)
    drvData |= (uint16_t)(LDC161x_Config_SLEEP_MODE_EN);
  if(obj->LdcConfig.RP_OVERRIDE_EN)
    drvData |= (uint16_t)(LDC161x_Config_RP_OVERRIDE_EN);
  if(obj->LdcConfig.SENSOR_ACTV_SEL)
    drvData |= (uint16_t)(LDC161x_Config_SENSOR_ACTV_SEL);
  if(obj->LdcConfig.AUTO_AMP_DIS)
    drvData |= (uint16_t)(LDC161x_Config_AUTO_AMP_DIS);
  if(obj->LdcConfig.REF_CLK_SRC)
    drvData |= (uint16_t)(LDC161x_Config_REF_CLK_SRC);
  if(obj->LdcConfig.INTB_DIS)
    drvData |= (uint16_t)(LDC161x_Config_INTB_DIS);
  if(obj->LdcConfig.HIGH_CURRENT_DRV)
    drvData |= (uint16_t)(LDC161x_Config_HIGH_CURRENT_DRV);

  *drvDataGet = drvData; 
  
  return;
}

void LDC161x_getChData(LDC_Handle handle,const LDC161x_ChNum_e ChNum,uint32_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  struct Data{
    uint16_t  LSB;
    uint16_t  MSB;
  };
  union data_u
  {
    struct Data    Data_t;
    uint32_t       Data_u32;
  }drvData;
  drvData.Data_u32 = 0x00000000;

  switch(ChNum)
  {
    case LDC161x_ChNum_CH0:
            drvData.Data_t.MSB |= (obj->LdcChData.CH0_DATA.MSB.DAT_MB);
            drvData.Data_t.LSB |=  obj->LdcChData.CH0_DATA.LSB;
            break;
    case LDC161x_ChNum_CH1:
            drvData.Data_t.MSB |= (obj->LdcChData.CH1_DATA.MSB.DAT_MB);
            drvData.Data_t.LSB |=  obj->LdcChData.CH1_DATA.LSB;
            break;
    case LDC161x_ChNum_CH2:
            drvData.Data_t.MSB |= (obj->LdcChData.CH2_DATA.MSB.DAT_MB);
            drvData.Data_t.LSB |=  obj->LdcChData.CH2_DATA.LSB;         
            break;
    case LDC161x_ChNum_CH3:
            drvData.Data_t.MSB |= (obj->LdcChData.CH3_DATA.MSB.DAT_MB);
            drvData.Data_t.LSB |=  obj->LdcChData.CH3_DATA.LSB;
            break;
    default: break;
  }
  
  *drvDataGet = drvData.Data_u32;

  return;
}


void LDC161x_getRcount(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;

  switch(Channel)
  {
    case 0: drvData = obj->LdcRcount.RCOUNT_CH0; break;
    case 1: drvData = obj->LdcRcount.RCOUNT_CH1; break;
    case 2: drvData = obj->LdcRcount.RCOUNT_CH2; break;
    case 3: drvData = obj->LdcRcount.RCOUNT_CH3; break;
    default: break;
  }
  
  *drvDataGet = drvData;

  return;
}

void LDC161x_getOffset(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;

  switch(Channel)
  {
    case 0: drvData = obj->LdcOffset.OFFSET_CH0; break;
    case 1: drvData = obj->LdcOffset.OFFSET_CH1; break;
    case 2: drvData = obj->LdcOffset.OFFSET_CH2; break;
    case 3: drvData = obj->LdcOffset.OFFSET_CH3; break;
    default: break;
  }
  
  *drvDataGet = drvData;

  return;
}

void LDC161x_getSettleCnt(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;

  switch(Channel)
  {
    case 0: drvData = obj->LdcSettleCnt.SETTLECOUNT_CH0; break;
    case 1: drvData = obj->LdcSettleCnt.SETTLECOUNT_CH1; break;
    case 2: drvData = obj->LdcSettleCnt.SETTLECOUNT_CH2; break;
    case 3: drvData = obj->LdcSettleCnt.SETTLECOUNT_CH3; break;
    default: break;
  }
  
  *drvDataGet = drvData;

  return;
}

void LDC161x_getClkDivs(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  uint16_t drvData = 0x0000;

  switch(Channel)
  {
    case 0: drvData = obj->LdcClkDiv.CLK_DIVS_CH0.FREF_DIVIDER
                   | (obj->LdcClkDiv.CLK_DIVS_CH0.FIN_DIVIDER << 12);
    break;
    case 1: drvData = obj->LdcClkDiv.CLK_DIVS_CH1.FREF_DIVIDER
                   | (obj->LdcClkDiv.CLK_DIVS_CH1.FIN_DIVIDER << 12);
    break;
    case 2: drvData = obj->LdcClkDiv.CLK_DIVS_CH2.FREF_DIVIDER
                   | (obj->LdcClkDiv.CLK_DIVS_CH2.FIN_DIVIDER << 12);
    break;
    case 3: drvData = obj->LdcClkDiv.CLK_DIVS_CH3.FREF_DIVIDER
                   | (obj->LdcClkDiv.CLK_DIVS_CH3.FIN_DIVIDER << 12);
    break;
    default: break;
  }
  
  *drvDataGet = drvData;

  return;
}

void LDC161x_ReFilter(LDC161x_Handle handle,const LDC161x_ChNum_e ChNum,uint32_t *drvDataGet)
{
    LDC161x_Obj *obj = (LDC161x_Obj *)handle;
    uint32_t   DataTmp;
    static uint32_t   Avage = 0x04000000;
    static uint32_t   Sum = 0x40000000;
    
    if(obj->RxTimeOut == true) 
    {
       LDC161x_resetRxTimeout(handle);
       DataTmp = Avage;
    }
    else if(obj->RxTimeOut == true)
    {
       LDC161x_resetTxTimeout(handle);
       DataTmp = Avage;
    }
    else
    {
      LDC161x_getChData(handle->ldcHandle,ChNum, &DataTmp);
    }

    Sum += DataTmp;
    Sum -= Avage;
    Avage = Sum >> 4;
    
    *drvDataGet = Avage;

    return;
}

void LDC161x_KalmanFilter(LDC161x_Handle handle,const LDC161x_ChNum_e ChNum,uint32_t *drvDataGet)
{
    LDC161x_Obj *obj = (LDC161x_Obj *)handle;
    
    uint32_t DataTmp;
    uint32_t x_Mid;
    uint32_t p_Mid;
    float Kg;

    // get the source data
    if(obj->RxTimeOut == true) 
    {
       LDC161x_resetRxTimeout(handle);
       I2C_unlockBus(handle);
       DataTmp = obj->ldc161x.LdcKalman.data_Last;
    }
    else if(obj->TxTimeOut == true)
    {
       LDC161x_resetTxTimeout(handle);
       I2C_unlockBus(handle);
       DataTmp = obj->ldc161x.LdcKalman.data_Last;
    }
    else
    {
      LDC161x_getChData(handle->ldcHandle,ChNum, &DataTmp);
    }

    x_Mid = obj->ldc161x.LdcKalman.x_Last;
    p_Mid = obj->ldc161x.LdcKalman.p_Last + LDC161x_Kalman_Q;
    
    Kg = (1.0 * p_Mid)/(p_Mid + LDC161x_Kalman_R);
    
    if(DataTmp > x_Mid)
      obj->ldc161x.LdcKalman.x_Last = x_Mid + (uint32_t)(Kg * (DataTmp - x_Mid));
    else
      obj->ldc161x.LdcKalman.x_Last = x_Mid - (uint32_t)(Kg * (x_Mid - DataTmp));

    obj->ldc161x.LdcKalman.p_Last = p_Mid - (uint32_t)(Kg * p_Mid);
    obj->ldc161x.LdcKalman.data_Last = DataTmp;

    *drvDataGet = obj->ldc161x.LdcKalman.x_Last;

    return;
}

void LDC161xReg_ReConfig(LDC161x_Handle handle)
{

  LDC161x_ResetSensor(handle);
  LDC161x_writeRcount(handle,LDC161x_ChNum_CH0);
  LDC161x_writeSettleCnt(handle,LDC161x_ChNum_CH0);
  LDC161x_writeClkDivs(handle,LDC161x_ChNum_CH0);
  LDC161x_writeConfig(handle);
  LDC161x_writeMuxConfig(handle);

  return;
}

void I2C_unlockBus(LDC161x_Handle handle)
{
   LDC161x_Obj *obj = (LDC161x_Obj *)handle;
   uint16_t i;

   GPIO_setMode(obj->gpioHandle,GPIO_Number_33,GPIO_33_Mode_GeneralPurpose);
   GPIO_setDirection(obj->gpioHandle,GPIO_Number_33,GPIO_Direction_Output);
   GPIO_setLow(obj->gpioHandle,GPIO_Number_33);
   for(i=0x00ff;i>0;i--)
   {
     _nop();
   }
   //refuse i2c function in scl pin
   GPIO_setMode(obj->gpioHandle,GPIO_Number_33,GPIO_33_Mode_SCLA);

  return;
}



LDC_Handle LDC161xReg_init(void *pMemory,const size_t numBytes)
{
  LDC_Handle handle;

  if(numBytes < sizeof(LDC161x_REG_Obj))
    return((LDC_Handle)NULL);

  // assign the handle
  handle = (LDC_Handle)pMemory;

  return(handle);
} // end of LDC161xReg_init() functions

void LDC161x_setI2cHandle(LDC161x_Handle handle, I2C_Handle i2cHandle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;

  obj->i2cHandle = i2cHandle;

  return;

}

void LDC161x_setGpioHandle(LDC161x_Handle handle, GPIO_Handle gpioHandle)
{
  LDC161x_Obj *obj = (LDC161x_Obj *)handle;

  obj->gpioHandle = gpioHandle;

  return;

}

LDC161x_Handle LDC1612_init(void *pMemory,const size_t numBytes)
{
  LDC161x_Handle handle;


  if(numBytes < sizeof(LDC161x_Obj))
    return((LDC161x_Handle)NULL);


  // assign the handle
  handle = (LDC161x_Handle)pMemory;
  handle->ldcHandle = LDC161xReg_init(&(handle->ldc161x)
      ,sizeof(LDC161x_REG_Obj));

  LDC161x_resetRxTimeout(handle);
  LDC161x_resetTxTimeout(handle);


  return(handle);
} // end of LDC161X_init() functions


