SET MyProgram="%~1"

REM Copy empty file
REM %MyProgram% Empty.txt "%TEMP%\output.txt" || goto err

REM ����� ������ �������
exit /B 0

REM ���� ����� ������ � �������
:err
echo Test failed
exit /B 1