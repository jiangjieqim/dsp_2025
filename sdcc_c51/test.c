#include "STC89C5xRC.h"

#define _nop_() __asm nop __endasm


// void main(void) {
//     // 直接操作标准寄存器，语法与 Keil 几乎一致
//     P1 = 0x00;    // 设置 P1 口全部为低电平
//     TMOD = 0x01;  // 配置定时器0为模式1
//     TR0 = 1;      // 启动定时器0
//     EA = 1;       // 开启总中断

//     while(1) {
//         // 你的代码
//     }
// }



void main() {
    while(1) {
        P1 = 0x0;
        _nop_();
        P1 = 0x1;
        _nop_();
    }
}