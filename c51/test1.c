/*
2400-115200
*/
#include <reg51.h>
#include <intrins.h>

sbit LED = P0 ^ 0;

#define __DELAY__ 1

static void
delay(unsigned int time)
{
    /*
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 125; j++);

    */
   /*
    Simulation is not running in real time due to excessive CPU load.
    0.012789069s



以最常见的标准8051架构（12T，即12个时钟一个机器周期）为例，假设你的单片机使用12MHz晶振：
计算单个机器周期时间：12 / 12,000,000Hz = 0.000001秒 = 1微秒 (µs)
得到 _nop_() 执行时间：因为 _nop_() = 1个机器周期，所以它的执行时间就是 1微秒 (µs)。
   */
    _nop_();
}

// 使用参数time控制延时长度
static void delayMs(unsigned int time)
{
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 120; j++)  // 内层循环大约1ms（@12MHz晶振）
            _nop_();
}


void main()
{
    while (1)
    {
        LED = 0;
        _nop_();
        // delay(__DELAY__);
        LED = 1;
        _nop_();
        // delay(__DELAY__);
    }
}
