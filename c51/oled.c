//https://chat.deepseek.com/a/chat/s/cb1e1cb3-0d7b-49f8-865b-a9fbf6183d4e
#include <reg52.h>
#include <intrins.h>

// OLED引脚定义（根据实际接线修改）
sbit OLED_SCL  =  P0 ^ 1;  // I2C时钟线
sbit OLED_SDA  =  P0 ^ 0;  // I2C数据线

// I2C地址（0x78或0x3C，根据OLED模块决定）
#define OLED_ADDRESS  0x78

// 命令/数据选择
#define OLED_CMD     0x00
#define OLED_DATA    0x40
#define DElAY_TIME   1


// 延时函数（12MHz晶振下粗略延时）
void Delay_us(unsigned int t) {
    while (t--);
}

void Delay_ms(unsigned int t) {
    while (t--) {
        Delay_us(1000);
    }
}
//-----------------------------------------------------------------------------------------------------
// I2C起始信号
void I2C_Start() {
    OLED_SCL = 1;
    OLED_SDA = 1;
    Delay_us(DElAY_TIME);
    OLED_SDA = 0;
    Delay_us(DElAY_TIME);
    OLED_SCL = 0;
}

// I2C停止信号
void I2C_Stop() {
    OLED_SCL = 0;
    OLED_SDA = 0;
    Delay_us(DElAY_TIME);
    OLED_SCL = 1;
    Delay_us(DElAY_TIME);
    OLED_SDA = 1;
}

// 等待ACK应答
void I2C_Wait_Ack() {
    OLED_SCL = 1;
    Delay_us(DElAY_TIME);
    while (OLED_SDA);
    OLED_SCL = 0;
    Delay_us(DElAY_TIME);
}

// 发送一个字节
void I2C_Write_Byte(unsigned char dat) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        OLED_SCL = 0;
        OLED_SDA = (dat & 0x80) ? 1 : 0;
        dat <<= 1;
        Delay_us(DElAY_TIME);
        OLED_SCL = 1;
        Delay_us(DElAY_TIME);
    }
    OLED_SCL = 0;
    OLED_SDA = 1;  // 释放SDA
    Delay_us(DElAY_TIME);
}
//-----------------------------------------------------------------------------------------------------
// 向OLED写入命令或数据
void OLED_Write(unsigned char mode, unsigned char dat) {
    I2C_Start();
    I2C_Write_Byte(OLED_ADDRESS);  // 发送设备地址
    I2C_Wait_Ack();
    I2C_Write_Byte(mode);          // 发送命令/数据模式
    I2C_Wait_Ack();
    I2C_Write_Byte(dat);           // 发送具体值
    I2C_Wait_Ack();
    I2C_Stop();
}

// 设置显示位置（x: 0-127, y: 0-7）
void OLED_Set_Pos(unsigned char x, unsigned char y) {
    OLED_Write(OLED_CMD, 0xB0 + y);              // 设置页地址
    OLED_Write(OLED_CMD, ((x & 0xF0) >> 4) | 0x10); // 列地址高4位
    OLED_Write(OLED_CMD, x & 0x0F);              // 列地址低4位
}

// 清屏
void OLED_Clear() {
    unsigned char i, j;
    for (j = 0; j < 8; j++) {
        OLED_Set_Pos(0, j);
        for (i = 0; i < 128; i++) {
            OLED_Write(OLED_DATA, 0x00);  // 写入全0
        }
    }
}

