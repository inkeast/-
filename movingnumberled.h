#ifndef __movingnumberled_h__
#define __movingnumberled_h__

extern void movingnumberled(unsigned int a0,unsigned int a1,unsigned int a2,unsigned int a3,unsigned int a4,unsigned int a5,unsigned int a6,unsigned int a7);
#endif


sbit LSA=P3^0;
sbit LSB=P3^1;
sbit LSC=P3^7;

unsigned int n[8];

unsigned char smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
					


					void delayS(uchar i)
{
uchar j;
while(i--)for(j=11;j>0;j--);
}

void movingnumberled(unsigned int a0,unsigned int a1,unsigned int a2,unsigned int a3,unsigned int a4,unsigned int a5,unsigned int a6,unsigned int a7)
{
	unsigned char i;

	
	n[0]=a0;
	n[1]=a1;
	n[2]=a2;
	n[3]=a3;
	n[4]=a4;
	n[5]=a5;
	n[6]=a6;
	n[7]=a7;
	
	for(i=0;i<=7;i++)
	{
	
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		P0=smgduan[n[i]];//发送段码
		delayS(1); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
				LSA=0;LSB=0;LSC=1;
		P0=0x00;//消隐
}

