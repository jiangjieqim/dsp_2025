cd ..\C51
set logfile=build_log.txt
set Keil=C:\Keil\UV4\Uv4.exe

if not exist %Keil% ( echo not exist %Keil% & goto:end )

%Keil% -b -j0 test.uvproj -o .\%logfile%
@REM C:\Keil\UV4\Uv4.exe -c test.uvproj
type .\%logfile%

dir test.hex /p

del *.M51 *.plg *.lnp *.OBJ *.LST *.lst *.bak *.txt *.uvopt
del test

:end