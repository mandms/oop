#include <iostream>
#include <string>

const std::string ARGUMENTS_COUNT_ERROR = "Invalid arguments count";
const std::string SAME_WEEK_DAY = "Same week day";
const std::string DIFFERENT_WEEK_DAY = "Different week day";
const std::string ERROR_MESSAGE = "ERROR";
const std::string ERROR_YEAR_VALUE_OUT_OF_RANGE = "Error. Year value out of range.";
const std::string ERROR_MONTH_VALUE_OUT_OF_RANGE = "Error. Month value out of range.";
const std::string ERROR_DAY_VALUE_OUT_OF_RANGE = "Error. Day value out of range.";
const int MIN_YEAR_VALUE = 1900;
const int MAX_YEAR_VALUE = 9999;
const int MIN_MONTH_VALUE = 1;
const int MAX_MONTH_VALUE = 12;
const int MIN_DAY_VALUE = 1;
const int MAX_DAY_VALUE = 31;
const int LEAP_YEAR_DIVIDEND_FIRST = 4;
const int LEAP_YEAR_DIVIDEND_SECOND = 100;
const int LEAP_YEAR_DIVIDEND_THIRD = 400;
const int MONTH_COEF = 13;
const int WEEK_DAYS = 7;
const int WEEK_COEF = 5;
const int THIRD_MONTH = 3;

struct Date
{
	int year;
	int month;
	int day;
};

struct Args
{
	Date dateFirst;
	Date dateSecond;
};

Args ParseDates()
{
	Args args;

	Date date1;
	std::cin >> date1.year >> date1.month >> date1.day;

	Date date2;
	std::cin >> date2.year >> date2.month >> date2.day;

	args.dateFirst = date1;
	args.dateSecond = date2;
	return args;
}

bool IsLeap(int year)
{
	return (year % LEAP_YEAR_DIVIDEND_THIRD == 0) || 
		((year % 4 == LEAP_YEAR_DIVIDEND_FIRST) && 
			(year % LEAP_YEAR_DIVIDEND_SECOND != 0));
}

int Zeller(Date date)
{
	int day = date.day;
	int month = date.month;
	int year = date.year;

	if (month < THIRD_MONTH) {
		month += MAX_MONTH_VALUE;
		year--;
	}

	return (day + (MONTH_COEF * (month + 1)) / 
		WEEK_COEF + year + year / LEAP_YEAR_DIVIDEND_FIRST - year / 
		LEAP_YEAR_DIVIDEND_SECOND + year / LEAP_YEAR_DIVIDEND_THIRD) % WEEK_DAYS;
}

bool IsValidDate(Date date)
{
	if ((date.month == 2) && date.day > 29)
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if ((MIN_YEAR_VALUE > date.year) || (date.year > MAX_YEAR_VALUE))
	{
		std::cout << ERROR_YEAR_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if ((MIN_MONTH_VALUE > date.month) || (date.month > MAX_MONTH_VALUE))
	{
		std::cout << ERROR_MONTH_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if (!IsLeap(date.year) && date.month == 2 && date.day > 28)
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if ((MIN_DAY_VALUE > date.day) || (date.day > MAX_DAY_VALUE))
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	return true;
}

bool IsDifferentYearValue(Args args)
{
	if (args.dateFirst.year != args.dateSecond.year)
	{
		std::cout << ERROR_MESSAGE << std::endl;
		return false;
	}

	return true;
}

int main()
{
	auto args = ParseDates();

	if (!IsValidDate(args.dateFirst) || 
		!IsValidDate(args.dateSecond) || 
		!IsDifferentYearValue(args))
	{
		return 1;
	}

	int dayOfWeek1 = Zeller(args.dateFirst);
	int dayOfWeek2 = Zeller(args.dateSecond);

	if (dayOfWeek1 == dayOfWeek2)
	{
		std::cout << SAME_WEEK_DAY << std::endl;
	}
	else
	{
		std::cout << DIFFERENT_WEEK_DAY << std::endl;
	}
	return 0;
}