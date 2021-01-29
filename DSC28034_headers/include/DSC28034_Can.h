#ifndef DSC28034_CAN_H
#define DSC28034_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Interrupt Status Register  0x000
// 
struct INTSTATUS_BITS
{                          // bits    description
    Uint32 rsvd1:2;        // 1:0       Reserved
	Uint32 ARB_LOSS:1;     // 2       Arbitration loss
	Uint32 OVR_LOAD:1;     // 3       Overload condition detected	
	Uint32 BIT_ERR:1;      // 4       Bit error
	Uint32 STUFF_ERR:1;    // 5       Bit stuffing error
	Uint32 ACK_ERR:1;      // 6       Acknowledge error
	Uint32 FORM_ERR:1;     // 7       Format error
	Uint32 CRC_ERR:1;      // 8       CRC errory  
	Uint32 BUS_OFF:1;      // 9       Bus-off
	Uint32 RX_MSG_LOSS:1;  // 10      Received message lost
	Uint32 TX_MSG:1;       // 11      Message transmitted
	Uint32 RX_MSG:1;       // 12      Receive message available
	Uint32 RTR_MSG:1;      // 13      RTR auto-reply message sent
	Uint32 STUCK_AT_0:1;   // 14      Stuck at dominant error
	Uint32 SST_FAILURE:1;  // 15      Single shot transmission failure
	Uint32 rsvd2:16;       // 31-16   Reserved    
};

union INTSTATUS_REG
{
	Uint32               all;
	struct  INTSTATUS_BITS  bit;
};


//
// Interrupt Enable Register  0x004
// 
struct INTEBL_BITS
{                          // bits    description

	Uint32 INT_EBL:1;      // 1       Global interrupt enable flag
    Uint32 rsvd1:1;        // 0       Reserved
	Uint32 ARB_LOSS:1;     // 2       Arbitration loss
	Uint32 OVR_LOAD:1;     // 3       Overload condition detected	
	Uint32 BIT_ERR:1;      // 4       Bit error
	Uint32 STUFF_ERR:1;    // 5       Bit stuffing error
	Uint32 ACK_ERR:1;      // 6       Acknowledge error
	Uint32 FORM_ERR:1;     // 7       Format error
	Uint32 CRC_ERR:1;      // 8       CRC errory  
	Uint32 BUS_OFF:1;      // 9       Bus-off
	Uint32 RX_MSG_LOSS:1;  // 10      Received message lost
	Uint32 TX_MSG:1;       // 11      Message transmitted
	Uint32 RX_MSG:1;       // 12      Receive message available
	Uint32 RTR_MSG:1;      // 13      RTR auto-reply message sent
	Uint32 STUCK_AT_0:1;   // 14      Stuck at dominant error
	Uint32 SST_FAILURE:1;  // 15      Single shot transmission failure
	Uint32 rsvd2:16;       // 31-16   Reserved    
};

union INTEBL_REG
{
	Uint32               all;
	struct  INTEBL_BITS  bit;
};


//
// RxMessage Buffer Status    0x008
// 
struct RXBUFFERSTATUS_BITS
{                              // bits    description

	Uint32 RXMESSAGE0:1;       // 0       MsgAv Flag
	Uint32 RXMESSAGE1:1;       // 1       MsgAv Flag
	Uint32 RXMESSAGE2:1;       // 2       MsgAv Flag
	Uint32 RXMESSAGE3:1;       // 3       MsgAv Flag
	Uint32 RXMESSAGE4:1;       // 4       MsgAv Flag
	Uint32 RXMESSAGE5:1;       // 5       MsgAv Flag
	Uint32 RXMESSAGE6:1;       // 6       MsgAv Flag
	Uint32 RXMESSAGE7:1;       // 7       MsgAv Flag
	Uint32 RXMESSAGE8:1;       // 8       MsgAv Flag
	Uint32 RXMESSAGE9:1;       // 9       MsgAv Flag
	Uint32 RXMESSAGE10:1;      // 10      MsgAv Flag
	Uint32 RXMESSAGE11:1;      // 11      MsgAv Flag
	Uint32 RXMESSAGE12:1;      // 12      MsgAv Flag
	Uint32 RXMESSAGE13:1;      // 13      MsgAv Flag
	Uint32 RXMESSAGE14:1;      // 14      MsgAv Flag
	Uint32 RXMESSAGE15:1;      // 15      MsgAv Flag
	Uint32 RXMESSAGE16:1;      // 16      MsgAv Flag
	Uint32 RXMESSAGE17:1;      // 17      MsgAv Flag
	Uint32 RXMESSAGE18:1;      // 18      MsgAv Flag
	Uint32 RXMESSAGE19:1;      // 19      MsgAv Flag
	Uint32 RXMESSAGE20:1;      // 20      MsgAv Flag
	Uint32 RXMESSAGE21:1;      // 21      MsgAv Flag
	Uint32 RXMESSAGE22:1;      // 22      MsgAv Flag
	Uint32 RXMESSAGE23:1;      // 23      MsgAv Flag
	Uint32 RXMESSAGE24:1;      // 24      MsgAv Flag
	Uint32 RXMESSAGE25:1;      // 25      MsgAv Flag
	Uint32 RXMESSAGE26:1;      // 26      MsgAv Flag
	Uint32 RXMESSAGE27:1;      // 27      MsgAv Flag
	Uint32 RXMESSAGE28:1;      // 28      MsgAv Flag
	Uint32 RXMESSAGE29:1;      // 29      MsgAv Flag
	Uint32 RXMESSAGE30:1;      // 30      MsgAv Flag
	Uint32 RXMESSAGE31:1;      // 31      MsgAv Flag
   
};

