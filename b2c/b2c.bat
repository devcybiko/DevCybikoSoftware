@echo off
b2cpp\release\b2cpp.exe %1.bas > %1.b2c
if errorlevel 1 goto end
debug\b2c.exe %1.b2c
if errorlevel 1 goto end
del %1.b2c
:end
