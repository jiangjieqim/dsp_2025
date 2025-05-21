#include <reg51.h>
#include <intrins.h>
#define LINE_MAX_NUM 16
#define u8 unsigned char  //0~255
//数据端口
#define LED1602_DS P0

sbit LED1602_RS = P2 ^ 2;
sbit LED1602_RW = P2 ^ 1;
sbit LED1602_E = P2 ^ 0;

#define __DELAY__ 1

int u_strlen(char* s){
	int i = 0;
	while (s[i]!=0){
		i++;
	}
	return i;
}

/*
/****************** 忙检测 *********************
LCD_Data 与 0x80 进行或运算，判断 bit7 位状态

若 LCD_Data 的 bit7 位是 0，则 LCD 不忙
若 LCD_Data 的 bit7 位是 1，则 LCD 忙

----------
|10000000|----->忙
----------
|00000000|----->闲
----------
一般有两种方法来等待数据写入，

1：采用延时等待;

2是采用检测忙信号来完成，一般都是采用后者来判断数据是否写入完成。

初始化过程的：

1:首先延时15ms，

2：写指令38h在延时5ms

3：在写指令38h，在延时5ms，

4：在写指令38h，以后每次写指令。

读写数据操作之前都要检测忙信号，以确保数据写入。
***********************************************/
#pragma region LCD_Check_Busy

void delay(int i){
   while (i--);
}

static void
LCD_Check_Busy(){
    u8 temp;
    LED1602_DS = 0xff;           //1111 1111
    LED1602_RS = 0;              // 0 指令
    LED1602_RW = 1;              // 1 读
    do{
        LED1602_E = 1;           // 拉高
        temp = LED1602_DS;       // 将 LCD 状态保存在 temp 中，用于判忙
        LED1602_E = 0;           // 负跳变使能
    } while (temp & 0x80);       // 结果为 1，LCD 忙，继续循环；结果为 0，LCD 不忙，可以进行后面的操作 ,0x08 = 1000 0000  
}
#pragma endregion
static void
WriteCommand(unsigned char c)
{
    LCD_Check_Busy();
    // u_delayMS(5); //short delay before operation
    
    LED1602_E = 0;
    LED1602_RS = 0;
    LED1602_RW = 0;
    delay(__DELAY__);
    LED1602_E = 1;
    LED1602_DS = c;
    LED1602_E = 0;
}
static void 
WriteData(unsigned char c)
{
    // u_delayMS(5); //short delay before operation
    LCD_Check_Busy();
    LED1602_E = 0;
    LED1602_RS = 1;
    LED1602_RW = 0;
    delay(__DELAY__);
    LED1602_E = 1;
    LED1602_DS = c;
    LED1602_E = 0;
    LED1602_RS = 0;
}
static void 
f_showChar(unsigned char pos, unsigned char c){
    u8 p;
    if (pos >= 0x10)
        p = pos + 0xb0; //是第二行则命令代码高4位为0xc
    else
        p = pos + 0x80; //是第二行则命令代码高4位为0x8
    WriteCommand(p);    //write command
    WriteData(c);       //write data
}
/*************************************************************************/
static void 
f_showStr(unsigned char line, char *ptr){
    u8 l, i,len;
    len = u_strlen(ptr);
    l = line << 4;
    for (i = 0; i < len; i++)
        f_showChar(l++, *(ptr + i)); //循环显示16个字符
}

void LCD1602_init()
{
    // u_delayMS(15);
    // WriteCommand(0x38); //display mode
    // WriteCommand(0x38); //display mode

    //display mode 设置显示模式 0011 1000 :8位数据接口 两行显示 5X7点阵
    WriteCommand(0x38); 

    //输入方式设置 0000 0110 数据读/写操作之后 AC自加1,画面不动
    WriteCommand(0x06);

    /*
    显示开关控制  
        0x0c ---->0000 1100 显示开 光标关 闪烁关
        0x08                显示关 光标关 闪烁关
        0x0d                显示开 光表光 闪烁开
    */
    WriteCommand(0x0d);

    //清屏 0000 0001 清除DDRAM和AC值,光标复位
    WriteCommand(0x01); //显示清屏
    // LCD1602_clear();

    delay(20);
}

void LCD1602_refresh(const char* s){
    
    u8 len =	u_strlen(s);
	u8 _max = LINE_MAX_NUM;
	
    // char data out[] = "               ";//这个函数内声明的字符缓冲区会占用程序空间
	// sprintf(out, "str len is:%d",len); //the first line	 *?gzguava.1111 
    f_showStr(0, s);
	if(len > _max){
		f_showStr(1, s+_max);
	}
}

void LCD1602_clear(){
    WriteCommand(0x01);
}


void main(void){
	// char arr[] = "                ";
	// unsigned int v = 0xf0fc;
	// A = 0;
	// B = 0;
	// C = 0;
	char s[] = "abc123";
	LCD1602_init();
	//sprintf(s,"%d",sizeof(unsigned short));
	LCD1602_refresh(s);

    while (1){
    }
}