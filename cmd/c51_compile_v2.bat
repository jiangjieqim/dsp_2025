@echo off
@REM set project=D:\github\dsp_2025
set keil=C:/Keil_v5/C51
set myc51=D:\github\dsp_2025\c51
@REM set inc=D:\github\dsp_2025\c51/include
@REM SET C51INC=%keil%/INC/Atmel/;%keil%/INC/;%inc%;
@REM SET C51LIB=%keil%/LIB
@REM SET CPU_TYPE=AT89C52
@REM SET CPU_VENDOR=Atmel
@REM SET CPU_XTAL=11059200

cd %myc51%

REM 检查是否传入文件名参数
if "%1"=="" (
    echo 错误：请指定文件名！
    echo 用法：%~nx0 文件名（不含扩展名）
    pause
    exit /b 1
)

REM 设置文件名变量
set filename=%1

set "filename=test1.c"
set "basename=%filename:.c=%"

set filename=%basename%

@REM echo filename is %filename%

REM 汇编 STARTUP 文件
"%keil%/BIN/A51.EXE" STARTUP.A51 SET (SMALL) DEBUG EP

REM 编译 C 文件生成 SRC 文件
"%keil%/BIN/C51.EXE" %filename%.c ROM(LARGE) SRC

REM 将生成的 SRC 文件汇编成 OBJ 文件
"%keil%/BIN/A51.EXE" %filename%.src

REM 链接生成最终文件
"%keil%/BIN/BL51.EXE" STARTUP.OBJ,%filename%.OBJ TO "%filename%" RAMSIZE(256)

REM 生成 HEX 文件
"%keil%/BIN/OH51.EXE" %filename%

if exist %filename%.hex (
    echo Finish！build：%filename%.hex
    for %%A in (%filename%.hex) do (
        echo file size %%~zA bytes
    )
) else (
    echo Error：build %filename%.hex
)