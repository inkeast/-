#ifndef __gameoverbeep_h__
#define  __gameoverbeep_h__

extern void god(void);
#endif

#include<reg52.h>
sbit beep=P3^6;
int count=0;
unsigned char Array[]={
0x0D,0x01, 0x10,0x01, 0x15,0x02, 0x16,0x02, 0x17,0x02,
0x10,0x02, 0x15,0x02, 0x16,0x02, 0x11,0x02, 0x11,0x02,
0x11,0x02, 0x11,0x02, 0x16,0x01, 0x0F,0x01, 0x11,0x02,
0x15,0x02, 0x16,0x02, 0x0F,0x02, 0x15,0x02, 0x11,0x02,
0x10,0x02, 0x10,0x02, 0x10,0x02, 0x21,0x02, 0x1A,0x02,
0x1F,0x02, 0x20,0x02, 0x21,0x02, 0x1A,0x02, 0x15,0x02,
0x20,0x02, 0x1B,0x02, 0x1B,0x02, 0x1B,0x02, 0x1B,0x02,
0x20,0x02, 0x19,0x02, 0x1B,0x02, 0x1F,0x02, 0x20,0x02,
0x19,0x02, 0x1F,0x02, 0x1B,0x02, 0x1A,0x02, 0x1A,0x02,
0x00,0x00 
};
void delay_B(uchar n)
{
 uchar i;
 while(n--)
  for(i=0;i<3000;i++); //??1?? 

}
void sound_delay(uchar n)
{ 
 uchar i;
 while(n--)
 {
  for(i=0;i<48;i++);
 }
}
void init_com()
{
 TMOD=0x01;
 TH0=0xff;
 TL0=0xff;
 EA=1;
 ET0=1;
}
void timer0(void) interrupt 1 
{
 count=count+1;
 TH0=0xd8; //??????????? 
 TL0=0xef;
}


void god(void){
	int de;
	int despace;
	int design;
	init_com();
	de=0;
	count=0;

	while(Array[de]!=0x00){
		      if(Array[de]==0xff)
   {
     TR0=0;
     de++;
     delay_B(100);
     continue;
    }
		     
					design=Array[de++];
					despace=Array[de];
					de++;
					 TR0=1;
					 while(count!=despace){
				 beep=~beep;
				sound_delay(design);
						 
					 } 
				   count=0;
		}

	}
	
	

