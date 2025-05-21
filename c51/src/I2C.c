#include <reg51.h>
#include "I2C.h"
#include "utils.h"
/*
    tSU.STA Start Set-up Time 4.7 4.7 0.6 µs
    建立时间不能小于的时间
*/
#define tSU_STA 5
/*
    tHD.STA Start Hold Time 4.0 4.0 0.6 µs
    开始保持时间不能小于的时间
*/ 
#define tHD_STA 4
/**
    tLOW Clock Pulse Width Low 4.7 4.7 1.2 µs
    时钟线低电平的最小维持时间
*/
#define tLOW 5
/*
    tHIGH Clock Pulse Width High 4.0 4.0 0.6 µs
    时钟线高电平最小维持时间
*/
#define tHIGH 4
/*
*    tSU.DAT Data In Set-up Time 200 200 100 ns
*    数据线输入设置时间不能低于的时间
*/
#define tSU_DAT 1
/*
    tDH Data Out Hold Time 100 100 50 ns
    数据线输出保持时间不能低于的时间
*/
#define tDH 1
/* 
    tR Inputs Rise Time(1)MAX 1.0 1.0 0.3 µs
    上升沿时间不能大于的时间
*/
#define tR 1
/*
Stop Set-up Time 
停止状态建立时间不能小于(4.7,4.7,0.6)us
*/
#define tSU_STO 5
/*
Time the bus must be free before a new transmission can start 4.7 4.7 1.2
总线切换到开始状态不能低于4.7us
*/
#define tBUF 5 

/* 
*tAA Clock Low to Data Out Valid 0.1-4.5 0.1-4.5 0.1-0.9 µs
*SCL时钟线在低电平的时候,SDA数据有效时间区间2.5V电压时(最小不能小于0.1us 最大不能大于4.5us)
*该时间区间内数据线用以改变数据
*/
#define tAA 1

/* 
    tHD.DAT Data In Hold Time 0 0 0 µs
    数据线需要保持的时间
*/
#define tHD_DAT 0

//D:\BaiduNetdiskDownload\STC89C52开发板-附件\10-扩展例程(C语言)-仅供移植参考\10-扩展例程(C语言)-仅供移植参考\10、扩展例程(C语言)\58-EEPROM-IIC

/**
 * SCL高电平时候 SDA 从高到低的跳变
*/
void I2C_Start(){
    u_GPIO_set(GPIO_SCL, 1);
    u_delayUS(tSU_STA);
    u_GPIO_set(GPIO_SDA, 1);
    u_delayUS(tHD_STA);
    u_GPIO_set(GPIO_SDA, 0);

    /*
        GPIO_SCL 1->0 产生一下降沿, Inputs Fall Time 
        下降沿的时间不能大于300ns,超时就会进入亚稳态
    */
    u_GPIO_set(GPIO_SCL, 0);
}
/**
 * SCL高电平的时候 SDA由低向高的跳变
 */
void I2C_Stop(){
    u_GPIO_set(GPIO_SDA,0);
    u_delayUS(tSU_DAT);
    u_GPIO_set(GPIO_SCL,1);
    u_delayUS(tSU_STO);
    u_GPIO_set(GPIO_SDA,1);
    u_delayUS(tBUF);
}

void I2C_SendByte(unsigned char dat){
    unsigned char i;
    for (i = 0; i < 8; i++){

        u_GPIO_set(GPIO_SDA,dat >> 7);
        dat = dat << 1;
        u_delayUS(tSU_DAT);

        u_GPIO_set(GPIO_SCL,1);
        u_delayUS(tHIGH);

        u_GPIO_set(GPIO_SCL,0);
        u_delayUS(tLOW);
    }
    I2C_ReceiveAck();
}

u8 I2C_ReceiveByte(){
    u8 a=0,dat=0;
    u_GPIO_set(GPIO_SCL,0);
    u_delayUS(tLOW);
    u_GPIO_set(GPIO_SDA,1);
    //起始和发送一个字节之后SCL都是0
    u_delayUS(tHIGH);
    for (a = 0; a < 8; a++){
        //接收8个字节
        
        u_GPIO_set(GPIO_SCL,1);
        u_delayUS(tHIGH);
        
        dat <<= 1;
        dat |= u_GPIO_get(GPIO_SDA);
        u_delayUS(tDH);
        u_GPIO_set(GPIO_SCL,0);
        u_delayUS(tLOW);
    }
    return dat;
}
/**等待应答*/
unsigned char I2C_ReceiveAck(){
    // unsigned char AckBit;
    u8 b=0;
    u_GPIO_set(GPIO_SDA,1);
    u_delayUS(tSU_DAT);
    u_GPIO_set(GPIO_SCL,1);
    u_delayUS(tHIGH);
    
    while (u_GPIO_get(GPIO_SDA)){ 
        //ACK  等待应答，也就是等待从设备把SDA拉低
        b++;
        if (b > 2000){ 
            //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
            u_GPIO_set(GPIO_SCL,0);
            u_delayUS(tAA);

            u_GPIO_set(GPIO_ERR,1);
            return 0;
        }
    }
    u_GPIO_set(GPIO_SCL,0);
    u_delayUS(tLOW);
    return 1;
}