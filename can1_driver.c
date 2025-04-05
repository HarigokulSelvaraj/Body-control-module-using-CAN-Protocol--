#include <LPC21xx.H>
#include "header.h"
//u32 *ptr=(u32*)0xE0038000;


void can1_init()
{
	VPBDIV=1;//PCLK=60MHz
	PINSEL1&=~(1<<19);
	PINSEL1=(1<<18);
	C1MOD=0x1;//CAN1 into reset mode
	C1BTR=0x001C000E;//B250Kbps at PCLK=60MHz
	
	AFMR=0x2;//Accept all incoming messages
//	ptr[0]=0x00010003;
//	ptr[1]=0x00050007;
//	ptr[2]=0x0009000B;
//	SFF_sa=0;
//	SFF_GRP_sa=0xC;
//	EFF_sa=0xC;
//	EFF_GRP_sa=0xC;
//	ENDofTable=0xC;
//	AFMR=0;
	C1MOD=0x0;//CAN1 into normal mode
}
/*

void can1_tx(CAN_MSG m1)
{

	C1TID1=m1.id;
	C1TFI1=(m1.dlc<<16);
	if(m1.rtr==0) //if data frame
	{
		C1TFI1&=~(1<<30);//RTR=0
		C1TDA1=m1.byteA;
		C1TDB1=m1.byteB;
		
	}
	else	
		C1TFI1|=(1<<30);
	
	C1CMR=(1<<0)|(1<<5);//Start Xmission & use Tx Buf1
	while((C1SR&(1<<3))==0);		
}
*/
void can1_rx(CAN_MSG *m1)
{
	while((C1SR&1)==0);
	m1->id=C1RID;
	
	m1->rtr=(C1RFS>>30)&1;
	m1->dlc=(C1RFS>>16)&0xF;
	if(m1->rtr==0) //if data frame
	{	
		m1->byteA=C1RDA;
		
		m1->byteB=C1RDB;
		
	}	
	C1CMR=(1<<2);//free receiver buffers
}








