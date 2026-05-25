#include <reg51.h>
#include <intrins.h>

#define FOSC 11059200L
// 机器周期微秒数 * 10 = 10.85，避免浮点数
#define MACHINE_CYCLE_US_X10 1085  // 1.085us * 1000

sbit GPIO_P0_0 = P0 ^ 0;

unsigned int interrupt_cnt = 0;// 当前中断发生次数
unsigned int target_cnt = 1;   // 需要达到的中断次数

// 设置定时器（单位：微秒）
// 使用整数运算提高精度
void timer_config_us(unsigned int us) {
    unsigned long cycles;
    unsigned int value;
    
    // us * (11.0592MHz/12) / 1000000 = us * 0.9216
    // 用整数运算：us * 9216 / 10000
    cycles = (unsigned long)us * 9216L / 10000L;
    
    if(cycles > 65536) cycles = 65536;
    if(cycles < 1) cycles = 1;
    
    value = 65536 - cycles;
    TH0 = value >> 8;
    TL0 = value & 0xFF;
}

void timer0_init(void) {
    TMOD = (TMOD & 0xF0) | 0x01;
    timer_config_us(1000);  // 1ms中断
    
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void timer0_isr(void) interrupt 1 {
    timer_config_us(1000);  // 重新加载
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