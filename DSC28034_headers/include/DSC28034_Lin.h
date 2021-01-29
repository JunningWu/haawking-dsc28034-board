
#ifndef DSC28034_LIN_H
#define DSC28034_LIN_H


struct LSEL_BITS
{
/***************************************************************************************************
    这个是是FIFO 位置，通过这个可以控制数据 放入FIFO 的位置。
*******************************************************************************************/
	Uint32  INDEX:4; // 0 - 3  Location of the LIN response data byte into the FIFO data buffer.
	/********************************************
	Setting this bit adds a delay between writing to LCR register and executing the command in DLIN. 
	The length of the delay is ½ the length of the 	bit on the LIN bus.
	0:Delay is disabled 
	1:Delay is enabled
	****************************************/
	Uint32  DLY:1; //   1
	Uint32  rsvd1:2;
	/**********************************************
	Auto increment FIFO index after access
	0:Auto increment mode disabled 
	1:Auto increment mode enabled

	数据自动压入FIFO 功能，当开启的时候，发送端数据按照顺序放入FIFO 中，每次向LBUF 写入数据，
	INDEX，也就是位置 就会自动加一
	读取的时候也是每次读取LBUF ，INDEX 就会自动加一
	
	*************************************************/
	Uint32 AINC:1;
	Uint32 rsvd2:24;
};


union    LSEL_REG
{
	Uint32 all;
	struct LSEL_BITS bit;
};

struct LID_BITS
{
/*******************************************
Indicates LIN bus identifier.
If LCR[5:2] are “1111” then bits LID[5:4] indicates number of data in message frame:
 00 – 2 bytes
 01 – 2 bytes
 10 – 4 bytes
 11 – 8 bytes
*****************************************************/
	Uint32  ID:6;
	Uint32  rsvd:26;
};

union    LID_REG
{
	Uint32 all;
	struct LID_BITS bit;
};


struct LER_BITS
{
/***************************************************
Framing error flag. This flag indicates that the received character did not have a valid Stop bit.
0:No framing error has been detected. 
1:Framing error has been detected.
*************************************************/
	Uint32  FER:1;
/***********************************************
Bit error flag. This flag indicates that bit value monitored on bus is different from the bit value that is sent 
0:No bit error has been detected.
1:Bit error has been detected.
*****************************************************/
	Uint32 BITER:1;
/**************************************************
Parity error flag. This flag indicates that received header did not have correct
Protected Identifier field. 
0:No parity error has been detected. 
1:Parity error has been detected in received header
******************************************************/
	Uint32 PER:1;
/******************************************************
Checksum error flag. This flag indicates that inverted modulo-256 sum of all received 
data bytes added to the checksum does not result in 0xFF
0:No checksum error has been detected.
1:Checksum error has been detected.
**********************************************/
	Uint32 CHKSER:1;
/*******************************************************
Frame time out error flag.
0:No timeout error has been detected.
1:Timeout error has been detected.
**********************************************/
	Uint32 TOVER:1;
/**********************************************
Synchronization error flag. (slave mode only)
0:No error with the SYNC field has been detected
1:Edges of SYNC field are outside of the maximum tolerance
****************************************************/
	Uint32 SYNCER:1;
/**************************************************
Overrun error flag. This flag indicates that write has been occurred while RDY flag is low. 
0:No overrun error has been detected.
1:Overrun error has been detected.
**************************************************/
	Uint32 OVER:1;
/********************************************
Wake up error flag (slave node only). 
0:No wake-up error has been detected.
1:Wake-up response from master node not has been received.
*****************************************************/
	Uint32 WAKEER:1;

	Uint32 rsvd:24;
};


union   LER_REGS
{
	Uint32 all;
	struct LER_BITS bit;
};


struct LIE_BITS
{
/**********************************************
Enable header receive interrupt. (slave mode only)
0:Header received interrupt disabled.
1:Header received interrupt enabled.
***********************************************/
	Uint32   LIDE:1;
/*************************************************
Enable ready interrupt 
0:Ready interrupt disabled 
1:Ready interrupt enabled
******************************************************/
	Uint32 RDYE:1;
/****************************************************
Enable Error Interrupt 
0:Error interrupt disabled
1:Error interrupt enabled
************************************************/
	Uint32 ERRE:1;
/***************************************************
Enable ABORT Interrupt
0:Abort command interrupt disabled 
1:Abort command interrupt enabled
***************************************************/
	Uint32 ABORTE:1;
/***************************************************
Sleep condition interrupt. 
0:Sleep interrupt disable
1:Sleep interrupt enable
************************************************/
	Uint32 SLEEP:1;
/*****************************************************
Enable wakeup detection interrupt
0:Wake-up interrupt disable
1:Wake-up interrupt enable
**********************************************/
	Uint32  WAKEE:1;

	Uint32 rsvd:26;
};


union   LIE_REGS
{
	Uint32 all;
	struct LIE_BITS bit;
};

struct LSR_BITS 
{
/**************************************************
Header receive flag. (slave mode only)
0:no header received
1:Complete header has been received.
**********************************************/
	Uint32  LID:1;
/************************************************
Ready flag. This bit is set after command executed.
0:current command is in the progress
1:indicates idle state
******************************************************/
	Uint32  RDY:1;
/*************************************************
Error flag. 
0:no error
1:indicates transmission error
*************************************************/
	Uint32  ERR:1;
/************************************************
Abort command flag. Abort transfer command is executed, while BUSY flag is set.
0:no abort command 
1:current command execution has been aborted
******************************************************/
	Uint32 ABORT:1;
/************************************************
Detected size of received message , available only when log mode is 
enable. In others cases return 0000
**************************************************/
	Uint32 LOG_SIZE:4;

	Uint32 rsvd:24;
};


union   LSR_LCR_REGS
{
/******************************************
由于 LCR 是只写寄存器,并且读取时候是返回LSR 的值， 
所以不能通过bit域 的方式进行赋值
**************************************************/
	Uint32 all;
	struct LSR_BITS LSR_bit;
};


struct  DLL_BITS
{
	Uint32 DLL:8;
	Uint32 rsvd:24;
};


union   DLL_REGS
{
	Uint32  all;
	struct  DLL_BITS bit;
};

struct DLH_BITS
{
/******************************************
[6:0] Baud rate divider most significant bits.
****************************************/
	Uint32  DLH:7; //0-6
/************************************************
Synchronization mode (slave mode only)
0:Synchronization mode disabled 
1:Synchronization mode enabled
This bit is automatically cleared after detection of the synchronization field
**********************************************/	
	Uint32  SYNC:1;// 7
	Uint32  rsvd:24;
};

union   DLH_REGS
{
	Uint32 all;
	struct DLH_BITS  DLH;
};


struct LBR_BITS
{
/****************************************************
Sleep mode. 
0:DLIN is normal mode
1:DLIN is in sleep mode
**************************************/
	Uint32 SLEEPM:1;// 0
/************************************************
Wake-up signal detection
0:No wake-up signal
1:Wake-up signal detected
*********************************************/	
	Uint32 WAKEUP:1;//1
/***********************************************
Sleep mode detection
0:No Sleep condition occurred
1:Sleep condition occur
***************************************************/	
	Uint32 SLEEP:1;

	Uint32 rsvd:29;
};


union  LBR_REG 
{
	Uint32 all;
	struct LBR_BITS bit;
};


struct IDTH_BITS
{
	Uint32 IDT:5;//0-4 
	Uint32 rsvd1:2;
	Uint32 IDTRUN:1;
	Uint32 rsvd2:24;
};


union  IDTH_REGS
{
	Uint32 all;
	struct IDTH_BITS bit;
};

struct LRBR_BITS
{
	Uint32 RBR:8; //receive data buf
	Uint32 RSVD_RBR:24;
};

struct LDLL_BITS
{
/********************************************************************************************
Divisor Latch (Low).
This register makes up the lower 8-bits of a 16-bit, read/write, Divisor Latch register that contains 
the baud rate divisor for the UART.The output baud rate is equal to the serial clock (pclk if one clock design,
sclk if two clock design (CLOCK_MODE == Enabled)) frequency divided by sixteen times the value of the baud rate 
divisor, as follows: baud rate = (serial clock freq) / (16 * divisor).
Note that with the Divisor Latch Registers (DLL and DLH) set to zero, the baud clock is disabled and no 
serial communications will occur. Also, once the DLL is set, at least 8 clock cycles of the slowest DW_apb_uart
clock should be allowed to pass before transmitting or receiving data.
Value After Reset: 0x0
Exists: Always
****************************************************************************************************/
	Uint32 DLL:8;//0-7
	Uint32 RSVD_DLL : 24;
};

struct LTHR_BITS
{
	Uint32 THR:8;     //Transmit Holding RegisterU
	Uint32 RSVD_THR:23;
};

union LRBR_DLL_THR_REG
{
	Uint32 all;
	struct LRBR_BITS  LRBR_bits;
	struct LDLL_BITS  LDLL_bits;
	struct LTHR_BITS  LTHR_bits;
};


struct LDLH_BITS
{
	Uint32 dlh:8;//Upper 8-bits of a 16-bit, read/write, Divisor Latch register that contains the baud rate divisor for the UART.
//The output baud rate is equal to the serial clock (pclk if one clock design, sclk if two clock design (CLOCK_MODE == Enabled)) frequency 
//divided by sixteen times the value of the baud rate divisor, as follows: baud rate = (serial clock freq) /
	Uint32 rsvd:24;
};


