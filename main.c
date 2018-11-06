#include <reg52.h>
#include <stdlib.h>
#include "ds1302.h"
#include "gameoverbeep.h"
#include "infrared.h"
#include "movingnumberled.h"
#define uchar unsigned char
#define uint unsigned int
#define max_length 64
#define up 1
#define down 2
#define left 3
#define right 4
	

uchar code zong[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; 
uchar code redblue[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe}; 
uchar code starty[]={0x40,0xa0,0x58,0x3c,0x3c,0x18,0x02,0x00};
uchar code endjudge[2][8]={{0x10,0x20,0x40,0x88,0x40,0x20,0x10,0x08},{0x10,0x22,0x42,0x8e,0x48,0x20,0x10,0x08}};

uint  speed=2000; 
uchar  lastx,lasty,gc=2;
uchar idata snakex[max_length],snakey[max_length]; 
uchar length; 
uchar fooddirection,snakedirection;  
//char snakecount;
//char foodcount;

//char H_snakecount;
//char H_foodcount;
//char L_foodcount;
//char L_snakecount;
char score;
char C_S;
char F_D;
char C_F;

bit snakelive;


uchar foodx,foody;  
bit exist;


void delay(uchar i)
{
uchar j;
while(i--)for(j=110;j>0;j--);
}

//void pause();
void jump();
void snakemove();
void foodmove();
void foodjump();
void foodpause();
void init();
void creatfood();
void drawsnake();
void drawfood();
void playgame();
void snakekeyscan();
void foodkeyscan();
void eatfood();
void gameover();
void di();
void UsartInit();
bit snakewall();
bit snakeself();
bit foodwall();
void main()
{
init();
playgame();
gameover();
}

void di()
{ uint i=50;
	while(1){
		
		i--;
		if(i>0){
			beep=~beep;
			delay(2);
		}else{
			break;
		}
	}
}

sfr AUXR   = 0x8E;

void InitUART(void)
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xD9;
    TL1 = TH1;
    PCON = 0x00;
    TR1 = 1;
}



void init() //???
{
	uchar i;
score=30;
//snakecount=8;
//foodcount=0;
//H_snakecount=12;
//H_foodcount=0;
//L_foodcount=0;
//L_snakecount=2;
C_S=0;
C_F=0;
F_D=0;
length=6;
 AUXR = AUXR|0x40;  // T1, 1T Mode
    InitUART();
for(i=0;i<length;i++);{
	snakex[i]=0;
	snakey[i]=0;
}


foodx=7;
foody=7;
exist=1;
snakedirection=4;
fooddirection=3;
snakelive=1;
srand(gettime()); //?ds1302???,???????
while(getkeynum()!=45){
	for(i=0;i<8;i++){
	P0=starty[i];
	P1=redblue[i];
		snakekeyscan();
		foodkeyscan();
		P0=0;
    P1=0xff;
	}
}
}
void playgame()
{
uint p;
delay(5);
snakemove();
	while(snakelive)
	{  
		if(score<=0){
			break;
		}
//		if(snakecount==0){
//			snakecount=8;
//			foodcount=0;
//		}
//		if(H_snakecount==0){
//			H_snakecount=12;
//			H_foodcount=0;
//		}
//		if(L_snakecount==0){
//			L_snakecount=2;
//			L_foodcount=0;
//		}
		if(snakewall()&&snakeself())
		{
			if(!foodwall())
			{
				di();
				exist=0;
			}
			if(!exist)
			{
				creatfood();
			}
			exist=1;
			eatfood();
			if(score>=80){
				break;
			}
			for(p=speed;p>0;p--) //????,????
			{
				drawsnake();
				P0=0;
				movingnumberled(C_F/10,C_F%10,C_S/10,C_S%10,0,score/100%10,score/10%10,score%10);
				drawfood();
			}
			snakemove();
			if(!F_D){
			foodmove();
			}
		}else{
		snakelive=0;
		}

	}
}
void drawsnake()   //???
{
uchar i;
for(i=0;i<length;i++)
{
//P0=0;
//movingnumberled(C_F/10,C_F%10,C_S/10,C_S%10,0,score/100%10,score/10%10,score%10);
//P0=0;
P0=zong[snakey[i]];
P2=redblue[snakex[i]];
snakekeyscan();
if(!C_S)
	foodpause();
P0=0;
P2=0xff;
}
}

