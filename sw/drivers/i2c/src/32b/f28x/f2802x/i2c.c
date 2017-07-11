//#############################################################################
//
//! \file   f2802x_common/source/i2c.c
//!
//! \brief  Contains the various functions related to the inter-integrated 
//!         circuit (I2C) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
//! \addtogroup i2c_api
//! @{
//*****************************************************************************

#include "sw/drivers/i2c/src/32b/f28x/f2802x/i2c.h"



//*****************************************************************************
//
//! \internal
//! Checks an I2C base address.
//!
//! \param spiHandle specifies the I2C module base address.
//!
//! This function determines if a I2C module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
bool_t I2C_isHandleValid(I2C_Handle i2cHandle)
{
    return ((i2cHandle == (I2C_Handle) &I2caRegs));
}
#endif

I2C_Handle I2C_init(void *pMemory,const size_t numBytes)
{
    //assert(pMemory == (void *)I2CA_BASE_ADDR);
    

    I2C_Handle i2cHandle;

    if(numBytes < sizeof(I2C_Obj))
    return((I2C_Handle)NULL);

    // assign the handle
    i2cHandle = (I2C_Handle)pMemory;
    
    return (i2cHandle);
} // end of I2C_init() function


//Note final clock must be between 7 and 12MHz for propper I2C operation
void I2C_setupClock(I2C_Handle i2cHandle, const uint16_t preScalar, 
        const  uint16_t bitTimeLow, const uint16_t bitTimeHigh)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;
    
    i2c->I2CPSC = (preScalar - 1) & I2C_I2CPSC_IPSC_BITS;
    i2c->I2CCLKL = bitTimeLow;
    i2c->I2CCLKH = bitTimeHigh;
    
}

//*****************************************************************************
//! Disable the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will enable operation of the I2C Master block.
//!
//! \return None.
//*****************************************************************************
void I2C_disable(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Disable the I2C peripheral
    i2c->I2CMDR &= ~I2C_I2CMDR_IRS_BIT;
}

//*****************************************************************************
//! Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will enable operation of the I2C Master block.
//!
//! \return None.
//*****************************************************************************
void I2C_enable(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Enable the I2C peripheral
    i2c->I2CMDR |= I2C_I2CMDR_IRS_BIT;
}

//*****************************************************************************
//! Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This will enable operation of the I2C Master block.
//!
//! \return None.
//*****************************************************************************
void I2C_setMaster(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Enable the master block.
    i2c->I2CMDR |= I2C_I2CMDR_MST_BIT;
}

//*****************************************************************************
//! Enables the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This will enable operation of the I2C Slave block.
//!
//! \return None.
//*****************************************************************************
void I2C_setSlave(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Enable the slave.
    i2c->I2CMDR &= ~I2C_I2CMDR_MST_BIT;
}

//*****************************************************************************
//! Enables the I2C interrupts
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Enables the I2C Master interrupt source.
//!
//! \return None.
//*****************************************************************************
void I2C_enableInt(I2C_Handle i2cHandle, const I2C_IntEnable_e interrupts)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Enable interrupts
    i2c->I2CIER |= interrupts;
}

void I2C_enableFifo(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Enable the fifo
    i2c->I2CFFTX |= I2C_I2CFFTX_FFEN_BIT;
}

void I2C_clearTxFifoInt(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Clear the FIFO interrupt
    i2c->I2CFFTX |= I2C_I2CFFTX_TXFFINTCLR_BIT;
}

void I2C_clearRxFifoInt(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Clear the FIFO interrupt
    i2c->I2CFFRX |= I2C_I2CFFRX_RXFFINTCLR_BIT;
}

void I2C_disableFifo(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Disable the fifo
    i2c->I2CFFTX &= ~I2C_I2CFFTX_FFEN_BIT;
}

void I2C_resetTxFifo(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Reset the TX FIFO
    i2c->I2CFFTX |= I2C_I2CFFTX_TXFFRST_BIT;
}

void I2C_resetRxFifo(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Reset the RX FIFO
    i2c->I2CFFRX |= I2C_I2CFFRX_RXFFRST_BIT;
}


//*****************************************************************************
//! Disables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! Disables the I2C Master interrupt source.
//!
//! \return None.
//*****************************************************************************
void I2C_disableInt(I2C_Handle i2cHandle, const I2C_IntEnable_e interrupts)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Disable interrupts
    i2c->I2CIER &= ~interrupts;
}



