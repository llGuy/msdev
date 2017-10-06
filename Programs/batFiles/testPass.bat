@echo off

echo create password and username
echo.
echo check password and username
echo.

set /p CHOICE = WHAT WOULD YOU LIKE TO DO: 
goto %CHOICE%
pause

:create
set /p PASSWORD = WHAT WOULD YOU LIKE THE PASSWORD TO BE: 
echo %PASSWORD% > testpass.txt
:check
start testpass.txt
pause



