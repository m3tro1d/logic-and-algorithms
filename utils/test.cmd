@echo off

set subject="%~1"
if %subject% == "" (
  echo Usage: test.cmd ^<filename^>
  goto error
)

FOR %%f in (tests\*.in) DO (
  COPY %%f input.txt > nul
  %subject% > nul || goto failed
  fc output.txt "tests\%%~nf.out" > nul || goto failed
  echo Test %%f passed
)

echo.
echo All tests passed
del input.txt output.txt
exit /B 0

:failed
echo.
echo Test failed
del input.txt output.txt
exit /B 1

:error
del input.txt output.txt
exit /B 1
