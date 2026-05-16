/*
2400-115200
*/
#include <reg51.h>
#include <intrins.h>
#include "delay_us.h"

sbit LED = P0 ^ 0;

void main()
{
    while (1)
    {
        LED = 0;
        delay_us(5);
        LED = 1;
        delay_us(5);
    }
}
