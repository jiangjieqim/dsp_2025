/*
2400-115200


*/
#include <reg51.h>
sbit LED = P0^0;
#define __DELAY__ 250
static void 
delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 125; j++);
}
void main() {
    while(1) {
        LED = 0;    
        delay(__DELAY__); 
        LED = 1;   
        delay(__DELAY__);
    }
}