union RXBUFFERSTATUS_REG
{
	Uint32               all;
	struct  RXBUFFERSTATUS_BITS  bit;
};


//
// TxMessage Buffer Status    0x00C
// 
struct TXBUFFERSTATUS_BITS
{                              // bits    description

	Uint32 TXMESSAGE0:1;       // 0       TxReq pending
	Uint32 TXMESSAGE1:1;       // 1       TxReq pending
	Uint32 TXMESSAGE2:1;       // 2       TxReq pending
	Uint32 TXMESSAGE3:1;       // 3       TxReq pending
	Uint32 TXMESSAGE4:1;       // 4       TxReq pending
	Uint32 TXMESSAGE5:1;       // 5       TxReq pending
	Uint32 TXMESSAGE6:1;       // 6       TxReq pending
	Uint32 TXMESSAGE7:1;       // 7       TxReq pending
	Uint32 TXMESSAGE8:1;       // 8       TxReq pending
	Uint32 TXMESSAGE9:1;       // 9       TxReq pending
	Uint32 TXMESSAGE10:1;      // 10      TxReq pending
	Uint32 TXMESSAGE11:1;      // 11      TxReq pending
	Uint32 TXMESSAGE12:1;      // 12      TxReq pending
	Uint32 TXMESSAGE13:1;      // 13      TxReq pending
	Uint32 TXMESSAGE14:1;      // 14      TxReq pending
	Uint32 TXMESSAGE15:1;      // 15      TxReq pending
	Uint32 TXMESSAGE16:1;      // 16      TxReq pending
	Uint32 TXMESSAGE17:1;      // 17      TxReq pending
	Uint32 TXMESSAGE18:1;      // 18      TxReq pending
	Uint32 TXMESSAGE19:1;      // 19      TxReq pending
	Uint32 TXMESSAGE20:1;      // 20      TxReq pending
	Uint32 TXMESSAGE21:1;      // 21      TxReq pending
	Uint32 TXMESSAGE22:1;      // 22      TxReq pending
	Uint32 TXMESSAGE23:1;      // 23      TxReq pending
	Uint32 TXMESSAGE24:1;      // 24      TxReq pending
	Uint32 TXMESSAGE25:1;      // 25      TxReq pending
	Uint32 TXMESSAGE26:1;      // 26      TxReq pending
	Uint32 TXMESSAGE27:1;      // 27      TxReq pending
	Uint32 TXMESSAGE28:1;      // 28      TxReq pending
	Uint32 TXMESSAGE29:1;      // 29      TxReq pending
	Uint32 TXMESSAGE30:1;      // 30      TxReq pending
	Uint32 TXMESSAGE31:1;      // 31      TxReq pending
   
};

union TXBUFFERSTATUS_REG
{
	Uint32               all;
	struct  TXBUFFERSTATUS_BITS  bit;
};


//
// CAN Error Status  0x010
// 
struct ERRSTATUS_BITS
{                            // bits     description

	Uint32 TX_ERR_CNT:8;     // 7:0      The transmitter error counter according to the CAN standard.
	Uint32 RX_ERR_CNT:8;     // 15:8     The receive error counter according to the CAN 2.0 specification.
	Uint32 ERROR_STATE:2;    // 17:16    The error state of the CAN node      T
	Uint32 TXGTE96:1;        // 18       The Tx error counter is greater or equal 96dec
	Uint32 RXGTE96:1;        // 19       The Rx error counter is greater or equal 96dec
    Uint32 rsvd2:12;         // 31-20    Reserved   
    
};

