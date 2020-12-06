#include<reg51.h>
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay();
void main()
{
	unsigned char x;
	SCON = 0X50;			// initialize serial communication
	TMOD = 0X20;			// timer 1 mode 2
	TH1 = -3;					// baudrate 9600
	TR1 = 1;					// start timer
	lcdcmd(0x38);     // 5x7 matrix initializing all rows and columns
	delay();
	lcdcmd(0x01);		//clear the screen
	delay();
	lcdcmd(0x10);   // display on cursor blinking
	delay();
	lcdcmd(0x0c);    // cursor position shifted to right
	delay();
	lcdcmd(0x80);
	delay();
	while(1)
	{
		while(RI == 0);
		x = SBUF;					//store the character inside a register//
		SBUF = x;          // re-transmit to terminal 
		while(TI == 0);			// wait transmission is over
		TI=0;								// clear Ti for next transmission
		RI=0;								// clear Ri for nxt receiver
		lcddat(x);					// display on LCD received data
		delay();
	}
}

void  lcdcmd(unsigned char val)
{
	P1 = val;
	rs = 0;
	rw = 0;
	en = 1;
	delay();
	en = 0;
}

void lcddat(unsigned char dat)
{
	P1 = dat;
	rs = 1;
	rw = 0;
	en = 1;
	delay();
	en = 0;
}

void delay()
{
	unsigned int i,j;
	for(i=0;i<1200;i++);
	for(j=0;j<10;j++);
}