echo off

set project=%githubdir%\dsp_2025
set Keil_v5=C:\Keil_v5

if not exist %Keil_v5% ( echo not exist %Keil_v5% & exit )

set workspaceFolder=%1

REM 检查是否传入参数
@REM like ${workspaceFolder} test1.c
if "%1"=="" (
    echo param error
    exit /b 1
)

if "%2"=="" (
    echo param error
    exit /b 1
)


echo RUN BAT"%~f0 %1 %2"


set keil=%Keil_v5%/C51

set myc51=%githubdir%\dsp_2025\c51
set inc=%githubdir%\dsp_2025\c51/include
SET C51INC=%keil%/INC/Atmel/;%keil%/INC/;%inc%;
SET C51LIB=%keil%/LIB
SET CPU_TYPE=AT89C52
SET CPU_VENDOR=Atmel
SET CPU_XTAL=11059200

set TARGET=%2

set "basename=%TARGET:.c=%"
set TARGET=%basename%


"%keil%/BIN/A51.EXE" "%myc51%/STARTUP.A51" SET (SMALL) DEBUG EP
"%keil%/BIN/C51.EXE" "%myc51%/%TARGET%.c" ROM(LARGE)

cd %myc51%
"%keil%/BIN/BL51.EXE" "STARTUP.obj,%TARGET%.obj" TO "%TARGET%" RAMSIZE(256)

"%keil%/BIN/OH51.EXE" "%TARGET%"

for %%A in (%TARGET%.hex) do (
    echo file size %%~zA bytes
)