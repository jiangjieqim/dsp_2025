#include <reg51.h>
sbit LED = P1^0;   // 定义LED连接到P1.0引
static void 
delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 125; j++);
}
void main() {
    while(1) {
        LED = 0;    // LED亮（假设低电平点亮）
        delay(500); // 延时约500ms
        LED = 1;    // LED灭
        delay(500); // 延时约500ms
    }
}