//*****************************************************************************
//! Gets the current I2C Master interrupt status.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bMasked is false if the raw interrupt status is requested and
//! true if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Master module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//*****************************************************************************
I2C_IntSource_e I2C_getIntSource(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Return the i2c status 
    return (i2c->I2CISRC);
}

//*****************************************************************************
//! Gets the current I2C Master interrupt status.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bMasked is false if the raw interrupt status is requested and
//! true if the masked interrupt status is requested.
//!
//! This returns the interrupt status for the I2C Master module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//*****************************************************************************
I2C_Status_e I2C_getStatus(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Return the i2c status 
    return (i2c->I2CSTR);
}
//

//*****************************************************************************
//! Initializes the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C Slave module.
//! \param ucSlaveAddr 7-bit slave address
//!
//! This function initializes operation of the I2C Slave block.  Upon
//! successful initialization of the I2C blocks, this function will have set
//! the slave address and have enabled the I2C Slave block.
//!
//! The parameter \e ucSlaveAddr is the value that will be compared against the
//! slave address sent by an I2C master.
//!
//! \return None.
//*****************************************************************************
void I2C_setSlaveAddress(I2C_Handle i2cHandle, const uint16_t slaveAddress)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;
    

    // Must enable the device before doing anything else.
    I2C_setSlave(i2cHandle);

    // Set up the slave address.
    i2c->I2COAR = slaveAddress;
}

//*****************************************************************************
//! Sets the address that the I2C Master will place on the bus.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr 7-bit slave address
//! \param bReceive flag indicating the type of communication with the slave
//!
//! This function will set the address that the I2C Master will place on the
//! bus when initiating a transaction.  When the \e bReceive parameter is set
//! to \b true, the address will indicate that the I2C Master is initiating a
//! read from the slave; otherwise the address will indicate that the I2C
//! Master is initiating a write to the slave.
//!
//! \return None.
//*****************************************************************************
void I2C_setMasterSlaveAddr(I2C_Handle i2cHandle, const uint16_t slaveAddress)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Set the address of the slave with which the master will communicate.
    i2c->I2CSAR = slaveAddress;
}

//*****************************************************************************
//! Indicates whether or not the I2C Master is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C Master is
//! busy transmitting or receiving data.
//!
//! \return Returns \b true if the I2C Master is busy; otherwise, returns
//! \b false.
//*****************************************************************************
_Bool I2C_isMasterBusy(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Return the busy status.
    if(i2c->I2CSTR & I2C_I2CSTR_BB_BITS)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//! Controls the state of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ulCmd command to be issued to the I2C Master module
//!
//! This function is used to control the state of the Master module send and
//! receive operations.  The \e ucCmd parameter can be one of the following
//! values:
//!
//! - \b I2C_MASTER_CMD_SINGLE_SEND
//! - \b I2C_MASTER_CMD_SINGLE_RECEIVE
//! - \b I2C_MASTER_CMD_BURST_SEND_START
//! - \b I2C_MASTER_CMD_BURST_SEND_CONT
//! - \b I2C_MASTER_CMD_BURST_SEND_FINISH
//! - \b I2C_MASTER_CMD_BURST_SEND_ERROR_STOP
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_START
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_CONT
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_FINISH
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP
//!
//! \return None.
//*****************************************************************************
void I2C_MasterControl(I2C_Handle i2cHandle, I2C_Control_e action, I2C_BitCount_e bitCount, uint16_t bytes)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    //assert(bitCount <= 7);
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;
    
    // Write the number of bytes to send or receive
    i2c->I2CCNT = bytes;

    // Send the command.
    i2c->I2CMDR = action | bitCount;
}

//*****************************************************************************
//! Gets the error status of the I2C Master module.
//*****************************************************************************


//*****************************************************************************
//! Transmits a byte from the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData data to be transmitted from the I2C Master
//!
//! This function will place the supplied data into I2C Master Data Register.
//!
//! \return None.
//*****************************************************************************
void I2C_putData(I2C_Handle i2cHandle, uint16_t data)
{
    // Check the arguments.
   // assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Write the byte.
    i2c->I2CDXR = data;
}

//*****************************************************************************
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! unsigned long.
//*****************************************************************************
uint16_t I2C_getData(I2C_Handle i2cHandle)
{
    // Check the arguments.
    //assert(I2C_isHandleValid(i2cHandle));
    
    I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

    // Read the byte.
    return (i2c->I2CDRR);
}


