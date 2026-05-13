#include <reg51.h>
#include <intrins.h>

// 定义ILI9341常用命令
#define ILI9341_SOFTRESET     0x01
#define ILI9341_SLEEPIN       0x10
#define ILI9341_SLEEPOUT      0x11
#define ILI9341_NORMALDISP    0x13
#define ILI9341_INVERTOFF     0x20
#define ILI9341_INVERTON      0x21
#define ILI9341_GAMMASET      0x26
#define ILI9341_DISPLAYOFF    0x28
#define ILI9341_DISPLAYON     0x29
#define ILI9341_COLADDRSET    0x2A
#define ILI9341_PAGEADDRSET   0x2B
#define ILI9341_MEMORYWRITE   0x2C
#define ILI9341_MEMORYREAD    0x2E
#define ILI9341_PIXELFORMAT   0x3A
#define ILI9341_FRAMECONTROL  0xB1
#define ILI9341_DISPLAYFUNC   0xB6
#define ILI9341_ENTRYMODE     0xB7
#define ILI9341_POWERCONTROL1 0xC0
#define ILI9341_POWERCONTROL2 0xC1
#define ILI9341_VCOMCONTROL1  0xC5
#define ILI9341_VCOMCONTROL2  0xC7
#define ILI9341_MADCTL        0x36
#define ILI9341_MADCTL_MY    0x80
#define ILI9341_MADCTL_MX    0x40
#define ILI9341_MADCTL_MV    0x20
#define ILI9341_MADCTL_ML    0x10
#define ILI9341_MADCTL_RGB   0x00
#define ILI9341_MADCTL_BGR   0x08

// 定义SPI引脚连接
sbit LCD_SCK  = P0^0;   // SPI时钟
sbit LCD_MOSI = P0^1;   // SPI数据输出
sbit LCD_RST  = P0^2;   // 复位
sbit LCD_DC   = P0^3;   // 数据/命令选择
sbit LCD_CS   = P0^4;   // 片选

// 8x16 ASCII字体 (只包含部分字符)
const unsigned char Font8x16[] = {
    // 'H'
    0x00, 0x00, 0x41, 0x41, 0x41, 0x41, 0x7F, 0x41, 
    0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00,
    // 'e'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 
    0x7E, 0x40, 0x40, 0x3C, 0x00, 0x00, 0x00, 0x00,
    // 'l'
    0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
    // 'o'
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00,
};
// 颜色定义 (RGB565)
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// 延时函数
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<114; j++);
}

// SPI写一个字节
void SPI_WriteByte(unsigned char dat) {
    unsigned char i;
    LCD_CS = 0;  // 使能片选
    for(i=0; i<8; i++) {
        LCD_SCK = 0;
        if(dat & 0x80) LCD_MOSI = 1;
        else LCD_MOSI = 0;
        LCD_SCK = 1;
        dat <<= 1;
    }
    LCD_CS = 1;  // 禁用片选
}

// 写命令
void LCD_WriteCmd(unsigned char cmd) {
    LCD_DC = 0;  // 命令模式
    SPI_WriteByte(cmd);
}

// 写数据
void LCD_WriteData(unsigned char dat) {
    LCD_DC = 1;  // 数据模式
    SPI_WriteByte(dat);
}

// 写16位数据
void LCD_WriteData16(unsigned int dat) {
    LCD_WriteData(dat >> 8);
    LCD_WriteData(dat);
}

// 设置显示窗口
void LCD_SetWindow(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd) {
    LCD_WriteCmd(ILI9341_COLADDRSET);
    LCD_WriteData16(xStart);
    LCD_WriteData16(xEnd);
    
    LCD_WriteCmd(ILI9341_PAGEADDRSET);
    LCD_WriteData16(yStart);
    LCD_WriteData16(yEnd);
    
    LCD_WriteCmd(ILI9341_MEMORYWRITE);
}

// 填充颜色
void LCD_FillColor(unsigned int color, unsigned long size) {
    unsigned long i;
    LCD_DC = 1;
    for(i=0; i<size; i++) {
        SPI_WriteByte(color >> 8);
        SPI_WriteByte(color);
    }
}

// 初始化ILI9341
void LCD_Init(void) {
    // 硬件复位
    LCD_RST = 1;
    delay_ms(5);
    LCD_RST = 0;
    delay_ms(20);
    LCD_RST = 1;
    delay_ms(150);
    
    // 软件复位
    LCD_WriteCmd(ILI9341_SOFTRESET);
    delay_ms(150);
    
    // 退出睡眠模式
    LCD_WriteCmd(ILI9341_SLEEPOUT);
    delay_ms(150);
    
    // 设置像素格式为16位
    LCD_WriteCmd(ILI9341_PIXELFORMAT);
    LCD_WriteData(0x55);  // 16位像素
    
    // 设置显示方向
    LCD_WriteCmd(ILI9341_MADCTL);
    LCD_WriteData(0x48);  // MX=1, MY=0, MV=1, ML=0, BGR=0
    
    // 正常显示模式
    LCD_WriteCmd(ILI9341_NORMALDISP);
    LCD_WriteCmd(ILI9341_DISPLAYON);
    delay_ms(100);
}

// 清屏
void LCD_Clear(unsigned int color) {
    LCD_SetWindow(0, 0, 239, 319);
    LCD_FillColor(color, 240*320);
}

// 画一个像素点
void LCD_DrawPixel(unsigned int x, unsigned int y, unsigned int color) {
    LCD_SetWindow(x, y, x, y);
    LCD_WriteData16(color);
}

// 显示一个字符 (8x16字体)
void LCD_ShowChar8x16(unsigned int x, unsigned int y, char c, unsigned int color, unsigned int bgcolor) {
    unsigned char i, j;
    unsigned char line;
    
    for(i=0; i<16; i++) {
        line = Font8x16[c*16 + i];
        for(j=0; j<8; j++) {
            if(line & 0x80) {
                LCD_DrawPixel(x+j, y+i, color);
            } else {
                LCD_DrawPixel(x+j, y+i, bgcolor);
            }
            line <<= 1;
        }
    }
}

// 显示字符串
void LCD_ShowString(unsigned int x, unsigned int y, char *str, unsigned int color, unsigned int bgcolor) {
    while(*str) {
        LCD_ShowChar8x16(x, y, *str, color, bgcolor);
        x += 8;
        str++;
    }
}


void main() {
    // 初始化LCD
    LCD_Init();
    
    // 清屏为白色
    LCD_Clear(WHITE);
    
    // 显示"Hello"
    LCD_ShowString(100, 150, "Hello", RED, WHITE);
    
    while(1);
}