union ERRSTATUS_REG
{
	Uint32               all;
	struct  ERRSTATUS_BITS  bit;
};


//
// CAN Command & Revision Control Register  0x014
// 
struct COMMAND_BITS
{                                // bits     description

	Uint32 RUN_STOP_MODE:1;      // 0        Run/Stop mode
	Uint32 TEST_MODE:2;          // 2:1      Test Mode
	Uint32 SRAM_TEST_MODE:1;     // 3        SRAM test mode
	Uint32 rsvd1:12;             // 15-4     Reserved  
	Uint32 VERSION_NUMBER:8;     // 23:16    Revision number  
	Uint32 MINOR_VERSION:4;      // 27:24    Minor version
	Uint32 MAJOR_VERSION:4;      // 28:31    Major version      T  
    
};

union COMMAND_REG
{
	Uint32               all;
	struct  COMMAND_BITS  bit;
};



//
// CAN Configuration  0x018
// 
struct CONFIG_BITS
{                                // bits     description

	Uint32 EDGE_MODE:1;          // 0        CAN bus synchronization logic
	Uint32 SAMPLING_MODE:1;      // 1        CAN bus bit sampling
	Uint32 CFG_SJW:2;            // 3:2      Synchronization jump width - 1
	Uint32 AUTO_RESTART:1;       // 4        After bus-off, the CAN must be restarted 
	Uint32 CFG_TSEG2:3;          // 7:5      Time segment 2
	Uint32 CFG_TSEG1:4;          // 11:8     Time segment 1
	Uint32 CFG_ARBITER:1;        // 12       Transmit buffer arbiter
	Uint32 SWAP_ENDIAN:1;        // 13       The byte position of the CAN receive and transmit data fields 
	Uint32 ECR_MODE:1;           // 14       Error capture mode
	Uint32 rsvd1:1;              // 15       Reserved
	Uint32 CFG_BITRATE:15;       // 30:16    Prescaler for generating the time quantum which defines the TQ
	Uint32 rsvd2:1;              // 31       Reserved   
	    
};

union CONFIG_REG
{
	Uint32               all;
	struct  CONFIG_BITS  bit;
};


//=================================================================
//
// TxMessagex.Control    
// 
struct TXMSG_CONTROL_BITS
{                                // bits     description

	Uint32 TXREQ:1;              // 0        Transmit Request
	Uint32 TXABORT:1;            // 1        Transmit Abort Request
	Uint32 TXINTEBL:1;           // 2        Tx Interrupt Enable
	Uint32 WPNL:1;       		 // 3        Write Protect Not Low
	Uint32 rsvd1:12;             // 15:4     Reserved
	Uint32 DLC:4;                // 19:16    Data Length Code
	Uint32 IDE:1;                // 20       Extended Identifier Bit
	Uint32 RTR:1;                // 21       Remote Bit
	Uint32 rsvd2:1;              // 22       Reserved
	Uint32 WPNH:1;               // 23       Write Protect Not High
	Uint32 rsvd3:8;              // 31:24    Reserved
	    
};

union TXMSG_CONTROL_REG
{
	Uint32               all;
	struct  TXMSG_CONTROL_BITS  bit;
};


//
// RxMessagex.Control
// 
struct RXMSG_CONTROL_BITS
{                                // bits      description

	Uint32 MSGAV_RTRSENT:1;      // 0         Message Available/RTR sent
	Uint32 RTREPLY_PENDING:1;    // 1         RTR reply request pending
	Uint32 RTRABORT:1;           // 2         RTR Abort Request
	Uint32 BUFFER_ENABLE:1;      // 3         Buffer Enable
	Uint32 RTRREPLY:1;           // 4         automatic message reply upon receipt of an RTR message
	Uint32 RXINTEBL:1;           // 5         Receive Interrupt Enable
	Uint32 LINK_FLAG:1;          // 6         Link Flag
	Uint32 WPNL:1;               // 7         Write Protect Not Low
	Uint32 rsvd1:8;              // 15:8      Reserved
	Uint32 DLC:4;                // 19:16     Data Length Code
	Uint32 IDE:1;                // 20        Extended Identifier Bit
	Uint32 RTR:1;                // 21        Remote Bit
	Uint32 rsvd2:1;              // 22        Reserved
	Uint32 WPNH:1;               // 23        Write Protect Not High
	Uint32 rsvd3:8;              // 31:24     Reserved
	
};

union RXMSG_CONTROL_REG
{
	Uint32               all;
	struct  RXMSG_CONTROL_BITS  bit;
};


//
// Tx/RxMessagex.ID    
// 
struct MSG_ID_BITS
{                                // bits     description

