#ifndef __DELAY_US_H__
#define __DELAY_US_H__

void delay_us(unsigned char us);

// 支持不同晶振频率
#ifndef FOSC
#define FOSC 11059200  // 默认 12MHz
#endif

// 根据晶振频率自动调整
#if FOSC == 12000000  // 12MHz
    #define ONE_US _nop_()
#elif FOSC == 11059200  // 11.0592MHz
    #define ONE_US { _nop_(); }  // 约 1.085μs，近似使用
#elif FOSC == 24000000  // 24MHz
    #define ONE_US { _nop_(); _nop_(); }  // 24MHz下2个_nop_约1μs
#else
    // 通用计算：每个_nop_为12/FOSC微秒
    #define ONE_US do { \
        unsigned char _i = 12 * 1000000 / FOSC; \
        while (_i--) _nop_(); \
    } while(0)
#endif

//n 1-255
#define delay_us_Macros(n) do { \
    unsigned char _cnt = (n); \
    while (_cnt--) { \
        ONE_US; \
    } \
} while(0)



#endif