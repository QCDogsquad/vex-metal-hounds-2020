@echo off
call %CD:~0,2%\Robotics\Vex\shell.bat

make
call upload.bat