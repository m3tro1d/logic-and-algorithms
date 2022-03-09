@echo off

set subject="%~1"
if %subject% == "" (
  echo Usage: test.cmd ^<filename^>
  goto error
)

FOR %%f in (tests\*.in) DO (
  %subject% <"%%f" >"tests\%%~nf.txt" || goto failed
  fc "tests\%%~nf.txt" "tests\%%~nf.out" > nul || goto failed
  echo Test %%f passed
)

echo All tests passed
del tests\*.txt
exit /B 0

:failed
echo Test failed
del tests\*.txt
exit /B 1

:error
del tests\*.txt
exit /B 1
