#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <malloc.h>
// #include <string.h>
// #include <math.h>
// extern "C" {
// #include "utils.h"
// }
/**测试接口*/
// static void 
// c51_utils_test(){
// 	unsigned int v1 = 0x00;
//   	// u_setv(&v1,Bit01|Bit08);
// 	printf("c51:%d\n",v1);
//     //16 65536
//     //pow(2,8)
// }
// class Base {
// private:
// 	int num;
// public:
// 	Base() { num = 10; }
// 	~Base(){
// 		printf("free ~ Base\n");
// 	}
// 	virtual void virFunc1() {				//基类虚函数1
// 		// cout << "Base中虚函数1" << endl;
// 	}
// 	virtual void virFunc2() {
// 		// cout << "Base中虚函数2" << endl;	//基类虚函数2
// 	}
// 	virtual void virFunc3() {
// 		// cout << "Base中虚函数3" << endl;	//基类虚函数3
// 	}
// 	virtual void virRealFunc() = 0;
// protected:

// 	void Show(){
// 		printf("Base Show...");
// 	}
// };

// class Son :public Base {
// private:
// 	int age;

// public:
// 	char *name;
// 	virtual void virFunc2() {				//派生类重写虚函数2
// 		// cout << "Son中虚函数2" << endl;
// 	}
// 	Son(int age,const char* name){
// 		this->age = age;
// 		this->name = (char*)malloc(sizeof(strlen(name)));
// 		printf("Son age is %d name is %s\n",age,name);
// 	}
// 	~Son(){
// 		printf("free ~ Son\n");
// 		free(name);
// 	}
// 	void virRealFunc(){
// 		printf("Son`s virRealFunc...\n");
// 	}

// 	int getAge(){
// 		return age;
// 	}

// protected:
// 	void Show(){
// 		Base:Show();
// 		printf("Son Show...");
// 	}
// };
// static void 
// testSon(){
// 	// Son son(10,"jack");
// 	// int a = son.getAge();
// 	// printf("son`s age is %d\n",a);

// 	Son* _son1 = new Son(6,"tom");
// 	_son1->virRealFunc();
// 	delete _son1;
// }
static void
f_HexToBin(unsigned int a){
	int i;
	int j = 0;
	char s[16];
	memset(s,0,16);
	itoa(a,s,2);
	// printf("%s %d\n",s,strlen(s));
	for(i = 0;i < 16;i++){
		if(j >= 4){
			j=0;
			printf(" ");
		}
		j++;
		printf("%c",s[i]);
	}
	printf("\n");
}
void main(){
	/*
	// u_pwm(100,20);

    // printf("ada");
    // getchar();
    // c51_utils_test();
	// testSon();
	// printf("############################## testSon end...\n");
	// printf("jiang\n");
	// getchar();
	unsigned int a = 0xF0FC;
	// 0xF0FC;//	1111 0000 1111 1100
	//0x8000 ---> 1000 0000 0000 0000
	// f_HexToBin(a);
	unsigned char a1 = (a >> 8);//high
	unsigned char a2 = 0x00ff & a;
	f_HexToBin(a1);
	f_HexToBin(a2);
	*/
	int a = 31;
	int b = 10;
	unsigned char d = (unsigned char)(ceil((float)a / (float)b));
	// int d = (int)c;
	printf("%d\n",d);  
}