void I2C_SendData(I2C_Handle i2cHandle, uint16_t cmd, uint16_t data)
{
	I2C_Obj *i2c = (I2C_Obj *)i2cHandle;

	while(i2c->I2CSTR & I2C_Status_Busy == I2C_Status_Busy);
	i2c->I2CSAR = 0x20;
	i2c->I2CCNT = 2;
	i2c->I2CDXR = cmd;
	i2c->I2CDXR = data;
	i2c->I2CMDR = 0x6e20;
	return;
}

void I2C_WrData(I2C_Handle i2cHandle, uint16_t SlaveAddr, uint16_t *data, uint16_t num)
{
    uint16_t i;
	// wait bus not busy
    while(I2C_isMasterBusy(i2cHandle))
		I2C_MasterControl(i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);

	// Start I2c Transmit and Send Address
	I2C_setMasterSlaveAddr(i2cHandle, SlaveAddr);
	I2C_MasterControl(i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,num);
	I2C_enable(i2cHandle);

	// Send Data
	for(i=num;i>0;i--)
	{
	I2C_putData(i2cHandle, *data++);
	// Wait Tx register Ready
	while((I2C_getStatus(i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy);
	}
	// Wait the data Transmit
	while((I2C_getStatus(i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop);

    return;
}

void I2C_RdData(I2C_Handle i2cHandle, uint16_t SlaveAddr, uint16_t cmd, uint16_t *data, uint16_t num)
{
    uint16_t i;

	while(I2C_isMasterBusy(i2cHandle))
			I2C_MasterControl(i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);

	// Start I2c Transmit and Send Address
	I2C_setMasterSlaveAddr(i2cHandle, SlaveAddr);
	I2C_MasterControl(i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x01);
    I2C_enable(i2cHandle);

    // Send command for read
	I2C_putData(i2cHandle, cmd);
	while((I2C_getStatus(i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy);
	while(I2C_isMasterBusy(i2cHandle));

	// Start I2c Transmit and Send Address
	I2C_setMasterSlaveAddr(i2cHandle, SlaveAddr);
	I2C_MasterControl(i2cHandle, I2C_Control_Single_RX, I2C_BitCount_8_Bits,num);
    I2C_enable(i2cHandle);

	// read Register
    for(i=num;i>0;i--)
    {
	  *data++ = I2C_getData(i2cHandle);
	  // Wait the Rx Register Ready
	  while((I2C_getStatus(i2cHandle) & I2C_Status_Rx_Rdy) != I2C_Status_Rx_Rdy);
    }
    // Wait the data Receive
    while((I2C_getStatus(i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop);

    return;
}

/*
void HAL_I2c_Pca9555_WrData(HAL_Handle handle, uint16_t cmd, uint16_t data)
{
	HAL_Obj *obj = (HAL_Obj *)handle;

	while(I2C_isMasterBusy(obj->i2cHandle))
		I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x02);
    // Send Address
	I2C_setMasterSlaveAddr(obj->i2cHandle, 0x20);
	I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x02);
	I2C_enable(obj->i2cHandle);
	// Send Data1
	I2C_putData(obj->i2cHandle, cmd);
	// Wait Tx register Ready
	while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy);
	I2C_putData(obj->i2cHandle, data);
	// Wait The data Transmit
	while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop);
	//
    return;
}

uint16_t HAL_I2c_Pca9555_RdData(HAL_Handle handle, uint16_t cmd)
{
	HAL_Obj *obj = (HAL_Obj *)handle;
    uint16_t DataTmp;

	while(I2C_isMasterBusy(obj->i2cHandle))
			I2C_MasterControl(obj->i2cHandle, I2C_Control_Stop, I2C_BitCount_8_Bits,0x01);

	I2C_setMasterSlaveAddr(obj->i2cHandle, 0x20);
	I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_TX, I2C_BitCount_8_Bits,0x01);
    I2C_enable(obj->i2cHandle);
	I2C_putData(obj->i2cHandle, cmd);
	while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Tx_Rdy) != I2C_Status_Tx_Rdy);
	while(I2C_isMasterBusy(obj->i2cHandle));
	I2C_setMasterSlaveAddr(obj->i2cHandle, 0x20);
	I2C_MasterControl(obj->i2cHandle, I2C_Control_Single_RX, I2C_BitCount_8_Bits,0x01);
    I2C_enable(obj->i2cHandle);
    DataTmp = I2C_getData(obj->i2cHandle);
    //while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Rx_Rdy) != I2C_Status_Rx_Rdy);
    //DataTmp <<= 8;
    //DataTmp |= I2C_getData(obj->i2cHandle);
    while((I2C_getStatus(obj->i2cHandle) & I2C_Status_Stop) != I2C_Status_Stop);
    return DataTmp;

}

*/