	Uint32 rsvd1:3;              // 2:0      Reserved
	Uint32 ID:29;                 // 31:3     ID[28:0]
	    
};

union MSG_ID_REG
{
	Uint32               all;
	struct  MSG_ID_BITS  bit;
};


//
// Tx/RxMessagex.DataHigh    
// 
struct MSG_DATAHIGH_BITS
{                                // bits      description
                                 //                  big endian    little endian
	Uint32 BYTE4:8;              // 7:0       CAN data byte 4        byte 1
	Uint32 BYTE3:8;              // 15:8      CAN data byte 3        byte 2
	Uint32 BYTE2:8;              // 23:16     CAN data byte 2        byte 3
	Uint32 BYTE1:8;              // 31:24     CAN data byte 1        byte 4
	    
};

union MSG_DATAHIGH_REG
{
	Uint32               all;
	struct  MSG_DATAHIGH_BITS  byte;
};


//
// Tx/RxMessagex.DataLow    
// 
struct MSG_DATALOW_BITS
{                                // bits      description
	                             //					big endian	  little endian
	Uint32 BYTE8:8;              // 7:0       CAN data byte 8     byte 5
	Uint32 BYTE7:8;              // 15:8      CAN data byte 7     byte 6
	Uint32 BYTE6:8;              // 23:16     CAN data byte 6     byte 7
	Uint32 BYTE5:8;              // 31:24     CAN data byte 5     byte 8
	    
};

union MSG_DATALOW_REG
{
	Uint32               all;
	struct  MSG_DATALOW_BITS  byte;
};


//
// Rx Acceptance Mask/Code Register    
// 
struct RXMSG_AMR_ACR_BITS
{                                // bits      description
	Uint32 rsvd1:1;              // 0         Reserved
	Uint32 RTR:1;                // 1         
	Uint32 IDE:1;                // 2         
	Uint32 IDENTIFIER:29;        // 31:3      Identifier    
};

union RXMSG_AMR_ACR_REG
{
	Uint32               all;
	struct  RXMSG_AMR_ACR_BITS  bit;
};


//
// Rx Acceptance Mask/Code Register – Data   
// 
struct RXMSG_AMR_ACR_DATA_BITS
{                                // bits      description
	Uint32 BYTE1:8;              // 7:0       
	Uint32 BYTE2:8;              // 15:8
	Uint32 rsvd1:16;             // 31:16         Reserved	    
};

union RXMSG_AMR_ACR_DATA_REG
{
	Uint32               all;
	struct  RXMSG_AMR_ACR_DATA_BITS  byte;
};


//=====================================================

//
// TxMessagex Buffer
// 
struct TXMSG_BUFFER_REGS
{
	union TXMSG_CONTROL_REG       TXMSG_CONTROL;
	union MSG_ID_REG              MSG_ID;
	union MSG_DATAHIGH_REG        DATAHIGH;
	union MSG_DATALOW_REG	      DATALOW;	
};


//
// RxMessagex Buffer
// 
struct RXMSG_BUFFER_REGS
{
	union RXMSG_CONTROL_REG          RXMSG_CONTROL;
	union MSG_ID_REG                 MSG_ID;
	union MSG_DATAHIGH_REG           DATAHIGH;
	union MSG_DATALOW_REG            DATALOW;
	union RXMSG_AMR_ACR_REG          AMR;
	union RXMSG_AMR_ACR_REG          ACR;
	union RXMSG_AMR_ACR_DATA_REG     AMR_DATA;     
	union RXMSG_AMR_ACR_DATA_REG     ACR_DATA;
};


struct ERROR_CAP_BITS
{                                // bits      description
	Uint32 STATUS:1;             // 0         Status
	Uint32 ERROR_TYPE:3;         // 3:1       Error type
	Uint32 RX_MODE:1;            // 4         Rx mode
	Uint32 TX_MODE:1;            // 5         Tx mode
	Uint32 BIT_NUMBER:6;         // 11:6      Bit number	
	Uint32 FIELD:5;              // 16:12     Field
	Uint32 rsvd1:15;             // 31:17     Reserved
					    
};

union ERROR_CAP_REG
{
	Uint32               all;
	struct  ERROR_CAP_BITS  bit;
};



//
//=================================================================
//
struct CAN_REGS
{
	union INTSTATUS_REG           INTSTATUS;    
	union INTEBL_REG              INTEBL;    
	union RXBUFFERSTATUS_REG      RXTATUS;
	union TXBUFFERSTATUS_REG      TXTATUS;
	union ERRSTATUS_REG           ERRSTATUS;
	union COMMAND_REG             COMMAND;
	union CONFIG_REG              CONFIG;
    union ERROR_CAP_REG           ECR;    
	
