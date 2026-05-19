set workspaceFolder=%cd%

set PATH=C:\Program Files\SDCC\bin

sdcc --version


if not exist output (

    mkdir output 2>nul

)

del /Q %workspaceFolder%\output\*.*

sdcc -mmcs51 -I. --out-fmt-ihx -o output/ test.c
@REM sdcc -mmcs51 -I. --opt-code-size --out-fmt-ihx -o output/ test.c
cd output


packihx test.ihx > test.hex

pause
