//----------------------------------------------------------
//----------------------------------------------------------
#include <stdlib.h>
#include "sw/drivers/drvic/oled/oled.h"
#include "sw/drivers/drvic/oled/oledfont.h"



void Write_OLED(OLED_Handle handle, uint16_t OLED_Data)
{
  OLED_Obj *obj = (OLED_Obj *)handle;
  static volatile uint16_t WaitTimeOut;
  // Check if bus busy
  while(I2C_isMasterBusy(obj->i2cHandle))
     I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);


  // Setup slave address
  I2C_setMasterSlaveAddr(obj->i2cHandle, OLED_Slave_Address);
  I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x02);
  I2C_enable(obj->i2cHandle);

  // Send register address
  if(obj->TxType == OLED_CMD)
     I2C_putData(obj->i2cHandle, 0x00);
  else
     I2C_putData(obj->i2cHandle, 0x40);

  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy
    && (WaitTimeOut < 0xffff))
  {
     if(++WaitTimeOut > 0xfffe)
       obj->TxTimeOut = true;
   //  return;
  }

  // Setup data to send
  I2C_putData(obj->i2cHandle, OLED_Data);
  
  // Wait The data Transmit
  WaitTimeOut = 0;
  while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop
    && (WaitTimeOut < 0xffff))
  {
     if(++WaitTimeOut > 0xfffe)
       obj->TxTimeOut = true;
   //  return;
  }

  return;
}

void OLED_WrData(OLED_Handle handle, uint16_t oledData)
{
   OLED_Obj *obj = (OLED_Obj *)handle;

   obj->TxType = OLED_DATA;
   Write_OLED(handle, oledData);
   // if timeout retry again
   if(obj->TxTimeOut == true)
   {
     OLED_resetTxTimeout(handle);
     Write_OLED(handle, oledData);
   }
   
   return;
}

void OLED_WrCmd(OLED_Handle handle, uint16_t oledCmd)
{
   OLED_Obj *obj = (OLED_Obj *)handle;

   obj->TxType = OLED_CMD;
   Write_OLED(handle, oledCmd);
   // if timeout retry again
   if(obj->TxTimeOut == true)
   {
     OLED_resetTxTimeout(handle);
     Write_OLED(handle, oledCmd);
   }

   return;
}



/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
  unsigned int m;
  for(;Del_50ms>0;Del_50ms--)
    for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
  unsigned char j;
  while(Del_1ms--)
  {
    for(j=0;j<5;j++);
  }
}


void OLED_RegInit(OLED_Handle handle)
{   
 
  Delay_50ms(200);

  OLED_WrCmd(handle,0xAE);//--display off
  OLED_WrCmd(handle,0x00);//---set low column address
  OLED_WrCmd(handle,0x10);//---set high column address
  OLED_WrCmd(handle,0x40);//--set start line address  
  OLED_WrCmd(handle,0xB0);//--set page address
  OLED_WrCmd(handle,0x81); // contract control
  OLED_WrCmd(handle,0xFF);//--128   

  OLED_WrCmd(handle,0xA1);//set segment remap 

  OLED_WrCmd(handle,0xA6);//--normal / reverse

  OLED_WrCmd(handle,0xA8);//--set multiplex ratio(1 to 64)
  OLED_WrCmd(handle,0x3F);//--1/32 duty

  OLED_WrCmd(handle,0xC8);//Com scan direction

  OLED_WrCmd(handle,0xD3);//-set display offset
  OLED_WrCmd(handle,0x00);//
  OLED_WrCmd(handle,0xD5);//set osc division
  OLED_WrCmd(handle,0x80);//
  OLED_WrCmd(handle,0xD8);//set area color mode off
  OLED_WrCmd(handle,0x05);//
  OLED_WrCmd(handle,0xD9);//Set Pre-Charge Period
  OLED_WrCmd(handle,0xF1);//
  OLED_WrCmd(handle,0xDA);//set com pin configuartion
  OLED_WrCmd(handle,0x12);//
  OLED_WrCmd(handle,0xDB);//set Vcomh
  OLED_WrCmd(handle,0x30);//
  OLED_WrCmd(handle,0x8D);//set charge pump enable
  OLED_WrCmd(handle,0x14);//
  OLED_WrCmd(handle,0xAF);//--turn on oled panel

}  

void OLED_setI2cHandle(OLED_Handle handle, I2C_Handle i2cHandle)
{
  OLED_Obj *obj = (OLED_Obj *)handle;
  
  obj->i2cHandle = i2cHandle;

  return;
}

OLED_Handle OLED_Init(void *pMemory,const size_t numBytes)
{
  OLED_Handle handle;
  if(numBytes < sizeof(OLED_Obj))
    return((OLED_Handle)NULL);
  handle = (OLED_Handle)pMemory;

  OLED_resetTxTimeout(handle); 

  return(handle);

}

