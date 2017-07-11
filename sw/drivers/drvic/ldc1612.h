
#ifndef _LDC1612_H_ 
#define _LDC1612_H_


// **************************************************************************
// the includes

// drivers
#include "sw/drivers/i2c/src/32b/f28x/f2802x/i2c.h"
#include "sw/drivers/gpio/src/32b/f28x/f2802x/gpio.h"





#ifdef __cplusplus
extern "C" {
#endif

#define LDC161x_DATA_MASK               (0x0FFF)
#define LDC161x_RESET_MASK              (0x8000)
#define LDC161x_FIN_DIV_MASK            (0xF000)
#define LDC161x_FREF_DIV_MASK           (0x03FF)
#define LDC161x_NUM_OF_AVG              (0x10)

#define LDC161x_Kalman_Q                (150)
#define LDC161x_Kalman_R                (1000)


// **************************************************************************
// the typedefs

//! \brief Enumeration for the R/W modes
//!


typedef enum 
{
  LDC_Type_1612 = 0,
  LDC_Type_1614
}LDC_SensorType_e;

typedef enum
{
  LDC161x_Slave_Addr0 = 0x2A,
  LDC161x_Slave_Addr1 = 0x2B
} LDC_SensorSerial_e;



typedef enum 
{
  LDC161x_CtrlMode_Read = 1 << 15,   //!< Read Mode
  LDC161x_CtrlMode_Write = 0 << 15   //!< Write Mode
} LDC161x_CtrlMode_e;

typedef enum 
{
  LDC161x_RegName_Ch0DataMSB      = 0x00,   // 
  LDC161x_RegName_Ch0DataLSB      = 0x01,   //
  LDC161x_RegName_Ch1DataMSB      = 0x02,   // 
  LDC161x_RegName_Ch1DataLSB      = 0x03,   //
  LDC161x_RegName_Ch2DataMSB      = 0x04,   // 
  LDC161x_RegName_Ch2DataLSB      = 0x05,   //
  LDC161x_RegName_Ch3DataMSB      = 0x06,   // 
  LDC161x_RegName_Ch3DataLSB      = 0x07,   //
  LDC161x_RegName_Ch0Rcount       = 0x08,
  LDC161x_RegName_Ch1Rcount       = 0x09,
  LDC161x_RegName_Ch2Rcount       = 0x0A,
  LDC161x_RegName_Ch3Rcount       = 0x0B,
  LDC161x_RegName_Ch0Offset       = 0x0C,
  LDC161x_RegName_Ch1Offset       = 0x0D,
  LDC161x_RegName_Ch2Offset       = 0x0E,
  LDC161x_RegName_Ch3Offset       = 0x0F,
  LDC161x_RegName_Ch0SettleCnt    = 0x10,
  LDC161x_RegName_Ch1SettleCnt    = 0x11,
  LDC161x_RegName_Ch2SettleCnt    = 0x12,
  LDC161x_RegName_Ch3SettleCnt    = 0x13,
  LDC161x_RegName_Ch0ClkDiv       = 0x14,
  LDC161x_RegName_Ch1ClkDiv       = 0x15,
  LDC161x_RegName_Ch2ClkDiv       = 0x16,
  LDC161x_RegName_Ch3ClkDiv       = 0x17,
  LDC161x_RegName_STATUS          = 0x18,
  LDC161x_RegName_ERROR_CONFIG    = 0x19,
  LDC161x_RegName_CONFIG          = 0x1A, 
  LDC161x_RegName_MUX_CONFIG      = 0x1B,
  LDC161x_RegName_RESET_DEV       = 0x1C,
  LDC161x_RegName_Ch0DrvCurrent   = 0x1E,
  LDC161x_RegName_Ch1DrvCurrent   = 0x1F,
  LDC161x_RegName_Ch2DrvCurrent   = 0x20,
  LDC161x_RegName_Ch3DrvCurrent   = 0x21,  
  LDC161x_RegName_MANUFACTURER_ID = 0x7E,
  LDC161x_RegName_DEVICE_ID       = 0x7F

} LDC161x_RegName_e;


typedef enum 
{

 LDC161x_ChNum_CH0 = 0,
 LDC161x_ChNum_CH1,
 LDC161x_ChNum_CH2,
 LDC161x_ChNum_CH3

} LDC161x_ChNum_e;

typedef enum 
{
  LDC161x_DataFlag_ERR_UR_BIT = (1 << 15),
  LDC161x_DataFlag_ERR_OR_BIT = (1 << 14),
  LDC161x_DataFlag_ERR_WD_BIT = (1 << 13), 
  LDC161x_DataFlag_ERR_AE_BIT = (1 << 13)

} LDC161x_DataFlag_e;

typedef enum 
{
  LDC161x_StatusType_CH3_UNRDCONV = (1 << 0),
  LDC161x_StatusType_CH2_UNRDCONV = (1 << 1),
  LDC161x_StatusType_CH1_UNRDCONV = (1 << 2),
  LDC161x_StatusType_CH0_UNRDCONV = (1 << 3),
  LDC161x_StatusType_DRDY         = (1 << 6),
  LDC161x_StatusType_ERR_ZC       = (1 << 8),
  LDC161x_StatusType_ERR_ALE      = (1 << 9),
  LDC161x_StatusType_ERR_AHE      = (1 << 10),
  LDC161x_StatusType_ERR_WD       = (1 << 11),
  LDC161x_StatusType_ERR_OR       = (1 << 12),
  LDC161x_StatusType_ERR_UR       = (1 << 13),
  LDC161x_StatusType_ERR_CHAN0    = (1 << 14),
  LDC161x_StatusType_ERR_CHAN1    = (1 << 15)
} LDC161x_Status_e;

typedef enum 
{
  LDC161x_FaultType_DRDY_2INT  = (1 << 0),  //
  LDC161x_FaultType_ZC_ERR2INT = (1 << 2),  //
  LDC161x_FaultType_FAL_ERR2IN = (1 << 3),  //
  LDC161x_FaultType_AH_ERR2INT = (1 << 4),  //
  LDC161x_FaultType_WD_ERR2INT = (1 << 5),  //
  LDC161x_FaultType_OR_ERR2INT = (1 << 6),  //
  LDC161x_FaultType_UR_ERR2INT = (1 << 7),  //
  LDC161x_FaultType_AL_ERR2OUT = (1 << 11), //
  LDC161x_FaultType_AH_ERR2OUT = (1 << 12), //
  LDC161x_FaultType_WD_ERR2OUT = (1 << 13), //
  LDC161x_FaultType_OR_ERR2OUT = (1 << 14), //
  LDC161x_FaultType_UR_ERR2OUT = (1 << 15)  //

} LDC161x_FaultType_e;


typedef enum 
{
  LDC161x_Config_ACTIVE_CHAN_1      = (1 << 15),
  LDC161x_Config_ACTIVE_CHAN_0      = (1 << 14),
  LDC161x_Config_SLEEP_MODE_EN      = (1 << 13),
  LDC161x_Config_RP_OVERRIDE_EN     = (1 << 12),
  LDC161x_Config_SENSOR_ACTV_SEL    = (1 << 11),
  LDC161x_Config_AUTO_AMP_DIS       = (1 << 10),
  LDC161x_Config_REF_CLK_SRC        = (1 << 9),
  LDC161x_Config_INTB_DIS           = (1 << 7),
  LDC161x_Config_HIGH_CURRENT_DRV   = (1 << 6)

} LDC161x_Config_e;

typedef enum
{
  LDC161x_MuxConfig_DEGLITCH_0    = (1 << 0),
  LDC161x_MuxConfig_DEGLITCH_1    = (1 << 1),
  LDC161x_MuxConfig_DEGLITCH_2    = (1 << 2),
  LDC161x_MuxConfig_RR_SEQUENCE_0 = (1 << 13),
  LDC161x_MuxConfig_RR_SEQUENCE_1 = (1 << 14),
  LDC161x_MuxConfig_AUTOSCAN_EN   = (1 << 15)

} LDC161x_MuxConfig_e;



typedef enum
{
  LDC161x_Deglith_1Mhz    = 0x1,
  LDC161x_Deglith_3p3Mhz  = 0x4,
  LDC161x_Deglith_10Mhz   = 0x5,
  LDC161x_Deglith_33Mhz   = 0x7
   
} LDC161x_DeglithFreq_e;


typedef struct _LDC_161x_CHDATA_MSB_t_
{ 
  bool                ERR_UR;
  bool                ERR_OR;
  bool                ERR_WD;
  bool                ERR_AE;
  uint16_t            DAT_MB;

}LDC_161x_CHDATA_MSB_t_;

typedef struct _LDC_161x_CHDATA_t_
{
  LDC_161x_CHDATA_MSB_t_   MSB;
  uint16_t                 LSB;

}LDC_161x_CHDATA_t_;

typedef struct _LDC_161x_DATA_t_
{
  LDC_161x_CHDATA_t_  CH0_DATA;
  LDC_161x_CHDATA_t_  CH1_DATA;
  LDC_161x_CHDATA_t_  CH2_DATA;
  LDC_161x_CHDATA_t_  CH3_DATA;

}LDC_161x_DATA_t_;

typedef struct _LDC161x_RCOUNT_t_
{
  uint16_t            RCOUNT_CH0;
  uint16_t            RCOUNT_CH1;
  uint16_t            RCOUNT_CH2;
  uint16_t            RCOUNT_CH3;
}LDC161x_RCOUNT_t_;

typedef struct _LDC161x_OFFSET_t_
{
  uint16_t            OFFSET_CH0;
  uint16_t            OFFSET_CH1;
  uint16_t            OFFSET_CH2;
  uint16_t            OFFSET_CH3;
}LDC161x_OFFSET_t_;

typedef struct _LDC161x_SETTLECOUNT_t_
{
  uint16_t            SETTLECOUNT_CH0;
  uint16_t            SETTLECOUNT_CH1;
  uint16_t            SETTLECOUNT_CH2;
  uint16_t            SETTLECOUNT_CH3;
}LDC161x_SETTLECOUNT_t_;

typedef struct _CLK_DIV_t_
{
  uint16_t            FREF_DIVIDER;
  uint16_t            FIN_DIVIDER;
} CLK_DIV_t_;

typedef struct _LDC161x_CLK_DIVS_t_
{
  CLK_DIV_t_     CLK_DIVS_CH0;
  CLK_DIV_t_     CLK_DIVS_CH1;
  CLK_DIV_t_     CLK_DIVS_CH2;
  CLK_DIV_t_     CLK_DIVS_CH3;
}LDC161x_CLK_DIVS_t_;

typedef struct _LDC161x_STATUS_t_
{
  bool     UNRDCONV_CH3;
  bool     UNRDCONV_CH2;
  bool     UNRDCONV_CH1;
  bool     UNRDCONV_CH0;
  bool     DRDY; 
  bool     ERR_ZC;
  bool     ERR_ALE;
  bool     ERR_AHE;
  bool     ERR_WD;
  bool     ERR_OR;
  bool     ERR_UR;
  bool     ERR_CHAN_0;
  bool     ERR_CHAN_1;

}LDC161x_STATUS_t_;

typedef struct _LDC161x_ERROR_CONFIG_t_
{
 bool      UR_ERR2OUT;
 bool      OR_ERR2OUT;
 bool      WD_ERR2OUT;
 bool      AH_ERR2OUT;
 bool      AL_ERR2OUT;
 bool      UR_ERR2INT;
 bool      OR_ERR2INT;
 bool      WD_ERR2INT;
 bool      AH_ERR2INT;
 bool      AL_ERR2INT;
 bool      ZC_ERR2INT;
 bool      DRDY_2INT;

}LDC161x_ERROR_CONFIG_t_;

typedef struct _LDC1612_CONFIG_t_
{
  bool     ACTIVE_CHAN_0;
  bool     ACTIVE_CHAN_1;
  bool     SLEEP_MODE_EN;
  bool     RP_OVERRIDE_EN;
  bool     SENSOR_ACTV_SEL;
  bool     AUTO_AMP_DIS;
  bool     REF_CLK_SRC;
  bool     INTB_DIS;
  bool     HIGH_CURRENT_DRV;

}LDC1612_CONFIG_t_;

typedef struct _LDC161x_MUX_CONFIG_t_
{
  bool     AUTOSCAN_EN;
  bool     RR_SEQUENCE_0;
  bool     RR_SEQUENCE_1;
  bool     DEGLITCH_0; 
  bool     DEGLITCH_1; 
  bool     DEGLITCH_2; 
  
}LDC161x_MUX_CONFIG_t_;

typedef struct _LDC161x_RESET_DEV_t_
{
  bool     RESET_DEV;

}LDC1612_RESET_DEV_t_;

typedef struct _DRIVE_CURRENT_t_
{
 uint16_t            IDRIVE;
 uint16_t            INIT_IDRIVE;

}DRIVE_CURRENT_t_;

typedef struct _LDC161x_DRIVE_CURRENT_t_
{
  DRIVE_CURRENT_t_       DRIVE_CURRENT_CH0;
  DRIVE_CURRENT_t_       DRIVE_CURRENT_CH1;
  DRIVE_CURRENT_t_       DRIVE_CURRENT_CH2;
  DRIVE_CURRENT_t_       DRIVE_CURRENT_CH3;

}LDC161x_DRIVE_CURRENT_t_;

typedef struct _LDC161x_Kalman_t_
{
  uint32_t         x_Last;
  uint32_t         p_Last;
  uint32_t         data_Last;
} LDC161x_Kalman_t_;


typedef struct _LDC161x_REG_Obj_
{
  LDC_161x_DATA_t_           LdcChData;
  LDC161x_RCOUNT_t_          LdcRcount;
  LDC161x_OFFSET_t_          LdcOffset;
  LDC161x_SETTLECOUNT_t_     LdcSettleCnt;
  LDC161x_CLK_DIVS_t_        LdcClkDiv;
  LDC161x_STATUS_t_          LdcStatus;
  LDC161x_ERROR_CONFIG_t_    LdcError;
  LDC1612_CONFIG_t_          LdcConfig;
  LDC161x_MUX_CONFIG_t_      LdcMuxConf;
  DRIVE_CURRENT_t_           LdcDriveCurrent;
  LDC161x_Kalman_t_          LdcKalman;
  LDC_SensorType_e           LdcType;
  LDC_SensorSerial_e         LdcSerial;


}LDC161x_REG_Obj;

typedef struct LDC161x_REG_Obj *LDC_Handle;


//! \brief Defines the LDC161x object
//!
typedef struct _LDC161x_Obj_
{
  I2C_Handle       i2cHandle;        //!< the handle for the serial peripheral interface
  GPIO_Handle      gpioHandle;
  LDC_Handle       ldcHandle;
  LDC161x_REG_Obj  ldc161x;

  bool             RxTimeOut;    //
  bool             TxTimeOut;    //
} LDC161x_Obj;


//! \brief Defines the LDC161x handle
//!
typedef struct _LDC161x_Obj_ *LDC161x_Handle;




LDC161x_Handle LDC1612_init(void *pMemory,const size_t numBytes);
LDC_Handle LDC161xReg_init(void *pMemory,const size_t numBytes);
void LDC161x_setI2cHandle(LDC161x_Handle handle, I2C_Handle i2cHandle);
void LDC161x_setGpioHandle(LDC161x_Handle handle, GPIO_Handle gpioHandle);

void LDC161x_writeI2c(LDC161x_Handle handle, const LDC161x_RegName_e regName,const uint16_t data);
uint16_t LDC161x_readI2c(LDC161x_Handle handle,const LDC161x_RegName_e regName);

void LDC161x_setChData_MSB(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setChData_LSB(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setRcount(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setOffset(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setSettleCnt(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setClkDivs(LDC_Handle handle,const uint16_t Channel, uint16_t drvData);
void LDC161x_setStatus(LDC_Handle handle,uint16_t drvData);
void LDC161x_setErrors(LDC_Handle handle,uint16_t drvData);
void LDC161x_setConfig(LDC_Handle handle,uint16_t drvData);
void LDC161x_setMuxConfig(LDC_Handle handle,uint16_t drvData);
void LDC161x_getConfig(LDC_Handle handle,uint16_t *drvDataGet);
void LDC161x_getRcount(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet);
void LDC161x_getOffset(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet);
void LDC161x_getSettleCnt(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet);
void LDC161x_getClkDivs(LDC_Handle handle,const uint16_t Channel,uint16_t *drvDataGet);
void LDC161x_getMuxConfig(LDC_Handle handle, uint16_t *drvDataGet);
void LDC161x_getChData(LDC_Handle handle,const LDC161x_ChNum_e ChNum, uint32_t *drvDataGet);
void LDC161x_ReFilter(LDC161x_Handle handle,const LDC161x_ChNum_e ChNum, uint32_t *drvDataGet);
void LDC161x_KalmanFilter(LDC161x_Handle handle,const LDC161x_ChNum_e ChNum, uint32_t *drvDataGet);

void LDC161x_readChData(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_readRcount(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_readOffset(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_readSettleCnt(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_readClkDivs(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_writeRcount(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_writeOffset(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_writeSettleCnt(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_writeClkDivs(LDC161x_Handle handle, LDC161x_ChNum_e ChannelNum);
void LDC161x_readStatus(LDC161x_Handle handle);
void LDC161x_readErrors(LDC161x_Handle handle);
void LDC161x_readConfig(LDC161x_Handle handle);
void LDC161x_writeConfig(LDC161x_Handle handle);
void LDC161x_writeMuxConfig(LDC161x_Handle handle);
void LDC161xReg_ReConfig(LDC161x_Handle handle);

void LDC161x_ResetSensor(LDC161x_Handle handle);
void I2C_unlockBus(LDC161x_Handle handle);

inline uint16_t LDC161x_ReadRegData(LDC161x_Handle handle, LDC161x_RegName_e RegName)
{
   //LDC161x_Obj *obj = (LDC161x_Obj *)handle;
   uint16_t  RegData;

   RegData = LDC161x_readI2c(handle,RegName);
   
   return (RegData);
}
inline void LDC161x_WriteRegData(LDC161x_Handle handle, LDC161x_RegName_e RegName, uint16_t RegData)
{
	//LDC161x_Obj *obj = (LDC161x_Obj *)handle;

    LDC161x_writeI2c(handle,RegName,RegData);

	return;
}

static inline void LDC161x_resetRxTimeout(LDC161x_Handle handle)
{
    LDC161x_Obj *obj = (LDC161x_Obj *)handle;

    obj->RxTimeOut = false;

    return;
}


static inline void LDC161x_resetTxTimeout(LDC161x_Handle handle)
{
    LDC161x_Obj *obj = (LDC161x_Obj *)handle;

    obj->TxTimeOut = false;

    return;
}

inline void LDC161x_setSensorID(LDC_Handle handle,LDC_SensorType_e SensorID)
{
  LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;
  
  obj->LdcType = SensorID;
  return;
}

inline void LDC161x_setSensorSerial(LDC_Handle handle,LDC_SensorSerial_e SensorSerial)
{
   LDC161x_REG_Obj *obj = (LDC161x_REG_Obj *)handle;

   obj->LdcSerial = SensorSerial;
   return;
}



#ifdef __cplusplus 
}
#endif



#endif

