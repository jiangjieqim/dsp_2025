#include "STC89C5xRC.h"
#define _nop_() __asm nop __endasm
void main() {
    while(1) {
        P1 = 0x0;
        _nop_();
        P1 = 0x1;
        _nop_();
    }
}