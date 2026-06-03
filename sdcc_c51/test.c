#include "STC89C5xRC.h"
#include "intrins.h"

#define DELAY_TIME   1   // 修正：DElAY_TIME -> DELAY_TIME

/* OLED引脚定义 */
/* I2C时钟线 */
__sbit __at(0x80 + 1) OLED_SCL;
/* I2C数据线 */
__sbit __at(0x80 + 0) OLED_SDA;

void Delay_us(unsigned int t) {
    while (t--);
}

// 添加函数原型声明
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char dat);
unsigned char I2C_WaitAck(void);

// I2C 起始信号
void I2C_Start(void) {
    OLED_SCL = 1;
    OLED_SDA = 1;
    Delay_us(DELAY_TIME);
    OLED_SDA = 0;
    Delay_us(DELAY_TIME);
    OLED_SCL = 0;
}

// I2C 停止信号
void I2C_Stop(void) {
    OLED_SDA = 0;
    OLED_SCL = 1;
    Delay_us(DELAY_TIME);
    OLED_SDA = 1;
    Delay_us(DELAY_TIME);
}

// I2C 发送一个字节
void I2C_SendByte(unsigned char dat) {
    unsigned char i;
    for(i = 0; i < 8; i++) {
        OLED_SDA = (dat & 0x80) >> 7;
        Delay_us(DELAY_TIME);
        OLED_SCL = 1;
        Delay_us(DELAY_TIME);
        OLED_SCL = 0;
        dat <<= 1;
    }
}

// 等待应答信号
unsigned char I2C_WaitAck(void) {
    unsigned char ack;
    OLED_SDA = 1;  // 释放SDA线
    Delay_us(DELAY_TIME);
    OLED_SCL = 1;
    Delay_us(DELAY_TIME);
    ack = OLED_SDA;  // 读取应答位（0=应答，1=非应答）
    OLED_SCL = 0;
    return ack;
}

void main(void) {
    // 初始化OLED
    I2C_Start();
    I2C_SendByte(0x78);  // OLED设备地址 + 写命令（示例）
    I2C_WaitAck();
    I2C_Stop();
    
    // while(1) {
        // P0 = 0x00;  // 点亮LED（注意：0x00或0xFF取决于电路连接）
    // }
}