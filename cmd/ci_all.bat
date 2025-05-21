@REM set workspaceFolder=%1
@REM echo [%cd%]
@REM exit 0

cd ..

echo cur folder is %cd%

"TortoiseGitProc.exe" /command:commit /path:%cd% /closeonend:0 /logmsg . 

git status  
git pull
git push
