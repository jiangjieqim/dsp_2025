#include <reg51.h>
#include <intrins.h>



void delay(unsigned char count) {
    #pragma asm
    MOV A, R7        // C函数参数通过R7传递
    MOV R7, A
DEL_LOOP:
    MOV R6, #2
    DJNZ R6, $
    DJNZ R7, DEL_LOOP
    #pragma endasm
}			
void main() {
    while(1) {
        P0 = 0x0;
       	delay(0x01);
        P0 = 0x1;
        delay(0x01);
    }
}