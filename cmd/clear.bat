echo off
set "workspaceFolder=%cd%"

cd ..

cd proteus1

del *.workspace *.pdsbak 2>nul
cd clip
del *.workspace *.pdsbak 2>nul

cd /d "%workspaceFolder%"

del *_ia *.__i *.plg *.bak *.lst *.obj *.M51 *.SRC 2>nul

REM 删除无扩展名的文件（更安全的方式）
for %%f in (*) do (
    if "%%~xf"=="" del "%%f" 2>nul
)