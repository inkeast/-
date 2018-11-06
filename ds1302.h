#include<reg52.h>
#define uchar unsigned char
sbit ACC7=ACC^7;
sbit ACC0=ACC^0;
sbit scl=P3^6;
sbit sda=P3^4;
sbit rst=P3^5;
void w1byte(uchar date)
{
uchar i;
ACC=date;
for(i=8;i>0;i--)
{
scl=0;
sda=ACC0;
scl=1;
ACC>>=1;
}
}

uchar r1byte()
{
uchar i;
for(i=8;i>0;i--)
{
scl=0;
ACC>>=1;
ACC7=sda;
scl=1;
}
return (ACC);
}

uchar rbyte(uchar command)
{
uchar a;
rst=0;
scl=0;
rst=1;
w1byte(command|0x01);
a=r1byte();
rst=0;
return(a);
}

uchar gettime()
{
uchar readval;
readval=rbyte(0x80);
readval=((readval&0x70)>>4)*10+(readval&0x0f);
return (readval);
}