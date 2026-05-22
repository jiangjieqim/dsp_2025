echo off

@REM set workspaceFolder=%cd%
@REM sdcc --version

set workspaceFolder=%1

set TARGET=%2

set "basename=%TARGET:.c=%"
set TARGET=%basename%

set PATH=C:\Program Files\SDCC\bin

set OUT_DIR=output

if not exist output (
    mkdir output 2>nul
) else (
    del /Q %workspaceFolder%\output\*.*
)

set program=program

@REM sdcc -mmcs51 -I%workspaceFolder%\include --out-fmt-ihx -o output/ %TARGET%.c

sdcc -c -mmcs51 -Iinclude %TARGET%.c -o %OUT_DIR%\%TARGET%.rel
sdcc -c -mmcs51 -Iinclude src\delay.c -o %OUT_DIR%\delay.rel

sdcc -mmcs51 %OUT_DIR%\%TARGET%.rel %OUT_DIR%\delay.rel -o %OUT_DIR%\%program%.ihx


@REM sdcc -mmcs51 -I%workspaceFolder%\include --opt-code-size --out-fmt-ihx -o output/ %TARGET%.c
cd output

packihx %program%.ihx > %program%.hex
for %%A in (%program%.hex) do (
    echo %program%.hex size %%~zA bytes
)

pause