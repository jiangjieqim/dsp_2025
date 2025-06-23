#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <reg51.h>
#include <absacc.h>
// #include "cstdlib.h"
/*************** 用户定义参数 *****************************/
#define uchar unsigned char
#define uint unsigned int

/**********************************************************/

sbit	SCLK    =P0^0;
sbit	SDA     =P0^1;
sbit	RES     =P0^2;
sbit	A0      =P0^3;
sbit	CS      =P0^4;

/****************** 编译器自动生成，用户请勿修改 ************************************/

//#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate0)		//Calculate the timer1 reload value	at 12T mode
#define T1_TimerReload	(256 - MAIN_Fosc / 16 / Baudrate0)		//Calculate the timer1 reload value ar 1T mode

/**********************************************************/
//==================================================
#define Black 		0x0000
#define White 		0xffff
#define Red 		0xf800
#define Green 		0x07e0
#define Blue 		0x001f
#define YELLOW      0xFFE0
#define MAGENTA     0xF81F

int FontColor=0;

int MaxCol=128;	   //屏宽度
int MaxRow=128;	   //屏高度

int px=0;		   //x偏移
int py=32;		   //y偏移

int PicW=128;	   //图片宽
int PicH=128;	   //图片高
//==================================================
void  Delay(uint t);
uchar code Zk_ASCII8X16[];

//==================================================

//==================================================
void Delay(uint time)
{
	uint i,j;
	for(i=0;i<time;i++)
		for(j=0;j<200;j++);
}
void write(uchar a0,uchar DA)
{   
	uchar ii;
	CS=0;
	A0=a0;
	for(ii=0;ii<8;ii++)
	{
		SCLK=0;
		if((DA&0x80)==0x80)
			SDA=1;
		else
			SDA=0;
		SCLK=1;
		DA=DA<<1;
	}
	CS=1;
}

void wr_cmd(uchar x)
{
    write(0,x);
}
void wr_data(uchar x)
{
    write(1,x);
}

void LCD_CtrlWrite_IC(uchar com)
{
	wr_cmd(com);
}
void  LCD_DataWrite_IC(uchar dat)  
{
	wr_data(dat);
}

void LCD_DataWrite(uchar LCD_DataH,uchar LCD_DataL)
{
	LCD_DataWrite_IC(LCD_DataH);
	LCD_DataWrite_IC(LCD_DataL);
}

void SPI_write_com(uchar c)
{
	LCD_CtrlWrite_IC(c);   
}

void  SPI_write_data(uchar d)
{
	LCD_DataWrite_IC(d);
}
//===========================================
void Reset()
{
    RES=1;
    Delay(20);
    RES=0;
    Delay(80);
    RES=1;
    Delay(100);
}
void lcd_initial()
{
	Reset();
// **************************************************
    
SPI_write_com(0x11); //Sleep out
Delay(120); //Delay 120ms
//-------------------------ST7735S Frame Rate-----------------------------------------//
SPI_write_com(0xB1);
SPI_write_data(0x05);
SPI_write_data(0x3A);
SPI_write_data(0x3A);
SPI_write_com(0xB2);
SPI_write_data(0x05);
SPI_write_data(0x3A);
SPI_write_data(0x3A);
SPI_write_com(0xB3);
SPI_write_data(0x05);
SPI_write_data(0x3A);
SPI_write_data(0x3A);
SPI_write_data(0x05);
SPI_write_data(0x3A);
SPI_write_data(0x3A);
//------------------------------------End ST7735S Frame Rate-----------------------------------------//
SPI_write_com(0xB4); //Dot inversion
SPI_write_data(0x03);
//------------------------------------ST7735S Power Sequence-----------------------------------------//
SPI_write_com(0xC0);
SPI_write_data(0x62);
SPI_write_data(0x02);
SPI_write_data(0x04);
SPI_write_com(0xC1);
SPI_write_data(0xC0);
SPI_write_com(0xC2);
SPI_write_data(0x0D);
SPI_write_data(0x00);
SPI_write_com(0xC3);
SPI_write_data(0x8D);
SPI_write_data(0x6A);
SPI_write_com(0xC4);
SPI_write_data(0x8D);
SPI_write_data(0xEE);
//---------------------End ST7735S Power Sequence-------------------------------------//
SPI_write_com(0xC5); //VCOM
SPI_write_data(0x12);
//----------------------ST7735S Gamma Sequence-----------------------------------------//
SPI_write_com(0xE0);
SPI_write_data(0x03);
SPI_write_data(0x1B);
SPI_write_data(0x12);
SPI_write_data(0x11);
SPI_write_data(0x3F);
SPI_write_data(0x3A);
SPI_write_data(0x32);
SPI_write_data(0x34);
SPI_write_data(0x2F);
SPI_write_data(0x2B);
SPI_write_data(0x30);
SPI_write_data(0x3A);
SPI_write_data(0x00);
SPI_write_data(0x01);
SPI_write_data(0x02);
SPI_write_data(0x05);
SPI_write_com(0xE1);
SPI_write_data(0x03);
SPI_write_data(0x1B);
SPI_write_data(0x12);
SPI_write_data(0x11);
SPI_write_data(0x32);
SPI_write_data(0x2F);
SPI_write_data(0x2A);
SPI_write_data(0x2F);
SPI_write_data(0x2E);
SPI_write_data(0x2C);
SPI_write_data(0x35);
SPI_write_data(0x3F);
SPI_write_data(0x00);
SPI_write_data(0x00);
SPI_write_data(0x01);
SPI_write_data(0x05);
//---------------------End ST7735S Gamma Sequence-----------------------------------------//
SPI_write_com(0xFC); //Enable Gate power save mode
SPI_write_data(0x8C);
SPI_write_com(0x3A); //65k mode
SPI_write_data(0x05);
SPI_write_com(0x36); //65k mode
SPI_write_data(0xC8);
SPI_write_com(0x29); //Display on   

}

