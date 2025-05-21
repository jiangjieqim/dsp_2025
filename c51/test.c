#pragma region 编译流程
/*
         -----------------------------------------
        |51汇编编译器                             |
        |An assembler is a program that translates|
        |symbolic code (assembly language)        |
        |into executable object code.             |
         -----------------------------------------     ----------------------------------------------------
           |                                          |BL51连接器                                          |
           |                                          |The BL51 Linker/Locator merges segments from        |
        +-----+                                       |object modules, locates them, and creates programs. |
        | A51 |-----------+                           |This manual describes how to use BL51 and           |
        +-----+           |               ------------|includes the following chapters.                    |
                          V              |             ----------------------------------------------------
        +-----+    ---------------    +------+     +------+    ----------------
        | C51 |-->|output obj file|-->| BL51 |---->| OH51 |-->|output HEX file |
        +-----+    ---------------    +------+     +------+    ---------------- 
           |                                           |
           |                                            --------------
         ---------------------------------------------------------    |
        |Since the Cx51 Compiler is a cross compiler, some aspects|   |
        |of the C programming language and standard libraries are |   |
        |altered or enhanced to address the peculiarities of an   |   |
        |embedded target processor. Refer to Language Extensions  |   |
        |for more detailed information.                           |   |
        |Cx51交叉编译器,对C标准进行了增删                         |   |
         ---------------------------------------------------------    |
                                                                      |
         ------------------------------------------------             |
        |OH51                                            |            |
        |The OH51 Object-HEX Converter creates Intel HEX |            |
        |files from absolute object files. This manual   |<-----------
        |describes how to use OH51 and includes the      |
        |following chapters.                             |
         ------------------------------------------------
         

*/
#pragma endregion

/**
 * to do list
 * 将日志输出到LCD1602上 用通用接口进行封装
 */
// #include <string.h>
#include <reg51.h> //此文件中定义了51的一些特殊功能寄存器
// #include <stdio.h>
#include "utils.h"
#include <intrins.h>


// #include "../libs/utils.h"


//#include <intrins.h>
//#include <stdlib.h>
//#define _SEG_EXAMPLE_
//#define _74HC595_  //移位寄存器 for c51_mini
//#define _IIC_AT24C32_ //IIC测试
// #define STAND_START //启动测试
#define TIME_TEST //计时器测试
//#define UART_SEND
// #define _PMW_ //脉冲宽度调制
// #define _SERVO_ //陀机



#ifdef _SEG_EXAMPLE_
// sfr P2   = 0xA0;
// sfr P1   = 0x90;
sbit P2_3 = P2 ^ 3;
sbit P2_4 = P2 ^ 4;
static void
f_show_SEG(int v0, int v1){
#define SEG_CA0 P2_3
#define SEG_CA1 P2_4
	unsigned int time = 50;
	unsigned display[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};//共阳0-9

	SEG_CA0 = 1;
	SEG_CA1 = 0;
	P1 = display[v0];
	u_delayMS(time);

	SEG_CA0 = 0;
	SEG_CA1 = 1;
	P1 = display[v1];
	u_delayMS(time);

}
//连接标签组引脚可以测试
static void
f_SEG_test()
{
	int n = 0;
	int count = 10;
	for (n = 0; n < count; n++)
	{
		f_show_SEG(count-n, n);
		// u_delayMS(1000);
	}
}


#endif

// sfr P0   = 0x80;

// struct stVest{
// byte a;
// };
//74HC38译码器
/*
sbit A = P1 ^ 0;
sbit B = P1 ^ 1;
sbit C = P1 ^ 2;
*/
//========================================================================
#pragma region 74hc595

#ifdef _74HC595_
#include "../libs/led1602.h"
sbit DATA_A_595 = P1 ^ 0;      //串行数据输入引脚
sbit SHIFT_CLOCK_595 = P1 ^ 1; //移位寄存器时钟信号输入引脚
sbit LATCH_CLOCK_595 = P1 ^ 2; //锁存器时钟信号输入引脚

