#include "STC89C5xRC.h"
#include "intrins.h"
#include "delay_us.h"

void main(void) {
    while(1) {
        P0 = 0x0;
        DELAY_1US();
        P0 = 0x1;
        DELAY_1US();
    }
}