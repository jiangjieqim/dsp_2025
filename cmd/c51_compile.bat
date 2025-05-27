@REM D:\github\nodelib\nodejs_10.24

cd ..\..\
set workspaceFolder=%1
set filelistparm=%2
set filename=%3

echo filelistparm is %filelistparm%

set github=%cd%
set PATH=%github%\nodelib\nodejs_10.24;%github%\nodelib

cd %github%\nodelib
node c51_compile2.js --filelist %workspaceFolder%\%filelistparm% --file %filename% --workspace %workspaceFolder%


@REM // "rpath":"D:/github/dsp_2025/c51",

@REM --workspaceFolder %workspaceFolder% --entry test.c

exit 0

@REM set C51_TMP=C:\C51_TMP
@REM set C51_PATH=C:\Keil\C51

@REM set workspaceFolder=%1
@REM set entryfile=%2

@REM echo your workspaceFolder is[%workspaceFolder%]
@REM cd ..
@REM @REM D:\github\dsp
@REM set project=%cd%
@REM set cmdpath=%project%\cmd
@REM if "%workspaceFolder%" == "" (  echo warnning! your must be input workspaceFolder! & exit 0 )

@REM if "%entryfile%" == "" ( echo warnning! your must be input entryfile! & exit 0 )


@REM @REM mkdir cmd_test
@REM if not exist %C51_TMP% ( mkdir %C51_TMP% )

@REM SET TMP=%C51_TMP%
@REM SET C51INC=%C51_PATH%\INC
@REM SET C51LIB=%C51_PATH%\LIB
@REM set PATH=%PATH%;%C51_PATH%\BIN%;%C51INC%;%C51LIB%

@REM cd %workspaceFolder%

@REM @REM %C51_PATH%\BIN\C51 *.c
@REM @REM %C51_PATH%\BIN\C51 %project%\libs\*.c
@REM @REM %cmdpath%\compile_func test.c
@REM @REM cd 
@REM @REM call %cmdpath%\compile_func %project%\libs\utils.c 
@REM @REM call %cmdpath%\compile_func %project%\c51\test.c

@REM @REM %C51_PATH%\BIN\C51 test.c %project%\libs\utils.c

@REM @REM %cmdpath%\compile_func %project%\c51\test.c
@REM @REM %cmdpath%\compile_func %project%\libs\utils.c
@REM @REM pause

@REM @REM %cmdpath%\compile_func %project%\c51\test.c
@REM @REM pause

@REM @REM %C51_PATH%\BIN\BL51 test.OBJ, utils.OBJ

@REM %C51_PATH%\BIN\C51 %entryfile%
