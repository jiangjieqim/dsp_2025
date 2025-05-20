@REM set workspaceFolder=%1
@REM echo [%cd%]
@REM exit 0

"TortoiseGitProc.exe" /command:commit /path:%cd% /closeonend:0 /logmsg . 
git status  
git pull
git push
