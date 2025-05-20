@REM SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;
@REM SET CPU_TYPE=STM32F103C8
@REM SET CPU_VENDOR=STMicroelectronics
@REM SET UV2_TARGET=Target 1
@REM SET CPU_CLOCK=0x00B71B00
@REM "ArmAsm" --Via ".\objects\startup_stm32f10x_md._ia"
@REM "ArmCC" --Via ".\objects\system_stm32f10x.__i"
@REM "ArmCC" --Via ".\objects\main.__i"
@REM "ArmLink" --Via ".\Objects\1.lnp"
@REM "fromelf.exe" ".\Objects\1.axf" --i32combined --output ".\Objects\1.hex"

set KEIL_PATH="C:\Keil_v5\UV4\UV4.exe"

if not exist %KEIL_PATH% ( echo is not exist %KEIL_PATH% & exit )

set workspace=%cd%

set PROJECT="%workspace%\1.uvprojx"
set TARGET="Target 1"

echo build now...
%KEIL_PATH% -b %PROJECT% -t %TARGET% -j0

if %errorlevel% equ 0 (
    echo build succeed!
) else (
    echo build fail!
)