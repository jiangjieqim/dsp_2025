#ifndef __UTILS_H_
#define __UTILS_H_
/**进制转换 https://decimal.buyaocha.com/*/

/* 
    无符号的BYTE
    0~255 (FF)占用一个字节
*/
#define byte unsigned char
#define u8 unsigned char  //0~255
#define u16 unsigned int

/**二进制位定义*/
#define Bit01		0x01	//1 
#define Bit02	  	0x02	//2 
#define Bit03		0x04	//3 
#define Bit04		0x08	//4 
#define Bit05		0x10	//5 
#define Bit06		0x20	//6 
#define Bit07	    64		//7 
#define Bit08		128		//8

/**设置二进制位的值*/
void u_setv(u16* v,u16 flag);

/**毫秒延时函数 i 代表毫秒*/
void u_delayMS(unsigned int i);

/**t < 255 微秒延时函数 1(微秒)us = 1000(纳秒)ns*/
void u_delayUS(u8 t);

// void u_delayUS2(unsigned int t);

/**字符串的长度*/
int u_strlen(u8* s);

/**2个字节输出一个16进制的字符65536转化为FFFF*/
void u_hex2Str(u16 v, u8 *out);
/*
nop 函数消耗的时间
那么在我们的单片机中，一个 nop 的时间是多少呢？、

上面说到，一个 nop 表示一个机器周期，那么一个机器周期是多少？

机器周期当然与主频有关，在单片机中指的就是晶振的频率。

首先基本的东西还是要知道的 一个机器周期包含12个晶振周期。 所以我们可以通过下面的计算得知 nop 函数消耗的时间：

假设单片机 12M 晶振，晶振周期1/12微秒，一个机器周期包含12个晶振周期，所以12M晶振时机器周期 = 12x(1/12)us = 1us 。
.
所以12M 晶振中一个 nop 表示延时1us；
6M 晶振中延时2us,24M 晶振中延时 0.5 us

*/
void u_nop();

#define GPIO_SDA 0
#define GPIO_SCL 1
#define GPIO_ERR 2

/**
 * 设置一个引脚的值
 */ 
void u_GPIO_set(u8 type,bit v);
/**
 * 获取一个引脚的值
*/
u8 u_GPIO_get(u8 type);

/**
 * 中断微秒延迟
 * 注意:使用的时候不要超过 65536 us
*/
// void u_tmod_delay(unsigned int us);

/*
    1~255毫秒延迟
*/
void u_delay255MS(u8 n);

/*延迟500微秒*/
void u_delay500US(u8 n);
/*延迟n秒*/
void u_delaySec(u8 n);
#endif