//写一字节数据
void write_byte_74hc595(byte dat){
	byte i;
	for (i = 0; i < 8; i++)
	{
		DATA_A_595 = (dat << i) & 0x80;
		SHIFT_CLOCK_595 = 0;
		SHIFT_CLOCK_595 = 1;
	}
	LATCH_CLOCK_595 = 0;
	LATCH_CLOCK_595 = 1;
}

/**
 * 两个74HC595级联写2字节数据
 * @param dat   数据
 */ 
void write_ushort_74hc595(unsigned int dat){
	byte i;
	byte len = sizeof(unsigned int)*8;
	for (i = 0; i < len; i++){
		DATA_A_595 = (dat << i) & 0x8000;
		SHIFT_CLOCK_595 = 0;
		SHIFT_CLOCK_595 = 1;
	}
	LATCH_CLOCK_595 = 0;
	LATCH_CLOCK_595 = 1;
}


void main(void){
	char arr[] = "                ";
	unsigned int v = 0xf0fc;
	// A = 0;
	// B = 0;
	// C = 0;
	
	// char s[] = "         ";

	LCD1602_init();

	// sprintf(s,"%d",sizeof(unsigned short));
	// LCD1602_refresh(s);
	// */
	// itoa(v,buffer,2)
	// sprintf(buffer,"%X",v);//%x or %X
	// LCD1602_refresh(buffer);
	u_hex2Str(v,arr);
	
	LCD1602_refresh(arr);

	write_ushort_74hc595(v);

	while (1)
	{
		// write_byte_74hc595(80);
		// u_delayMS(1000);
		// write_byte_74hc595(240);
		// u_delayMS(1000);
	}
}

#endif
#pragma endregion
//========================================================================
#pragma region I2C
#ifdef _IIC_AT24C32_
#include "../libs/I2C.h"

#define AC24C02 0
#define AC24C32 1



/**
 *@breaf AT24C02写入一个字节
*@param WordAddress写入字节的地址
*@retval Data写入字节的数据
*/
void 
AT24CXX_WriteByte(u8 addr,unsigned int WordAddress,unsigned char wordlen,unsigned char Data){
	I2C_Start();
	I2C_SendByte(addr);
	if(wordlen > 1){
		unsigned char high = (WordAddress >> 8);//high
		unsigned char low = 0x00ff & WordAddress;//low
		I2C_SendByte(high);
		I2C_SendByte(low);
	}else{
		I2C_SendByte(WordAddress);
	}
	I2C_SendByte(Data);
	I2C_Stop();
}
/**
*@breaf AT24C02读取一个字节
*@param WordAddress读取字节的地址
*@retval Byte读取字节的内容
*/
u8 AT24CXX_ReadByte(u8 addr,unsigned int WordAddress,u8 wordlen){
	unsigned char Byte = 0;
	I2C_Start();
	I2C_SendByte(addr);
	if(wordlen > 1){
		unsigned char high = (WordAddress >> 8);//high
		unsigned char low = 0x00ff & WordAddress;//low
		I2C_SendByte(high);
		I2C_SendByte(low);
	}else{
		I2C_SendByte(WordAddress);
	}
	I2C_Start();
	I2C_SendByte(addr|0x01);
	Byte = I2C_ReceiveByte();
	I2C_Stop();
	return Byte;
}
struct AT24CXX
{
	// 地址字节个数
	u8 addrlen;

	//延迟读取的时间(毫秒)AT24C02极限温度下写数据需要1.5ms 留2ms让其写数据操作
	//AT24C32的最大时间需要20ms
	u8 ms;
};

void AT24CXX_init(struct AT24CXX* p,u8 type){
	//根据数据手册获得相关参数值
	switch (type)
	{
	case AC24C02:
		p->addrlen = 1;
		p->ms = 2;
		break;
	
	case AC24C32:
		p->addrlen = 2;
		p->ms = 20;
		break;
	}
}

