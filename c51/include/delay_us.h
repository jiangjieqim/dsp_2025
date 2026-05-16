#ifndef __DELAY_US_H__
#define __DELAY_US_H__
// 不同晶振对应的计数值表
// 索引：us值，内容：循环次数
code unsigned char us_table[] = {
    0,  // 0us
    2,  // 1us
    4,  // 2us
    6,  // 3us
    8,  // 4us
    10, // 5us
    12, // 6us
    14, // 7us
    16, // 8us
    18, // 9us
    20  // 10us
};

void delay_us(unsigned char us) {
    unsigned char i;
    unsigned char loops;
    
    if(us == 0) return;
    
    // 从表中获取循环次数
    if(us <= 10) {
        loops = us_table[us];
    } else {
        loops = us * 2;  // 近似值：1us≈2个循环
    }
    
    while(loops--) {
        i = 1;
        while(i--);
    }
}
#endif