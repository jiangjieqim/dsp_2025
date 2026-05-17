#include <reg51.h>
#include <intrins.h>

/*
右键点击项目 → Options for Target 'Target 1'

切换到 Listing 标签页

勾选 Assembler SRC 选项

重新编译

*/

void delay() {
    #pragma asm
    MOV R7, #10
DEL_LOOP:
    MOV R6, #20
    DJNZ R6, $
    DJNZ R7, DEL_LOOP
    #pragma endasm
}
				
void main() {
    while(1) {
        P0 = 0x0;
       	delay();
        P0 = 0x1;
        delay();
    }
}