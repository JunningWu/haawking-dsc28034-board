#ifndef DSC28034_I2C_H
#define DSC28034_I2C_H

#ifdef __cplusplus
extern "C" {
#endif


struct I2CIC_CON_BITS
{
/*********************************************
This bit controls whether the DW_apb_i2c master is enabled. 
0: master disabled
1: master enabled
Reset value: IC_MASTER_MODE configuration parameter
NOTE: Software should ensure that if this bit is written with ‘1,’ then 
bit 6 should also be written with a ‘1’.
********************************************/
	Uint32 MASTER_MODE:1; // 0   R/W
/************************************************
These bits control at which speed the DW_apb_i2c operates; its 
setting is relevant only if one is operating the DW_apb_i2c in master 
mode. Hardware protects against illegal values being programmed 
by software. This register should be programmed only with a value 
in the range of 1 to IC_MAX_SPEED_MODE; otherwise, hardware 
updates this register with the value of IC_MAX_SPEED_MODE.
■ 1: standard mode (0 to 100 Kb/s) 
■ 2: fast mode (≤ 400 Kb/s) or fast mode plus (≤ 1000 Kb/s)
■ 3: high speed mode (≤ 3.4 Mb/s)
Reset value: IC_MAX_SPEED_MODE configuration
************************************************/	
	Uint32 SPEED:2;		  // 1-2   R/W
/**************************************************
 When acting as a slave, this bit controls whether the DW_apb_i2c 
responds to 7- or 10-bit addresses.
0: 7-bit addressing. The DW_apb_i2c ignores transactions that 
involve 10-bit addressing; for 7-bit addressing, only the lower 7 bits 
of the IC_SAR register are compared.
1: 10-bit addressing. The DW_apb_i2c responds to only 10-bit 
addressing transfers that match the full 10 bits of the IC_SAR 
register.
Reset value: IC_10BITADDR_SLAVE configuration parameter
Note
Bits 3 and 4 of this register can be programmed differently and in any combination depending on 
which format is required for the transfers. For example, master mode can be configured with 10-bit 
addressing and slave mode can be configured with 7-bit addressing.
*****************************************************/	
	Uint32 IC_10BITADDR_SLAVE:1; // 3  R/W
/*****************************************************
If the I2C_DYNAMIC_TAR_UPDATE configuration parameter is set 
to “No” (0), this bit is named IC_10BITADDR_MASTER and controls 
whether the DW_apb_i2c starts its transfers in 7- or 10-bit 
addressing mode when acting as a master.
If I2C_DYNAMIC_TAR_UPDATE is set to “Yes” (1), the function of 
this bit is handled by bit 12 of IC_TAR register, and becomes a 
read-only copy called IC_10BITADDR_MASTER_rd_only.
0: 7-bit addressing
1: 10-bit addressing
Dependencies: If I2C_DYNAMIC_TAR_UPDATE = 1, then this bit is 
read-only. If I2C_DYNAMIC_TAR_UPDATE = 0, then this bit can be 
read or write.
Reset value: IC_10BITADDR_MASTER configuration parameter

Bits 3 and 4 of this register can be programmed differently and in any combination depending on 
which format is required for the transfers. For example, master mode can be configured with 10-bit 
addressing and slave mode can be configured with 7-bit addressing.
*******************************************************/	
	Uint32 IC_10BITADDR_MASTER_or_IC_10BITADDR_MASTER_rd_only:1; // 4   R/W or R
/*****************************************
 Determines whether RESTART conditions may be sent when acting 
as a master. Some older slaves do not support handling RESTART 
conditions; however, RESTART conditions are used in several 
DW_apb_i2c operations.
0: disable
1: enable
When the RESTART is disabled, the DW_apb_i2c master is 
incapable of performing the following functions:
■ Sending a START BYTE
■ Performing any high-speed mode operation
■ Performing direction changes in combined format mode
■ Performing a read operation with a 10-bit address
By replacing RESTART condition followed by a STOP and a 
subsequent START condition, split operations are broken down into 
multiple DW_apb_i2c transfers. If the above operations are 
performed, it will result in setting bit 6 (TX_ABRT) of the 
IC_RAW_INTR_STAT register.
Reset value: IC_RESTART_EN configuration parameter
*************************************************/	
	Uint32 IC_RESTART_EN:1;  //  5   R/W
/****************************************************
This bit controls whether I2C has its slave disabled, which means 
once the presetn signal is applied, then this bit takes on the value of 
the configuration parameter IC_SLAVE_DISABLE. You have the 
choice of having the slave enabled or disabled after reset is applied, 
which means software does not have to configure the slave. By 
default, the slave is always enabled (in reset state as well). If you 
need to disable it after reset, set this bit to 1.
If this bit is set (slave is disabled), DW_apb_i2c functions only as a 
master and does not perform any action that requires a slave.
0: slave is enabled
1: slave is disabled
Reset value: IC_SLAVE_DISABLE configuration parameter
NOTE: Software should ensure that if this bit is written with ‘0,’ then 
bit 0 should also be written with a ‘0’.
*****************************************************************/	
	Uint32 IC_SLAVE_DISABLE:1;		//  6    R/W
/*******************************************************
 In slave mode:
1’b1 – issues the STOP_DET interrrupt only when it is addressed.
1’b0 – issues the STOP_DET irrespective of whether it’s addressed 
or not.
Dependencies: This register bit value is applicable in the slave 
mode only (MASTER_MODE = 1’b0)
Reset value: 1’b0
NOTE: During a general call address, this slave does not issue the 
STOP_DET interrupt if STOP_DET_IF_ADDRESSED = 1’b1, even if 
the slave responds to the general call address by generating ACK.
The STOP_DET interrupt is generated only when the transmitted 
address matches the slave address (SAR).
*************************************************************/	
	Uint32 STOP_DET_IFADDRESSED:1;//   7  R/W
/***********************************************************
 This bit controls the generation of the TX_EMPTY interrupt, as 
described in the IC_RAW_INTR_STAT register.
Reset value: 0x0
******************************************************/	
	Uint32 TX_EMPTY_CTRL:1;//	8  R/W
/********************************************************
This bit controls whether DW_apb_i2c should hold the bus when the 
Rx FIFO is physically full to its RX_BUFFER_DEPTH, as described 
in the IC_RX_FULL_HLD_BUS_EN parameter.
Dependencies: This register bit value is applicable only when the 
IC_RX_FULL_HLD_BUS_EN configuration parameter is set to 1. If 
IC_RX_FULL_HLD_BUS_EN = 0, then this bit is read-only. If 
IC_RX_FULL_HLD_BUS_EN = 1, then this bit can be read or write. 
Reset value: 0x0
***************************************************/	
	Uint32 RX_FIFO_FULL_HLD_CTRL:1;  //  9  R/W  or R
	Uint32 rsvd:22;// 10-31
};

union I2CIC_CON_REG
{
	Uint32 all;
	struct I2CIC_CON_BITS bit;
};


struct I2CIC_TAR_BITS
{
/***********************************************
This is the target address for any master transaction. When 
transmitting a General Call, these bits are ignored. To generate a 
START BYTE, the CPU needs to write only once into these bits. 
Reset value: IC_DEFAULT_TAR_SLAVE_ADDR configuration 
parameter
If the IC_TAR and IC_SAR are the same, loopback exists but the 
FIFOs are shared between master and slave, so full loopback is not 
feasible. Only one direction loopback mode is supported (simplex), 
not duplex. A master cannot transmit to itself; it can transmit to only 
a slave.
*******************************************************/
	Uint32 IC_TAR:10;//  0-9  R/W
/*************************************************
 If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a 
General Call or START byte command is to be performed by the 
DW_apb_i2c.
■ 0: General Call Address – after issuing a General Call, only 
writes may be performed. Attempting to issue a read command 
results in setting bit 6 (TX_ABRT) of the IC_RAW_INTR_STAT
register. The DW_apb_i2c remains in General Call mode until 
the SPECIAL bit value (bit 11) is cleared.
■ 1: START BYTE
Reset value: 0x0
**********************************************/	
	Uint32 GC_OR_START:1;//  10 R/W
/********************************************************
 This bit indicates whether software performs a General Call or 
START BYTE command.
■ 0: ignore bit 10 GC_OR_START and use IC_TAR normally
■ 1: perform special I2C command as specified in 
GC_OR_START bit
Reset value: 0x0
*************************************************/	
	Uint32 SPECIAL:1;    //  11  R/W
/**********************************************
 This bit controls whether the DW_apb_i2c starts its transfers in 7-or 
10-bit addressing mode when acting as a master.
■ 0: 7-bit addressing
■ 1: 10-bit addressing
Dependencies: This bit exists in this register only if the 
I2C_DYNAMIC_TAR_UPDATE configuration parameter is set to 
Yes (1).
Reset value: IC_10BITADDR_MASTER configuration parameter
***************************************************/	
	Uint32 IC_10BITADDR_MASTER:1;//  12   R/W
	Uint32 Reserved:19;//  13 - 31
};


union I2CIC_TAR_REG
{
	Uint32 all;
	struct I2CIC_TAR_BITS bit;
};


struct I2CIC_SAR_BITS 
{
/******************************************
The IC_SAR holds the slave address when the I2C is operating as a slave. For 7-bit 
addressing, only IC_SAR[6:0] is used.
This register can be written only when the I2C interface is disabled, which corresponds 
to IC_ENABLE[0] being set to 0. Writes at other times have no effect.
NOTE: The default values cannot be any of the reserved address locations: that is, 
0x00 to 0x07, or 0x78 to 0x7f. The correct operation of the device is not guaranteed if 
you program the IC_SAR or IC_TAR to a reserved value. Refer to Table 3-1 on page 
39 for a complete list of these reserved values.
Reset value: IC_DEFAULT_SLAVE_ADDR configuration parameter
***********************************************/
	Uint32 IC_SAR:10;   //  0-9  R/W  
	Uint32 resvd:22;   // 10 - 31
};


union I2CIC_SAR_REG 
{
	Uint32 all;
	struct I2CIC_SAR_BITS bit;
};

struct I2CIC_HS_MADDR_BITS
{
/***************************************************
 This bit field holds the value of the I2C HS mode master code. HS-mode master 
codes are reserved 8-bit codes (00001xxx) that are not used for slave addressing 
or other purposes. Each master has its unique master code; up to eight highspeed mode masters can be present on the same I2C bus system. Valid values 
are from 0 to 7. This register goes away and becomes read-only returning 0’s if 
the IC_MAX_SPEED_MODE configuration parameter is set to either Standard 
(1) or Fast (2).
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
Reset value: IC_HS_MASTER_CODE configuration parameter
***************************************************/
	Uint32 IC_HS_MAR:3; //0-2  R/W
	Uint32 rsvd:29;// 3- 31
};


union I2CIC_HS_MADDR_REG
{
	Uint32 all;
	struct I2CIC_HS_MADDR_BITS bit;
};

struct I2CIC_DATA_CMD_BITS
{
/*********************************************************
This register contains the data to be transmitted or received on the I2C bus. If you are 
writing to this register and want to perform a read, bits 7:0 (DAT) are ignored by the 
DW_apb_i2c. However, when you read this register, these bits return the value of data 
received on the DW_apb_i2c interface. 
Reset value: 0x0
****************************************************************/
	Uint32 DAT:8; //  0-7  R/W
/******************************************
This bit controls whether a read or a write is performed. This bit does not control the
direction when the DW_apb_i2c acts as a slave. It controls only the direction when it 
acts as a master.
■ 1 = Read
■ 0 = Write
When a command is entered in the TX FIFO, this bit distinguishes the write and read 
commands. In slave-receiver mode, this bit is a “don’t care” because writes to this 
register are not required. In slave-transmitter mode, a “0” indicates that the data in 
IC_DATA_CMD is to be transmitted.
When programming this bit, you should remember the following: attempting to 
perform a read operation after a General Call command has been sent results in a 
TX_ABRT interrupt (bit 6 of the IC_RAW_INTR_STAT register), unless bit 11 
(SPECIAL) in the IC_TAR register has been cleared.
If a “1” is written to this bit after receiving a RD_REQ interrupt, then a TX_ABRT
interrupt occurs.
Reset value: 0x0
*************************************************/	
	Uint32 CMD:1; // 8  W
/***************************************************
 This bit controls whether a STOP is issued after the byte is sent or received. This bit is 
available only if IC_EMPTYFIFO_HOLD_MASTER_EN is configured to 1.
■ 1 – STOP is issued after this byte, regardless of whether or not the Tx FIFO is 
empty. If the Tx FIFO is not empty, the master immediately tries to start a new 
transfer by issuing a START and arbitrating for the bus.
■ 0 – STOP is not issued after this byte, regardless of whether or not the Tx FIFO is 
empty. If the Tx FIFO is not empty, the master continues the current transfer by 
sending/receiving data bytes according to the value of the CMD bit. If the Tx FIFO 
is empty, the master holds the SCL line low and stalls the bus until a new 
command is available in the Tx FIFO.
*******************************************************/	
	Uint32 STOP:1;// 9  W
/****************************************************
This bit controls whether a RESTART is issued before the byte is sent or received. 
This bit is available only if IC_EMPTYFIFO_HOLD_MASTER_EN is configured to 1.
■ 1 – If IC_RESTART_EN is 1, a RESTART is issued before the data is 
sent/received (according to the value of CMD), regardless of whether or not the 
transfer direction is changing from the previous command; if IC_RESTART_EN 
is 0, a STOP followed by a START is issued instead.
■ 0 – If IC_RESTART_EN is 1, a RESTART is issued only if the transfer direction is 
changing from the previous command; if IC_RESTART_EN is 0, a STOP followed 
by a START is issued instead.
****************************************************/	
	Uint32 RESTART:1; // 10  W
	Uint32 rsvd:21;//  11-31
	
};


union I2CIC_DATA_CMD_REG
{
	Uint32 all;
	struct I2CIC_DATA_CMD_BITS bit;
};

struct  I2CIC_SS_SCL_HCNT_BITS
{
/***********************************************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock high-period count 
for standard speed. For more information, refer to “IC_CLK Frequency 
Configuration” on page 59.
This register can be written only when the I2C interface is disabled which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
The minimum valid value is 6; hardware prevents values less than this being 
written, and if attempted results in 6 being set. For designs with 
APB_DATA_WIDTH = 8, the order of programming is important to ensure the 
correct operation of the DW_apb_i2c. The lower byte must be programmed 
first. Then the upper byte is programmed.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
NOTE: This register must not be programmed to a value higher than 65525, 
because DW_apb_i2c uses a 16-bit counter to flag an I2C bus idle condition 
when this counter reaches a value of IC_SS_SCL_HCNT + 10.
Reset value: IC_SS_SCL_HIGH_COUNT configuration parameter
*************************************************************************/
	Uint32 IC_SS_SCL_HCNT:16;// 0- 15 RW Read-only if IC_HC_COUNT_VALUES = 1.
	Uint32 rsvd:16;
};

union I2CIC_SS_SCL_HCNT_REG
{
	Uint32 all;
	struct  I2CIC_SS_SCL_HCNT_BITS  bit;
};

struct  I2CIC_SS_SCL_LCNT_BITS
{
/*******************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock low period count 
for standard speed. For more information, refer to “IC_CLK Frequency 
Configuration” on page 59.
This register can be written only when the I2C interface is disabled which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
The minimum valid value is 8; hardware prevents values less than this being 
written, and if attempted, results in 8 being set. For designs with 
APB_DATA_WIDTH = 8, the order of programming is important to ensure the 
correct operation of DW_apb_i2c. The lower byte must be programmed first, 
and then the upper byte is programmed.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
Reset value: IC_SS_SCL_LOW_COUNT configuration parameter
*******************************************************/
	Uint32 IC_SS_SCL_LCNT:16; //  0-15  R/W
	Uint32 rsvd:16;
};


union I2CIC_SS_SCL_LCNT_REG 
{
	Uint32 all;
	struct  I2CIC_SS_SCL_LCNT_BITS bit;
};

struct I2CIC_FS_SCL_HCNT_BITS
{
/**********************************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock high-period count 
for fast mode or fast mode plus. It is used in high-speed mode to send the 
Master Code and START BYTE or General CALL. For more information, refer 
to “IC_CLK Frequency Configuration” on page 59.
This register goes away and becomes read-only returning 0s if 
IC_MAX_SPEED_MODE = standard. This register can be written only when 
the I2C interface is disabled, which corresponds to IC_ENABLE[0] being set 
to 0. Writes at other times have no effect.
The minimum valid value is 6; hardware prevents values less than this being 
written, and if attempted results in 6 being set. For designs with 
APB_DATA_WIDTH == 8 the order of programming is important to ensure the 
correct operation of the DW_apb_i2c. The lower byte must be programmed 
first. Then the upper byte is programmed.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
Reset value: IC_FS_SCL_HIGH_COUNT configuration parameter
***********************************************************************/
	Uint32 IC_FS_SCL_HCNT:16; // 0-15 RW  1Read-only if IC_HC_COUNT_VALUES = 1.
	Uint32 rsvd:16; // 16 - 31
};


union I2CIC_FS_SCL_HCNT_REG
{
	Uint32 all;
	struct I2CIC_FS_SCL_HCNT_BITS bit;
};


struct  I2CIC_FS_SCL_LCNT_BITS
{
/************************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock low period count for 
fast mode or fast mode plus. It is used in high-speed mode to send the Master 
Code and START BYTE or General CALL. For more information, refer to 
“IC_CLK Frequency Configuration” on page 59.
This register goes away and becomes read-only returning 0s if 
IC_MAX_SPEED_MODE = standard.
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
The minimum valid value is 8; hardware prevents values less than this being 
written, and if attempted results in 8 being set. For designs with 
APB_DATA_WIDTH = 8 the order of programming is important to ensure the 
correct operation of the DW_apb_i2c. The lower byte must be programmed 
first. Then the upper byte is programmed. If the value is less than 8 then the 
count value gets changed to 8.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
Reset value: IC_FS_SCL_LOW_COUNT configuration parameter
*********************************************************/
	Uint32 IC_FS_SCL_LCNT:16; // 0 - 15  R/W   1Read-only if IC_HC_COUNT_VALUES = 1.
	Uint32 rsvd:16; //   16  - 31
};

union I2CIC_FS_SCL_LCNT_REG
{
	Uint32 all;
	struct  I2CIC_FS_SCL_LCNT_BITS bit;
};


struct I2CIC_HS_SCL_HCNT_BITS
{
/********************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock low period count for 
fast mode or fast mode plus. It is used in high-speed mode to send the Master 
Code and START BYTE or General CALL. For more information, refer to 
“IC_CLK Frequency Configuration” on page 59.
This register goes away and becomes read-only returning 0s if 
IC_MAX_SPEED_MODE = standard.
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
The minimum valid value is 8; hardware prevents values less than this being 
written, and if attempted results in 8 being set. For designs with 
APB_DATA_WIDTH = 8 the order of programming is important to ensure the 
correct operation of the DW_apb_i2c. The lower byte must be programmed 
first. Then the upper byte is programmed. If the value is less than 8 then the 
count value gets changed to 8.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
Reset value: IC_FS_SCL_LOW_COUNT configuration parameter
**************************************************************/
	Uint32 IC_FS_SCL_LCNT:16; // 0-15   R/W   Read-only if IC_HC_COUNT_VALUES = 1.  
	Uint32 rsvd:16; //  16  -  31
};


union I2CIC_HS_SCL_HCNT_REG 
{
	Uint32 all;
	struct I2CIC_HS_SCL_HCNT_BITS bit;
};

struct  I2CIC_HS_SCL_LCNT_BITS
{
/**************************************
This register must be set before any I2C bus transaction can take place to 
ensure proper I/O timing. This register sets the SCL clock low period count for 
fast mode or fast mode plus. It is used in high-speed mode to send the Master 
Code and START BYTE or General CALL. For more information, refer to 
“IC_CLK Frequency Configuration” on page 59.
This register goes away and becomes read-only returning 0s if 
IC_MAX_SPEED_MODE = standard.
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have no 
effect.
The minimum valid value is 8; hardware prevents values less than this being 
written, and if attempted results in 8 being set. For designs with 
APB_DATA_WIDTH = 8 the order of programming is important to ensure the 
correct operation of the DW_apb_i2c. The lower byte must be programmed 
first. Then the upper byte is programmed. If the value is less than 8 then the 
count value gets changed to 8.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this 
register is read only.
Reset value: IC_FS_SCL_LOW_COUNT configuration parameter
************************************************************/
	Uint32 IC_FS_SCL_LCNT:16; // 0 - 15  R/W   Read-only if IC_HC_COUNT_VALUES = 1.
	Uint32 rsvd:16;//   16 - 31
};

union I2CIC_HS_SCL_LCNT_REG
{
	Uint32 all;
	struct  I2CIC_HS_SCL_LCNT_BITS bit;
};

struct I2CIC_INTR_STAT_BITS
{
	Uint32 R_RX_UNDER:1;//  0
	Uint32 R_RX_OVER:1; //  1
	Uint32 R_RX_FULL:1;//   2
	Uint32 R_TX_OVER:1; //  3
	Uint32 R_TX_EMPTY:1;//  4
	Uint32 R_RD_REQ:1;//   5
	Uint32 R_TX_ABRT:1;//  6
	Uint32 R_RX_DONE:1;//  7
	Uint32 R_ACTIVITY:1;// 8
	Uint32 R_STOP_DET:1;// 9 
	Uint32 R_START_DET:1;// 10
	Uint32 R_GEN_CALL:1;//  11
	Uint32 R_RESTART_DET:1;// 12
	Uint32 R_MST_ON_HOLD:1;// 13
	Uint32 rsvd:18;
};


union I2CIC_INTR_STAT_REG
{
	Uint32 all;
	struct I2CIC_INTR_STAT_BITS bit;
};

struct I2CIC_INTR_MASK_BITS
{
	Uint32 M_RX_UNDER:1;//  0 
	Uint32 M_RX_OVER:1;//  1
	Uint32 M_RX_FULL:1;//  2
	Uint32 M_TX_OVER:1;//  3
	Uint32 M_TX_EMPTY:1;// 4
	Uint32 M_RD_REQ:1;//   5
	Uint32 M_TX_ABRT:1;//  6
	Uint32 M_RX_DONE:1;//  7
	Uint32 M_ACTIVITY:1;// 8
	Uint32 M_STOP_DET:1;// 9
	Uint32 M_START_DET:1;// 10
/*************************************
These bits mask their corresponding interrupt status bits in the 
IC_INTR_STAT register.
Reset value: 14’h8ff
**********************************************/
	Uint32 M_GEN_CALL:1;//  11  RW
/******************************************************************
This bit masks the R_RESTART_DET interrupt status bit in the 
IC_INTR_STAT register.
Dependencies: If IC_SLV_RESTART_DET_EN = 1, then 
M_RESTART_DET is read/write. Otherwise M_RESTART_DET is readonly.
Reset value: 14’h8ff
************************************************************/	
	Uint32 M_RESTART_DET:1;// 12 R or R/W  
/*********************************************************
This bit masks the R_MST_ON_HOLD interrupt bit in the IC_INTR_STAT
register.
Dependencies: If I2C_DYNAMIC_TAR_UPDATE = 1 and 
IC_EMPTYFIFO_HOLD_MASTER_EN = 1, then M_MST_ON_HOLD is 
read/write. Otherwise M_MST_ON_HOLD is read-only.
Reset value: 14’h8ff
******************************************************/
	Uint32 M_MST_ON_HOLD:1;// 13 R or R/W  
	Uint32 rsvd:18;//  14  - 31
};


union I2CIC_INTR_MASK_REG
{
	Uint32 all;
	struct I2CIC_INTR_MASK_BITS bit;
};

struct I2CIC_RAW_INTR_STAT_BITS
{
/**************************************************************
 Set if the processor attempts to read the receive buffer when it is empty by 
reading from the IC_DATA_CMD register. If the module is disabled 
(IC_ENABLE[0]=0), this bit keeps its level until the master or slave state 
machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
Reset value: 0x0
**************************************************/
	Uint32 RX_UNDER:1; // 0   R
/******************************************************
Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and 
an additional byte is received from an external I2C device. The DW_apb_i2c 
acknowledges this, but any data bytes received after the FIFO is full are lost. If 
the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the 
master or slave state machines go into idle, and when ic_en goes to 0, this 
interrupt is cleared.
NOTE: If IC_RX_FULL_HLD_BUS_EN=1, then the RX_OVER interrupt is 
never set to 1, because the criteria to set this interrupt are never met.
Reset value: 0x0
**************************************************/	
	Uint32 RX_OVER:1; //  1   R
/*******************************************
 Set when the receive buffer reaches or goes above the RX_TL threshold in 
the IC_RX_TL register. It is automatically cleared by hardware when buffer 
level goes below the threshold. If the module is disabled (IC_ENABLE[0]=0), 
the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. So 
this bit is cleared once IC_ENABLE[0] is set to 0, regardless of the activity 
that continues.
Reset value: 0x0
*****************************************************/	
	Uint32 RX_FULL:1;//   2   R
/*************************************************
 Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH 
and the processor attempts to issue another I2C command by writing to the 
IC_DATA_CMD register. When the module is disabled, this bit keeps its level 
until the master or slave state machines go into idle, and when ic_en goes to 
0, this interrupt is cleared.
Reset value: 0x0
************************************************/	
	Uint32 TX_OVER:1;//  3   R
/******************************************************
 The behavior of the TX_EMPTY interrupt status differs based on the 
TX_EMPTY_CTRL selection in the IC_CON register.
■ When TX_EMPTY_CTRL = 0:
This bit is set to 1 when the transmit buffer is at or below the threshold 
value set in the IC_TX_TL register.
■ When TX_EMPTY_CTRL = 1:
This bit is set to 1 when the transmit buffer is at or below the threshold 
value set in the IC_TX_TL register and the transmission of the 
address/data from the internal shift register for the most recently popped 
command is completed.
It is automatically cleared by hardware when the buffer level goes above the 
threshold. When IC_ENABLE[0] is set to 0, the TX FIFO is flushed and held in 
reset. There the TX FIFO looks like it has no data within it, so this bit is set 
to 1, provided there is activity in the master or slave state machines. When 
there is no longer any activity, then with ic_en=0, this bit is set to 0.
Reset value: 0x0
*******************************************************/	
	Uint32 TX_EMPTY:1;// 4   R
/***************************************************
 This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C 
master is attempting to read data from DW_apb_i2c. The DW_apb_i2c holds 
the I2C bus in a wait state (SCL=0) until this interrupt is serviced, which 
means that the slave has been addressed by a remote master that is asking 
for data to be transferred. The processor must respond to this interrupt and 
then write the requested data to the IC_DATA_CMD register. This bit is set to 
0 just after the processor reads the IC_CLR_RD_REQ register.
Reset value: 0x0
*******************************************************/	
	Uint32 RD_REQ:1;   //  5  R
/**********************************************************
This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete 
the intended actions on the contents of the transmit FIFO. This situation can 
occur both as an I2C master or an I2C slave, and is referred to as a “transmit 
abort”.
When this bit is set to 1, the IC_TX_ABRT_SOURCE register indicates the 
reason why the transmit abort takes places.
NOTE: The DW_apb_i2c flushes/resets/empties both TX_FIFO and 
RX_FIFO whenever there is a transmit abort caused by any of the events 
tracked by the IC_TX_ABRT_SOURCE register. The Tx FIFO remains in this 
flushed state until the register IC_CLR_TX_ABRT is read. Once this read is 
performed, the Tx FIFO is then ready to accept more data bytes from the APB 
interface.
Reset value: 0x0
***************************************************************/	
	Uint32 TX_ABRT:1;  //  6  R
/*********************************************************
 When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the 
master does not acknowledge a transmitted byte. This occurs on the last byte 
of the transmission, indicating that the transmission is done.
Reset value: 0x0
************************************************************************/	
	Uint32 RX_DONE:1;  //  7  R
/******************************************************
This bit captures DW_apb_i2c activity and stays set until it is cleared. There 
are four ways to clear it: 
■ Disabling the DW_apb_i2c
■ Reading the IC_CLR_ACTIVITY register
■ Reading the IC_CLR_INTR register
■ System reset
Once this bit is set, it stays set unless one of the four methods is used to clear 
it. Even if the DW_apb_i2c module is idle, this bit remains set until cleared, 
indicating that there was activity on the bus.
Reset value: 0x0
**************************************************************/	
	Uint32 ACTIVITY:1; //  8   R
/*****************************************
The behavior of the STOP_DET interrupt status differs based on the 
STOP_DET_IFADDRESSED selection in the IC_CON register
■ When STOP_DET_IFADDRESSED =0
Indicates whether a STOP condition has occurred on the I2C interface 
regardless of whether DW_apb_i2c is operating in slave or master mode. 
In slave mode, a STOP_DET interrupt is generated irrespective of whether 
the slave is addressed or not.
■ When STOP_DET_IFADDRESSED = 1
In Master Mode (MASTER_MODE = 1’b1), indicates a STOP condition 
has occured on the I2C interface.
In Slave Mode (MASTER_MODE = 1'b0), a STOP_DET interrupt is 
generated only if the slave is addressed.
NOTE: During a general call address, this slave does not issue a STOP_DET 
interrupt if STOP_DET_IFADDRESSED=1'b1, even if the slave responds to 
the general call address by generating ACK. The STOP_DET interrupt is 
generated only when the transmitted address matches the slave address 
(SAR).
Reset value: 0x0
************************************************/	
	Uint32 STOP_DET:1; //  9  R
/**********************************************************
 Indicates whether a START or RESTART condition has occurred on the I2C 
interface regardless of whether DW_apb_i2c is operating in slave or master 
mode.
Reset value: 0x0
************************************************************************/	
	Uint32 START_DET:1;//  10  R
/**********************************************************
 Set only when a General Call address is received and it is acknowledged. It 
stays set until it is cleared either by disabling DW_apb_i2c or when the CPU 
reads bit 0 of the IC_CLR_GEN_CALL register. DW_apb_i2c stores the 
received data in the Rx buffer.
Reset value: 0x0
*******************************************************/	
	Uint32 GEN_CALL:1;//   11  R
/**************************************************
 Indicates whether a RESTART condition has occurred on the I2C interface 
when DW_apb_i2c is operating in slave mode and the slave is the addressed 
slave.
Enabled only when IC_SLV_RESTART_DET_EN = 1
NOTE: However, in high-speed mode or during a START BYTE transfer, the 
RESTART comes before the address field as per the I2C protocol. In this 
case, the slave is not the addressed slave when the RESTART is issued, 
therefore DW_apb_i2c does not generate the RESTART_DET interrupt.
Reset value: 0x0
*****************************************************/	
	Uint32 RESTART_DET:1;// 12 R
/****************************************************
Indicates whether a master is holding the bus and the Tx FIFO is empty. 
Enabled only when I2C_DYNAMIC_TAR_UPDATE = 1 and 
IC_EMPTYFIFO_HOLD_MASTER_EN = 1
Reset value: 0X0
********************************************************/	
	Uint32 MST_ON_HOLD:1;// 13 R
	Uint32 rsvd:18;//  14 - 31
 };


union I2CIC_RAW_INTR_STAT_REG
{
	Uint32 all;
	struct I2CIC_RAW_INTR_STAT_BITS bit;
};


struct I2CIC_RX_TL_BITS
{
/*************************************
Controls the level of entries (or above) that triggers the RX_FULL interrupt (bit 2 in 
IC_RAW_INTR_STAT register). The valid range is 0-255, with the additional 
restriction that hardware does not allow this value to be set to a value larger than 
the depth of the buffer. If an attempt is made to do that, the actual value set will be 
the maximum depth of the buffer.
A value of 0 sets the threshold for 1 entry, and a value of 255 sets the threshold for 
256 entries.
Reset value: IC_RX_TL configuration parameter
**************************************************/
	Uint32 RX_TL:8; //  0- 7 R/W
	Uint32 rsvd:24;//  8 - 31
};


union I2CIC_RX_TL_REG
{
	Uint32 all;
	struct I2CIC_RX_TL_BITS bit;
};

struct I2CIC_TX_TL_BITS
{
/*****************************
Controls the level of entries (or below) that trigger the TX_EMPTY interrupt (bit 4 in 
IC_RAW_INTR_STAT register). The valid range is 0-255, with the additional 
restriction that it may not be set to value larger than the depth of the buffer. If an 
attempt is made to do that, the actual value set will be the maximum depth of the 
buffer.
A value of 0 sets the threshold for 0 entries, and a value of 255 sets the threshold for 
255 entries.
Reset value: IC_TX_TL configuration parameter
**************************************/
	Uint32 TX_TL:8; // 0- 7 RW
	Uint32 rsvd:24;// 9 - 31
};


union I2CIC_TX_TL_REG
{
	Uint32 all;
	struct I2CIC_TX_TL_BITS bit;
};

struct  I2CIC_CLR_INTR_BITS
{
/**********************************
 Read this register to clear the combined interrupt, all individual interrupts, and the 
IC_TX_ABRT_SOURCE register. This bit does not clear hardware clearable 
interrupts but software clearable interrupts. Refer to Bit 9 of the 
IC_TX_ABRT_SOURCE register for an exception to clearing 
IC_TX_ABRT_SOURCE.
Reset value: 0x0
*************************************************/
	Uint32 CLR_INTR:1; // 0  R  
	Uint32 rsvd:30;   //  1-31 
};

union I2CIC_CLR_INTR_REG
{
	Uint32 all;
	struct  I2CIC_CLR_INTR_BITS bit;
};

struct I2CIC_CLR_RX_UNDER_BITS
{
/**********************************
 Read this register to clear the RX_UNDER interrupt (bit 0) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
*************************************************/
	Uint32 CLR_RX_UNDER:1; // 0  R
	Uint32 rsvd:30;//  1 -  31
};


union I2CIC_CLR_RX_UNDER_REG
{
	Uint32 all;
	struct I2CIC_CLR_RX_UNDER_BITS bit;
};


struct  I2CIC_CLR_RX_OVER_BITS
{
/********************************************
Read this register to clear the RX_OVER interrupt (bit 1) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
***************************************************/
	Uint32 CLR_RX_OVER:1; //  0  R  
	Uint32 rsvd:30; //    1 -  31
};

union I2CIC_CLR_RX_OVER_REG
{
	Uint32 all;
	struct  I2CIC_CLR_RX_OVER_BITS bit;
};

struct  I2CIC_CLR_TX_OVER_BITS
{
/*******************************************
Read this register to clear the TX_OVER interrupt (bit 3) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
******************************************************/
	Uint32 CLR_TX_OVER:1; // 0  R
	Uint32 rsvd:30; //   1  -  31
};

union I2CIC_CLR_TX_OVER_REG
{
	Uint32 all;
	struct  I2CIC_CLR_TX_OVER_BITS bit;
};

struct I2CIC_CLR_RD_REQ_BITS 
{
/***********************************************
Read this register to clear the RD_REQ interrupt (bit 5) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
****************************************************/
	Uint32 CLR_RD_REQ:1; // 0  R 
	Uint32 rsvd:30;
};


union I2CIC_CLR_RD_REQ_REG 
{
	Uint32 all;
	struct I2CIC_CLR_RD_REQ_BITS bit;
};

struct  I2CIC_CLR_TX_ABRT_BITS
{
/****************************************
Read this register to clear the TX_ABRT interrupt (bit 6) of the 
IC_RAW_INTR_STAT register, and the IC_TX_ABRT_SOURCE register.
This also releases the Tx FIFO from the flushed/reset state, allowing more 
writes to the Tx FIFO.
Refer to Bit 9 of the IC_TX_ABRT_SOURCE register for an exception to 
clearing IC_TX_ABRT_SOURCE.
Reset value: 0x0
****************************************************/
	Uint32 CLR_TX_ABRT:1;// 0  R
};

union I2CIC_CLR_TX_ABRT_REG
{
	Uint32 all;
	struct  I2CIC_CLR_TX_ABRT_BITS bit;
};

struct  I2CIC_CLR_RX_DONE_BITS
{
/*************************************
Read this register to clear the RX_DONE interrupt (bit 7) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
****************************************************/
	Uint32 CLR_RX_DONE:1; // 0  R 
	Uint32 rsvd:30; //    1 - 31
};

union I2CIC_CLR_RX_DONE_REG
{
	Uint32 all;
	struct  I2CIC_CLR_RX_DONE_BITS bit;
};

struct I2CIC_CLR_ACTIVITY_BITS
{
/****************************************
Reading this register clears the ACTIVITY interrupt if the I2C is not active 
anymore. If the I2C module is still active on the bus, the ACTIVITY interrupt 
bit continues to be set. It is automatically cleared by hardware if the module 
is disabled and if there is no further activity on the bus. The value read from 
this register to get status of the ACTIVITY interrupt (bit 8) of the 
IC_RAW_INTR_STAT register. 
Reset value: 0x0
****************************************************/
	Uint32 CLR_ACTIVITY:1;// 0  R
	Uint32 rsvd:30; //  1  - 31
};

union I2CIC_CLR_ACTIVITY_REG
{
	Uint32 all;
	struct I2CIC_CLR_ACTIVITY_BITS bit;
};

union I2CIC_CLR_STOP_DET_REG
{
/***************************************************
Read this register to clear the STOP_DET interrupt (bit 9) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
****************************************************/
	Uint32 CLR_STOP_DET:1;//  0  R 
	Uint32 rsvd:30;//  1  -  31
};

struct 	I2CIC_CLR_START_DET_BITS
{
/**************************************
Read this register to clear the START_DET interrupt (bit 10) of the 
IC_RAW_INTR_STAT register.
Reset value: 0x0
***********************************************************/
	Uint32  CLR_START_DET:1; // 0  R 
	Uint32 rsvd:30;//   1 -  31
};


union I2CIC_CLR_START_DET_REG
{
	Uint32 all;
	struct 	I2CIC_CLR_START_DET_BITS bit;
};

struct I2CIC_CLR_GEN_CALL_BITS
{
/*****************************
Read this register to clear the GEN_CALL interrupt (bit 11) of 
IC_RAW_INTR_STAT register.
Reset value: 0x0
********************************************/
	Uint32 CLR_GEN_CALL:1; //  0  R
	Uint32 rsvd:30;   //  1 - 31
};

union I2CIC_CLR_GEN_CALL_REG
{
	Uint32 all;
	struct I2CIC_CLR_GEN_CALL_BITS bit;
};

struct I2CIC_ENABLE_BITS
{
/*******************************
 Controls whether the DW_apb_i2c is enabled. 
■ 0: Disables DW_apb_i2c (TX and RX FIFOs are held in an erased state)
■ 1: Enables DW_apb_i2c
Software can disable DW_apb_i2c while it is active. However, it is important that care be 
taken to ensure that DW_apb_i2c is disabled properly. A recommended procedure is 
described in “Disabling DW_apb_i2c” on page 56.
When DW_apb_i2c is disabled, the following occurs:
■ The TX FIFO and RX FIFO get flushed.
■ Status bits in the IC_INTR_STAT register are still active until DW_apb_i2c goes into 
IDLE state.
If the module is transmitting, it stops as well as deletes the contents of the transmit 
buffer after the current transfer is complete. If the module is receiving, the DW_apb_i2c 
stops the current transfer at the end of the current byte and does not acknowledge the 
transfer.
In systems with asynchronous pclk and ic_clk when IC_CLK_TYPE parameter set to 
asynchronous (1), there is a two ic_clk delay when enabling or disabling the 
DW_apb_i2c.
For a detailed description on how to disable DW_apb_i2c, refer to “Disabling 
DW_apb_i2c” on page 56.
Reset value: 0x0
*******************************************/
	Uint32 ENABLE:1;// 0 R/W
/*****************************************
When set, the controller initiates the transfer abort.
■ 0: ABORT not initiated or ABORT done
■ 1: ABORT operation in progress
The software can abort the I2C transfer in master mode by setting this bit. The software 
can set this bit only when ENABLE is already set; otherwise, the controller ignores any 
write to ABORT bit. The software cannot clear the ABORT bit once set. In response to 
an ABORT, the controller issues a STOP and flushes the Tx FIFO after completing the 
current transfer, then sets the TX_ABORT interrupt after the abort operation. The 
ABORT bit is cleared automatically after the abort operation.
For a detailed description on how to abort I2C transfers, refer to “Aborting I2C Transfers” 
on page 57.
Reset value: 0x0
***************************************************/
	Uint32 ABORT:1; //  1  R/W
	Uint32 rsvd:30; //  2 - 31
};

union I2CIC_ENABLE_REG
{
	Uint32 all;
	struct I2CIC_ENABLE_BITS bit;
};

struct  I2CIC_STATUS_BITS
{
/***********************************************
 I2C Activity Status. 
Reset value: 0x0
**********************************************/
	Uint32 ACTIVITY:1; // 0   R 
/***********************************************
Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty
locations, and is cleared when the FIFO is full.
■ 0: Transmit FIFO is full
■ 1: Transmit FIFO is not full
Reset value: 0x1
**********************************************************************/	
	Uint32 TFNF:1; //  1   R
/******************************************************
Transmit FIFO Completely Empty. When the transmit FIFO is completely empty, 
this bit is set. When it contains one or more valid entries, this bit is cleared. This bit 
field does not request an interrupt.
■ 0: Transmit FIFO is not empty
■ 1: Transmit FIFO is empty
Reset value: 0x1
*****************************************************/	
	Uint32 TFE:1; // 2   R
/*********************************************
Receive FIFO Not Empty. This bit is set when the receive FIFO contains one or 
more entries; it is cleared when the receive FIFO is empty. 
■ 0: Receive FIFO is empty
■ 1: Receive FIFO is not empty
Reset value: 0x0
**************************************************/	
	Uint32 RFNE:1;// 3  R
/**************************************************
 Receive FIFO Completely Full. When the receive FIFO is completely full, this bit is 
set. When the receive FIFO contains one or more empty location, this bit is 
cleared.
■ 0: Receive FIFO is not full
■ 1: Receive FIFO is full
Reset value: 0x0
*****************************************************************/	
	Uint32 RFF:1;//  4  R
/*********************************************************
Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in
the IDLE state, this bit is set.
■ 0: Master FSM is in IDLE state so the Master part of DW_apb_i2c is not Active
■ 1: Master FSM is not in IDLE state so the Master part of DW_apb_i2c is Active
NOTE: IC_STATUS[0]—that is, ACTIVITY bit—is the OR of SLV_ACTIVITY and 
MST_ACTIVITY bits.
Reset value: 0x0
*********************************************************/	
	Uint32 MST_ACTIVITY:1; // 5  R
/************************************************
 Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in 
the IDLE state, this bit is set.
■ 0: Slave FSM is in IDLE state so the Slave part of DW_apb_i2c is not Active
■ 1: Slave FSM is not in IDLE state so the Slave part of DW_apb_i2c is Active
Reset value: 0x0
**************************************************/	
	Uint32  SLV_ACTIVITY:1;// 6  R
	Uint32  rsvd:25; //  7 -- 31
};

union I2CIC_STATUS_REG
{
	Uint32 all;
	struct  I2CIC_STATUS_BITS bit;
};

struct I2CIC_TXFLR_BITS
{
/*********************************************
Transmit FIFO Level. Contains the number of valid data entries in the 
transmit FIFO.
Reset value: 0x0
*******************************************************/
	Uint32 TXFLR:1;// 0  R
	Uint32 rsvd:30; // 1 - 31 
};


union I2CIC_TXFLR_REG
{
	Uint32 all;
	struct I2CIC_TXFLR_BITS bit;
};

struct I2CIC_RXFLR_BITS
{
/*************************************************
Receive FIFO Level. Contains the number of valid data entries in the 
receive FIFO.
Reset value: 0x0
************************************************************/
	Uint32 RXFLR:1;//  0  R
	Uint32 rsvd:30; // 1 - 31
};

union I2CIC_RXFLR_REG
{
	Uint32 all;
	struct I2CIC_RXFLR_BITS bit;
};

struct  I2CIC_SDA_HOLD_BITS
{
/*************************************************
Sets the required SDA hold time in units of ic_clk period, when 
DW_apb_i2c acts as a transmitter.
Reset value: IC_DEFAULT_SDA_HOLD
************************************************************/
	Uint32 IC_SDA_TX_HOLD:16; //  0  -  15 R/W
/******************************************************
 Sets the required SDA hold time in units of ic_clk period, when 
DW_apb_i2c acts as a reciever.
Reset value: IC_DEFAULT_SDA_HOLD
********************************************************/	
	Uint32 IC_SDA_RX_HOLD:8; //  16 - 23   R/W
	Uint32 rsvd:8; // 24- 31
};

union I2CIC_SDA_HOLD_REG
{
	Uint32 all;
	struct  I2CIC_SDA_HOLD_BITS bit;
};

struct I2CIC_TX_ABRT_SOURCE_BITS
{
/**********************************************
■ 1: Master is in 7-bit addressing mode and 
the address sent was not acknowledged by 
any slave.
Reset value: 0x
*****************************************************/
	Uint32 ABRT_7B_ADDR_NOACK:1; //  0  R
/****************************************************
■ 1: Master is in 10-bit address mode and 
the first 10-bit address byte was not 
acknowledged by any slave.
Reset value: 0x0
********************************************************************/	
	Uint32 ABRT_10ADDR1_NOACK:1; //  1  R
/*****************************************************
■ 1: Master is in 10-bit address mode and 
the second address byte of the 10-bit 
address was not acknowledged by any 
slave.
Reset value: 0x0
******************************************************/	
	Uint32 ABRT_10ADDR2_NOACK:1; //  2  R
/****************************************************
 1: This is a master-mode only bit. Master 
has received an acknowledgement for the 
address, but when it sent data byte(s) 
following the address, it did not receive an 
acknowledge from the remote slave(s).
Reset value: 0x0
****************************************************************/	
	Uint32 ABRT_TXDATA_NOACK:1; //   3   R
/******************************************************************
■ 1: DW_apb_i2c in master mode sent a 
General Call and no slave on the bus 
acknowledged the General Call.
Reset value: 0x0
******************************************************************/	
	Uint32 ABRT_GCALL_NOACK:1; //   4   R
/****************************************************************
1: DW_apb_i2c in master mode sent a 
General Call but the user programmed the 
byte following the General Call to be a read 
from the bus (IC_DATA_CMD[9] is set to 
1).
Reset value: 0x0
**********************************************************/	
	Uint32 ABRT_GCALL_READ:1;  //   5  R
/**********************************************************
1: Master is in High Speed mode and the 
High Speed Master code was 
acknowledged (wrong behavior).
Reset value: 0x0
**********************************************************************/	
	Uint32 ABRT_HS_ACKDET:1;  //   6  R
/******************************************************************
1: Master has sent a START Byte and the 
START Byte was acknowledged (wrong behavior)
Reset value: 0x0
********************************************************************/	
	Uint32 ABRT_SBYTE_ACKDET:1; //  7  R
/******************************************************
1: The restart is disabled 
(IC_RESTART_EN bit (IC_CON[5]) = 0) 
and the user is trying to use the master to 
transfer data in High Speed mode.
Reset value: 0x0
*********************************************************************/	
	Uint32 ABRT_HS_NORSTRT:1;   //  8  R
/*****************************************************************
 To clear Bit 9, the source of the 
ABRT_SBYTE_NORSTRT must be fixed first; 
restart must be enabled (IC_CON[5]=1), the 
SPECIAL bit must be cleared (IC_TAR[11]), or 
the GC_OR_START bit must be cleared 
(IC_TAR[10]). Once the source of the 
ABRT_SBYTE_NORSTRT is fixed, then this 
bit can be cleared in the same manner as 
other bits in this register. If the source of the 
ABRT_SBYTE_NORSTRT is not fixed before 
attempting to clear this bit, bit 9 clears for one 
cycle and then gets re-asserted.
1: The restart is disabled (IC_RESTART_EN
bit (IC_CON[5]) = 0) and the user is trying to 
send a START Byte.
Reset value: 0x0
*************************************************************************/	
	Uint32 ABRT_SBYTE_NORSTRT:1; // 9  R
/********************************************************
■ 1: The restart is disabled 
(IC_RESTART_EN bit (IC_CON[5]) = 0) 
and the master sends a read command in 
10-bit addressing mode.
Reset value: 0x0
****************************************************************/	
	Uint32 ABRT_10B_RD_NORSTRT:1;// 10 R
/***************************************************************
1: User tries to initiate a Master operation 
with the Master mode disabled.
Reset value: 0x0
*******************************************************************/	
	Uint32 ABRT_MASTER_DIS:1;    //  11  R
/*************************************************
1: Master has lost arbitration, or if 
IC_TX_ABRT_SOURCE[14] is also set, 
then the slave transmitter has lost 
arbitration.
Reset value: 0x0
****************************************************/	
	Uint32 ARB_LOST:1;           //  12  R  
/*******************************************
1: Slave has received a read command 
and some data exists in the TX FIFO so 
the slave issues a TX_ABRT interrupt to 
flush old data in TX FIFO.
Reset value: 0x0
***************************************/	
	Uint32 ABRT_SLVFLUSH_TXFIFO:1;//  13 R
/************************************************************
1: Slave lost the bus while transmitting data 
to a remote master. 
IC_TX_ABRT_SOURCE[12] is set at the 
same time. 
NOTE: Even though the slave never “owns” 
the bus, something could go wrong on the 
bus. This is a fail safe check. For instance, 
during a data transmission at the low-to-high 
transition of SCL, if what is on the data bus is 
not what is supposed to be transmitted, then 
DW_apb_i2c no longer own the bus.
Reset value: 0x0
********************************************************************/	
	Uint32 ABRT_SLV_ARBLOS:1;    //   14 R
/**********************************************************
 1: When the processor side responds to a 
slave mode request for data to be transmitted 
to a remote master and user writes a 1 in 
CMD (bit 8) of IC_DATA_CMD register.
Reset value: 0x0
*********************************************************/	
	Uint32 ABRT_SLVRD_INTX:1;    //   15 R
/*************************************************************
This is a master-mode-only bit. Master has 
detected the transfer abort (IC_ENABLE[1]).
Reset value: 0x0
**********************************************************************/	
	Uint32 ABRT_USER_ABRT:1;	//  16  R
	Uint32 rsvd:7;				// 17 - 23
/***************************************************
 This field preserves the TXFLR value prior to 
the last TX_ABRT event. It is cleared 
whenever I2C is disabled.
Reset value: 0x0
*************************************************/	
	Uint32 TX_FLUSH_CNT:8;		// R  24 - 31
};

union I2CIC_TX_ABRT_SOURCE_REG
{
	Uint32 all;
	struct I2CIC_TX_ABRT_SOURCE_BITS bit;
};

struct I2CIC_SLV_DATA_NACK_ONLY_BITS 
{
/*********************************************
 Generate NACK. This NACK generation only occurs when DW_apb_i2c is a slavereceiver. If this register is set
 to a value of 1, it can only generate a NACK after a 
data byte is received; hence, the data transfer is aborted and the data received is 
not pushed to the receive buffer. 
When the register is set to a value of 0, it generates NACK/ACK, depending on 
normal criteria. 
■ 1 = generate NACK after data byte received
■ 0 = generate NACK/ACK normally
Reset value: 0x0
****************************************************************/
	Uint32 NACK:1;  // 0  R/W
	Uint32 rsvd:31; //  1 - 31
};

union I2CIC_SLV_DATA_NACK_ONLY_REG
{
	Uint32 all;
	struct I2CIC_SLV_DATA_NACK_ONLY_BITS bit;
};

struct I2CIC_DMA_CR_BITS
{
/*********************************************************************
Receive DMA Enable. This bit enables/disables the receive FIFO DMA channel.
■ 0 = Receive DMA disabled
■ 1 = Receive DMA enabled 
Reset value: 0x0
*********************************************************************/
	Uint32 RDMAE:1; //  0  R/W
/*********************************************************
Transmit DMA Enable. This bit enables/disables the transmit FIFO DMA channel.
■ 0 = Transmit DMA disabled
■ 1 = Transmit DMA enabled
Reset value: 0x0
**************************************************************/	
	Uint32 TDMAE:1;//   1  R/W
	Uint32 rsvd:30; //  2 - 31 
};

union I2CIC_DMA_CR_REG
{
	Uint32 all;
	struct I2CIC_DMA_CR_BITS bit;
};

struct  I2CIC_DMA_TDLR_BITS 
{
/******************************************************
Transmit Data Level. This bit field controls the level at which a DMA 
request is made by the transmit logic. It is equal to the watermark 
level; that is, the dma_tx_req signal is generated when the number of 
valid data entries in the transmit FIFO is equal to or below this field 
value, and TDMAE = 1.
Reset value: 0x0
******************************************************************/
	Uint32 DMATDL:32; // 0 - 31  R/W
//	Uint32 rsvd:1;
};

union I2CIC_DMA_TDLR_REG
{
	Uint32 all;
	struct  I2CIC_DMA_TDLR_BITS bit;
};

struct I2CIC_DMA_RDLR_BITS
{
/****************************************************
 Receive Data Level. This bit field controls the level at which a DMA 
request is made by the receive logic. The watermark level = DMARDL+1; 
that is, dma_rx_req is generated when the number of valid data entries in 
the receive FIFO is equal to or more than this field value + 1, and 
RDMAE = 1. For instance, when DMARDL is 0, then dma_rx_req is 
asserted when 1 or more data entries are present in the receive FIFO. 
Reset value: 0x0
*****************************************************/
	Uint32 DMARDL:32;  // >2 RW
//	Uint32 rsvd:1;
};

union I2CIC_DMA_RDLR_REG
{
	Uint32 all;
	struct I2CIC_DMA_RDLR_BITS bit;
};

struct I2CIC_SDA_SEUP_BITS
{
/****************************************
SDA Setup. It is recommended that if the required delay is 1000ns, then for an 
ic_clk frequency of 10 MHz, IC_SDA_SETUP should be programmed to a 
value of 11. IC_SDA_SETUP must be programmed with a minimum value of 2.
Default Reset value: 0x64, but can be hardcoded by setting the 
IC_DEFAULT_SDA_SETUP configuration parameter.
**************************************************/
	Uint32 SDA_SETUP:8;  //  0  --  7
	Uint32 rsvd:24; //   8 - 31
};

union I2CIC_SDA_SEUP_REG
{
	Uint32 all;
	struct I2CIC_SDA_SEUP_BITS bit;
};

struct I2CIC_ACK_GENERAL_CALL_BITS
{
/****************************************************
ACK General Call. When set to 1, DW_apb_i2c responds with a ACK (by 
asserting ic_data_oe) when it receives a General Call. When set to 0, the 
DW_apb_i2c does not generate General Call interrupts.
Default Reset value: 0x1, but can be hardcoded by setting the 
IC_DEFAULT_ACK_GENERAL_CALL configuration parameter.
*********************************************************/
	Uint32 ACK_GEN_CALL:1; // 0  R/W 
	Uint32 rsvd:31; // 1 - 31
};


union I2CIC_ACK_GENERAL_CALL_REG
{
	Uint32 all;
	struct I2CIC_ACK_GENERAL_CALL_BITS bit;
};

struct I2CIC_ENABLE_STATUS_BITS
{
/************************************************
 ic_en Status. This bit always reflects the value driven on the output port 
ic_en.
■ When read as 1, DW_apb_i2c is deemed to be in an enabled state.
■ When read as 0, DW_apb_i2c is deemed completely inactive.
NOTE: The CPU can safely read this bit anytime. When this bit is read as 
0, the CPU can safely read SLV_RX_DATA_LOST (bit 2) and 
SLV_DISABLED_WHILE_BUSY (bit 1).
Reset value: 0x0
********************************************************/
	Uint32 IC_EN:1;    //   0   R 
/******************************************************
 Slave Disabled While Busy (Transmit, Receive). This bit indicates if a 
potential or active Slave operation has been aborted due to setting bit 0 of 
the IC_ENABLE register from 1 to 0. This bit is set when the CPU writes 
a 0 to bit 0 of IC_ENABLE while: (a) DW_apb_i2c is receiving the address 
byte of the Slave-Transmitter operation from a remote master; OR, (b) 
address and data bytes of the Slave-Receiver operation from a remote 
master.
When read as 1, DW_apb_i2c is deemed to have forced a NACK during 
any part of an I2C transfer, irrespective of whether the I2C address 
matches the slave address set in DW_apb_i2c (IC_SAR register) OR if the 
transfer is completed before bit 0 of IC_ENABLE is set to 0, but has not 
taken effect. 
NOTE: If the remote I2C master terminates the transfer with a STOP 
condition before the DW_apb_i2c has a chance to NACK a transfer, and 
bit 0 of IC_ENABLE has been set to 0, then this bit will also be set to 1.
When read as 0, DW_apb_i2c is deemed to have been disabled when 
there is master activity, or when the I2C bus is idle.
NOTE: The CPU can safely read this bit when IC_EN (bit 0) is read as 0.
Reset value: 0x0
******************************************************/	
	Uint32 SLV_DISABLED_WHILE_BUSY:1;//   1  R
/***************************************************************
Slave Received Data Lost. This bit indicates if a Slave-Receiver operation 
has been aborted with at least one data byte received from an I2C transfer 
due to setting IC_ENABLE[0] from 1 to 0.
When read as 1, DW_apb_i2c is deemed to have been actively engaged in 
an aborted I2C transfer (with matching address) and the data phase of the 
I2C transfer has been entered, even though a data byte has been 
responded with a NACK. 
NOTE: If the remote I2C master terminates the transfer with a STOP 
condition before the DW_apb_i2c has a chance to NACK a transfer, and 
IC_ENABLE[0] has been set to 0, then this bit is also set to 1.
When read as 0, DW_apb_i2c is deemed to have been disabled without 
being actively involved in the data phase of a Slave-Receiver transfer.
NOTE: The CPU can safely read this bit when IC_EN (bit 0) is read as 0.
Reset value: 0x0
******************************************************************/	
	Uint32 SLV_RX_DATA_LOST:1;   //     2   R
	Uint32 rsvd:29;				//		3 - 31  
};

union I2CIC_ENABLE_STATUS_REG
{
	Uint32 all;
	struct I2CIC_ENABLE_STATUS_BITS bit;
};

struct I2CIC_FS_SPKLEN_BITS
{
/***********************************************
This register must be set before any I2C bus transaction can take place to 
ensure stable operation. This register sets the duration, measured in ic_clk
cycles, of the longest spike in the SCL or SDA lines that are filtered out by 
the spike suppression logic; for more information, refer to “Spike 
Suppression” on page 57.
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have 
no effect.
The minimum valid value is 1; hardware prevents values less than this 
being written, and if attempted, results in 1 being set. 
Reset value: IC_DEFAULT_FS_SPKLEN configuration parameter
*****************************************************************/
	Uint32 IC_FS_SPKLEN:8;//  0 - 7  R/W
	Uint32 rsvd:24;  //  8  -  31
};


union I2CIC_FS_SPKLEN_REG
{
	Uint32 all;
	struct I2CIC_FS_SPKLEN_BITS bit;
};

struct I2CIC_HS_SPKLEN_BITS
{
/************************************************
 This register must be set before any I2C bus transaction can take place to 
ensure stable operation. This register sets the duration, measured in ic_clk
cycles, of the longest spike in the SCL or SDA lines that are filtered out by 
the spike suppression logic; for more information, refer to “Spike 
Suppression” on page 57.
This register can be written only when the I2C interface is disabled, which 
corresponds to IC_ENABLE[0] being set to 0. Writes at other times have 
no effect.
The minimum valid value is 1; hardware prevents values less than this 
being written, and if attempted, results in 1 being set. 
This register is implemented only if the component is configured to support 
HS mode; that is, if the IC_MAX_SPEED_MODE parameter is set to 3.
Reset value: IC_DEFAULT_HS_SPKLEN configuration parameter
**********************************************************/
	Uint32 IC_HS_SPKLEN:8; //  0 - 7   R/W
	Uint32 rsvd:24;			//  8 - 31
};


union I2CIC_HS_SPKLEN_REG
{
	Uint32 all;
	struct I2CIC_HS_SPKLEN_BITS bit;
};


struct I2CIC_CLR_RESTART_DET_BITS
{
/*******************************************
Read this register to clear the RESTART_DET interrupt (bit 12) of 
the IC_RAW_INTR_STAT register. 
Dependencies: This register is present only when 
IC_SLV_RESTART_DET_EN = 1.
Reset value: 0x0
***************************************************/
	Uint32 CLR_RESTART_DET:1; //  0    R 
	Uint32 rsvd:31; 			//  1 - 31 
};


union I2CIC_CLR_RESTART_DET_REG
{
	Uint32 all;
	struct I2CIC_CLR_RESTART_DET_BITS bit;
};

struct I2CIC_COMP_PARAM_1_BITS
{
/*******************************************************
The value of this register is derived from the 
APB_DATA_WIDTH coreConsultant parameter. For a 
description of this parameter, see Table 4-1 on page 77. ■ 0x0 = 8 bits
■ 0x1 = 16 bits
■ 0x2 = 32 bits
■ 0x3 = Reserved
*************************************************************/
	Uint32 APB_DATA_WIDTH:2;  //  0 - 1 R
/*********************************************************
The value of this register is derived from the 
IC_MAX_SPEED_MODE coreConsultant parameter. For a 
description of this parameter, see Table 4-1 on page 77. ■ 0x0 = Reserved
■ 0x1 = Standard
■ 0x2 = Fast
■ 0x3 = High
*********************************************************/	
	Uint32 MAX_SPEED_MODE:2; //  2 - 3 R
/*********************************************************
The value of this register is derived from the 
IC_HC_COUNT_VALUES coreConsultant parameter. For a 
description of this parameter, see Table 4-1 on page 77. ■ 0: False
■ 1: True
****************************************************************/	
	Uint32 HC_COUNT_VALUES:1; //  4   R
/***********************************************************
 The value of this register is derived from the IC_INTR_IO 
coreConsultant parameter. For a description of this 
parameter, see Table 4-1 on page 77. ■ 0: Individual
■ 1: Combined
**********************************************************/	
	Uint32 INTR_IO:1;  //5  R 
/*******************************************************
 The value of this register is derived from the IC_HAS_DMA 
coreConsultant parameter. For a description of this 
parameter, see Table 4-1 on page 77. ■ 0: False
■ 1: True
******************************************************/	
	Uint32 HAS_DMA:1;  // 6  R
/**************************************************************
The value of this register is derived from the 
IC_ADD_ENCODED_PARAMS coreConsultant parameter. 
For a description of this parameter, see Table 4-1 on page 
77. Reading 1 in this bit means that the capability of reading 
these encoded parameters via software has been included. 
Otherwise, the entire register is 0 regardless of the setting of 
any other parameters that are encoded in the bits.
■ 0: False
■ 1: True
********************************************************************/	
	Uint32 ADD_ENCODED_PARAMS:1;//  7   R
/*************************************************************
 The value of this register is derived from the 
IC_RX_BUFFER_DEPTH coreConsultant parameter. For a 
description of this parameter, see Table 4-1 on page 77. ■ 0x00 = Reserved
■ 0x01 = 2
■ 0x02 = 3
…■ 0xFF = 256
********************************************/	
	Uint32 RX_BUFFER_DEPTH:8;	// 8  -  15  R
/*********************************************************************
 The value of this register is derived from the 
IC_TX_BUFFER_DEPTH coreConsultant parameter. 
■ 0x00 = Reserved
■ 0x01 = 2
■ 0x02 = 3
…■ 0xFF = 256
**********************************************************/	
	Uint32 TX_BUFFER_DEPTH:8;	// 16 - 23  R 
	Uint32 rsvd:8;				//  24 - 31
};

union I2CIC_COMP_PARAM_1_REG
{
	Uint32 all;
	struct I2CIC_COMP_PARAM_1_BITS bit;
};



struct I2C_REGS {
	union I2CIC_CON_REG I2CIC_CON;  	// 00H   I2C Contro 
	union I2CIC_TAR_REG I2CIC_TAR;	// 04H   
	union I2CIC_SAR_REG I2CIC_SAR;	// 08H    
	union I2CIC_HS_MADDR_REG I2CIC_HS_MADDR;// 0CH 
	union I2CIC_DATA_CMD_REG I2CIC_DATA_CMD; //10H 
	union I2CIC_SS_SCL_HCNT_REG I2CIC_SS_SCL_HCNT; //14H  
	union I2CIC_SS_SCL_LCNT_REG I2CIC_SS_SCI_LCNT; //18H  
	union I2CIC_FS_SCL_HCNT_REG I2CIC_FS_SCL_HCNT; //1CH  
	union I2CIC_FS_SCL_LCNT_REG I2CIC_FS_SCL_LCNT; //20H  
	union I2CIC_HS_SCL_HCNT_REG I2CIC_HS_SCL_HCNT; //24H  
	union I2CIC_HS_SCL_LCNT_REG I2CIC_HS_SCL_LCNT; //28H  
	union I2CIC_INTR_STAT_REG I2CIC_INTR_STAT;  //2CH   Reset value: 0x0
	union I2CIC_INTR_MASK_REG I2CIC_INTR_MASK;  //30H	
	union I2CIC_RAW_INTR_STAT_REG I2CIC_RAW_INTR_STAT; //34H
	union I2CIC_RX_TL_REG I2CIC_RX_TL;   //   38H
	union I2CIC_TX_TL_REG I2CIC_TX_TL;   	//3CH
	union I2CIC_CLR_INTR_REG I2CIC_CLR_INTR;	//40H
	union I2CIC_CLR_RX_UNDER_REG I2CIC_CLR_RX_UNDER;//44H
	union I2CIC_CLR_RX_OVER_REG  I2CIC_CLR_RX_OVER;// 48H
	union I2CIC_CLR_TX_OVER_REG I2CIC_CLR_TX_OVER; //4CH
	union I2CIC_CLR_RD_REQ_REG I2CIC_CLR_RD_REQ;//  50H
	union I2CIC_CLR_TX_ABRT_REG I2CIC_CLR_TX_ABRT;// 54H
	union I2CIC_CLR_RX_DONE_REG I2CIC_CLR_RX_DONE;// 58H
	union I2CIC_CLR_ACTIVITY_REG I2CIC_CLR_ACTIVITY;//5CH
	union I2CIC_CLR_STOP_DET_REG I2CIC_CLR_STOP_DET;//60h
	union I2CIC_CLR_START_DET_REG I2CIC_CLR_START_DET;//64H
	union I2CIC_CLR_GEN_CALL_REG I2CIC_CLR_GEN_CALL;// 68H
	union I2CIC_ENABLE_REG I2CIC_ENABLE;		//  6CH
	union I2CIC_STATUS_REG I2CIC_STATUS;		//  70H
	union I2CIC_TXFLR_REG I2CIC_TXFLR;		//  74H
	union I2CIC_RXFLR_REG I2CIC_RXFLR;		//  78H
	union I2CIC_SDA_HOLD_REG I2CIC_SDA_HOLD;	//  7CH
	union I2CIC_TX_ABRT_SOURCE_REG I2CIC_TX_ABRT_SOURCE; //80H
	union I2CIC_SLV_DATA_NACK_ONLY_REG I2CIC_SLV_DATA_NACK_ONLY;//84H
	union I2CIC_DMA_CR_REG I2CIC_DMA_CR;////			88h
	union I2CIC_DMA_TDLR_REG I2CIC_DMA_TDLR;//			8CH
	union I2CIC_DMA_RDLR_REG I2CIC_DMA_RDLR;//			90H
	union I2CIC_SDA_SEUP_REG I2CIC_SDA_SEUP;//		94H
	union I2CIC_ACK_GENERAL_CALL_REG I2CIC_ACK_GENERAL_CALL;		//98H
	union I2CIC_ENABLE_STATUS_REG I2CIC_ENABLE_STATUS;	//9CH
	union I2CIC_FS_SPKLEN_REG I2CIC_FS_SPKLEN;				//A0H
	union I2CIC_HS_SPKLEN_REG I2CIC_HS_SPKLEN;		//A4H
	union I2CIC_CLR_RESTART_DET_REG I2CIC_CLR_RESTART_DET;//		A8H
	Uint32 rsvd1[18];
	union I2CIC_COMP_PARAM_1_REG I2CIC_COMP_PARAM_1;    //   F4H
	Uint32 I2CIC_VERSION;   //    F8H
	/****************************
	Designware Component Type number = 0x44_57_01_40. This 
assigned unique hex value is constant and is derived from the two 
ASCII letters “DW” followed by a 16-bit unsigned number.
	**************/
	Uint32  I2CIC_COMP_TYPE;//		  FCH	
};


extern volatile struct I2C_REGS *const P_I2caRegs ;
extern volatile struct I2C_REGS I2caRegs ;

	

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2802x_I2C_H definition

//===========================================================================
// End of file.
//===========================================================================