// 初始化OLED
void OLED_Init() {
    Delay_ms(100);  // 等待OLED电源稳定
    OLED_Write(OLED_CMD, 0xAE);  // 关闭显示
    OLED_Write(OLED_CMD, 0xD5);  // 设置时钟分频
    OLED_Write(OLED_CMD, 0x80);
    OLED_Write(OLED_CMD, 0xA8);  // 设置多路复用比例
    OLED_Write(OLED_CMD, 0x3F);
    OLED_Write(OLED_CMD, 0xD3);  // 设置显示偏移
    OLED_Write(OLED_CMD, 0x00);
    OLED_Write(OLED_CMD, 0x40);  // 设置起始行
    OLED_Write(OLED_CMD, 0x8D);  // 电荷泵设置
    OLED_Write(OLED_CMD, 0x14);
    OLED_Write(OLED_CMD, 0x20);  // 内存地址模式
    OLED_Write(OLED_CMD, 0x00);
    OLED_Write(OLED_CMD, 0xA1);  // 段重映射
    OLED_Write(OLED_CMD, 0xC8);  // COM扫描方向
    OLED_Write(OLED_CMD, 0xDA);  // COM引脚配置
    OLED_Write(OLED_CMD, 0x12);
    OLED_Write(OLED_CMD, 0x81);  // 对比度设置
    OLED_Write(OLED_CMD, 0xCF);
    OLED_Write(OLED_CMD, 0xD9);  // 预充电周期
    OLED_Write(OLED_CMD, 0xF1);
    OLED_Write(OLED_CMD, 0xDB);  // VCOMH电平
    OLED_Write(OLED_CMD, 0x40);
    OLED_Write(OLED_CMD, 0xA4);  // 全局显示开启
    OLED_Write(OLED_CMD, 0xA6);  // 正常显示模式
    OLED_Write(OLED_CMD, 0xAF);  // 开启显示
    OLED_Clear();                // 清屏
}

#define OFFSET 97
// ASCII 6x8 字库（每个字符6字节，对应6列x8行像素）
const unsigned char ASCII_6x8[][6] = {
    {0x20, 0x54, 0x54, 0x54, 0x78, 0x00}, // a (97)
    {0x7F, 0x48, 0x44, 0x44, 0x38, 0x00}, // b (98)
    {0x38, 0x44, 0x44, 0x44, 0x20, 0x00}, // c (99)
    {0x38, 0x44, 0x44, 0x48, 0x7F, 0x00}, // d (100)
    {0x38, 0x54, 0x54, 0x54, 0x18, 0x00}, // e (101)
    {0x08, 0x7E, 0x09, 0x01, 0x02, 0x00}, // f (102)
    {0x08, 0x14, 0x54, 0x54, 0x3C, 0x00}, // g (103)
    {0x7F, 0x08, 0x04, 0x04, 0x78, 0x00}, // h (104)
    {0x00, 0x44, 0x7D, 0x40, 0x00, 0x00}, // i (105)
    {0x20, 0x40, 0x44, 0x3D, 0x00, 0x00}, // j (106)
    {0x7F, 0x10, 0x28, 0x44, 0x00, 0x00}, // k (107)
    {0x00, 0x41, 0x7F, 0x40, 0x00, 0x00}, // l (108)
    {0x7C, 0x04, 0x18, 0x04, 0x78, 0x00}, // m (109)
    {0x7C, 0x08, 0x04, 0x04, 0x78, 0x00}, // n (110)
    {0x38, 0x44, 0x44, 0x44, 0x38, 0x00}, // o (111)
    {0x7C, 0x14, 0x14, 0x14, 0x08, 0x00}, // p (112)
    {0x08, 0x14, 0x14, 0x18, 0x7C, 0x00}, // q (113)
    {0x7C, 0x08, 0x04, 0x04, 0x08, 0x00}, // r (114)
    // {0x48, 0x54, 0x54, 0x54, 0x20, 0x00}, // s (115)
    // {0x04, 0x3F, 0x44, 0x40, 0x20, 0x00}, // t (116)
    // {0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00}, // u (117)
    // {0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00}, // v (118)
    // {0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00}, // w (119)
    // {0x44, 0x28, 0x10, 0x28, 0x44, 0x00}, // x (120)
    // {0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00}, // y (121)
    // {0x44, 0x64, 0x54, 0x4C, 0x44, 0x00}, // z (122)
};

// 显示一个字符（6x8像素）
void OLED_ShowChar(unsigned char x, unsigned char y, char chr) {
    unsigned char i;
    OLED_Set_Pos(x, y);
    for (i = 0; i < 6; i++) {
        OLED_Write(OLED_DATA, ASCII_6x8[chr - OFFSET][i]);
    }
}

// 显示字符串
void OLED_ShowString(unsigned char x, unsigned char y, char *str) {
    while (*str) {
        OLED_ShowChar(x, y, *str++);
        x += 6;
        if (x > 122) {  // 换行处理
            x = 0;
            y++;
        }
    }
}

/*
*/
void main() {
    OLED_Init();                  // 初始化OLED
    OLED_ShowString(0, 0, "abcde");
    OLED_ShowString(0, 1, "fbcdk");
    OLED_ShowString(0, 3, "abcde");
    
    while (1) {
        // 其他逻辑...
    }
}