struct LIER_BITS
{
/************************
Enable Received Data Available Interrupt. This is used to enable/disable
the generation of Received Data Available Interrupt 
and the Character Timeout Interrupt (if in FIFO mode and FIFO's enabled). 
These are the second highest priority interrupts.
Values:
■0x0 (DISABLED): Disable Receive data Interrupt
■0x1 (ENABLED): Enable Receive data Interrupt
Value After Reset: 0x0
Exists: Always
***********************************/
	Uint32 ERBFI:1;// 0 R/W  
/********************************************************************
Enable Transmit Holding Register Empty Interrupt. This is used to enable/disable
the generation of Transmitter Holding Register Empty Interrupt. This is the 
third highest priority interrupt.
Values:
■0x0 (DISABLED): Disable Transmit empty interrupt
■0x1 (ENABLED): Enable Transmit empty interrupt
Value After Reset: 0x0
Exists: Always
*******************************************************************/	
	Uint32 ETBEI:1;// 1 R/W
/*********************************************************************
Enable Receiver Line Status Interrupt. This is used to enable/disable the
generation of Receiver Line Status Interrupt. This is the highest priority interrupt.
Values:
■0x0 (DISABLED): Disable Receiver Line Status Interrupt
■0x1 (ENABLED): Enable Receiver Line Status Interrupt
Value After Reset: 0x0
Exists: Always
**************************************************************/
	Uint32 ELSI:1;//  2 R/W

/************************************************************************
Enable Modem Status Interrupt. This is used to enable/disable the generation of 
Modem Status Interrupt. This is the fourth highest priority interrupt.
Values:
■0x0 (DISABLED): Disable Modem Status Interrupt
■0x1 (ENABLED): Enable Modem Status Interrupt
Value After Reset: 0x0
Exists: Always

*********************************************************************/	
	Uint32 EDSSI:1;// 3 R/W

/*******************************************************************
Interrupt Enable Register: ELCOLR, this bit controls the method for clearing 
the status in the LSR register. This is applicable only for Overrun Error,
Parity Error, Framing Error, and Break Interrupt status bits. 0 = LSR status 
bits are cleared either on reading Rx FIFO (RBR Read) or On reading LSR register.
1 = LSR status bits are cleared only on reading LSR register.
Writeable only when LSR_STATUS_CLEAR == Enabled, always readable.
Values:
■0x0 (DISABLED): Disable ALC
■0x1 (ENABLED): Enable ALC
Value After Reset: 0x0
Exists: Always
Memory Access: "(LSR_STATUS_CLEAR==1) ? \"read-write\" : \"read-only\"

*************************************************************/
	Uint32 ELCOLR:1;// 4  * Varies

/*********************************************************************
IER 6to5 Reserved bits read as zero (0).
Value After Reset: 0x0
Exists: Always
*****************************************************************/
	Uint32 RSVD_IER_6to5:2; // 5-6 R

/****************************************************************************
Programmable THRE Interrupt Mode Enable. Writeable only when 
THRE_MODE_USER == Enabled, always readable. 
This is used to enable/disable the generation of THRE Interrupt.
Values:
■0x0 (DISABLED): Disable Programmable THRE Interrupt Mode
■0x1 (ENABLED): Enable Programmable THRE Interrupt Mode
Value After Reset: 0x0
Exists: Always
Memory Access: "(THRE_MODE_USER==1 && FIFO_MODE!=0) ? \"read-write\" : \"read-only\""
****************************************************************************/
	Uint32 PTIME:1; //7  * Varies

/***********************************************************
IER 31to8 Reserved bits and read as zero (0).
Value After Reset: 0x0
Exists: Always
*************************************************************/	
	Uint32 RSVD_IER_31to8:24; // 8-31  R  
	
 };

union LDLH_IER_REG
{
	Uint32 all;
	struct LDLH_BITS LDLH_bits;
	struct LIER_BITS LIER_bits;
};

struct LFCR_BITS
{
/*****************************************
FIFO Enable (or FIFOE). This enables/disables the transmit (XMIT) 
and receive (RCVR) FIFOs. Whenever the value of this bit is 
changed both the XMIT and RCVR controller portion of FIFOs is reset.
Values:
■0x0 (DISABLED): FIFO disabled
■0x1 (ENABLED): FIFO enabled
Value After Reset: 0x0
Exists: Always
**************************************************/
	Uint32 FIFOE:1; //0 W 
/***********************************************
RCVR FIFO Reset (or RFIFOR). This resets the control 
portion of the receive FIFO and treats the FIFO as empty. 
This will also de-assert the DMA RX request and single 
signals when additional DMA handshaking signals are selected 
.(DMA_EXTRA == YES). Note that this bit is 'self-clearing' 
and it is not necessary to clear this bit.
Values:
■0x1 (RESET): Receive FIFO reset
Value After Reset: 0x0
Exists: Always
**************************************************/	
	Uint32 RFIFOR:1; //1 W
/**************************************************************
XMIT FIFO Reset (or XFIFOR). This resets the control portion of 
the transmit FIFO and treats the FIFO as empty. This will also 
de-assert the DMA TX request and single signals when additional 
DMA handshaking signals are selected (DMA_EXTRA == YES). Note 
that this bit is 'self-clearing' and it is not necessary to clear this bit.
Values:
■0x1 (RESET): Transmit FIFO reset
Value After Reset: 0x0
Exists: Always
************************************************************/	
	Uint32 XFIFOR:1; //2 W
/**********************************************************
DMA Mode (or DMAM). This determines the DMA signalling mode 
used for the dma_tx_req_n and dma_rx_req_n output signals 
when additional DMA handshaking signals are not selected 
(DMA_EXTRA == NO). For details on DMA support, refer to 
'DMA Support' section of data book.
Values:
■0x0 (MODE0): Mode 0
■0x1 (MODE1): Mode 1
Value After Reset: 0x0
Exists: Always
*********************************************************/
	Uint32 DMAM:1;  // 3 W
/**************************************************************
TX Empty Trigger (or TET). Writes will have no effect when THRE_MODE_USER == 
Disabled. This is used to select the empty threshold level at which the 
THRE Interrupts will be generated when the mode is active. It also determines 
when the dma_tx_req_n signal will be asserted when in certain modes of operation.
For details on DMA support, refer to 'DMA Support' section of data book.
Values:
■0x0 (FIFO_EMPTY): FIFO Empty
■0x1 (FIFO_CHAR_2): 2 characters in FIFO
■0x2 (FIFO_QUARTER_FULL): FIFO 1/4 full
■0x3 (FIFO_HALF_FULL): FIFO 1/2 full
Value After Reset: 0x0
Exists: Always
Memory Access: "(THRE_MODE_USER==1) ? \"write-only\" : \"read-only\""
**************************************************************/
	Uint32 TET:2; // 4-5  * Varies
/*************************************************************
RCVR Trigger (or RT). This is used to select the trigger level 
in the receiver FIFO at which the Received Data Available Interrupt
will be generated. In auto flow control mode, it is used to determine 
when the rts_n signal will be de-asserted only when RTC_FCT is disabled.
It also determines when the dma_rx_req_n signal will be asserted when in
certain modes of operation. For details on DMA support, 
refer to 'DMA Support' section of data book.
Values:
■0x0 (FIFO_CHAR_1): 1 character in FIFO
■0x1 (FIFO_QUARTER_FULL): FIFO 1/4 full
■0x2 (FIFO_HALF_FULL): FIFO 1/2 full
■0x3 (FIFO_FULL_2): FIFO 2 less than full
Value After Reset: 0x0
Exists: Always
***************************************************************/	
	Uint32 RT:2; //6-7 W
	Uint32 RSVD_FCR_31to8:24;
};

struct LIIR_BITS
{
/******************************************************************************
Interrupt ID (or IID). This indicates the highest priority pending interrupt which 
can be one of the following types specified in Values. For information on several 
levels into which the interrupt priorities are split into, see the 'Interrupts' 
section in the DW_apb_uart Databook. Note: an interrupt of type 0111 (busy detect)
will never get indicated if UART_16550_COMPATIBLE == YES in coreConsultant.
Bit 3 indicates an interrupt can only occur when the FIFOs are enabled and used 
to distinguish a Character Timeout condition interrupt.
Values:
■0x0 (MODEM_STATUS): modem status
■0x1 (NO_INTERRUPT_PENDING): no interrupt pending
■0x2 (THR_EMPTY): THR empty
■0x4 (RECEIVED_DATA_AVAILABLE): received data available
■0x6 (RECEIVER_LINE_STATUS): receiver line status
■0x7 (BUSY_DETECT): busy detect
■0xc (CHARACTER_TIMEOUT): character timeout
Value After Reset: 0x1
Exists: Always
********************************************************************************/
	Uint32 IID:4; //0-3 R
	Uint32 RSVD_IIR_5to4:2;// 4-5
/*******************************************************************************
FIFOs Enabled (or FIFOSE). This is used to indicate whether the FIFOs are enabled or disabled.
Values:
■0x0 (DISABLED): FIFOs are disabled
■0x3 (ENABLED): FIFOs are enabled
Value After Reset: 0x0
Exists: Always
*******************************************************************************/
	Uint32 FIFOSE:2; //6-7  R	
	Uint32 RSVD_IIR_31to8:24;	
	
};

union LFCR_IIR_REG
{
	Uint32 all;
	struct LFCR_BITS   LFCR_bits;
	struct LIIR_BITS   LIIR_bits;
};


struct LLCR_BITS
{
/*************************************************************************
Data Length Select (or CLS as used in legacy).
If UART_16550_COMPATIBLE == NO then, writeable only when UART is 
not busy (USR[0] is zero),otherwise always writable and always readable.
When DLS_E in LCR_EXT is set to 0,this register is used to select the
number of data bits per character that the peripheral will transmit and receive.
Values:
■0x0 (CHAR_5BITS): 5 data bits per character
■0x1 (CHAR_6BITS): 6 data bits per character
■0x2 (CHAR_7BITS): 7 data bits per character
■0x3 (CHAR_8BITS): 8 data bits per character
Value After Reset: 0x0
Exists: Always
**************************************************************************/
	Uint32 DLS:2; //0-1  RW
/*******************************************************************
Number of stop bits.
If UART_16550_COMPATIBLE == NO then, writeable only when UART is not 
busy (USR[0] is zero), otherwise always writable and always readable. 
This is used to select the number of stop bits per character that the
peripheral will transmit and receive. If set to zero, one stop bit is 
transmitted in the serial data.If set to one and the data bits are 
set to 5 (LCR[1:0] set to zero) one and a half stop bits is transmitted.
Otherwise, two stop bits are transmitted. Note that regardless of the 
number of stop bits selected the receiver will only check the first stop bit.
Note: NOTE: The STOP bit duration implemented by DW_apb_uart may appear 
longer due to idle time inserted between characters for some configurations 
and baud clock divisor values in the transmit direction; for details on idle
time between transmitted transfers, refer to 'Back-to-Back Character Stream 
Transmission' section in data book.
Values:
■0x0 (STOP_1BIT): 1 stop bit
■0x1 (STOP_1_5BIT_OR_2BIT): 1.5 stop bits when DLS (LCR[1:0]) is zero, else 2 stop bit
Value After Reset: 0x0
Exists: Always
**********************************************************/
	Uint32 STOP:1; //2   RW

/*****************************************************************
Parity Enable
. If UART_16550_COMPATIBLE == NO then, writeable only when UART
is not busy (USR[0] is zero), otherwise always writable and always
readable. This bit is used to enable and disable parity generation 
and detection in transmitted and received serial character respectively.
Values:
■0x0 (DISABLED): disable parity
■0x1 (ENABLED): enable parity
Value After Reset: 0x0
Exists: Always
*******************************************************************/
	Uint32 PEN:1; //3  RW	
/***************************************************************
Even Parity Select.
If UART_16550_COMPATIBLE == NO then, writeable only when UART is 
not busy (USR[0] is zero), otherwise always writable and always readable. 
This is used to select between even and odd parity, when parity is 
enabled (PEN set to one). If set to one, an even number of logic '1's 
is transmitted or checked. If set to zero, an odd number of logic '1's is transmitted or checked.
Values:
■0x0 (ODD_PARITY): an odd parity is transmitted or checked
■0x1 (EVEN_PARITY): an even parity is transmitted or checked
Value After Reset: 0x0
Exists: Always

******************************************************************/
	Uint32 EPS:1; //4 RW	
/**********************************************************************************************
Stick Parity.
If UART_16550_COMPATIBLE = NO, then writeable only when UART is not busy (USR[0] is 0); 
otherwise always writable and always readable. This bit is used to force parity value. When PEN, 
EPS and Stick Parity are set to 1, the parity bit is transmitted and checked as logic 0. 
If PEN and Stick Parity are set to 1 and EPS is a logic 0, then parity bit is transmitted and 
checked as a logic 1. If this bit is set to 0, Stick Parity is disabled.
Values:
■0x0 (DISABLED): Stick parity disabled
■0x1 (ENABLED): Stick parity enabled
Value After Reset: 0x0
Exists: Always
**********************************************************************************************/
	Uint32 SP:1;// 5 RW
/****************************************************************************************
Break Control Bit.
This is used to cause a break condition to be transmitted to the receiving device. 
If set to one the serial output is forced to the spacing (logic 0) state. When not in
Loopback Mode, as determined by MCR[4], the sout line is forced low until the Break bit is 
cleared. If SIR_MODE == Enabled and active (MCR[6] set to one) the sir_out_n line is 
continuously pulsed. When in Loopback Mode, the break condition is internally looped 
back to the receiver and the sir_out_n line is forced low.
Values:
■0x0 (DISABLED): Serial output is released for data transmission
■0x1 (ENABLED): Serial output is forced to spacing state
Value After Reset: 0x0
Exists: Always
*****************************************************************************************/	
	Uint32 BC:1;// 6 RW
/*************************************************************
Divisor Latch Access Bit.
If UART_16550_COMPATIBLE == NO then, writeable only when UART 
is not busy (USR[0] is zero), otherwise always writable and always readable. 
This bit is used to enable reading and writing of the Divisor Latch register 
(DLL and DLH/LPDLL and LPDLH) to set the baud rate of the UART. This bit must
be cleared after initial baud rate setup in order to access other registers.
Values:
■0x0 (DISABLED): Divisor Latch register is writable only when UART Not BUSY
■0x1 (ENABLED): Divisor Latch register is always readable and writable
Value After Reset: 0x0
Exists: Always
*************************************************************************/
	Uint32 DLAB:1;// 7 RW
	Uint32 RSVD_LCR_31to8:24;
	
};

