@echo off

set workspaceFolder=%1

cd %workspaceFolder%

set filename=%2

set "basename=%filename:.c=%"

set filename=%basename%


REM 设置环境变量
set PATH=C:\Keil_v5\C51\BIN;%PATH%
set C51LIB=C:\Keil_v5\C51\LIB
set C51INC=C:\Keil_v5\C51\INC

if exist %filename%.hex ( del %filename%.hex )

del %filename%.SRC

REM 编译 C 文件，生成 .SRC
C51 %filename%.c SRC
REM 重命名 .SRC 为 .A51
ren %filename%.SRC %filename%.A51

REM 汇编
A51 %filename%.A51

REM 链接（库会自动从 C51LIB 路径查找）
BL51 %filename%.obj TO %filename%

REM 生成 HEX 文件
OH51 %filename%

for %%A in (%filename%.hex) do (
    echo file size %%~zA bytes
)

pause