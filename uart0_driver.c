#include <LPC214X.H>
#include <stdio.h>
#include "header.h"
#define THRE (U0LSR&(1<<5))
#define RDR  (U0LSR&0x1)

void uart0_init(u32 baud)
{
	PINSEL0 |= 5;//P0.0=TXD0, P0.1=RXD0
	U0LCR=0x83;//DLAB=1, WORD LENGTH=8bits, PARITY=Disabled,No of Stop Bits=1
	switch(baud)	//setting baudrate
	{	
//		case 4800:	U0DLL=195;break;//4800bps
//		case 7200:	U0DLL=130;break;//7200bps
		case 9600:	U0DLL=195;break;//9600bps
//		case 57600:	U0DLL=16;break;//9600bps
		case 115200:U0DLL=32;break;//@PCLK=60MHz 
		default: 		U0DLL=195;//for PCLK=30MHz
	}	
	U0LCR=0x3;////DLAB=0, WORD LENGTH=8bits, PARITY=Disabled,No of Stop Bits=1
}

void uart0_tx(u8 data)
{
	U0THR=data;  //SUBF register in 8051
	while (THRE == 0);
}

void uart0_string(char *s)
{
	while(*s)
		uart0_tx(*s++);
}

void uart0_hex(u32 n)
{
	char buf[10];
	sprintf(buf,"%X",n);
	uart0_string(buf);
}


