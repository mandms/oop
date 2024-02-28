@echo off

REM путь к программе
SET SameWeekDay="%~1"

REM защита от запуска без аргумента
if %SameWeekDay%=="" (
	echo Please specify path to program
	echo /B 1
)

REM Should output the Same week day
echo Test 1: Same week day
%SameWeekDay% < input1.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\SameWeekDay.txt || goto err
echo Test 1 completed successfully

REM Should output the different week day
echo Test 2: Different week day
%SameWeekDay% < input2.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\DifferentWeekDay.txt || goto err
echo Test 2 completed successfully

REM Should output the ERROR
echo Test 3: ERROR. Different meaning of year
%SameWeekDay% < input3.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\Error.txt || goto err
echo Test 3 completed successfully

exit /B 0

:err
echo Test failed
exit /B 1