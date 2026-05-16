#ifndef __DELAY_H__
#define __DELAY_H__

/*
1-10us短延时：使用循环计数版本即可

10-100us延时：使用嵌套循环版本

100us以上：建议改用定时器或delay_ms

关键时序：必须用示波器实际校准

中断影响：延时期间会响应中断，时间会变长
*/

#include <reg51.h>

// // 配置系统晶振频率（单位：MHz）
// // 根据你的实际晶振修改，例如 11.0592MHz 或 12MHz
#define FOSC_MHZ   12

// // 是否使用定时器方式（1：定时器精确延时；0：简单循环延时）
// #define USE_TIMER_DELAY  0

void delay_s(unsigned int s);

void delay_ms(unsigned int ms);

#endif