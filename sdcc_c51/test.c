#include "STC89C5xRC.h"

#define _nop_() __asm nop __endasm

void main(void) {
    while(1) {
        P0 = 0x0;
        _nop_();
        P0 = 0x1;
        _nop_();
    }
}