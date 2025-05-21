#include <reg51.h>
#include <intrins.h>

sbit GPIO_P0_0 = P0 ^ 0;
unsigned int num = 0;

//中断的间隔次数
unsigned int _interruptCount=10;
/*12M晶振频率 秒*/
#define FREQUENCY 11059200
/*分频数*/
#define FREQUENCY_SPLIT 12

static unsigned int _needTime;

/**
 * 设置定时器寄存器状态
 */
void init_tmod(){
	// us_time	 =  (FREQUENCY/FREQUENCY_SPLIT/1000000);//
	// if(us_time <= 0) us_time = 1;//0.9216 约等于  1us需要的周期

	//_needTime = 1000/us_time;//1ms需要的周期
	
	/*
		1.设置TMOD寄存器状态位值来开启定时器功能功能
		+--------------------+
		|7 6 5  4   3 2 1  0 |
		|0 0 0  0   0 0 0  1 |
		|    M1 M0      M1 M0|
		+--------------------+

		设置定时器0 工作方式1

		0000 0001 标识-->16位定时器/计数器 TL0和TH0全用
	*/
	TMOD = 0x01;

	/*
		2.设置TH0和TL0寄存器中的值

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
void set_delay_us( unsigned int t){
	if(t > 65536){
		t = 0;
	}
	_needTime = t;
}

void main(){
	set_delay_us(65535);
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