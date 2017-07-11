//-------------------------------------------------------
//-------------------------------------------------------
#ifndef __OLED_H
#define __OLED_H           
#include "sw/drivers/i2c/src/32b/f28x/f2802x/i2c.h"
//#include ""

#define OLED_Slave_Address        (0x3c)

#define OLED_MODE     0
#define SIZE          8
#define XLevelL      0x00
#define XLevelH      0x10
#define Max_Column    128
#define Max_Row      64
#define  Brightness    0xFF 
#define X_WIDTH        128
#define Y_WIDTH       64                    

typedef enum
{
  OLED_CMD,
  OLED_DATA

}OLED_TxType_e;

typedef enum
{
  OLED_FontSize_12, 
  OLED_FontSize_16 

}OLED_FontSize_e;

typedef enum
{
   //Set Lower Column Start 
   //Address for Page Addressing Mode (0x00~0x0F)
   OLED_SetLCSBA = 0x00,

   //Set Higher Column Start 
   //Address for Page Addressing Mode 0x10-0x1F
   OLED_SetHCSBA = 0x10, 
   //Set Memory Addressing Mod
   OLED_SetMemAddrMod = 0x20,
   //Set Column Address
   OLED_SetColAddr = 0x21,
   //Set Page Address 
   OLED_SetPageAddr = 0x22,
   //Set Display Start Line 0x40-0x7F
   OLED_SetDispStLine = 0x40, 
   //Set Contrast Control for BANK0 
   OLED_SetCCBank0 = 0x81,
   //Set Segment Re-map 
   OLED_SegReMap = 0xA0,
   //Entire Display ON
   OLED_SetDispOn = 0xA4,
   //Set Normal/Inverse Display
   OLED_SetNorDisp = 0xA6,
   OLED_SetInvDisp = 0xA7,
   //Set Multiplex Ratio A8h
   OLED_SetMultRatio = 0xA8,
   //Set Display ON/OFF
   OLED_DispOn = 0xAE,
   OLED_DispOff = 0xAF,
   //Set Page Start Address 
   //for Page Addressing Mode 0xB0 -0xB7
   OLED_SetPageStAddr = 0xB0,
   //Set COM Output Scan Direction 0xC0/0xC8
   OLED_SetComOutScDir = 0xC0,
   //Set Display Offset 0xD3
   OLED_SetDispOffset = 0xD3,
   //Set Display Clock Divide 
   //Ratio/Oscillator Frequency
   OLED_SetDispClkDiv = 0xD5,
   //Set Pre-charge Period
   OLED_SetPreChargePe = 0xD9,
   //Set COM Pins Hardware Configuration
   OLED_SetComPinHwConf = 0xDA,
   //Set VCOMH Deselect Level
   OLED_SetVcomDeselLevel = 0xDB,
   //No Operation Command
   OLED_NOP  = 0xE3,
   //Charge Pump Setting
   OLED_SetChgPump = 0x8D

}OLED_SetCmd_e;


typedef struct _OLED_Pos_t
{
  uint16_t      Xpos:8;
  uint16_t      Ypos:8;

} OLED_Pos_t;



typedef struct _OLED_Obj_
{
  I2C_Handle        i2cHandle;
  OLED_TxType_e     TxType;
  OLED_Pos_t        OledPos;

  bool              TxTimeOut;

}OLED_Obj;

typedef struct _OLED_Obj_ *OLED_Handle;
typedef unsigned char  uchar;



//OLED functions
void Write_OLED(OLED_Handle handle, uint16_t OLED_Data);
void OLED_RegInit(OLED_Handle handle);
void OLED_setI2cHandle(OLED_Handle handle, I2C_Handle i2cHandle);
OLED_Handle OLED_Init(void *pMemory,const size_t numBytes);
void OLED_Clear(OLED_Handle handle);
void OLED_setPos(OLED_Handle handle, uint16_t x, uint16_t y);
void OLED_PositionSetup(OLED_Handle handle);
void OLED_ShowChar(OLED_Handle handle, OLED_FontSize_e FontSize, uchar DisChr);
void OLED_ShowString(OLED_Handle handle, OLED_FontSize_e FontSize, uchar *DispString);
void OLED_ShowNum(OLED_Handle handle,OLED_FontSize_e FontSize,uint32_t num,uint16_t len);

static inline void OLED_resetTxTimeout(OLED_Handle handle)
{
  OLED_Obj *obj = (OLED_Obj *)handle;

  obj->TxTimeOut = false;

  return;
}











#endif  