void creatfood()
{
uchar i;
loop: foodx=((int)rand()%6)+1;
foody=((int)rand()%6)+1;
for(i=0;i<length;i++)
{
if((foodx==snakex[i])&&((foody)==snakey[i]))
goto loop;
}
}
void drawfood() //????
{
if(exist)
{
//movingnumberled(C_F/10,C_F%10,C_S/10,C_S%10,0,score/100%10,score/10%10,score%10);
//P0=0;
//P2=0xff;
P0=zong[foody];
P1=redblue[foodx];
foodkeyscan(); 
if(!C_S){
	if(!C_F)
		foodjump();
}
P0=0;
P1=0xff;
}
}

void foodkeyscan(){
	if(getkeynum()==40)
{
fooddirection=up;
}


if(getkeynum()==19)
{
fooddirection=down;
}


if(getkeynum()==7)
{
fooddirection=left;
}

if(getkeynum()==9)
{
fooddirection=right;
}

}

void snakekeyscan() //????
{

if(getkeynum()==18)
{
if(snakedirection!=down)snakedirection=up;
}


if(getkeynum()==52)
{
if(snakedirection!=up)snakedirection=down;
}


if(getkeynum()==8)
{
if(snakedirection!=right)snakedirection=left;
}


if(getkeynum()==60)
{
if(snakedirection!=left)snakedirection=right;
}

}

void snakemove()
{
uchar k;
if(F_D){
F_D--;
}
if(C_S){
C_S--;
}
if(C_F){
C_F--;
}
score--;
//snakecount--;
//H_snakecount--;
//L_snakecount--;
lastx=snakex[length-1];
lasty=snakey[length-1];
for(k=length-1;k>0;k--)
{
snakex[k]=snakex[k-1];
snakey[k]=snakey[k-1];
}
switch(snakedirection)
{
case up: snakey[0]++;
break;
case down: snakey[0]--;
break;
case left: snakex[0]--;
break;
case right: snakex[0]++;
break;
}
	SBUF=(C_F);
	while(!TI);			 
	TI=0;
delay(1);
	SBUF=(C_S);
	while(!TI);			 
	TI=0;
delay(1);
	SBUF=(score);
	while(!TI);			 
	TI=0;
}
void foodmove(){
	switch(fooddirection)
{
case up: foody++;
break;
case down: foody--;
break;
case left: foodx--;
break;
case right: foodx++;
break;
}
}

//void pause(){
//		L_snakecount=2;
//	  L_foodcount=L_snakecount;
//}

void jump(){
	switch(fooddirection)
{
case up: foody+=2;
break;
case down: foody-=2;
break;
case left: foodx-=2;
break;
case right: foodx+=2;
break;
}
}

void foodjump()
{
	if(getkeynum()==15)
		
	{ 
		C_F=8;
		di();
		jump();
//		snakecount=8;
//		foodcount=snakecount;
	}
}

void foodpause(){
	if(getkeynum()==22)
	{
		C_S=12;
		F_D=3;
		di();
//		pause();
//		H_snakecount=12;
//		H_foodcount=H_snakecount;
	}
}

bit snakewall()  //???????
{
if((snakex[0]>7)||(snakey[0]>7))return 0;
else return 1;
}
bit snakeself()  //????????
{
uchar i;
for(i=3;i<length;i++)
{
if((snakex[0]==snakex[i])&&(snakey[0]==snakey[i]))
return 0;
}
return 1;
}

bit foodwall()
{
		if(foodx>7||foody>7){
		score+=15;
		return 0;
		}else return 1;
}

void eatfood()
{
uchar i;
for(i=0;i<length;i++)
{
if((foodx==snakex[i])&&(foody==snakey[i]))
{
score+=15;
di();
exist=0;
break;
}
}
}

void gameover() //????,??
{
uchar i;
god();
if(score<=0||snakelive==0){
	score=0;
}else{
	score=1;
}
while(getkeynum()!=45){
	for(i=0;i<8;i++){
  P0=endjudge[score][i];
	P1=redblue[i];
		snakekeyscan();
		foodkeyscan();
		P0=0;
    P1=0xff;
	}
}
	

}