#include <reg52.h>
sbit duanxuan = P2 ^ 5;        //数码管驱动芯片74Hc573段选
sbit wiexuan = P2 ^ 6;         //数码管驱动芯片74Hc573位选
sbit DATA_A_595 = P1 ^ 0;      //74HC595 串行数据输入引脚
sbit SHIFT_CLOCK_595 = P1 ^ 4; //74HC595 移位寄存器时钟信号输入引脚
sbit LATCH_CLOCK_595 = P2 ^ 3; //74HC595 锁存器时钟信号输入引脚
typedef signed char int8;      //8位有符号字符型
typedef signed int int16;      //16位有符号整型
typedef signed long int32;     //32位有符号长整型
typedef unsigned char uint8;   //8位无符号字符型
typedef unsigned int uint16;   //16位无符号整型
typedef unsigned long uint32;  //32位无符号长整型
void main(void)
{
    while (1)
    {
        duanxuan = 0;
        wiexuan = 0;
        P0 = 0xc0;    //数码管段码显示0
        duanxuan = 1; //段选
        duanxuan = 0;

        duanxuan = 0;
        wiexuan = 0;
        P0 = 0x01; //数码管段码显示0
        wiexuan = 1;
        wiexuan = 0;
    }
}
void write_byte_74hc595(uint8 dat) //给595芯片写一字节数据函数
{
    uint8 i;
    for (i = 0; i < 8; i++)
    {
        DATA_A_595 = (dat << i) & 0x80; //74HC595 串行数据输入引脚
        SHIFT_CLOCK_595 = 0;            //74HC595 移位寄存器时钟信号输入引脚
        SHIFT_CLOCK_595 = 1;            //74HC595 移位寄存器时钟信号输入引脚
    }
    LATCH_CLOCK_595 = 0; //74HC595 锁存器时钟信号输入引脚
    LATCH_CLOCK_595 = 1; //74HC595 锁存器时钟信号输入引脚
}

void delay(uint16 x_ms) //延迟  x_ms*1  毫秒
{
    uint16 i, j;
    for (i = x_ms; i > 0; i--)
        for (j = 114; j > 0; j--)
            ;
}