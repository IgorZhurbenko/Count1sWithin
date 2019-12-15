echo off
chcp 855
cls
gcc main.c
if %errorlevel% == 0 (
a.exe )
pause
