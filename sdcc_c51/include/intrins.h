#ifndef __INTRINS_H__
#define __INTRINS_H__
/*
标准 8051：一个 NOP = 1 个机器周期
11.0592 MHz	≈ 1.085 us	12 / 11,059,200 ≈ 0.000001085秒
*/
#define _nop_() __asm nop __endasm

#endif