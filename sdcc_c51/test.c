#include "STC89C5xRC.h"
#include "intrins.h"
#include "delay.h"

void main(void) {
    while(1) {
        P0 = 0x0;
        delay_ms(1000);
        P0 = 0x1;
        delay_ms(1000);
    }
}
