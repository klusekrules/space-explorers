@echo off
cd > tmpFile 
set /p var= < tmpFile 
cd %1
call unitTests.bat
cd %var%
del tmpFile 
@echo on