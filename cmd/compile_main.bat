@REM echo off
@REM echo %time% start
set outfilename=main

set CURDIR=%cd%

cd ..

set PROJECT=%cd%

cd ..

set GITHUB_DIR=%cd%

@REM cd %GITHUB_DIR%\game20210510sub

::dsp C51
set dsp=%GITHUB_DIR%\dsp\libs

set MYDIR=%GITHUB_DIR%\MicrosoftVisualStudio8

set Lib=%MYDIR%\VC\lib\;%MYDIR%\VC\PlatformSDK\Lib;

set Include=%MYDIR%\VC\include;%MYDIR%\VC\PlatformSDK\Include;%dsp%;

set PATH=%MYDIR%\VC\bin\;%MYDIR%\Common7\IDE;

set INCLUDE=%INCLUDE%;%PROJECT%\libs;

set LIB=%LIB%;

@REM 清理
cd %PROJECT%\test & del *.exe *.pdb

cd %PROJECT%\test

@REM "%MYDIR%/VC/bin/cl.exe" %PROJECT%\libs\*.c %PROJECT%\test\*.cpp -o %outfilename%.exe  /D _ALL /Z7

"%MYDIR%/VC/bin/cl.exe" %PROJECT%\test\*.cpp  -o %outfilename%.exe  /D _DUMMY_CODE_ /Z7

@REM %PROJECT%\libs\*.c

del *.obj *.ilk

echo ============================================================================== 
call %outfilename%