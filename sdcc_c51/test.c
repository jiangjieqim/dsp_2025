#include "STC89C5xRC.h"
#include "intrins.h"
#include "delay.h"

/*
// 延时函数，延时时间约 1 秒（晶振 11.0592MHz）
void delay1s() {
    unsigned int i, j;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 120; j++) {
            // 两重循环，约 1ms 内层
        }
    }
}
*/
void main(void) {
    while(1) {
        P0 = 0x0;//light
        delay_ms(1000);
        // _nop_();
        // delay1s();
        P0 = 0x1;
        // delay1s();
        delay_ms(1000);
        // _nop_();
    }
}
