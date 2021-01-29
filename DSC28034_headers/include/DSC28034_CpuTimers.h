

#ifndef DSC28034_CPU_TIMERS_H
#define DSC28034_CPU_TIMERS_H



#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// CPU Timer Register Bit Definitions:
//
//
// TCR: Control register bit definitions:
struct  TCR_BITS {          // bits  description
   Uint32    rsvd1:4;       // 3:0   reserved
   Uint32    TSS:1;         // 4     Timer Start/Stop
   Uint32    TRB:1;         // 5     Timer reload
   Uint32    rsvd2:4;       // 9:6   reserved
   Uint32    SOFT:1;        // 10    Emulation modes
   Uint32    FREE:1;        // 11
   Uint32    rsvd3:2;       // 12:13 reserved
   Uint32    TIE:1;         // 14    Output enable
   Uint32    TIF:1;         // 15    Interrupt flag
   Uint32    rsvd16:16;
};

union TCR_REG {
   Uint32           all;
   struct TCR_BITS  bit;
};

// TPR: Pre-scale low bit definitions:
struct  TPR_BITS {        // bits  description
   Uint32     TDDR:16;     // 15:0   Divide-down 
   Uint32     PSC:16;      // 31:16  Prescale counter 
};

union TPR_REG {
   Uint32           all;
   struct TPR_BITS  bit;
};




//---------------------------------------------------------------------------
// CPU Timer Register File:
//
struct CPUTIMER_REGS {
   Uint32 TIM;   // Timer counter register
   Uint32 PRD;   // Period register
   union TCR_REG   TCR;   // Timer control register
   union TPR_REG   TPR;   // Timer pre-scale 

};

//---------------------------------------------------------------------------
// CPU Timer Support Variables:
//
struct CPUTIMER_VARS {
   volatile struct  CPUTIMER_REGS  *RegsAddr;
   Uint32    InterruptCount;
   float   CPUFreqInMHz;
   float   PeriodInUSec;
};

//---------------------------------------------------------------------------
// Function prototypes and external definitions:
//
void InitCpuTimers(void);
void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period);




extern volatile struct CPUTIMER_REGS *const  P_CpuTimer0Regs;  
extern volatile struct CPUTIMER_REGS *const  P_CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS *const  P_CpuTimer2Regs; 

extern volatile struct CPUTIMER_REGS CpuTimer0Regs;  
extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs; 



extern struct CPUTIMER_VARS CpuTimer0;
extern struct CPUTIMER_VARS CpuTimer1;
extern struct CPUTIMER_VARS CpuTimer2;





//---------------------------------------------------------------------------
// Usefull Timer Operations:
//

// Start Timer:
#define StartCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 0
#define StartCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 0
#define StartCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 0

// Stop Timer:
#define StopCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 1
#define StopCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 1
#define StopCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
#define ReloadCpuTimer0() CpuTimer0Regs.TCR.bit.TRB = 1
#define ReloadCpuTimer1() CpuTimer1Regs.TCR.bit.TRB = 1
#define ReloadCpuTimer2() CpuTimer2Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
#define ReadCpuTimer0Counter() CpuTimer0Regs.TIM.all
#define ReadCpuTimer1Counter() CpuTimer1Regs.TIM.all
#define ReadCpuTimer2Counter() CpuTimer2Regs.TIM.all

// Read 32-Bit Period Value:
#define ReadCpuTimer0Period() CpuTimer0Regs.PRD.all
#define ReadCpuTimer1Period() CpuTimer1Regs.PRD.all
#define ReadCpuTimer2Period() CpuTimer2Regs.PRD.all

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2802x_CPU_TIMERS_H definition

//===========================================================================
// End of file.
//===========================================================================
