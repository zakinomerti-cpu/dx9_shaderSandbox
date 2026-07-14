@echo off

set vsvarsalpath="C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"
set dxpath=C:\DXSDK2005

call %vsvarsalpath% x86
cl MAIN.C /I"%dxpath%\Include" /link /LIBPATH:"%dxpath%\Lib\x86" d3d9.lib d3dx9.lib user32.lib

del MAIN.OBJ
