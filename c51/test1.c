#include <reg51.h>
sbit LED = P1^0;
static void 
delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 125; j++);
}
void main() {
    while(1) {
        LED = 0;    
        delay(500); 
        LED = 1;   
        delay(500);
    }
}
