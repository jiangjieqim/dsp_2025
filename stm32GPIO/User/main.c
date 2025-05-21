//..\stm32GPIO\Objects\1.hex


/*
#region flow

+----------------------+
|startup_stm32f10x_md.s|--->启动文件
+----------------------+


stm32f10x.h
system_stm32f10x.c

#endregion
*/


#include "stm32f10x.h"  // 根据实际型号包含对应的头文件

void SoftwareDelay(uint32_t delay) {
    while (delay--) {
        __asm("NOP");
    }
}
/*
#include "stm32f10x.h"                  // Device header

(1) 现代架构（1 机器周期 = 1 时钟周期）
每个 NOP 耗时 0.125\,\mu\text{s}0.125μs。

1 秒 = 1\,000\,000\,\mu\text{s}1000000μs。

可执行的 NOP 数量：

\frac{1\,000\,000\,\mu\text{s}}{0.125\,\mu\text{s}} = 8\,000\,000 \text{ 个 NOP}
0.125μs
1000000μs
​
 =8000000 个 NOP
*/
/*
#define __DELAY__ 800000
int main(void)
{
//	RCC->APB2ENR = 0x00000010;
//	GPIOC->CRH = 0x00300000;
//	GPIOC->ODR = 0x0;//0x00002000;
	//int t = int(1000000/(1/8)); 8000000
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);

	while(1){
		
		SoftwareDelay(__DELAY__);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		SoftwareDelay(__DELAY__);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}			
}
*/

#define __DELAY__ 800000
void GPIO_PC13_Init(void)
{
    // 1. 启用 GPIOC 时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    
    // 2. 配置 PC13 为推挽输出
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);  // 清除原有配置
    GPIOC->CRH |= GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0; // 输出模式，最大速度50MHz
}

int main(void)
{
    GPIO_PC13_Init();
    
    while(1)
    {
        // 3. 切换 PC13 状态
        GPIOC->BSRR = GPIO_BSRR_BS13;  // 置高
        SoftwareDelay(__DELAY__);            // 简单延时
        GPIOC->BSRR = GPIO_BSRR_BR13;  // 置低
        SoftwareDelay(__DELAY__);
    }
}