/*
0xF0 :1111 0000
0XDB :1101 1011
*/
void main(){
	#define delay 100

	/*	
	24CXX地址
	Device Address  1010 A2 A1 A0
	*/
	//				1010 0 0 0 0
	#define AT24C32_ADDRESS1 0XA0
	//				1010 0 0 1 0
	#define AT24C32_ADDRESS2 0XA2

	struct AT24CXX p;
	unsigned char a = 0xff;
	
	AT24CXX_init(&p,AC24C32);
	u_GPIO_set(GPIO_ERR,0);
	
	while (1){
		// unsigned char out;
		// I2C_ERR = ~I2C_ERR;
		//0xF0 1111 0000
		//0xFA 1111 1010
		unsigned int _wordAddress = 0x0001;//写入的地址
		AT24CXX_WriteByte(AT24C32_ADDRESS1,_wordAddress,p.addrlen,a);//0xFA
		a++;

		// printf("%d\n",a);
		u_delayMS(p.ms);

		P0 = AT24CXX_ReadByte(AT24C32_ADDRESS1,_wordAddress,p.addrlen);
		u_delayMS(delay);
		//===================================================
		AT24CXX_WriteByte(AT24C32_ADDRESS2,_wordAddress,p.addrlen,0x0);
		u_delayMS(p.ms);
		P0 = AT24CXX_ReadByte(AT24C32_ADDRESS2,_wordAddress,p.addrlen);
		u_delayMS(delay);
	}
}
#endif
#pragma endregion


// void main(){
// 	u8 a = 0;
// 	while (1)
// 	{
// 		a++;
// 		// u8 b = u_GPIO_get(GPIO_ERR);
// 		// b=~b;
// 		// u_GPIO_set(GPIO_ERR,b);
// 		// P0=~P0;

// 		u_GPIO_set(GPIO_ERR,a%2);
// 		u_delayMS(10);
// 	}
// }
#ifdef STAND_START
sbit GPIO_P0_0 = P0 ^ 0;

void main(){
	while (1){
		GPIO_P0_0 = ~GPIO_P0_0;
		_nop_();
	}
}
#endif

#ifdef TIME_TEST
#pragma region TIME_TEST

sbit GPIO_P0_0 = P0 ^ 0;
u16 num = 0;
//中断的间隔时间(毫秒)
u16 _interruptCount=1;
/*12M晶振频率 秒*/
#define FREQUENCY 11059200
/*分频数*/
#define FREQUENCY_SPLIT 12
// static u8 us_time; 
static u16 _needTime;

void init_tmod(){
	// us_time	 =  (FREQUENCY/FREQUENCY_SPLIT/1000000);//
	// if(us_time <= 0) us_time = 1;//0.9216 约等于  1us需要的周期

	//_needTime = 1000/us_time;//1ms需要的周期
	
	/*
		7 6 5  4   3 2 1  0
		0 0 0  0   0 0 0  1
		    M1 M0      M1 M0

		设置定时器0 工作方式1

		16位定时器/计数器 TL0和TH0全用
	*/
	TMOD = 0x01;
	/*
		根据溢出的值 计算TH0 TL0的值
	*/
	TH0  = (65536-_needTime)/256;//0xFC
	TL0  = (65536-_needTime)%256;//0x18
	
	EA   = 1;	//开总中断
	ET0  = 1;	//定时器0中断
	TR0  = 1;	//开始计时
}
void stop_delay(){
	EA   = 0;
	ET0  = 0;
	TR0 = 0;
}
/**设置中断间隔时间(微秒)*/
void set_delay_us(u16 t){
	_needTime = t;
}

void main(){
	set_delay_us(1000);
	init_tmod();
	P0 = 0;
	while(1){
		if (num == _interruptCount){
			num=0;
			GPIO_P0_0 = ~GPIO_P0_0;
			// stop_delay();
		}
	}
}

