#include<lpc21xx.h>
#include "header.h"
#define sw 1<<8
u32 led_sw(void)
{
	PINSEL0=0X00000000;
	IODIR0=0X000000000;
	
	if((IOPIN0&sw)==0)
		return 1;
	else 
		return 0;
}