union LLCR_REG
{
	Uint32 all;
	struct LLCR_BITS bit;
};


struct LMCR_BITS
{
/*************************************************************************************************
Data Terminal Ready.
This is used to directly control the Data Terminal Ready (dtr_n) output. The value written to 
this location is inverted and driven out on dtr_n.The Data Terminal Ready output is used to
inform the modem or data set that the UART is ready to establish communications. Note that in
Loopback mode (MCR[4] set to one), the dtr_n output is held inactive high while the value of 
this location is internally looped back to an input.
Values:
■0x0 (INACTIVE): dtr_n de-asserted (logic1)
■0x1 (ACTIVE): dtr_n asserted (logic 0)
Value After Reset: 0x0
Exists: Always
********************************************************************************************************/
	Uint32 DTR:1;//0  RW
/***********************************************************************************************
Request to Send.
This is used to directly control the Request to Send (rts_n) output. The Request To Send (rts_n) 
output is used to inform the modem or data set that the UART is ready to exchange data.
When Auto RTS Flow Control is not enabled (MCR[5] set to zero), the rts_n signal is set low 
by programming MCR[1] (RTS) to a high. In Auto Flow Control, AFCE_MODE == Enabled and active
(MCR[5] set to one) and FIFO's enable (FCR[0] set to one), the rts_n output is controlled in 
the same way, but is also gated with the receiver FIFO threshold trigger (rts_n is inactive
high when above the threshold). The rts_n signal will be de-asserted when MCR[1] is set low.
Note that in Loopback mode (MCR[4] set to one), the rts_n output is held inactive high while
the value of this location is internally looped back to an input.
Values:
■0x0 (INACTIVE): Request to Send rts_n de-asserted (logic 1)
■0x1 (ACTIVE): Request to Send rts_n asserted (logic 0)
Value After Reset: 0x0
Exists: Always
**********************************************************************************************/
	Uint32 RTS:1;//	 1 RW
/***************************************************************************************
This is used to directly control the user-designated Output1 (out1_n) output. 
The value written to this location is inverted and driven out on out1_n. Note 
that in Loopback mode (MCR[4] set to one), the out1_n output is held inactive 
high while the value of this location is internally looped back to an input.
Values:
■0x0 (OUT1_0): out1_n de-asserted (logic 1)
■0x1 (OUT1_1): out1_n asserted (logic 0)
Value After Reset: 0x0
Exists: Always
***********************************************************************************/
	Uint32 OUT1:1;// 2 RW
/**********************************************************************
This is used to directly control the user-designated Output2 (out2_n) output. 
The value written to this location is inverted and driven out on out2_n. 
Note that in Loopback mode (MCR[4] set to one), the out2_n output is held 
inactive high while the value of this location is internally looped back to an input.
Values:
■0x0 (OUT2_0): out2_n de-asserted (logic 1)
■0x1 (OUT2_1): out2_n asserted (logic 0)
Value After Reset: 0x0
Exists: Always
*******************************************************************************/	
	Uint32 OUT2:1;// 3 RW
/*************************************************************************************
LoopBack Bit
. This is used to put the UART into a diagnostic mode for test purposes. 
If operating in UART mode (SIR_MODE != Enabled OR NOT active, MCR[6] set to zero),
data on the sout line is held high, while serial data output is looped back to the 
sin line, internally. In this mode all the interrupts are fully functional. Also, 
in loopback mode, the modem control inputs (dsr_n, cts_n, ri_n, dcd_n) are disconnected
and the modem control outputs (dtr_n, rts_n, out1_n, out2_n) are looped back to the inputs,
internally.If operating in infrared mode (SIR_MODE == Enabled AND active, MCR[6] set 
to one), data on the sir_out_n line is held low, while serial data output is inverted
and looped back to the sir_in line.
Values:
■0x0 (DISABLED): Loopback mode disabled
■0x1 (ENABLED): Loopback mode enabled
Value After Reset: 0x0
Exists: Always
***************************************************************************************/	
	Uint32 LoopBack:1;//4 RW
/******************************************************************
Auto Flow Control Enable
. Writeable only when AFCE_MODE == Enabled, always readable. 
When FIFOs are enabled and the Auto Flow Control Enable (AFCE) bit is set,
Auto Flow Control features are enabled as described in section 'Auto Flow 
Control' in data book.
Values:
■0x0 (DISABLED): Auto Flow Control Mode disabled
■0x1 (ENABLED): Auto Flow Control Mode enabled
Value After Reset: 0x0
Exists: Always
Memory Access: "(AFCE_MODE==1) ? \"read-write\" : \"read-only\""
*********************************************************************/	
	Uint32 AFCE:1;  //5 RW

/************************************************************
SIR Mode Enable
. Writeable only when SIR_MODE == Enabled, always readable. 
This is used to enable/ disable the IrDA SIR Mode features as 
described in section 'IrDA 1.0 SIR Protocol' in the databook.
Note: To enable SIR mode, write the appropriate value to the MCR
register before writing to the LCR register. For details of the 
recommended programming sequence, refer to 'Programing Examples' 
section of data book.
Values:
■0x0 (DISABLED): IrDA SIR Mode disabled
■0x1 (ENABLED): IrDA SIR Mode enabled
Value After Reset: 0x0
Exists: Always
Memory Access: "(SIR_MODE==1) ? \"read-write\" : \"read-only\""

**********************************************************/	
	Uint32 SIRE:1; // 6  * Varies
	Uint32 RSVD_MCR_31to7:25; // 7-31
};

union LMCR_REG
{
	Uint32 all;
	struct LMCR_BITS bit;
};

struct LLSR_BITS
{
/**********************************************************************
Data Ready bit.
This is used to indicate that the receiver contains at least one character
in the RBR or the receiver FIFO. This bit is cleared when the RBR
is read in the non-FIFO mode, or when the receiver FIFO is empty, in the FIFO mode.
Values:
■0x0 (NOT_READY): data not ready
■0x1 (READY): data ready
Value After Reset: 0x0
Exists: Always
********************************************************************/
	Uint32 DR:1; //0 R
/****************************************************************************
Overrun error bit.
This is used to indicate the occurrence of an overrun error. 
This occurs if a new data character was received before the previous data was read.
In the non-FIFO mode, the OE bit is set when a new character arrives in the receiver
before the previous character was read from the RBR. When this happens, the data in
the RBR is overwritten. In the FIFO mode, an overrun error occurs when the FIFO is
full and a new character arrives at the receiver. The data in the FIFO is retained
and the data in the receive shift register is lost.Reading the LSR clears the OE
bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the OE bit
(if LSR_STATUS_CLEAR==0).
Values:
■0x0 (NO_OVER_RUN_ERROR): no overrun error
■0x1 (OVER_RUN_ERROR): overrun error
Value After Reset: 0x0
Exists: Always
***************************************************************************/
	Uint32 OE:1; //1 R
/******************************************************************
Parity Error bit.
This is used to indicate the occurrence of a parity error in the receiver
if the Parity Enable (PEN) bit (LCR[3]) is set.In the FIFO mode, since the
parity error is associated with a character received, it is revealed when 
the character with the parity error arrives at the top of the FIFO.
It should be noted that the Parity Error (PE) bit (LSR[2]) will be set if a break interrupt has occurred, as indicated by Break Interrupt (BI) bit (LSR[4]). In this situation, the Parity Error bit is set if parity generation and detection is enabled (LCR[3]=1) and the parity is set to odd (LCR[4]=0).
Reading the LSR clears the PE bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the PE bit (if LSR_STATUS_CLEAR==0).
Values:
■0x0 (NO_PARITY_ERROR): no parity error
■0x1 (PARITY_ERROR): parity error
Value After Reset: 0x0
Exists: Always
***************************************************************************/	
	Uint32 PE:1; //2 R
/********************************************************************************************
Framing Error bit.
This is used to indicate the occurrence of a framing error in the receiver.
A framing error occurs when the receiver does not detect a valid STOP bit in the received data.
In the FIFO mode, since the framing error is associated with a character received, 
it is revealed when the character with the framing error is at the top of the FIFO. 
When a framing error occurs the UART will try resynchronize. It does this by assuming 
that the error was due to the start bit of the next character and then continues 
receiving the other bit i.e. data, and/or parity and stop.It should be noted that 
the Framing Error (FE) bit (LSR[3]) will be set if a break interrupt has occurred,
as indicated by Break Interrupt (BI) bit (LSR[4]). This happens because the break 
character implicitly generates a framing error by holding the sin input to logic
0 for longer than the duration of a character.Reading the LSR clears the FE bit 
(if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the FE bit (if LSR_STATUS_CLEAR==0).
Values:
■0x0 (NO_FRAMING_ERROR): no framing error
■0x1 (FRAMING_ERROR): framing error
Value After Reset: 0x0
Exists: Always
*******************************************************************************************/	
	Uint32 FE:1;// 3 R
/****************************************************************************
Break Interrupt bit.
This is used to indicate the detection of a break sequence on the serial input data.
If in UART mode it is set whenever the serial input, sin, is held in a logic '0' state
for longer than the sum of start time + data bits + parity + stop bits.
If in infrared mode it is set whenever the serial input, sir_in, is continuously pulsed 
to logic '0' for longer than the sum of start time + data bits + parity + stop bits. 
A break condition on serial input causes one and only one character, consisting of 
all zeros, to be received by the UART.In the FIFO mode, the character associated
with the break condition is carried through the FIFO and is revealed when the 
character is at the top of the FIFO.Reading the LSR clears the BI bit (if LSR_STATUS_CLEAR==13)
Or Reading the LSR or RBR clears the BI bit (if LSR_STATUS_CLEAR==0).
In the non-FIFO mode, the BI indication occurs immediately and persists until the LSR is read.
Note: If a FIFO is full when a break condition is received, a FIFO overrun occurs. The break
condition and all the information associated with it-parity and framing errors-is discarded; 
any information that a break character was received is lost.
Values:
■0x0 (NO_BREAK): No break sequence detected
■0x1 (BREAK): Break sequence detected
Value After Reset: 0x0
Exists: Always
***************************************************************************/
	Uint32 BI:1;// 4 R
/*********************************************************************************
Transmit Holding Register Empty bit.
If THRE_MODE_USER = Disabled or THRE mode is disabled (IER[7] set to zero) and 
regardless of FIFO's being implemented/enabled or not, this bit indicates that 
the THR or TX FIFO is empty.This bit is set whenever data is transferred from 
the THR or TX FIFO to the transmitter shift register and no new data has been
written to the THR or TX FIFO. This also causes a THRE Interrupt to occur, 
if the THRE Interrupt is enabled. If THRE_MODE_USER == Enabled AND FIFO_MODE != NONE
and both modes are active (IER[7] set to one and FCR[0] set to one respectively), 
the functionality is switched to indicate the transmitter FIFO is full, and no
longer controls THRE interrupts, which are then controlled by the FCR[5:4]
threshold setting. Programmable THRE interrupt mode operation is described
in detail in section 'Programmable THRE Interrupt' in data book.
Values:
■0x0 (DISABLED): THRE interrupt control is disabled
■0x1 (ENABLED): THRE interrupt control is enabled
Value After Reset: 0x1
Exists: Always
*****************************************************************************/	
	Uint32 THRE:1;// 5 R
/*******************************************************************************
Transmitter Empty bit.
If in FIFO mode (FIFO_MODE != NONE) and FIFO's enabled (FCR[0] set to one),
this bit is set whenever the Transmitter Shift Register and the FIFO are both 
empty. If in the non-FIFO mode or FIFO's are disabled, this bit is set whenever
the Transmitter Holding Register and the Transmitter Shift Register are both empty.
Values:
■0x0 (DISABLED): Transmitter not empty
■0x1 (ENABLED): Transmitter empty
Value After Reset: 0x1
Exists: Always
***********************************************************************************/
	Uint32 TEMT:1;//6 R
/***************************************************************************************
Receiver FIFO Error bit.
This bit is only relevant when FIFO_MODE != NONE AND FIFO's are enabled (FCR[0] set to one). 
This is used to indicate if there is at least one parity error, framing error, or break 
indication in the FIFO.This bit is cleared when the LSR is read and the character with the
error is at the top of the receiver FIFO and there are no subsequent errors in the FIFO.
Values:
■0x0 (NO_RX_FIFO_ERROR): No error in RX FIFO
■0x1 (RX_FIFO_ERROR): Error in RX FIFO
Value After Reset: 0x0
Exists: FIFO_MODE != 0
**********************************************************************************/	
	Uint32 RFE:1;// 7 R	
/*********************************************************************************
Address Received Bit.
If 9Bit data mode (LCR_EXT[0]=1) is enabled, this bit is used to indicate the 9th
bit of the receive data is set to 1. This bit can also be used to indicate whether 
the incoming character is address or data.
■1 = Indicates the character is address.
■0 = Indicates the character is data.
In the FIFO mode, since the 9th bit is associated with a character received, 
it is revealed when the character with the 9th bit set to 1 is at the top of the FIFO.
Reading the LSR clears the 9BIT.
Note: User needs to ensure that interrupt gets cleared (reading LSR register)
before the next address byte arrives. If there is a delay in clearing the interrupt, 
then Software will not be able to distinguish between multiple address related interrupt.
Value After Reset: 0x0
Exists: UART_9BIT_DATA_EN == 1
***************************************************************************/	
	Uint32 ADDR_RCVD:1;// 8 R
	Uint32 RSVD_LSR_31to9:23;
	
};