	struct TXMSG_BUFFER_REGS      TXMSG0;
	struct TXMSG_BUFFER_REGS      TXMSG1;
	struct TXMSG_BUFFER_REGS      TXMSG2;
	struct TXMSG_BUFFER_REGS      TXMSG3;
	struct TXMSG_BUFFER_REGS      TXMSG4;
	struct TXMSG_BUFFER_REGS      TXMSG5;
	struct TXMSG_BUFFER_REGS      TXMSG6;
	struct TXMSG_BUFFER_REGS      TXMSG7;
	struct TXMSG_BUFFER_REGS      TXMSG8;
	struct TXMSG_BUFFER_REGS      TXMSG9;
	struct TXMSG_BUFFER_REGS      TXMSG10;
	struct TXMSG_BUFFER_REGS      TXMSG11;
	struct TXMSG_BUFFER_REGS      TXMSG12;
	struct TXMSG_BUFFER_REGS      TXMSG13;
	struct TXMSG_BUFFER_REGS      TXMSG14;
	struct TXMSG_BUFFER_REGS      TXMSG15;
	struct TXMSG_BUFFER_REGS      TXMSG16;
	struct TXMSG_BUFFER_REGS      TXMSG17;
	struct TXMSG_BUFFER_REGS      TXMSG18;
	struct TXMSG_BUFFER_REGS      TXMSG19;
	struct TXMSG_BUFFER_REGS      TXMSG20;
	struct TXMSG_BUFFER_REGS      TXMSG21;
	struct TXMSG_BUFFER_REGS      TXMSG22;
	struct TXMSG_BUFFER_REGS      TXMSG23;
	struct TXMSG_BUFFER_REGS      TXMSG24;
	struct TXMSG_BUFFER_REGS      TXMSG25;
	struct TXMSG_BUFFER_REGS      TXMSG26;
	struct TXMSG_BUFFER_REGS      TXMSG27;
	struct TXMSG_BUFFER_REGS      TXMSG28;
	struct TXMSG_BUFFER_REGS      TXMSG29;
	struct TXMSG_BUFFER_REGS      TXMSG30;
	struct TXMSG_BUFFER_REGS      TXMSG31;

	struct RXMSG_BUFFER_REGS      RXMSG0;
	struct RXMSG_BUFFER_REGS      RXMSG1;
	struct RXMSG_BUFFER_REGS      RXMSG2;
	struct RXMSG_BUFFER_REGS      RXMSG3;
	struct RXMSG_BUFFER_REGS      RXMSG4;
	struct RXMSG_BUFFER_REGS      RXMSG5;
	struct RXMSG_BUFFER_REGS      RXMSG6;
	struct RXMSG_BUFFER_REGS      RXMSG7;
	struct RXMSG_BUFFER_REGS      RXMSG8;
	struct RXMSG_BUFFER_REGS      RXMSG9;
	struct RXMSG_BUFFER_REGS      RXMSG10;
	struct RXMSG_BUFFER_REGS      RXMSG11;
	struct RXMSG_BUFFER_REGS      RXMSG12;
	struct RXMSG_BUFFER_REGS      RXMSG13;
	struct RXMSG_BUFFER_REGS      RXMSG14;
	struct RXMSG_BUFFER_REGS      RXMSG15;
	struct RXMSG_BUFFER_REGS      RXMSG16;
	struct RXMSG_BUFFER_REGS      RXMSG17;
	struct RXMSG_BUFFER_REGS      RXMSG18;
	struct RXMSG_BUFFER_REGS      RXMSG19;
	struct RXMSG_BUFFER_REGS      RXMSG20;
	struct RXMSG_BUFFER_REGS      RXMSG21;
	struct RXMSG_BUFFER_REGS      RXMSG22;
	struct RXMSG_BUFFER_REGS      RXMSG23;
	struct RXMSG_BUFFER_REGS      RXMSG24;
	struct RXMSG_BUFFER_REGS      RXMSG25;
	struct RXMSG_BUFFER_REGS      RXMSG26;
	struct RXMSG_BUFFER_REGS      RXMSG27;
	struct RXMSG_BUFFER_REGS      RXMSG28;
	struct RXMSG_BUFFER_REGS      RXMSG29;
	struct RXMSG_BUFFER_REGS      RXMSG30;
	struct RXMSG_BUFFER_REGS      RXMSG31;

};

extern volatile struct CAN_REGS *const P_CanaRegs;

extern volatile struct CAN_REGS CanaRegs;


#ifdef __cplusplus

} 

#endif


#endif
