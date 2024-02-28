@echo off

REM путь к программе
SET Join="%~1"

REM защита от запуска без аргумента
if %Join%=="" (
	echo Please specify path to program
	echo /B 1
)

REM Join empty files
echo Test 1: join empty files
%Join% tests\Empty.bin tests\Empty2.bin "%TEMP%\output.bin" || goto err
fc tests\EmptyResult.bin "%TEMP%\output.bin" > nul || goto err
echo Test 1 completed successfully

REM Join non empty files
echo Test 2: join non empty files
%Join% tests\NonEmpty.bin tests\NonEmpty2.bin "%TEMP%\output.bin" || goto err
fc tests\NonEmptyResult.bin "%TEMP%\output.bin" > nul || goto err
echo Test 2 completed successfully

REM Join missing files
echo Test 3: join missing files
%Join% > nul tests\Missing.bin tests\Missing2.bin "%TEMP%\output.bin" && goto err
echo Test 3 completed successfully

REM If output file not specified, program must fail
echo Test 4: join missing files
%Join% > nul tests\Missing.bin tests\Missing2.bin && goto err
echo Test 4 completed successfully

REM If input and output files are not specified, program must fail
echo Test 5: join missing files
%Join% > nul && goto err
echo Test 5 completed successfully

echo All tests completed successfully
exit /B 0

REM Если тесты прошли с ошибкой
:err
echo Test failed
exit /B 1