union LLSR_REG
{
	Uint32 all;
	struct LLSR_BITS bit;
};

struct LMSR_BITS
{
/****************************************************************
Delta Clear to Send.
This is used to indicate that the modem control line cts_n has
changed since the last time the MSR was read.
Reading the MSR clears the DCTS bit. In Loopback Mode (MCR[4] set to one),
DCTS reflects changes on MCR[1] (RTS).Note, if the DCTS bit is not 
set and the cts_n signal is asserted (low) and a reset occurs (software 
or otherwise), then the DCTS bit will get
set when the reset is removed if the cts_n signal remains asserted.
Values:
■0x0 (NO_CHANGE): no change on cts_n since last read of MSR
■0x1 (CHANGE): change on cts_n since last read of MSR
Value After Reset: 0x0
Exists: Always
***********************************************************************/
	Uint32 DCTS:1;// 0 R
/***********************************************************************
Delta Data Set Ready.
This is used to indicate that the modem control line dsr_n has changed
since the last time the MSR was read.Reading the MSR clears the DDSR bit. 
In Loopback Mode (MCR[4] set to one), DDSR reflects changes on MCR[0] (DTR).
Note, if the DDSR bit is not set and the dsr_n signal is asserted (low) and 
a reset occurs (software or otherwise), then the DDSR bit will get set when
the reset is removed if the dsr_n signal remains asserted.
Values:
■0x0 (NO_CHANGE): no change on dsr_n since last read of MSR
■0x1 (CHANGE): change on dsr_n since last read of MSR
Value After Reset: 0x0
Exists: Always
************************************************************************/	
	Uint32 DDSR:1;// 1 R
/************************************************************************
Trailing Edge of Ring Indicator.
This is used to indicate that a change on the input ri_n (from an active 
low, to an inactive high state) has occurred since the last time the MSR was read.
Reading the MSR clears the TERI bit. In Loopback Mode (MCR[4] set to one),
TERI reflects when MCR[2] (Out1) has changed state from a high to a low.
Values:
■0x0 (NO_CHANGE): no change on ri_n since last read of MSR
■0x1 (CHANGE): change on ri_n since last read of MSR
Value After Reset: 0x0
Exists: Always
****************************************************************************************/	
	Uint32 TERI:1;// 2 R
/*************************************************************************************
Delta Data Carrier Detect.
This is used to indicate that the modem control line dcd_n has changed since the
last time the MSR was read.Reading the MSR clears the DDCD bit. In Loopback Mode 
(MCR[4] set to one), DDCD reflects changes on MCR[3] (Out2).Note, if the DDCD bit
is not set and the dcd_n signal is asserted (low) and a reset occurs (software or otherwise),
then the DDCD bit will get set when the reset is removed if the dcd_n signal remains asserted.
Values:
■0x0 (NO_CHANGE): No change on dcd_n since last read of MSR
■0x1 (CHANGE): change on dcd_n since last read of MSR
Value After Reset: 0x0
Exists: Always
*************************************************************************************/
	Uint32 DDCD:1;// 3 R	
/****************************************************************
Clear to Send.
This is used to indicate the current state of the modem control line cts_n.
That is, this bit is the complement cts_n. When the Clear to Send input (cts_n)
is asserted it is an indication that the modem or data set is ready to exchange
data with the DW_apb_uart.
In Loopback Mode (MCR[4] set to one), CTS is the same as MCR[1] (RTS).
Values:
■0x0 (DEASSERTED): cts_n input is de-asserted (logic 1)
■0x1 (ASSERTED): cts_n input is asserted (logic 0)
Value After Reset: 0x0
Exists: Always
********************************************************************/	
	Uint32 CTS:1; // 4 R
/**********************************************************************
Data Set Ready.
This is used to indicate the current state of the modem control line dsr_n. 
That is this bit is the complement dsr_n. When the Data Set Ready input (dsr_n)
is asserted it is an indication that the modem or data set is ready to establish
communications with the DW_apb_uart.
In Loopback Mode (MCR[4] set to one), DSR is the same as MCR[0] (DTR).
Values:
■0x0 (DEASSERTED): dsr_n input is de-asserted (logic 1)
■0x1 (ASSERTED): dsr_n input is asserted (logic 0)
Value After Reset: 0x0
Exists: Always
************************************************************************/
	Uint32 DSR:1;//5 R
/******************************************************************
Ring Indicator.
This is used to indicate the current state of the modem control line ri_n.
That is this bit is the complement ri_n. When the Ring Indicator input (ri_n) 
is asserted it is an indication that a telephone ringing signal has been
received by the modem or data set.
In Loopback Mode (MCR[4] set to one), RI is the same as MCR[2] (Out1).
Values:
■0x0 (DEASSERTED): ri_n input is de-asserted (logic 1)
■0x1 (ASSERTED): ri_n input is asserted (logic 0)
Value After Reset: 0x0
Exists: Always
***********************************************************************/
	Uint32 RI:1; // 6 R	
/**********************************************************************
Data Carrier Detect.
This is used to indicate the current state of the modem control line dcd_n. 
That is this bit is the complement dcd_n. When the Data Carrier Detect input 
(dcd_n) is asserted it is an indication that the carrier has been detected 
by the modem or data set.In Loopback Mode (MCR[4] set to one), DCD is
the same as MCR[3] (Out2).
Values:
■0x0 (DEASSERTED): dcd_n input is de-asserted (logic 1)
■0x1 (ASSERTED): dcd_n input is asserted (logic 0)
Value After Reset: 0x0
Exists: Always
*********************************************************************/
	Uint32 DCD:1;// 7 R
	Uint32 RSVD_MSR_31to8:23;
	
};


union LMSR_REG
{
	Uint32 all;
	struct LMSR_BITS bit;
};


struct LSCR_BITS
{
/***********************************************************
This register is for programmers to use as a temporary storage space.
It has no defined purpose in the DW_apb_uart.
Value After Reset: 0x0
Exists: Always
*************************************************************/
	Uint32 SCR:8;//0-7 RW
	Uint32 RSVD_SCR_31to8:24;
};


union LSCR_REG
{
	Uint32 all;
	struct LSCR_BITS bit;
};

struct LLPDLL_BITS
{
/*************************************************
This register makes up the lower 8-bits of a 16-bit, read/write,
Low Power Divisor Latch register that contains the baud rate divisor
for the UART which must give a baud rate of 115.2K. This is required 
for SIR Low Power (minimum pulse width) detection at the receiver.
The output low power baud rate is equal to the serial clock (sclk) 
frequency divided by sixteen times the value of the baud rate divisor, as follows:
Low power baud rate = (serial clock freq) / (16 * divisor)
Therefore a divisor must be selected to give a baud rate of 115.2K.
Note: When the Low Power Divisor Latch Registers (LPDLL and LPDLH) are
set to zero, the low power baud clock is disabled and no low power pulse
detection (or any pulse detection for that matter) will occur at the receiver.
Also, once the LPDLL is set at least 8 clock cycles of the slowest DW_apb_uart
clock should be allowed to pass before transmitting or receiving data.
Value After Reset: 0x0
Exists: Always
*********************************************************************************/
	Uint32 LPDLL:8;//0-7 RW
	Uint32 RSVD_LPDLL_31to8:24;//8-31 
};

union LLPDLL_REG 
{
	Uint32 all;
	struct LLPDLL_BITS  bit;
};


