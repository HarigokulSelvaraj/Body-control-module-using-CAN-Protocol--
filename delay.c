void delay_ms(unsigned int ms)
{
	unsigned int i;
	for(;ms>0;ms--)
		for(i=48000;i>0;i--);
}
