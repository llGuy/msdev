@echo off

:start

set /p MATH=Equation :
set /a RESULT=%MATH%
echo %MATH% 
echo %RESULT%

if %RESULT%==5 start myFirstHTML.html

pause
cls
goto start