struct LLPDLH_BITS
{
/************************************************************************
This register makes up the upper 8-bits of a 16-bit, read/write, Low Power 
Divisor Latch register that contains the baud rate divisor for the UART which
must give a baud rate of 115.2K. This is required for SIR Low Power 
(minimum pulse width) detection at the receiver.The output low power baud 
rate is equal to the serial clock (sclk) frequency divided by sixteen times
the value of the baud rate divisor, as follows:
Low power baud rate = (serial clock freq) / (16 * divisor)
Therefore a divisor must be selected to give a baud rate of 115.2K.
Note: When the Low Power Divisor Latch Registers (LPDLL and LPDLH) are set
to zero, the low power baud clock is disabled and no low power pulse detection
(or any pulse detection for that matter) will occur at the receiver. Also, once
the LPDLH is set, at least 8 clock cycles of the slowest DW_apb_uart clock should
be allowed to pass before transmitting or receiving data.
Value After Reset: 0x0
Exists: Always
*************************************************************************/
	Uint32 LPDLH:8;// 0-7 RW
	Uint32 RSVD_LPDLH_31to8:24;// 8-31

};


union LLPDLH_REG
{
	Uint32 all;
	struct LLPDLH_BITS bit;
};

struct LFAR_REG_BITS
{
	/***********************************************************************************
	Writes will have no effect when FIFO_ACCESS == No, always readable. This register is
	use to enable a FIFO access mode for testing, so that the receive FIFO can be written 
	by the master and the transmit FIFO can be read by the master when FIFO's are implemented
	and enabled. When FIFOs are not implemented or not enabled it allows the RBR to be written
	by the master and the THR to be read by the master.Note, that when the FIFO access
	mode is enabled/disabled, the control portion of the receive FIFO and transmit FIFO
	is reset and the FIFO's are treated as empty.
	Values:
	■0x0 (DISABLED): FIFO access mode disabled
	■0x1 (ENABLED): FIFO access mode enabled
	Value After Reset: 0x0
	Exists: Always
	Memory Access: "(FIFO_ACCESS==1) ? \"read-write\" : \"read-only\""
	**************************************************************************************/
		Uint32 FAR:1;//0 * Varies
		Uint32 RSVD_FAR_31to1:31;

};

union LFAR_REG
{
	Uint32 all;
	struct LFAR_REG_BITS bit;
};

struct LTFR_BITS
{
/********************************************
Transmit FIFO Read.
These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one).
When FIFO's are implemented and enabled, reading this register gives the data at the
top of the transmit FIFO. Each consecutive read pops the transmit FIFO and gives the 
next data value that is currently at the top of the FIFO.
When FIFO's are not implemented or not enabled, reading this register gives the data
in the THR.
Value After Reset: 0x0
Exists: Always
*****************************************************/
	Uint32 TFR:8;//0-7  
	Uint32 RSVD_TFR_31to8:24;
};

union LTFR_REG 
{
	Uint32 all;
	struct LTFR_BITS bit;
};


struct LRFW_BITS
{
/************************************************************
Receive FIFO Write Data.
These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one).
When FIFO's are implemented and enabled, the data that is written to the RFWD is 
pushed into the receive FIFO. Each consecutive write pushes the new data to the next
write location in the receive FIFO. When FIFO's are not implemented or not enabled,
the data that is written to the RFWD is pushed into the RBR.
Value After Reset: 0x0
Exists: Always
***************************************************************/
	Uint32 RFWD:8; //0-7  W
/*******************************************************************
Receive FIFO Parity Error.
These bits are only valid when FIFO access mode is enabled 
(FAR[0] is set to one). When FIFO's are implemented and enabled, 
this bit is used to write parity error detection information to 
the receive FIFO. When FIFO's are not implemented or not enabled, 
this bit is used to write parity error detection information to the RBR.
Values:
■0x0 (DISABLED): Parity error disabled
■0x1 (ENABLED): Parity error enabled
Value After Reset: 0x0
Exists: Always
***************************************************************************/	
	Uint32 RFPE:1;// 8 W
/***********************************************************************
Receive FIFO Framing Error.
These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one).
When FIFO's are implemented and enabled, this bit is used to write framing error
detection information to the receive FIFO. When FIFO's are not implemented or not
enabled, this bit is used to write framing error detection information to the RBR.
Values:
■0x0 (DISABLED): Frame error disabled
■0x1 (ENABLED): Frame error enabled
Value After Reset: 0x0
Exists: Always
*******************************************************************************/	
	Uint32 RFFE:1;// 9 W
	Uint32 RSVD_RFW_31to10:22;
};


union LRFW_REG
{
	Uint32 all;
	struct LRFW_BITS  bit;
};

struct LUSR_BITS
{
/*************************************************************
UART Busy.
This bit is only valid when UART_16550_COMPATIBLE == NO. This indicates 
that a serial transfer is in progress, when cleared indicates that the DW_apb_uart is idle or inactive.
This bit will be set to 1 (busy) under any of the following conditions:
- Transmission in progress on serial interface
- Transmit data present in THR, when FIFO access mode is not being used 
(FAR = 0) and the baud divisor is non-zero ({DLH,DLL} does not equal 0) 
when the divisor latch access bit is 0 (LCR.DLAB = 0)
- Reception in progress on the interface
- Receive data present in RBR, when FIFO access mode is not being used (FAR = 0)
Note: It is possible for the UART Busy bit to be cleared even though a new 
character may have been sent from another device. That is, if the DW_apb_uart
has no data in the THR and RBR and there is no transmission in progress and a 
start bit of a new character has just reached the DW_apb_uart. This is due to
the fact that a valid start is not seen until the middle of the bit period and 
this duration is dependent on the baud divisor that has been programmed. If a 
second system clock has been implemented (CLOCK_MODE == Enabled), the assertion
of this bit will also be delayed by several cycles of the slower clock.
Values:
■0x0 (IDLE): DW_apb_uart is idle or inactive
■0x1 (BUSY): DW_apb_uart is busy (actively transferring data)
Value After Reset: 0x0
Exists: UART_16550_COMPATIBLE == 0
Volatile: true
*************************************************************************/
	Uint32 BUSY:1;//0  R
/*******************************************************************
Transmit FIFO Not Full.
This bit is only valid when FIFO_STAT == YES. This is used to indicate that the
transmit FIFO is not full. This bit is cleared when the TX FIFO is full.
Values:
■0x0 (FULL): Transmit FIFO is full
■0x1 (NOT_FULL): Transmit FIFO is not full
Value After Reset: "((FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1))
? 0x1 : 0x0"
Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1)
Volatile: true
******************************************************************/
	Uint32 TFNF:1;//1  R
/*******************************************************************
Transmit FIFO Empty.
This bit is only valid when FIFO_STAT == YES. This is used to indicate that
the transmit FIFO is completely empty. This bit is cleared when the TX FIFO 
is no longer empty.
Values:
■0x0 (NOT_EMPTY): Transmit FIFO is not empty
■0x1 (EMPTY): Transmit FIFO is empty
Value After Reset: "((FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1)) 
? 0x1 : 0x0"
Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1)
Volatile: true
*********************************************************************/	
	Uint32 TFE:1;// 2 R
/*******************************************************************
Receive FIFO Not Empty.
This bit is only valid when FIFO_STAT == YES. This is used to indicate 
that the receive FIFO contains one or more entries. This bit is cleared
when the RX FIFO is empty.
Values:
■0x0 (EMPTY): Receive FIFO is empty
■0x1 (NOT_EMPTY): Receive FIFO is not empty
Value After Reset: 0x0
Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1)
Volatile: true
****************************************************************/
	Uint32 RFNE:1;//3 R
/**********************************************************************
Receive FIFO Full.
This bit is only valid when FIFO_STAT == YES. This is used to indicate
that the receive FIFO is completely full. That is: This bit is cleared 
when the RX FIFO is no longer full.
Values:
■0x0 (NOT_FULL): Receive FIFO not full
■0x1 (FULL): Receive FIFO full
Value After Reset: 0x0
Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1)
Volatile: true
**************************************************************************/	
	Uint32 RFF:1; //4 R
	Uint32 RSVD_USR_31to5:27;

};

union LUSR_REG
{
	Uint32 all;
	struct LUSR_BITS bit;
};

struct LSRR_BITS
{
/**********************************************************************************
UART Reset.
This asynchronously resets the DW_apb_uart and synchronously removes the reset assertion.
For a two clock implementation both pclk and sclk domains will be reset.
Values:
■0x0 (NO_RESET): No Uart Reset
■0x1 (RESET): Uart reset
Value After Reset: 0x0
Exists: Always
**********************************************************************************/
	Uint32 UR:1;// 0  W
/*******************************************************************
RCVR FIFO Reset.
Writes will have no effect when FIFO_MODE == NONE. This is a shadow register 
for the RCVR FIFO Reset bit (FCR[1]). This can be used to remove the burden on
software having to store previously written FCR values (which are pretty static) 
just to reset the reeive FIFO. This resets the control portion of the receive FIFO 
and treats the FIFO as empty. This will also de-assert the DMA RX request and single
signals when additional DMA handshaking signals are selected (DMA_EXTRA == YES). 
Note that this bit is 'self-clearing' and it is not necessary to clear this bit.
Value After Reset: 0x0
Exists: Always
Memory Access: "(FIFO_MODE !=0) ? \"write-only\" : \"read-only\"
***********************************************************************************************/	
	Uint32 RFR:1;//1  * Varies
/********************************************************************************
XMIT FIFO Reset
. Writes will have no effect when FIFO_MODE == NONE. This is a shadow register
for the XMIT FIFO Reset bit (FCR[2]). This can be used to remove the burden on 
software having to store previously written FCR values (which are pretty static)
just to reset the transmit FIFO. This resets the control portion of the transmit
FIFO and treats the FIFO as empty. This will also de-assert the DMA TX request and 
single signals when additional DMA handshaking signals are selected (DMA_EXTRA = YES).
Note that this bit is 'self-clearing'. It is not necessary to clear this bit.
Value After Reset: 0x0
Exists: Always
Memory Access: "(FIFO_MODE !=0) ? \"write-only\" : \"read-only\""
*************************************************************************/	
	Uint32 XFR:1;//2  * Varies
	Uint32 RSVD_SRR_31to3:29;//3-31
};


union LSRR_REG
{
	Uint32 all;
	struct LSRR_BITS bit;
};

struct LSRTS_BITS 
{
/******************************************************
Shadow Request to Send.
This is a shadow register for the RTS bit (MCR[1]), this can be used to
remove the burden of having to performing a read modify write on the MCR.
This is used to directly control the Request to Send (rts_n) output. The 
Request To Send (rts_n) output is used to inform the modem or data set 
that the UART is ready to exchange data. When Auto RTS Flow Control is
not enabled (MCR[5] set to zero), the rts_n signal is set low by 
programming MCR[1] (RTS) to a high. In Auto Flow Control, AFCE_MODE == Enabled 
and active (MCR[5] set to one) and FIFO's enable (FCR[0] set to one), the rts_n
output is controlled in the same way, but is also gated with the receiver FIFO
threshold trigger (rts_n is inactive high when above the threshold) only when
RTC Flow Trigger is disabled; otherwise it is gated by the receiver FIFO 
almost-full trigger, where 'almost full' refers to two available slots
in the FIFO (rts_n is inactive high when above the threshold).
Note that in Loopback mode (MCR[4] set to one), the rts_n output is held inactive 
high while the value of this location is internally looped back to an input.
Values:
■0x0 (DEASSERTED): Shadow Request to Send uart_rts_n logic1
■0x1 (ASSERTED): Shadow Request to Send uart_rts_n logic0
Value After Reset: 0x0
Exists: Always
*********************************************************/
	Uint32 	SRTS:1;//0 RW
	Uint32 RSVD_SRTS_31to1:31;//	
};

