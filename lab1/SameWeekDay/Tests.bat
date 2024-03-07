@echo off

SET SameWeekDay="%~1"

if %SameWeekDay%=="" (
	echo Please specify path to program
	echo /B 1
)

REM Should output the Same week day
echo Test 1: Same week day
%SameWeekDay% < input1.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\SameWeekDay.txt > nul || goto err
echo Test 1 completed successfully

REM Should output the different week day
echo Test 2: Different week day
%SameWeekDay% < input2.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\DifferentWeekDay.txt > nul || goto err
echo Test 2 completed successfully

REM Should output the ERROR
echo Test 3: Different values of year
%SameWeekDay% < input3.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\Error.txt > nul || goto err
echo Test 3 completed successfully

REM Should output the ERROR
echo Test 4: Year is lower 1900 or bigger 9999
%SameWeekDay% < input4.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\YearOutOfRange.txt > nul || goto err
echo Test 4 completed successfully

REM Should output the ERROR
echo Test 5: Month is lower 1 or bigger 12
%SameWeekDay% < input5.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\MonthOutOfRange.txt > nul || goto err
echo Test 5 completed successfully

REM Should output the ERROR
echo Test 6: Day is lower 1 or bigger 31
%SameWeekDay% < input6.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\DayOutOfRange.txt > nul || goto err
echo Test 6 completed successfully

echo Test 7: Comparing leap year dates
%SameWeekDay% < LeapYear.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\DifferentWeekDay.txt > nul || goto err
echo Test 7 completed successfully

echo Test 8: Comparing not leap year dates
%SameWeekDay% < NotLeapYear.txt > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" tests\SameWeekDay.txt > nul || goto err
echo Test 8 completed successfully

exit /B 0

:err
echo Test failed
exit /B 1