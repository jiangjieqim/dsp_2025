@REM set workspaceFolder=%1
@REM echo [%cd%]
@REM exit 0

cd ..

echo cur folder is %cd%

"TortoiseGitProc.exe" /command:commit /path:%cd% /closeonend:0 /logmsg . 

@REM git status  
@REM git pull
start cmd.exe /c git push
ping 127.0.0.1