union LSRTS_REG
{
	Uint32 all;
	struct LSRTS_BITS bit;
};

struct LSBCR_BITS
{
/*****************************************************************
Shadow Break Control Bit.
This is a shadow register for the Break bit (LCR[6]), this can be used 
to remove the burden of having to performing a read modify write on the
LCR. This is used to cause a break condition to be transmitted to the
receiving device. If set to one the serial output is forced to the spacing 
(logic 0) state. When not in Loopback Mode, as determined by MCR[4], the
sout line is forced low until the Break bit is cleared.
If SIR_MODE == Enabled and active (MCR[6] set to one) the sir_out_n line 
is continuously pulsed. When in Loopback Mode, the break condition is 
internally looped back to the receiver.
Values:
■0x0 (NO_BREAK): No spacing on serial output
■0x1 (BREAK): Serial output forced to the spacing
Value After Reset: 0x0
Exists: Always
***********************************************************************/
	Uint32 SBCB:1;//0  RW
	Uint32 RSVD_SBCR_31to1:31;
};

union LSBCR_REG
{
	Uint32 all;
	struct LSBCR_BITS bit;
};

struct LSDMAM_BITS
{
/****************************************************
Shadow DMA Mode.
This is a shadow register for the DMA mode bit (FCR[3]).
This can be used to remove the burden of having to store the
previously written value to the FCR in memory and having to 
mask this value so that only the DMA Mode bit gets updated.
This determines the DMA signalling mode used for the dma_tx_req_n 
and dma_rx_req_n output signals when additional DMA handshaking
signals are not selected (DMA_EXTRA == NO). See section 5.9 on
page 54 for details on DMA support.
Values:
■0x0 (MODE_0): Mode 0
■0x1 (MODE_1): Mode 1
Value After Reset: 0x0
Exists: Always
*************************************************************************/
	Uint32 SDMAM:1;//0 RW
	Uint32 RSVD_SDMAM_31to1:31;
};


union LSDMAM_REG 
{
	Uint32 all;
	struct LSDMAM_BITS bit;
};

struct LSFE_BITS
{
/****************************************************************
Shadow FIFO Enable.
This is a shadow register for the FIFO enable bit (FCR[0]). This can be
used to remove the burden of having to store the previously written value 
to the FCR in memory and having to mask this value so that only the FIFO 
enable bit gets updated. This enables/disables the transmit (XMIT) and
receive (RCVR) FIFO's. If this bit is set to zero (disabled) after being
enabled then both the XMIT and RCVR controller portion of FIFO's will be reset.
Values:
■0x0 (DISABLED): FIFOs are disabled
■0x1 (ENABLED): FIFOs are enabled
Value After Rese
*****************************************************************************/
	Uint32 SFE:1;// 0  RW
	Uint32 RSVD_SFE_31to1:31;//1-31 R
};

union LSFE_REG
{
	Uint32 all;
	struct LSFE_BITS bit;
};

struct LSRT_BITS 
{
/******************************************************************************
Shadow RCVR Trigger.
This is a shadow register for the RCVR trigger bits (FCR[7:6]). 
This can be used to remove the burden of having to store the previously
written value to the FCR in memory and having to mask this value so that 
only the RCVR trigger bit gets updated.This is used to select the trigger
level in the receiver FIFO at which the Received Data Available Interrupt
will be generated. It also determines when the dma_rx_req_n signal will 
be asserted when DMA Mode (FCR[3]) is set to one.
Values:
■0x0 (FIFO_CHAR_1): 1 character in FIFO
■0x1 (FIFO_QUARTER_FULL): FIFO 1/4 full
■0x2 (FIFO_HALF_FULL): FIFO 1/2 full
■0x3 (FIFO_FULL_2): FIFO 2 less than full
Value After Reset: 0x0
Exists: Always
*****************************************************************************/
	Uint32 SRT:2;//0-1 RW
	Uint32 RSVD_SRT_31to2:30;
};


union LSRT_REG 
{
	Uint32 all;
	struct LSRT_BITS bit;
};

struct LSTET_BITS
{
/******************************************************
Shadow TX Empty Trigger.
This is a shadow register for the TX empty trigger bits (FCR[5:4]). 
This can be used to remove the burden of having to store the previously
written value to the FCR in memory and having to mask this value so that
only the TX empty trigger bit gets updated. Writes will have no effect
when THRE_MODE_USER == Disabled. This is used to select the empty threshold
level at which the THRE Interrupts will be generated when the mode is active.
Values:
■0x0 (FIFO_EMPTY): FIFO empty
■0x1 (FIFO_CHAR_2): 2 characters in FIFO
■0x2 (FIFO_QUARTER_FULL): FIFO 1/4 full
■0x3 (FIFO_HALF_FULL): FIFO 1/2 full
Value After Reset: 0x0
Exists: Always
************************************************************/
	Uint32 STET:2;//0-1 RW
	Uint32 RSVD_STET_31to2:30;
};


union LSTET_REG 
{
	Uint32 all;
	struct LSTET_BITS bit;
};

struct  LHTX_BITS
{
/**************************************************************************
Halt TX.
Writes will have no effect when FIFO_MODE == NONE, always readable. This register
is use to halt transmissions for testing, so that the transmit FIFO can be filled
by the master when FIFO's are implemented and enabled. Note, if FIFO's are
implemented and not enabled the setting of the halt TX register will have 
no effect on operation.
Values:
■0x0 (DISABLED): Halt Transmission disabled
■0x1 (ENABLED): Halt Transmission enabled
Value After Reset: 0x0
Exists: Always
Memory Access: "(FIFO_MODE==0) ? \"read-only\" : \"read-write\""
*********************************************************************************/
	Uint32 HTX:1;//0 * Varies
	Uint32 RSVD_HTX_31to1:31;
};

union LHTX_REG
{
	Uint32 all;
	struct  LHTX_BITS bit;
};

struct  LDMASA_BITS
{
/************************************************
DMA Software Acknowledge.
Writes will have no effect when DMA_EXTRA == No. This register
is use to perform DMA software acknowledge if a transfer needs
to be terminated due to an error condition. For example, if the
DMA disables the channel, then the DW_apb_uart should clear its
request. This will cause the TX request, TX single, RX request 
and RX single signals to de-assert. Note that this bit is
'self-clearing' and it is not necessary to clear this bit.
Values:
■0x1 (SOFT_ACK): DMA software acknowledge
Value After Reset: 0x0
Exists: Always
Memory Access: "(DMA_EXTRA==1) ? \"write-only\" : \"read-only\""
****************************************************************/
	Uint32 DMASA:1;//0 * Varies
	Uint32 RSVD_DMASA_31to1:31;
};

union LDMASA_REG
{
	Uint32 all;
	struct  LDMASA_BITS bit;
};

struct LTCR_BITS
{
/*********************************************************
RS485 Transfer Enable.
■0 : In this mode, the transfers are still in the RS232 mode. All other 
fields in this register are reserved and register DE_EN/RE_EN/TAT are also reserved.
■1 : In this mode, the transfers will happen in RS485 mode. All other
fields of this register are applicable.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
*****************************************************************************/
	Uint32 RS485_EN:1;//0 * Varies
/**************************************************************************
Receiver Enable Polarity.
■1: RE signal is active high
■0: RE signal is active low
Value After Reset: UART_RE_POL
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
**********************************************************************************/	
	Uint32 RE_POL:1;//1    * Varies
/****************************************************************************
Driver Enable Polarity.
■1: DE signal is active high
■0: DE signal is active low
Value After Reset: UART_DE_POL
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
****************************************************************************/	
	Uint32 DE_POL:1;//     2   * Varies
/*************************************************************************
Transfer Mode.
■0: In this mode, transmit and receive can happen simultaneously. The user can enable DE_EN, 
RE_EN at any point of time. Turn around timing as programmed in the TAT register is 
not applicable in this mode.■1: In this mode, DE and RE are mutually exclusive. 
Either DE or RE only one of them is expected to be enabled through programming.
Hardware will consider the Turn Around timings which are programmed in the TAT
register while switching from RE to DE or DE to RE. For transmission Hardware will
wait if it is in middle of receiving any transfer, before it starts transmitting.
■2: In this mode, DE and RE are mutually exclusive. Once DE_EN/RE_EN is programed 
- by default 're' will be enabled and DW_apb_uart controller will be ready to receive.
If the user programs the TX FIFO with the data then DW_apb_uart, after ensuring no
receive is in progress, disable 're' and enable 'de' signal. Once the TX FIFO becomes empty,
're' signal gets enabled and 'de' signal will be disabled. In this mode of operation hardware
will consider the Turn Around timings which are programmed in the TAT register while switching
from RE to DE or DE to RE. In this mode, 'de' and 're' signals are strictly complementary to
each other.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
*****************************************************************************/	
	Uint32 XFER_MODE:2;//  3-4 * Varies
	Uint32 RSVD_TCR_31to5:27;
};

union LTCR_REG
{
	Uint32 all;
	struct LTCR_BITS bit;
};

struct  LDE_EN_BITS
{
/***************************************************************************
DE Enable control.
The 'DE Enable' register bit is used to control assertion and de-assertion of 'de' signal.
- 0: De-assert 'de' signal - 1: Assert 'de' signal
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""

**************************************************************************/
	Uint32 DE_Enable:1;//0  * Varies
	Uint32 RSVD_DE_EN_31to1:31;//
};

union LDE_EN_REG
{
	Uint32 all;
	struct  LDE_EN_BITS bit;
};

struct LRE_EN_BITS
{
	/*******************************************
	RE Enable control.
	The 'RE Enable' register bit is used to control assertion and de-assertion of 're' signal.
	■0: De-assert 're' signal
	■1: Assert 're' signal
	Value After Reset: 0x0
	Exists: Always
	Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
	
	*************************************************/

	Uint32 RE_Enable:1;//* Varies
	Uint32 RSVD_RE_EN_31to1:31;
};

union LRE_EN_REG
{

	Uint32 all;
	struct LRE_EN_BITS bit;
};

struct LDET_BITS
{
/****************************************************************
Driver Enable assertion time.
This field controls the amount of time (in terms of number of serial clock periods)
between the assertion of rising edge of Driver output enable signal to serial transmit
enable. Any data in transmit buffer, will start on serial output (sout) after the transmit enable.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
************************************************************/
	Uint32 DE_Assertion_Time:8;//0-7  * Varies  
	Uint32 RSVD_DE_AT_15to8:8;//8-15
/*************************************************************************
* Varies
Driver Enable de-assertion time.
This field controls the amount of time (in terms of number of serial clock periods) 
between the end of stop bit on the sout to the falling edge of Driver output enable signal.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
**************************************************************************************/	
	Uint32 DE_De_assertion_Time:8;//16-23 * Varies
	Uint32 RSVD_DE_DEAT_31to24:8;//
};

