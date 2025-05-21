#ifndef __LED1612H__
#define __LED1612H__
#include <reg51.h>

sbit LED1602_RS = P2 ^ 2;
sbit LED1602_RW = P2 ^ 1;
sbit LED1602_E = P2 ^ 0;

//数据端口
#define LED1602_DS P0

/**
 * 初始化
*/
void LCD1602_init();

/**刷新整个字符缓冲区*/
void LCD1602_refresh(const char* s);

/**清屏*/
void LCD1602_clear();
#endif