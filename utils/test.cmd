@echo off

set subject="%~1"
if %subject% == "" (
  echo Usage: test.cmd ^<filename^>
  goto error
)

FOR %%f in (tests\*.in) DO (
  copy %%f input.txt > nul
  copy "tests\%%~nf.out" output_correct.txt > nul

  %subject% > nul || goto failed
  fc output.txt "tests\%%~nf.out" > nul || goto failed

  echo Test %%f passed
)

echo.
echo All tests passed
del input.txt output.txt output_correct.txt
exit /B 0

:failed
echo.
echo Test failed. Check input.txt, output.txt and output_correct.txt
exit /B 1

:error
exit /B 1