union LDET_REG
{
	Uint32 all;
	struct LDET_BITS bit;
};

struct LTAT_BITS
{
/***************************************************************
Driver Enable to Receiver Enable TurnAround time.
Turnaround time (in terms of serial clock) for DE De-assertion to RE assertion.
Note: The actual time is the programmed value + 1.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""

******************************************************************************/
	Uint32 DE_to_RE:16; //0-15  * Varies
/**************************************************************************
Receiver Enable to Driver Enable TurnAround time.
Turnaround time (in terms of serial clock) for RE De-assertion to DE assertion.
Note:
- If the DE assertion time in the DET register is 0, then the actual value is the 
programmed value + 3. - If the DE assertion time in the DET register is 1, then 
the actual value is the programmed value + 2. - If the DE assertion time in the DET 
register is greater than 1, then the actual value is the programmed value + 1.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""
**************************************************************************/	
	Uint32 RE_to_DE:16;//16- 31 * Varies
};

union LTAT_REG 
{
	Uint32 all;
	struct LTAT_BITS bit;
};

struct LDLF_BITS
{
/***************************************
Fractional part of divisor.
The fractional value is added to integer value set by DLH, DLL. Fractional 
value is determined by (Divisor Fraction value)/(2^DLF_SIZE). For information
on DLF values to be programmed for DLF_SIZE=4, see the 'Fractional Baud Rate
Support' section in the DW_apb_uart Databook.
Value After Reset: 0x0
Exists: Always
Range Variable[x]: DLF_SIZE - 1
Memory Access: "(FRACTIONAL_BAUD_DIVISOR_EN==1) ? \"read-write\" : \"read-only\""
*******************************************************************/
	Uint32 DLF:32;//* Varies
//	Uint32 RSVD_DLF;//
};


union LDLF_REG
{
	Uint32 all;
	struct LDLF_BITS  bit;
};

struct LRAR_BITS
{
/**********************************************************************
This is an address matching register during receive mode. If the 9-th bit 
is set in the incoming character then the remaining 8-bits will be checked 
against this register value. If the match happens then sub-sequent characters
with 9-th bit set to 0 will be treated as data byte until the next address
byte is received.
Note:
- This register is applicable only when 'ADDR_MATCH'(LCR_EXT[1] and 'DLS_E' (LCR_EXT[0]) bits are set to 1.
- If UART_16550_COMPATIBLE is configured to 0, then RAR should be programmed only when UART is not busy.
- If UART_16550_COMPATIBLE is configured to 0, then RAR can be programmed at any point of the time. However,
		user must not change this register value when any receive is in progress.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_9BIT_DATA_EN==1) ? \"read-write\" : \"read-only\""
***********************************************************************/
	Uint32 RAR:8;//0-7  * Varies
	Uint32 RSVD_RAR_31to8:24;//8-31
};


union LRAR_REG
{
	Uint32 all;
	struct LRAR_BITS bit;
};


struct LTAR_BITS
{
/*************************************************************
This is an address matching register during transmit mode. If DLS_E (LCR_EXT[0])
bit is enabled, then DW_apb_uart will send the 9-bit character with 9-th bit set
to 1 and remaining 8-bit address will be sent from this register provided 'SEND_ADDR'
(LCR_EXT[2]) bit is set to 1.
Note:
- This register is used only to send the address. The normal data should be sent by programming THR register.
- Once the address is started to send on the DW_apb_uart serial lane, then 'SEND_ADDR' bit will be auto-cleared by the hardware.
Value After Reset: 0x0
Exists: Always
Memory Access: "(UART_9BIT_DATA_EN==1) ? \"read-write\" : \"read-only\""
************************************************************************/
	Uint32 TAR:8;//0-7 * Varies
	Uint32 RSVD_TAR_31to8:24;//8-31;
};


union LTAR_REG
{
	Uint32 all;
	struct LTAR_BITS bit;
};


struct LLCR_EXT_BITS
{
/**********************************************************
Extension for DLS. This bit is used to enable 9-bit data for transmit and receive transfers.
Value After Reset: 0x0
Exists: Always
Volatile: true=
*************************************************************************/
	Uint32 DLS_E:1;//0 RW
/*********************************************************************
Address Match Mode.This bit is used to enable the address match feature during receive.
■1 = Address match mode; DW_apb_uart will wait until the incoming character with 9-th bit set
to 1. And further checks to see if the address matches with what is programmed in 'Receive
Address Match Register'. If match is found, then sub-sequent characters will be treated as 
valid data and DW_apb_uart starts receiving data.
■0 = Normal mode; DW_apb_uart will start to receive the data and 9-bit character will be 
formed and written into the receive RXFIFO. User is responsible to read the data and
differentiate b/n address and data.
Note: This field is applicable only when DLS_E is set to 1.
Value After Reset: 0x0
Exists: Always
Volatile: true

************************************************************************/
	Uint32 ADDR_MATCH:1;//1 RW
/************************************************************************
Send address control bit. This bit is used as a control knob for the user to determine 
when to send the address during transmit mode. 
■1 = 9-bit character will be transmitted with 9-th bit set to
		and the remaining 8-bits will match to what is being programmed in 'Transmit Address Register'.
■0 = 9-bit character will be transmitted with 9-th bit set to 0 and the
		maining 8-bits will be taken from the TXFIFO which is programmed through 8-bit wide THR/STHR register.
Note:
■1. This bit is auto-cleared by the hardware, after sending out the address
		aracter. User is not expected to program this bit to 0.
■2. This field is applicable only when DLS_E bit is set to 1 and TRANSMIT_MODE is set to 0.
Value After Reset: 0x0
Exists: UART_9BIT_DATA_EN == 1
Volatile: true
****************************************************************************/	
	Uint32 SEND_ADDR:1;// 2 RW
/******************************************************************
Transmit mode control bit. This bit is used to control the type of transmit mode during 9-bit data transfers.
■1: In this mode of operation, Transmit Holding Register (THR) and Shadow Transmit Holding Register (STHR)
are 9-bit wide. The user needs to ensure that the THR/STHR register is written correctly for address/data.
Address: 9th bit is set to 1,
Data : 9th bit is set to 0.
Note: Transmit address register (TAR) is not applicable in this mode of operation.
■0: In this mode of operation, Transmit Holding Register (THR) and Shadow Transmit Holding register 
(STHR) are 8-bit wide. The user needs to program the address into Transmit Address Register (TAR)
and data into the THR/STHR register. SEND_ADDR bit is used as a control knob to indicate the 
DW_apb_uart on when to send the address.
Value After Reset: 0x0
Exists: Always
Volatile: true
*********************************************************************************/
	Uint32 TRANSMIT_MODE:1;//3 RW
	Uint32 RSVD_LCR_EXT:28;//
};

union LLCR_EXT_REG
{
	Uint32 all;
	struct LLCR_EXT_BITS bit;
};

struct LUART_PROT_LEVEL_BITS
{
/*************************************************************
Protection level register.
Enabling protection on any of its three bits would require a privilege
greater than or equal to PPROT signal to gain access to protected registers.
Value After Reset: PROT_LEVEL_RST
Exists: Always
Memory Access: {(HC_PROT_LEVEL==0) ? "read-write" : "read-only"}
************************************************************************/
	Uint32 UART_PROT_LEVEL:3;//0-2  * Varies
	Uint32 RSVD_UART_PROT_LEVEL:29;//
};

union LUART_PROT_LEVEL_REG
{
	Uint32 all;
	struct LUART_PROT_LEVEL_BITS bit;
};

struct LREG_TIMEOUT_RST_BITS
{
/*******************************************
This field holds reset value of REG_TIMEOUT counter register.
Value After Reset: REG_TIMEOUT_VALUE
Exists: [<functionof> "(HC_REG_TIMEOUT_VALUE==0) ? 1 : 0"]
Volatile: true
Range Variable[x]: REG_TIMEOUT_WIDTH - 1
*****************************************************************/
	Uint32 REG_TIMEOUT_RST:32;//RW  
//	Uint32 RSVD_REG_TIMEOUT_RST:;//
};

union LREG_TIMEOUT_RST_REG
{
	Uint32 all;
	struct LREG_TIMEOUT_RST_BITS bit;
};

struct LAUTOBAUD_BITS
{
//1：使能    0：禁止 RW  复位为0
	Uint32 CDC:1;    // 0 自动检测波特率使能       
//1、使能中断         0禁止中断       RW  复位为0 
	Uint32 INTEN:1;//   1  波特率检测完成后是否发送中断 
	Uint32 IFC:1;//     2 波特率中断清除，写1 清除，RW ，复位值 0
	Uint32 DONE:1;//    3  波特率检测完成        0 没有完成        1：检测完成        RW  复位值 0
	Uint32 PE:1;//      4  波特率检测出现错误，起始位（0）和数据最低位（1） 过长 或者过短、数据不是字符  ：A/a,R/W,复位值 0
	Uint32 REV:8;//     5-12 自动检测波特率过程中收到的数据,(a/A),只读
	Uint32  CTRL:16;// 13- 28  波特率控制字,只读
	Uint32 Rsvd:4;
};

union LAUTOBAUD_REG 
{
	Uint32 all;
	struct LAUTOBAUD_BITS bit;
};

