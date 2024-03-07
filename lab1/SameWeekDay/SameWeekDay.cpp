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

struct Date
{
	int year;
	int month;
	int day;
};

struct Args
{
	Date date1;
	Date date2;
};

Args ParseDates()
{
	Args args;

	Date date1;
	std::cin >> date1.year >> date1.month >> date1.day;

	Date date2;
	std::cin >> date2.year >> date2.month >> date2.day;

	args.date1 = date1;
	args.date2 = date2;
	return args;
}

bool IsLeap(int year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

int Zeller(Date date)
{
	int day = date.day;
	int month = date.month;
	int year = date.year;

	if (month < 3) {
		month += 12;
		year--;
	}

	return (day + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
}

bool IsValidDate(Args args)
{
	if ((args.date1.month == 2) && args.date1.day > 29)
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if (((MIN_YEAR_VALUE > args.date1.year) || (args.date1.year > MAX_YEAR_VALUE)) ||
		((MIN_YEAR_VALUE > args.date2.year) || (args.date2.year > MAX_YEAR_VALUE)))
	{
		std::cout << ERROR_YEAR_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if (((MIN_MONTH_VALUE > args.date1.month) || (args.date1.month > MAX_MONTH_VALUE)) ||
		((MIN_MONTH_VALUE > args.date2.month) || (args.date2.month > MAX_MONTH_VALUE)))
	{
		std::cout << ERROR_MONTH_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if ((!IsLeap(args.date1.year) && args.date1.month == 2 && args.date1.day > 28) ||
		(!IsLeap(args.date2.year) && args.date2.month == 2 && args.date2.day > 28)
		)
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if (((MIN_DAY_VALUE > args.date1.day) || (args.date1.day > MAX_DAY_VALUE)) ||
		((MIN_DAY_VALUE > args.date2.day) || (args.date2.day > MAX_DAY_VALUE)))
	{
		std::cout << ERROR_DAY_VALUE_OUT_OF_RANGE << std::endl;
		return false;
	}

	if (args.date1.year != args.date2.year)
	{
		std::cout << ERROR_MESSAGE << std::endl;
		return false;
	}

	return true;
}

int main()
{
	auto args = ParseDates();

	if (!IsValidDate(args))
	{
		return 1;
	}

	int dayOfWeek1 = Zeller(args.date1);
	int dayOfWeek2 = Zeller(args.date2);

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