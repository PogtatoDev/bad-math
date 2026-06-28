@echo off
setlocal

set "HEADER=full_lib.hpp"

(
    echo #ifndef __ALL_HEADERS__
    echo #define __ALL_HEADERS__
) > "%HEADER%"

for %%F in (*.hpp) do (
    echo #include ^"%%~nxF^" >> "%HEADER%"
)

echo #endif >> "%HEADER%"

endlocal