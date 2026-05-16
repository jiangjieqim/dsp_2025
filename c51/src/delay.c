#include "delay.h"

/* --------------------------------------------
   定时器0初始化（16位模式）
-------------------------------------------- */
void Timer0_Init(void) {
    TMOD &= 0xF0;      // 清除 T0 模式位
    TMOD |= 0x01;      // 设置 T0 为 16 位定时器模式
}

/* --------------------------------------------
   微秒延时（使用定时器）
   注意：最小延时受中断响应时间影响
-------------------------------------------- */
/*
void timer_delay_us(unsigned int us) {
    unsigned int i;
    unsigned int count;
    
    // 计算每微秒需要的定时器计数值（12T模式）
    // 12MHz: 1us = 1个机器周期 = 1次计数
    count = FOSC_MHZ / 12;  // 12MHz时 count=1
    
    for(i = 0; i < us; i++) {
        TH0 = (65536 - count) >> 8;
        TL0 = (65536 - count) & 0xFF;
        TR0 = 1;
        while(TF0 == 0);   // 等待溢出
        TR0 = 0;
        TF0 = 0;
    }
}
*/
/* --------------------------------------------
   毫秒延时（使用定时器）
-------------------------------------------- */
void delay_ms(unsigned int ms) {
    unsigned int i;
    unsigned int count;
    
    // 1ms 需要的计数值（12MHz: 1000次计数）
    count = 1000 * (FOSC_MHZ / 12);
    
    for(i = 0; i < ms; i++) {
        TH0 = (65536 - count) >> 8;
        TL0 = (65536 - count) & 0xFF;
        TR0 = 1;
        while(TF0 == 0);
        TR0 = 0;
        TF0 = 0;
    }
}

void delay_s(unsigned int s) {
    unsigned int i;
    
    for(i = 0; i < s; i++) {
        delay_ms(1000);
    }
}