#include <reg51.h>
#include <intrins.h>
#include "utils.h"
void u_nop(){
	_nop_();
}
void u_setv(unsigned int *v, unsigned int flag){
	*v = (*v) | flag;
}

void u_delayMS(unsigned int i){
	while (--i){
		u_delayUS(250);
		u_delayUS(250);
		u_delayUS(250);
		u_delayUS(250);
	}
}
/*n毫秒*/
void u_delay255MS(u8 n){
	u8 t1;
	while (n>0){
		n--;
		//one _nop_ use 1.049 us
		for (t1 = 255; t1 > 0; t1--){
			_nop_();
		}
		for (t1 = 16; t1 > 0; t1--){
			_nop_();
		}
	}
}
/*n秒*/
void u_delaySec(u8 n){
	u8 b;
	for(b = n;b > 0;b--){
		u_delay255MS(255);
		u_delay255MS(255);
		u_delay255MS(255);
		u_delay255MS(255);
	}
}
/*500微秒*/
void u_delay500US(u8 n){
	u8 b;
	for(b = n;b > 0;b--){
		u8 t;
		for(t = 151;t > 0;t--){
			_nop_();
		}
	}
}
/*
The _nop_ routine inserts a NOP instruction into the program. 
This routine can be used to pause for 1 CPU cycle.
This routine is implemented as an intrinsic function. The NOP instruction is included inline.
*/
void u_delayUS(u8 us){
	//	220 --> 250 us
	//  250 --> 284 us

	// us = 1 has bug

	//delay us
	u8 uscnt;
	uscnt = us >> 1; // Crystal frequency in 12MHz
	while (--uscnt){
		;
	}

	// unsigned int k;
	// for(k = 0;k< us;k++){
	// 	_nop_();//占用一个机器周期的时间
	// }
}
// void u_delayUS2(unsigned int t){
// 	unsigned int i;
// 	for(i = 0;i< t;i++){
// 		u_delayUS(1);
// 	}
// }

int u_strlen(char* s){
	int i = 0;
	while (s[i]!=0){
		i++;
	}
	return i;
}

void u_hex2Str(unsigned int b, char *array){
	// char s[16];
	/*
	int i = 0;
	for (i = 0; i < 16; i++){
		*array += 0;
	}
	sprintf(array, "%X", b); //%x or %X
	*/
	char a[17] = {"0123456789ABCDEF"};
	int c[30] = {0},i = 0,base = 16,j = 0;
	while (b){
		c[i++] = b % base;
		b = b / base;
	}
	j = i;
	for(i--;i>=0;i--){
		array[j-i-1] = a[c[i]];
	}
	// return j;
}

//==========================================
#ifdef _USE_GPIO_set

sbit I2C_SDA1 = P2 ^ 5;
sbit I2C_SCL1 = P2 ^ 6;
sbit I2C_ERR = P2 ^ 7;

void u_GPIO_set(u8 type, bit v){
	switch (type){
		case GPIO_SDA:
			I2C_SDA1 = v;
			break;
		case GPIO_SCL:
			I2C_SCL1 = v;
			break;
		case GPIO_ERR:
			I2C_ERR = v;
			break;
	}
}
u8 u_GPIO_get(u8 type){
	switch (type)
	{
		case GPIO_SDA:
			return I2C_SDA1;
	}
	return 0;
}
#else
void u_GPIO_set(u8 type, bit v){
}
u8 u_GPIO_get(u8 type){
}
#endif
