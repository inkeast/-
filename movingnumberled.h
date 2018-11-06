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
	
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		P0=smgduan[n[i]];//���Ͷ���
		delayS(1); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}
				LSA=0;LSB=0;LSC=1;
		P0=0x00;//����
}

