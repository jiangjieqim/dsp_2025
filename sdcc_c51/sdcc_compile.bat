@REM set workspaceFolder=%cd%
@REM sdcc --version

set workspaceFolder=%1

set TARGET=%2

set "basename=%TARGET:.c=%"
set TARGET=%basename%

set PATH=C:\Program Files\SDCC\bin


if not exist output (

    mkdir output 2>nul

)

del /Q %workspaceFolder%\output\*.*

sdcc -mmcs51 -I%workspaceFolder%\include --out-fmt-ihx -o output/ %TARGET%.c
@REM sdcc -mmcs51 -I. --opt-code-size --out-fmt-ihx -o output/ test.c
cd output

packihx %TARGET%.ihx > %TARGET%.hex

@REM pause
