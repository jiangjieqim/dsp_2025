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
