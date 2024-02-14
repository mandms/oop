SET MyProgram="%~1"

REM Copy empty file
REM %MyProgram% Empty.txt "%TEMP%\output.txt" || goto err

REM Тесты прошли успешно
exit /B 0

REM Если тесты прошли с ошибкой
:err
echo Test failed
exit /B 1