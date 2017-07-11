/*************************************************************************
    > File Name: pca9555.h
    > Author: 
    > Mail: 
    > Created Time: Sat 08 Jul 2017 09:30:29 AM CST
 ************************************************************************/

#ifndef _PCA9555_H
#define _PCA9555_H

#include "sw/drivers/i2c/src/32b/f28x/f2802x/i2c.h"


#ifdef __cplusplus 
extern "C" { 
#endif

#define  PCA955X_SLAVE_ADDR         0x20

typedef enum
{
  PCA955x_PortNum_Port0 = 0,
  PCA955x_PortNum_Port1

} PCA955x_PortNum_e;

typedef enum
{
   PCA955x_RegName_Port0_IN = 0x00,
   PCA955x_RegName_Port1_IN,
   PCA955x_RegName_Port0_OUT,
   PCA955x_RegName_Port1_OUT,
   PCA955x_RegName_Port0_PolarInv,
   PCA955x_RegName_Port1_PolarInv,
   PCA955x_RegName_Port0_Config,
   PCA955x_RegName_Port1_Config

} PCA955x_RegName_e;

typedef enum
{
  PCA955x_StatusFlag_IGBT_OC    = (1<<0), 
  PCA955x_StatusFlag_IKCM_UV    = (1<<1),
  PCA955x_StatusFlag_RELAY_ON   = (1<<2),
  PCA955x_StatusFlag_EMERG_STP  = (1<<5),
  PCA955x_StatusFlag_SENSOR0    = (1<<6),
  PCA955x_StatusFlag_SENSOR1    = (1<<7)

} PCA955x_StatusFlag_e;

typedef struct _PORT_IN_t_
{
  bool  PORT0_SD;
  bool  PORT0_RELAY_OPEN;
  bool  PORT0_CLR_OC;
  bool  PORT0_CPLD_RST;
  bool  PORT0_LEDR;
  bool  PORT0_LEDY;
  bool  PORT0_LEDG;
  bool  PORT0_LEDB;
  bool  PORT1_IGBT_OC;
  bool  PORT1_IKCM_UV;
  bool  PORT1_RELAY_ON;
  bool  PORT1_EMERG_STP;
  bool  PORT1_SENSOR0;
  bool  PORT1_SENSOR1;

} PORT0_IN_t;




//typedef struct _PCA955x_Reg_t_
//{
//  PCA955x_Reg_Port0,
//
//
//
//} PCA955x_Reg_t;



typedef struct _PCA955x_Obj_
{
  I2C_Handle       i2cHandle;  
  
  bool             RxTimeOut;
  bool             TxTimeOut;

} PCA955x_Obj;


typedef struct _PCA955x_Obj_ *PCA955x_Handle;

PCA955x_Handle PCA955x_Init(void *pMemory,const size_t numBytes);
void PCA955x_setI2cHandle(PCA955x_Handle handle, I2C_Handle i2cHandle);
void PCA955x_WrData(PCA955x_Handle handle, PCA955x_RegName_e RegName, uint16_t data);
uint16_t PCA955x_RdData(PCA955x_Handle handle, PCA955x_RegName_e RegName);
void PCA955x_Configure(PCA955x_Handle handle, PCA955x_PortNum_e PortNum, uint16_t Config);
void PCA955x_WriteCommand(PCA955x_Handle handle, PCA955x_PortNum_e PortNum, uint16_t Command);
uint16_t PCA955x_ReadStatus(PCA955x_Handle handle, PCA955x_PortNum_e PortNum);


inline void PCA955x_resetRxTimeOut(PCA955x_Handle handle)
{
  PCA955x_Obj *obj = (PCA955x_Obj *)handle;
  
  obj->RxTimeOut = false;

  return;
}

inline void PCA955x_resetTxTimeOut(PCA955x_Handle handle)
{
  PCA955x_Obj *obj = (PCA955x_Obj *)handle;
  
  obj->TxTimeOut = false;

  return;
}



#ifdef __cplusplus
}
#endif // extern "C"


#endif
