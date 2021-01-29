//###########################################################################
//
// FILE:   DSC2803x_HRCap.h
//
// TITLE:  DSC2803x High Resolution Capture Register Definitions
//
//###########################################################################
// $TI Release: F2803x Support Library v2.01.00.00 $
// $Release Date: Fri May 24 03:36:54 CDT 2019 $
// $Copyright:
// Copyright (C) 2009-2019 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef DSC28034_HRCAP_H
#define DSC28034_HRCAP_H

#ifdef __cplusplus
extern "C" {
#endif

//
//  High-Resolution Capture Register Bit Definitions
//
struct HCCTL_BITS {            // bit     description
    Uint32   SOFTRESET:1;      // 0       Soft Reset
    Uint32   RISEINTE:1;       // 1       RISE Capture Interrupt Enable Bit
    Uint32   FALLINTE:1;       // 2       FALL Capture Interrupt Enable Bit
    Uint32   OVFINTE:1;        // 3       Counter Overflow Interrupt Enable Bit
    Uint32   rsvd1:4;          // 7:4     reserved
    Uint32   HCCAPCLKSEL:1;    // 8       Capture Clock Select Bit
    Uint32   rsvd2:7; 		   // 15:9	  reserved
    Uint32   rsvd3:16;         // 31:16    reserved

};

union HCCTL_REG  {
    Uint32                       all;
    struct HCCTL_BITS            bit;
};

struct HCIFR_BITS {            // bit       description
    Uint32   INT:1;            // 0         Global Interrupt Flag
    Uint32   RISE:1;           // 1         RISE Capture Interrupt Flag
    Uint32   FALL:1;           // 2         FALL Capture Interrupt Flag
    Uint32   COUNTEROVF:1;     // 3         Counter Overflow Interrupt Flag
    Uint32   RISEOVF:1;  	   // 4         RISE Interrupt Overflow Event Flag
    Uint32   rsvd1:11;         // 15:5      reserved
    Uint32   rsvd2:16;         // 31:16    reserved
};

union HCIFR_REG  {
    Uint32                       all;
    struct HCIFR_BITS            bit;
};

struct HCICLR_BITS {           // bit description
    Uint32   INT:1;            // 0   Global Interrupt Flag Clear Bit
    Uint32   RISE:1;           // 1   RISE Capture Interrupt Flag Clear Bit
    Uint32   FALL:1;           // 2   FALL Capture Interrupt Flag Clear Bit
    Uint32   COUNTEROVF:1;     // 3   Counter Overflow Interrupt Flag Clear Bit
    Uint32   RISEOVF:1;  	   // 4   RISE Int. Overflow Event Flag Clear Bit
    Uint32   rsvd1:11;         // 15:5 reserved
    Uint32   rsvd2:16;         // 31:16    reserved
};

union HCICLR_REG  {
    Uint32                       all;
    struct HCICLR_BITS           bit;
};

struct HCIFRC_BITS {           // bit  description
    Uint32   rsvd1:1;          // 0    reserved
    Uint32   RISE:1;           // 1    RISE Capture Interrupt Flag Force Bit
    Uint32   FALL:1;           // 2    FALL Capture Interrupt Flag Force Bit
    Uint32   COUNTEROVF:1;     // 3    Counter Overflow Interrupt Flag Force Bit
    Uint32   RISEOVF:1;  	   // 4    RISE Int. Overflow Event Flag Force Bit
    Uint32   rsvd2:11;         // 15:5 reserved
    Uint32   rsvd3:16;         // 31:16    reserved
};

union HCIFRC_REG  {
    Uint32                       all;
    struct HCIFRC_BITS           bit;
};


struct HCCAL_BITS {                  // bit     description
    Uint32   DLL_START_POINT:8;      // 0-7     Default:0x20
    Uint32   PHASE_DETECT_SEL:3;     // 8-10    Default:0x0
    Uint32   rsvd:3;                 // 11-13   reserved
    Uint32   HRCAPMODE:1;            // 14      捕获模式选择    
    Uint32   HRPWMSEL:1;             // 15      HRPWM选择     
    Uint32   rsvd2:16;               // 31:16   reserved
};

union HCCAL_REG  {
    Uint32                       all;
    struct HCCAL_BITS           bit;
};


struct HCMEPSTATUS_BITS {            // bit     description
    Uint32   LOCK_STATUS:2;          // 0-1     Value:0-unlock; 1-lock_done; 2/3-lock error
    Uint32   MEP_SCALE_FACTOR:8;     // 2-9     HRCAP校准结果
    Uint32   rsvd:6;                 // 10-15   reserved     
    Uint32   rsvd2:16;               // 31:16   reserved
};

union HCMEPSTATUS_REG  {
    Uint32                       all;
    struct HCMEPSTATUS_BITS           bit;
};



struct HRCAP_REGS {
    union  HCCTL_REG           HCCTL;            // h0 0xCC00
    union  HCIFR_REG           HCIFR;            // h1 0xCC04
    union  HCICLR_REG          HCICLR;           // h2 0xCC08
    union  HCIFRC_REG          HCIFRC;           // h3 0xCC0C
    Uint16                     HCCOUNTER;        // h4 0xCC10
    Uint16                     rsvd0;
    union  HCCAL_REG           HCCAL;            // h5 0xCC14 new
    Uint32                     HCCALMEP;         // h6 0xCC18 new
    union  HCMEPSTATUS_REG     HCMEPSTATUS;      // h7 0xCC1C new
    Uint32                     rsvd1[8];         
    Uint32                     HCCAPCNTRISE0;    // h10 0xCC40
    Uint32                     rsvd2[1];            
    Uint32                     HCCAPCNTFALL0;    // h12 0xCC48
    Uint32                     rsvd3[5];
    Uint32                     HCCAPCNTRISE1;    // h18 0xCC60
    Uint32                     rsvd4[1];
    Uint32                     HCCAPCNTFALL1;    // h1A 0xCC68
    //Uint32                     rsvd9;
    //Uint32                     rsvd10;
    //Uint32                     rsvd11;
    //Uint32                     rsvd12[2];
};

//
//  High Resolution Capture External References and Function Declarations
//
extern volatile struct HRCAP_REGS *const P_HRCap1Regs;
extern volatile struct HRCAP_REGS *const P_HRCap2Regs;
extern volatile struct HRCAP_REGS HRCap1Regs;
extern volatile struct HRCAP_REGS HRCap2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_HRCAP_H definition

//
// End of file
//

