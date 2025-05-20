@REM D:\github\nodelib\nodejs_10.24

cd ..\..\
set workspaceFolder=%1
set filename=%2

set github=%cd%
set PATH=%github%\nodelib\nodejs_10.24;%github%\nodelib

cd %github%\nodelib
node stm32_compile.js --workspace %workspaceFolder% --targetfile %filename%
