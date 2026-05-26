// SDCC版本 - 针对STC89C5xRC
#include <STC89C5xRC.h>

#define FOSC 11059200L
// 机器周期微秒数 * 10 = 10.85，避免浮点数
#define MACHINE_CYCLE_US_X10 1085  // 1.085us * 1000

// SDCC中sbit的定义方式略有不同
__sbit __at (0x80) GPIO_P0_0;  // P0.0地址为0x80

unsigned int target_cnt = 1000;     // 需要达到的中断次数
#define INTERRUPT_TIME    1000      // 每次中断的时长(us)
unsigned int interrupt_cnt = 0;     // 当前中断发生次数

/*
目标时间	timer_config_us参数	 target_cnt值
0.5秒	    10000 (10ms)	    50
1秒	        10000 (10ms)	    100
2秒	        10000 (10ms)	    200
1秒	        1000 (1ms)	        1000
1秒	        50000 (50ms)	    20

可选：使用50ms中断减少CPU负载

*/


// 设置定时器（单位：微秒）
// 使用整数运算提高精度
void timer_config_us(unsigned int us) {
    unsigned long cycles;
    unsigned int value;
    
    cycles = (unsigned long)us * 9216UL / 10000UL;
    
    // 边界检查（仅调试版本）
    #ifdef DEBUG
    /*
    即使你将 cycles 声明为 unsigned long，但 us 是 unsigned int（最大65535），计算一下最大值：
    65535 × 9216 ÷ 10000 ≈ 60400
    这个值确实小于 65536，所以 if(cycles > 65535) 这个判断永远不会成立，
    */
    if(cycles > 65535) {
        cycles = 65535;  // 实际永远不会执行
    }
    #endif
    
    if(cycles < 1) cycles = 1;
    
    value = 65536 - cycles;
    TH0 = (value >> 8) & 0xFF;
    TL0 = value & 0xFF;
}

void timer0_init(void) {
    TMOD = (TMOD & 0xF0) | 0x01;    // 模式1，16位定时器
    timer_config_us(INTERRUPT_TIME);// 1ms中断
    
    ET0 = 1;  // 允许定时器0中断
    EA = 1;   // 总中断使能
    TR0 = 1;  // 启动定时器0
}

// SDCC中断函数语法
void timer0_isr(void) __interrupt (1) __using (1) {
    timer_config_us(INTERRUPT_TIME);  // 重新加载
    interrupt_cnt++;
}

void main(void) {
    timer0_init();
    P0 = 0x00;
    
    while(1) {
        if(interrupt_cnt >= target_cnt) {
            interrupt_cnt = 0;
            GPIO_P0_0 = !GPIO_P0_0;
        }
    }
}