struct LCPR_BITS 
{
/***************************************************************************
Encoding of APB_DATA_WIDTH configuration parameter value.
Values:
■0x0 (APB_8BITS): APB data width is 8 bits
■0x1 (APB_16BITS): APB data width is 16 bits
■0x2 (APB_32BITS): APB data width is 32 bits
Value After Reset: UART_ENCODED_APB_WIDTH
Exists: Always
********************************************************************************/
	Uint32 APB_DATA_WIDTH:2;//0-1 R
	Uint32 RSVD_CPR_3to2:2;// 2-3 R
/****************************************************************************************
Encoding of AFCE_MODE configuration parameter value.
Values:
■0x0 (DISABLED): AFCE mode disabled
■0x1 (ENABLED): AFCE mode enabled
Value After Reset: AFCE_MODE
Exists: Always
******************************************************************************************/	
	Uint32 AFCE_MODE:1;//  4  R
/********************************************************************************
Encoding of THRE_MODE configuration parameter value.
Values:
■0x0 (DISABLED): THRE mode disabled
■0x1 (ENABLED): THRE mode enabled
Value After Reset: THRE_MODE_RST
Exists: Always
***************************************************************************/	
	Uint32 THRE_MODE:1;//  5  R
/***************************************************************************
Encoding of SIR_MODE configuration parameter value.
Values:
■0x0 (DISABLED): SIR mode disabled
■0x1 (ENABLED): SIR mode enabled
Value After Reset: SIR_MODE
Exists: Always
****************************************************************************/	
	Uint32 SIR_MODE:1;//   6  R
/***************************************************************************
Encoding of SIR_LP_MODE configuration parameter value.
Values:
■0x0 (DISABLED): SIR_LP mode disabled
■0x1 (ENABLED): SIR_LP mode enabled
Value After Reset: SIR_LP_MODE
Exists: Always
**************************************************************************/	
	Uint32 SIR_LP_MODE:1;//7 R	
/************************************************************************
Encoding of ADDITIONAL_FEATURES configuration parameter value.
Values:
■0x0 (DISABLED): Additional features disabled
■0x1 (ENABLED): Additional features enabled
Value After Reset: ADDITIONAL_FEATURES
Exists: Always
******************************************************************************/	
	Uint32 ADDITIONAL_FEAT:1;//8  R
/*************************************************************************
Encoding of FIFO_ACCESS configuration parameter value.
Values:
■0x0 (DISABLED): FIFO_ACCESS disabled
■0x1 (ENABLED): FIFO ACCESS enabled
Value After Reset: FIFO_ACCESS
Exists: Always
**********************************************************************************************/
	Uint32 FIFO_ACCESS:1;//  9  R
/************************************************************************
Encoding of FIFO_STAT configuration parameter value.
Values:
■0x0 (DISABLED): FIFO_STAT disabled
■0x1 (ENABLED): FIFO_STAT enabled
Value After Reset: FIFO_STAT
Exists: Always
***************************************************************************/	
	Uint32 FIFO_STAT:1;  //  10  R
/******************************************************************************
Encoding of SHADOW configuration parameter value.
Values:
■0x0 (DISABLED): SHADOW disabled
■0x1 (ENABLED): SHADOW enabled
Value After Reset: SHADOW
Exists: Always
***********************************************************************************/	
	Uint32 SHADOW:1;//      11  R
/*********************************************************************************
Encoding of UART_ADD_ENCODED_PARAMS configuration parameter value.
Values:
■0x0 (DISABLED): UART_ADD_ENCODED_PARAMS disabled
■0x1 (ENABLED): UART_ADD_ENCODED_PARAMS enabled
Value After Reset: UART_ADD_ENCODED_PARAMS
Exists: Always
****************************************************************************/	
	Uint32 UART_ADD_ENCODED_PARAMS:1;// 12 R
/************************************************************
Encoding of DMA_EXTRA configuration parameter value.
Values:
■0x0 (DISABLED): DMA_EXTRA disabled
■0x1 (ENABLED): DMA_EXTRA enabled
Value After Reset: DMA_EXTRA
Exists: Always
*****************************************************************************/	
	Uint32 DMA_EXTRA:1;//   13  R

	Uint32 RSVD_CPR_15to14:2;//14-15
/*******************************************************************
Encoding of FIFO_MODE configuration parameter value.
Values:
■0x0 (FIFO_MODE_0): FIFO mode is 0
■0x1 (FIFO_MODE_16): FIFO mode is 16
■0x2 (FIFO_MODE_32): FIFO mode is 32
■0x4 (FIFO_MODE_64): FIFO mode is 64
■0x8 (FIFO_MODE_128): FIFO mode is 128
■0x10 (FIFO_MODE_256): FIFO mode is 256
■0x20 (FIFO_MODE_512): FIFO mode is 512
■0x40 (FIFO_MODE_1024): FIFO mode is 1024
■0x80 (FIFO_MODE_2048): FIFO mode is 2048
Value After Reset: UART_ENCODED_FIFO_MODE
Exists: Always
**********************************************************************************/
	Uint32 FIFO_MODE:8;//16-23 R
	Uint32 RSVD_CPR_31to24:8;
	
};

union LCPR_REG
{
	Uint32 all;
	struct LCPR_BITS bit;
};

struct LIN_REGS
{
/********************************************
The LBUF is used to write or read data frame destined to send or received via LIN bus. The data buffer in DLIN is designed 
as FIFO, where INDEX field is the address pointer to the required data byte. The data byte can be read or written through 
LBUF register. Depending of AINC bit in LSEL register the data pointer can be automatically incremented after each 
access to LBUF. The first byte in the LIN frame is stored at the INDEX=0 and the last one is stored at the INDEX=7. In log 
mode, it is possible to access the ninth byte of FIFO, which is in this case the checksum byte. When DLIN executes RX 
response or TX response command it starts from first byte od data buffer (index=0).



***********************************************/
	Uint32 		LLBUF;			// 00
/************************************************
LSEL register is used to configure the FIFO memory: Auto increment index of FIFO memory after set a value into FIFO; 
INDEX bits are used to select used to select the place of FIFO index where the data will be setting
*********************************************************/
	union    LSEL_REG  LLSEL;		//04
/****************************************************
This register contains ID which is sent in header frame in master mode.
In case of slave mode this register contains received ID.
**************************************************/
	union    LID_REG   LLID;		//08
/*******************************************************
LIN Error Register is a read only register which provides information about a reason of an error that occurred. All flags 
are automatically set when corresponding event occurs and cleared by reading this register. The WAKEER bit is used 
only when DLIN is in a slave mode. It is set when master does not respond to the wake-up signal within time specified by 
WURT register. The second case where this bit is set is when the response counter is running (after sending the wake-up 
signal) and new data has been written to WURT register. If DLIN is in a master mode, this bit is not changed. The OVER
bit will be set when there is a write to DLIN registers while the current command is being executed. An exception is the 
writing of the ABORT command to the LCR register. The SYNCER bit is the another bit which is used in a slave mode only. 
This is set when the synchronizaction field measurement comes out after the specified range. The TOVER indicates that a 
frame was not completed within maximum time lenght or header was not received within maximum time length. The 
CHKSER indicates error checksum calculation in the received frame. The received header with incorrect pariry bits is 
indicated by set PER bit. When DLIN transmits frame it monitores bit value on the bus, if received bit is not the same as 
transmitted bit, the BITER flag is set. The FER bit is set when DLIN does not detect proper value of stop bit (recessive on 
LIN bus).
**********************************************/
	union   LER_REGS  LLER;			//0x0C
/*******************************************************
This register enables the four types of DLIN interrupts. Each interrupt can individually activate the interrupt IRQ output 
signal. It is possible to totally disable the interrupt system by resetting bits 0 through 5 of the LIN Interrupt Enable 
register. Similarly, setting bits of the LIE register to logic 1, enables the selected interrupt(s). Figure below shows the 
contents of the LIE details on each bit follow.
*******************************************************/
	union   LIE_REGS  LLIE;		//0x10
/*************************************************
LIN Status Register is a read only register which provides DLIN status information to the host CPU. All flags are 
automatically set when corresponding event occurs. When ERR bit is set it means that some errors were encountered. To 
find the source of error is read from the LER register (see the next section). Bit LID (LSR[0]) is cleared upon reading LID 
register. ERR bit (LSR[2]) is cleared when the LER register is read.

Control Register is used for controlling transmission frame. It is write only register,
reading of this address return contents of status register.

**************************************************/
	union   LSR_LCR_REGS  LLSR_LLCR;		//0x14


/********************************************************
The sync bit is used for enabling synchronization process (Slave mode only). Synchronization process uses SYNC field in 
transmitted header to synchronize slave data with master clock. It is based on time measurement between falling edges 
of the pattern. After finished synchronization SYNC bit is automatically clear by hardware.
*****************************************************/
/***********************************
DLL :Baud rate divider least significant bits.
**********************************/
	union   DLL_REGS  LDLL;  	//0x18
	union   DLH_REGS  LDLH;		//0x1C

/*********************************************************
The HDR it is 16-bit register which specifies additional delay between toggle Send Header command, 
by write to LSR register, and start Frame Header sending on LIN bus. After write to LSR register
value "xxxxxx10" the value from HDR register will be copied to internal counter. This counter will
be decremented when the prescaler counter reaches zero. When the HDR counter reaches 0 value, DLIN
starts sending Frame Header. Writing new value to HDR register during  countdown has no effect 
until current command is not finished. If the HDR register value is 0 and Send Header command 
is toggle, the Frame Header will be send immediately.
********************************************************************************/	
	Uint32   LHDRL;				//0x20
	Uint32   LHDRH;				//0x24
/*************************************************************************
The HDP it is 8-bit prescaler register which specifies interval of decrementing HDR register. 
Content of this register is decremented in every clock cycles when Send Header command is 
toggle. When counter reach zero the HDR register is decremented. Write new value to HDP register during
countdown has no effect until current command will not finish.
*************************************************************************/
	Uint32  LHDP;			//0x28
/*********************************************
The LBR it is 8-bit registers which contains information about LIN bus status. The SLEEPM bit is the only bit which can by 
set/clear by cpu host. Access to this bit is allowed only no command is executed. This bit can be automatically clear when 
wake-up signal is detected on LIN bus. The detection of wake-up signal is enabled only when SLEEPM bit is set. The 
WAKEUP bit is set when the wake-up signal is detected on LIN bus. The SLEEP bit indicates detection of sleep mode. This 
bit is set in one of two cases. When master send go to sleep command and when IDT timer detects inactivity of LIN bus
(if IDTRUN bit is set). When one of this continion occur the SLEEP bit is set and interrupt request in generated. The 
detection if sleep mode does not entry DLIN in low-power mode. It inform the application aboat sleep mode event. Read 
from this register automatically clear WAKEUP bit and SLEEP bit.
****************************************************/
	union  LBR_REG  LLBR;	//0x2C
	
/***********************************************************
The register contains 8 - bit value witch is compared with wake-up response timer value in waiting for response state. 
When DLIN work as slave and it sent the wake-up signal it reset and run wake-up response timer, this timer is increment 
at every bit time tick divided by 32. When counted value and WURT value are equal and no response detected then 
WUER bit is set and interrupt request is generated.
*******************************************************/
	Uint32 LWURT;		//0x30
/*******************************************************
The register contains 13- bit value which is compared with idle detection timer value. This timer is reset and run when 
dominant to recessive transition is detected, is increment at every bit time tick divided by 32. To enable counting the 
IDTRUN bit must be set, in this situaltion write to IDT[12:0] is locked. In order to save new value to IDT register, first clear 
IDTRUN bit and then write new value to IDT[12:0].
**************************************************/
	Uint32 LIDTL;		//0x34
	union  IDTH_REGS LIDTH;		//0x38

	Uint32 rsvd1[49];

	Uint32  LSCI_ENABLE;//切换  SCI 还是LIN//0xC500   写1是LIN  写0是Uart
	Uint32 rsvd2[63];
	union LRBR_DLL_THR_REG LRBR_DLL_THR;  //0
	union LDLH_IER_REG  LDLH_IER;       //0x04
	union LFCR_IIR_REG  LFCR_IIR;   //0x08
	union LLCR_REG LLCR;//Line Control Register   //0x0C
	union LMCR_REG LMCR;//Modem Control Register  //0x10
	union LLSR_REG LLSR;//Line Status Register	  //0x14
	union LMSR_REG LMSR;//Modem Status Register   //0x18
	union LSCR_REG LSCR;//Scratchpad Register		//0x1C
	Uint32 Resvd3[20];
	union LFAR_REG   LFAR;//FIFO Access Register				// 0x70
	Uint32 rsvd5[2];
	union LUSR_REG   LUSR;//UART Status register				//0x7C
	Uint32 rsvd6[9];
	union LHTX_REG  LHTX;//Halt TX								//0xA4
	union LDMASA_REG LDMASA;//DMA Software Acknowledge Register	//0xA8
	Uint32 rsvd7[17];

	union LAUTOBAUD_REG  LAUTOBAUD;//0xf0

};




extern volatile struct  LIN_REGS   *const  P_LinaRegs;
extern volatile struct  LIN_REGS     LinaRegs;




#endif



