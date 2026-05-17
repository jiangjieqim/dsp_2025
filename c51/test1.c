#include <reg51.h>
#include <intrins.h>

#include "delay_us.h"
// #include "utils.h"

//10 *20 * 2us = 0.4ms
// void delay() {
//     #pragma asm
//     MOV R7, #10
// DEL_LOOP:
//     MOV R6, #20
//     DJNZ R6, $
//     DJNZ R7, DEL_LOOP
//     #pragma endasm
// }

//80c51 晶振频率 11.0592MHz
// void delay_us(unsigned char count) {
//     #pragma asm
//     MOV A, R7        // C函数参数通过R7传递
//     MOV R7, A
// DEL_LOOP:
//     MOV R6, #2
//     DJNZ R6, $
//     DJNZ R7, DEL_LOOP
//     #pragma endasm
// }



void main() {
    while(1) {
        P0 = 0x0;
        delay_us_Macros(10);
        P0 = 0x1;
        delay_us_Macros(1);
    }
}