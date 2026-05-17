#ifndef __DELAY_US_H__
#define __DELAY_US_H__

void delay_us(unsigned char us);


// 11.0592MHz精确NOP数量表（已取整）
// 1μs = 0.92个NOP → 实际1个NOP(1.085μs)
// 10μs = 9.22个NOP → 实际9个NOP(9.765μs)或10个NOP(10.85μs)

#define DELAY_1US()  _nop_()                           // 1.085μs
#define DELAY_2US()  _nop_(), _nop_()                  // 2.170μs
#define DELAY_3US()  _nop_(), _nop_(), _nop_()         // 3.255μs
#define DELAY_4US()  DELAY_2US(), DELAY_2US()          // 4.340μs
#define DELAY_5US()  DELAY_4US(), DELAY_1US()          // 5.425μs
#define DELAY_6US()  DELAY_5US(), DELAY_1US()          // 6.510μs
#define DELAY_7US()  DELAY_5US(), DELAY_2US()          // 7.595μs
#define DELAY_8US()  DELAY_4US(), DELAY_4US()          // 8.680μs
#define DELAY_9US()  DELAY_8US(), DELAY_1US()          // 9.765μs
#define DELAY_10US() DELAY_5US(), DELAY_5US()          // 10.850μs
#define DELAY_11US() DELAY_10US(), DELAY_1US()         // 11.935μs
#define DELAY_12US() DELAY_6US(), DELAY_6US()          // 13.020μs
#define DELAY_13US() DELAY_12US(), DELAY_1US()         // 14.105μs
#define DELAY_14US() DELAY_12US(), DELAY_2US()         // 15.190μs
#define DELAY_15US() DELAY_10US(), DELAY_5US()         // 16.275μs

// 使用
// void test(void) {
//     P1 = 0xFF;
//     DELAY_10US();  // 精确10.85μs，零调用开销
//     P1 = 0x00;
// }



#endif