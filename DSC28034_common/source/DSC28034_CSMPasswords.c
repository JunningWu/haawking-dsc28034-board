
#include "DSC28034_Device.h"     // DSP2802x Headerfile Include File
/**********************************************
password file
*****************************************************************/

volatile struct CSM_PWL  CODE_SECTION(".CsmPwl") CsmPwl = 
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
};


void init_call(void)
{
	CsmPwl.PSWD0;
	CsmPwl.PSWD1;
	CsmPwl.PSWD2;
	CsmPwl.PSWD3;
}




