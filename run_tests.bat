@echo off
echo compiling files...
make clean_bin > nul 2>&1
make > nul 2>&1
cls
cd tests
tests.exe
cd..