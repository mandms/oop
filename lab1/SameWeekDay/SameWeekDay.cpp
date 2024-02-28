#include <iostream>
#include <string>
#include <optional>

const std::string argumentsCountError = "Invalid arguments count";
const std::string sameWeekDay = "Same week day";
const std::string differentWeekDay = "Different week day";
const std::string errorMessage = "ERROR";

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
    std::cin >> date1.year;
    std::cin >> date1.month;
    std::cin >> date1.day;

    Date date2;
    std::cin >> date2.year;
    std::cin >> date2.month;
    std::cin >> date2.day;

    args.date1 = date1;
    args.date2 = date2;
    return args;
}

int Zeller(Date date)
{
    //формула Зеллера
    return (date.day + date.month + date.year + 
        date.year / 4 - date.year / 100 + date.year / 400) % 7;
}

int main()
{
    auto args = ParseDates();
    
    if (args.date1.year != args.date2.year)
    {
        std::cout << errorMessage << std::endl;
        return 1;
    }

    int dayOfWeek1 = Zeller(args.date1);
    int dayOfWeek2 = Zeller(args.date2);

    if (dayOfWeek1 == dayOfWeek2)
    {
        std::cout << sameWeekDay << std::endl;
    }
    else 
    {
        std::cout << differentWeekDay << std::endl;
    }
    return 0;
}