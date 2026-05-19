#ifndef __DELAY_US_H__
#define __DELAY_US_H__

// void delay_us(unsigned char us);


/*
    优点:
        1.零调用开销,
            宏在预处理阶段展开，直接插入NOP指令
            无函数调用、无返回、无压栈/出栈
            时序完全可预测

        2.精度最高 
            只有NOP指令本身的时间（1.085μs/个）
            无循环判断的累积误差
            误差仅来自NOP数量的取整（±0.085μs的整数倍）

        3. 执行时间固定 ✅
            每次展开的指令数量固定
            不受中断、条件分支影响
            适合精确时序控制（如I2C、SPI、OneWire）

    缺点:代码膨胀严重 ,无法处理大延时(定时器方案(最精确))
*/
// 11.0592MHz精确NOP数量表（已取整）
// 1μs = 0.92个NOP → 实际1个NOP(1.085μs)
// 10μs = 9.22个NOP → 实际9个NOP(9.765μs)或10个NOP(10.85μs)

#define DELAY_1US()  _nop_()                           // 1.085μs
#define DELAY_2US()  _nop_(); _nop_()                  // 2.170μs
#define DELAY_3US()  _nop_(); _nop_(); _nop_()         // 3.255μs
#define DELAY_4US()  DELAY_2US(); DELAY_2US()          // 4.340μs
#define DELAY_5US()  DELAY_4US(); DELAY_1US()          // 5.425μs
#define DELAY_6US()  DELAY_5US(); DELAY_1US()          // 6.510μs
#define DELAY_7US()  DELAY_5US(); DELAY_2US()          // 7.595μs
#define DELAY_8US()  DELAY_4US(); DELAY_4US()          // 8.680μs
#define DELAY_9US()  DELAY_8US(); DELAY_1US()          // 9.765μs
#define DELAY_10US() DELAY_5US(); DELAY_5US()          // 10.850μs
#define DELAY_11US() DELAY_10US(); DELAY_1US()         // 11.935μs
#define DELAY_12US() DELAY_6US(); DELAY_6US()          // 13.020μs
#define DELAY_13US() DELAY_12US(); DELAY_1US()         // 14.105μs
#define DELAY_14US() DELAY_12US(); DELAY_2US()         // 15.190μs
#define DELAY_15US() DELAY_10US(); DELAY_5US()         // 16.275μs

// 使用
// void test(void) {
//     P1 = 0xFF;
//     DELAY_10US();  // 精确10.85μs，零调用开销
//     P1 = 0x00;
// }



#endif