void OLED_Clear(OLED_Handle handle)  
{  
  uint16_t i,n;        

  for(i=0;i<8;i++)  
  {  
    OLED_WrCmd(handle,0xb0+i);
    OLED_WrCmd(handle,0x00);
    OLED_WrCmd(handle,0x10);
    for(n=0;n<128;n++)
      OLED_WrData(handle,0x00); 
  }
   return;  
}

void OLED_AllShow(OLED_Handle handle)  
{  
  uint16_t i,n;
  for(i=0;i<8;i++)  
  {  
    OLED_WrCmd(handle,0xb0+i);
    OLED_WrCmd(handle,0x00);  
    OLED_WrCmd(handle,0x10);  
      for(n=0;n<128;n++)
    OLED_WrData(handle,0xff);
  } 
}

void OLED_setPos(OLED_Handle handle, uint16_t x, uint16_t y)
{
  OLED_Obj *obj = (OLED_Obj *)handle;
  
  if(x > Max_Column-1)
    {
      x=0;
      y=y+2;
    }

  obj->OledPos.Xpos = x;
  obj->OledPos.Ypos = y;

  return;
}       


void OLED_Display_On(OLED_Handle handle)
{
  OLED_WrCmd(handle,0X8D);  //SET DCDC
  OLED_WrCmd(handle,0X14);  //DCDC ON
  OLED_WrCmd(handle,0XAF);  //DISPLAY ON
}

void OLED_Display_Off(OLED_Handle handle)
{
  OLED_WrCmd(handle,0X8D);  //SET DCDC
  OLED_WrCmd(handle,0X10);  //DCDC OFF
  OLED_WrCmd(handle,0XAE);  //DISPLAY OFF
}              

//void OLED_SettingCmd(OLED_Handle handle, OLED_SetCmd_e SettingCmd)
//{
//  OLED_Obj *obj = (OLED_Obj *)handle;
//
//  
//
//}

void OLED_PositionSetup(OLED_Handle handle)
{
  OLED_Obj *obj = (OLED_Obj *)handle;
  uint16_t Pos_XCmd,Pos_Ycmd;

  Pos_Ycmd = 0xb0 + obj->OledPos.Ypos;
  Pos_XCmd = obj->OledPos.Xpos;

  OLED_WrCmd(handle, Pos_Ycmd);
  OLED_WrCmd(handle,((Pos_XCmd & 0xf0)>>4)|0x10);
  OLED_WrCmd(handle,(Pos_XCmd & 0x0f ));
  return;
}


OLED_Pos_t OLED_getPos(OLED_Handle handle)
{
  OLED_Obj *obj = (OLED_Obj *)handle;
  OLED_Pos_t DrawPos;

  DrawPos.Ypos = obj->OledPos.Ypos;
  DrawPos.Xpos = obj->OledPos.Xpos;

  return (DrawPos);
}

void OLED_ShowChar(OLED_Handle handle, OLED_FontSize_e FontSize, uchar DisChr)
{     
  OLED_Obj *obj = (OLED_Obj *)handle;  
  uint16_t i=0;
  uchar c;

  c = DisChr - ' ';
  
  if(FontSize == OLED_FontSize_16)
    {
      OLED_PositionSetup(handle);  
      for(i=0;i<8;i++)
        OLED_WrData(handle,F8X16[c*16+i]);

      obj->OledPos.Ypos += 1;
      OLED_PositionSetup(handle);
      for(i=0;i<8;i++)
        OLED_WrData(handle,F8X16[c*16+i+8]);
      obj->OledPos.Ypos -= 1;
    }
    else
    {

      OLED_PositionSetup(handle);
      for(i=0;i<6;i++)
        OLED_WrData(handle,F6x8[c][i]);
      
    }
}


void OLED_ShowString(OLED_Handle handle, OLED_FontSize_e FontSize, uchar *DispString)
{
  uint16_t j=0;
  OLED_Pos_t ShiftPos;

  while(DispString[j]!='\0')
  {
    OLED_ShowChar(handle, FontSize, DispString[j]);
    ShiftPos = OLED_getPos(handle);
    ShiftPos.Xpos += 8;
    if(ShiftPos.Xpos > 120)
    {
      ShiftPos.Xpos=0;
      ShiftPos.Ypos += 2;
    }
    OLED_setPos(handle, ShiftPos.Xpos, ShiftPos.Ypos);
    j++;
  }
}

inline uint32_t oled_pow(uint16_t m,uint16_t n)
{
  uint32_t result=1;
  while(n--)
    result*=m;
  return result;
}


void OLED_ShowNum(OLED_Handle handle,OLED_FontSize_e FontSize,uint32_t num,uint16_t len)
{           
  uint16_t t,temp;
  OLED_Pos_t ShiftPos;

  ShiftPos = OLED_getPos(handle);
  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    OLED_setPos(handle,ShiftPos.Xpos,ShiftPos.Ypos);

    if(FontSize == OLED_FontSize_12)
      ShiftPos.Xpos += 6;
    else
      ShiftPos.Xpos += 8;

    OLED_ShowChar(handle,FontSize,temp+'0'); 
  }

  return;
} 

























