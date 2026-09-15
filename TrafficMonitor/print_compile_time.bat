@echo off
rem Write beside the script regardless of the build working directory.
> "%~dp0compile_time.txt" echo %date% %time%
