#include <reg51.h>
#include <intrins.h>				
void main() {
    while(1) {
        P0 = 0x0;
       	_nop_();
        P0 = 0x1;
        _nop_();
    }
}