void Timer0() interrupt 1  //定时器中断
{
	TH0 = (65536-_needTime)/256;	//重新赋值
	TL0 = (65536-_needTime)%256;
	num++;//
}
#pragma endregion
#endif
#ifdef UART_SEND
#pragma region UART
// 串口

/**
  * @brief  串口初始化，9600bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void UART_Init(){
	SCON=0x40;
	PCON &=0x7F;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte){
	SBUF=Byte;
	while(TI==0);
	TI=0;
}
unsigned char Sec;
void main(){
	Sec = 0;
	UART_Init();			//串口初始化
	while(1)
	{
		UART_SendByte(Sec);	//串口发送一个字节
		Sec++;				//Sec自增
		u_delayMS(1000);		//延时1秒
	}
}

#pragma endregion
#endif

#ifdef UART_REVC
#pragma region UART_REVC

/**
  * @brief  串口初始化，9600bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void UART_Init(){
	SCON=0x50;
	PCON |= 0x7F;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte){
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/
//https://www.cnblogs.com/veis/p/12406204.html
//https://blog.csdn.net/qq_48579018/article/details/132413926
void main(){
	UART_Init();		//串口初始化
	while(1){
	}
}

void UART_Routine() interrupt 4
{
	if(RI==1){					//如果接收标志位为1，接收到了数据
		P2=~SBUF;				//读取数据，取反后输出到LED
		UART_SendByte(SBUF);	//将受到的数据发回串口
		RI=0;					//接收标志位清0
	}
}
/*
{
    "include": "D:/github/dsp/libs",
    "c51": "D:/github/dsp/c51",
    "entry": "test.c",
    "STARTUP": "STARTUP.A51",
    "src": {
        "path": "D:/github/dsp/libs",
        "files": ["utils.c"]
    }
}
*/
#pragma endregion
#endif


#ifdef _PMW_
/**PMW for P0 */
// sfr P0   = 0x80;
// static void 
// u_pwm(int t, int count){
// 	int n;
// 	unsigned int v1 = 0x00;
// 	u_setv(&v1, Bit01);
// 	for (n = 0; n < count; n++){
// 		P0 = 0x00;
// 		u_delayMS(t);
// 		P0 = v1;
// 		u_delayMS(count - t);
// 	}
// 	// printf("WARNING! u_pwm is not support ,your params:%d %d\n",t,count);
// }
// static void
// f_pmwtest(){
//     int i = 0;
//     int count = 10;
//     for (i = 1; i < count; i++){
//         u_pwm(i, count);
//     }
// }


#pragma region StepMotor
//步进电机
u8 s[]= {0x01,0x02,0x04,0x08};
u8 s8[]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};
sbit DC_GPOIO = P2 ^ 4;

static void f_step(int* p,int count,int dir){
	int i = *p;
	if(dir > 0){
		i++;
		if(i == count){
			i = 0;
		}
	}else{
		i--;
		if(i < 0){
			i = count - 1;
		}
	}
	*p = i;
}

void f_stepMotor(){
	// Step Motor
	#define R1 90
	u16 v1 = 50;//50;
	int i = 0;
	while (1){
		u8 a = 0;
		

		for(a = 0;a < R1;a++){
			u_delayMS(v1);
			P2 = s[i];
			f_step(&i,4,1);//逆时针旋转
		}
		for(a = 0;a < R1;a++){
			u_delayMS(v1);
			P2 = s[i];
			f_step(&i,4,-1);//顺时针旋转
		}
		

		// P2 = 0x00;// STOP
		// u_delayMS(2000);
	
	
		for(a = 0;a < R1;a++){
			u_delayMS(v1);
			P2 = s8[i];
			f_step(&i,8,1);
		}
		for(a = 0;a < R1;a++){
			u_delayMS(v1);
			P2 = s8[i];
			f_step(&i,8,-1);
		}
	
	}

	while (1){
	}
	
}
#pragma endregion
#pragma region DCMotor
void f_DCMotor(){
	while (1){
		u_delayMS(990);
		DC_GPOIO = 1;
		u_delayMS(10);
		DC_GPOIO = 0;
	}
}
void main(){
	f_stepMotor();
	// f_DCMotor();
}
#pragma endregion
#endif