//==================================================

void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) //
{
	 SPI_write_com(0x2a);
	 SPI_write_data((Xstart)>>8);
	 SPI_write_data((Xstart));
	 SPI_write_data((Xend)>>8);
	 SPI_write_data(Xend);
	
	 SPI_write_com(0x2b);
	 SPI_write_data((Ystart)>>8);
	 SPI_write_data((Ystart));
	 SPI_write_data((Yend)>>8);
	 SPI_write_data(Yend);

	 SPI_write_com(0x2c); 	
}

void  SetXY(uchar x,uchar y)
{
   BlockWrite(x+px,127,y+py,159);	
}
void Disp_Kuang()
{
	uchar i,j;
	SetXY(0,0); 
	for (i=0;i<MaxCol;i++) LCD_DataWrite(White>>8,White&0xff);
	for (i=0;i<MaxRow-2;i++)
	{
		LCD_DataWrite(White>>8,White&0xff);
		for (j=0;j<MaxCol-2;j++)	LCD_DataWrite(Black>>8,Black&0xff);
		LCD_DataWrite(White>>8,White&0xff);
	}
	for (i=0;i<MaxCol;i++) LCD_DataWrite(White>>8,White&0xff);
}

void Dsp_single_colour(DH,DL)
{
	uchar i,j;
	SetXY(0,0); 
	for (i=0;i<MaxRow;i++)
    {
		for (j=0;j<MaxCol;j++)
        {
            LCD_DataWrite(DH,DL);
        }
    }
}
void DispSingleColor(Color)
{
	Dsp_single_colour(Color>>8,Color&0xff);
}

void Output_Pixel(uint x,uint y)
{
    LCD_CtrlWrite_IC(0x2A);  //Column Address Set        ****
	LCD_DataWrite_IC(x>>8);//xsh 
	LCD_DataWrite_IC(x);//xsl 	
	LCD_CtrlWrite_IC(0x2B);//Row Address Set             ****
	LCD_DataWrite_IC(y>>8);//ysl 
	LCD_DataWrite_IC(y);//ysl 
	LCD_CtrlWrite_IC(0x2c);
	LCD_DataWrite(FontColor>>8,FontColor&0xff);
}

void Display_ASCII8X16(uint x0,uint y0,uchar *s)
{
	int i,j,k,x,y,xx;
	
	unsigned char qm;
	
	long int ulOffset;
	
	char  ywbuf[32],temp[2];

	for(i = 0; i<strlen((char*)s);i++)
	{
		if(((unsigned char)(*(s+i))) >= 161)
		{
			temp[0] = *(s+i);
			temp[1] = '\0';
			return;
		}
		
		else
		{
			qm = *(s+i);

			ulOffset = (long int)(qm) * 16;
			
            for (j = 0; j < 16; j ++)
            {
				ywbuf[j]=Zk_ASCII8X16[ulOffset+j];
           	}
             
            for(y = 0;y < 16;y++)
            {
	          	for(x=0;x<8;x++) 
	           	{
                	k=x % 8;
                	
				  	if(ywbuf[y]&(0x80 >> k))
				   	{
				  		xx=x0+x+i*8;
				    	Output_Pixel(xx,y+y0);
				  	}
			   	}
           }

		}
	}     	
}

void DisplayBlock(uchar x,uchar y,uchar w,uchar h,int blcolor)
{  uchar i,j;
   uchar sx=x,sy=y;
   for (i=0;i<h;i++)
	{
	 SetXY(sx,sy);
     for (j=0;j<w;j++)  LCD_DataWrite(blcolor>>8,blcolor&0xff);
	 sy++;
   }
}

void DisplayPic(uchar x,int y,uint w,int h,uchar *Pic)
{
   uint j;
   int i;
   for (i=0;i<h;i++)
	{
	 SetXY(x,y);
     for (j=0;j<w;j++)  LCD_DataWrite(Pic[i*w+(j++)],Pic[i*w+j]);
	 y++;
   }
}


//==================================================
main()
{
	int DelayNum=500;

	Delay(100);
	lcd_initial();
	
	while(1)
	{
		DispSingleColor(Black);
		Disp_Kuang();				Delay(DelayNum*2);
		DispSingleColor(White);		Delay(DelayNum*2);
		DispSingleColor(Black);		Delay(DelayNum*2);
		DispSingleColor(Red);		Delay(DelayNum*2);
		DispSingleColor(Green);		Delay(DelayNum*2);
		DispSingleColor(Blue);		Delay(DelayNum*2);
		DispSingleColor(YELLOW);		Delay(DelayNum*2);
		
		DisplayBlock(0 ,0 ,MaxCol/2,MaxRow/2,Red);
		DisplayBlock(MaxCol/2,0 ,MaxCol/2,MaxRow/2,Green);
		DisplayBlock(0 ,MaxRow/2,MaxCol/2,MaxRow/2,Blue);
		DisplayBlock(MaxCol/2,MaxRow/2,MaxCol/2,MaxRow/2,MAGENTA);
		Delay(DelayNum*2);

	}
}

