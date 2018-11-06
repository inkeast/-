#ifndef __infrared_h__
#define  __infrared_h__

extern int getkeynum(void);
#endif

#include<reg52.h>
sbit IRIN=P3^2;

unsigned char IrValue[6];
unsigned char Time,keynum;
void delay2(unsigned int i)
{
	while(i--);	
}
void IrInit()
{ unsigned char i;
	IT0=1;
	EX0=1;
	EA=1;	

	IRIN=1;
	for(i=0;i<6;i++){
		IrValue[i]=0;
	}
}
void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	delay2(1500);	//700
	if(IRIN==0)		
	{	 
		
		err=1000;				
		while((IRIN==0)&&(err>0))	 		
		{			
			delay2(24);
			err--;
		} 
		if(IRIN==1)			
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				delay2(24);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						delay2(24);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						delay2(240);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(Time>=8)			//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}	
	keynum=IrValue[2]/16*10+IrValue[2]%16;
}
int getkeynum(){
		IrInit();
	  return keynum;
}