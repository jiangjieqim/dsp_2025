#include "STC89C5xRC.h"
#include "intrins.h"
#include "delay.h"

void main(void) {
    while(1) {
        P0 = 0x0;
        // delay_ms(1);
        _nop_();
        P0 = 0x1;
        // delay_ms(1);
        _nop_();
    }
}