#pragma region _SERVO_SG90_

#ifdef _SERVO_

/*
+-------------------------+
|   中断方式实现的延迟器    |
+-------------------------+
*/

/*计算一个机器周期需要多少微秒*/
static u8 f_getUS(){
	/*12M晶振频率 秒*/
	#define FREQUENCY 11059200
	/*分频数*/
	#define FREQUENCY_SPLIT 12
	unsigned int us_time = (FREQUENCY / FREQUENCY_SPLIT / 1000000); //1 us 需要的机器周期
	if (us_time <= 0){
		us_time = 1; //0.9216 约等于  1us需要的周期
	}
	return us_time;
}
static unsigned _tempUs = 0;

/**延时器初始化*/
void u_delayInit(){
	TMOD = 0x01;
	EA   = 1;	//开总中断
	ET0  = 1;	//定时器0中断
}
#define U16TIME 65536
/**延时器设置延迟时间*/
void u_delayUsSet(unsigned int us){
	_tempUs = us;
	TMOD = 0x01;
	TH0  = (U16TIME-_tempUs)/256;
	TL0  = (U16TIME-_tempUs)%256;
	TR0  = 1;
	EA   = 1;	
	ET0  = 1;
}

void u_tmod_delay(unsigned int us){
	#define U16TIME 65536
	_tempUs = us;
	/*
		0000 0001
		设置定时器0工作方式1
		16位定时器 TL0和TH0全用
	*/
	TMOD = 0x01;
	/*
		计算TH0 TL0的值
	*/
	TH0  = (U16TIME-_tempUs)/256;//0xFC

	TL0  = (U16TIME-_tempUs)%256;//0x18
	EA   = 1;	//开总中断
	ET0  = 1;	//定时器0中断
	TR0  = 1;	//开始计时
}

// void f_Timer0() interrupt 1  //定时器中断
// {
// 	TH0 = (65536-_tempUs)/256;	//重新赋值
// 	TL0 = (65536-_tempUs)%256;
// 	// num++;//
// }

/*
20ms (50Hz)
+--------+--------+---------+---------+
|   ms   |  1.0   |   1.5   |    2.0  |
+--------+--------+---------+---------+
| drgree |  -90   |    0    |    90   |
+--------+--------+---------+---------+
*/
// 定义IO口连接舵机的引脚
sbit servoPin =  P2^7;

#define MIN_Hz 50
/**
 * @param pulseWidth 
 * **/
static void 
rotateClockwise(u8 pulseWidth) {
	u8 i;
    for(i = 0; i < MIN_Hz; i++) {
        servoPin = 1; 
		u_delay500US(pulseWidth);
		
        servoPin = 0;
		u_delay255MS(20-pulseWidth/2);
    }
}
/*
proteus servo电机参数设置
{MODDLL=ROTOR}
{PRIMITIVE=DIGITAL,HSERVO}
{ANGLE_MIN=-90}
{ANGLE_MAX=90}
{RPM=60}
{PW_MIN=1ms}
{PW_MAX=2ms}
{ITFMOD=NMOS}
*/
void main() {
	
	// while (1){
	// 	rotateClockwise(2);//1
	// 	rotateClockwise(3);//1.5
	// 	rotateClockwise(4);//2
	// }

	while(1)
	{
		// servoPin = ~servoPin; //0.500217ms - 0.496926ms = 3.291 us
		// u_delayUsSet(60000);



	}
}

#endif
#pragma endregion