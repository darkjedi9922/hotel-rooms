#include "Date.h"
#include <string>
using namespace std;

const int Date::DaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date()
{
	day = 1;
	month = 1;
	year = 1;
}
Date::Date(int day, int month, int year)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}
int Date::getDay() const
{
    return day;
}
int Date::getMonth() const
{
    return month;
}
int Date::getYear() const
{
    return year;
}
void Date::setDay(int day)
{
    if (day < 1 || day > DaysOfMonth[month - 1]) throw (string)"Значение дня некорректно";
    this->day = day;
}
void Date::setMonth(int month)
{
    if (month < 1 || month > 12) throw (string)"Значение месяца некорректно";
    this->month = month;
}
void Date::setYear(int year)
{
    if (year < 1) throw (string)"Значение года некорректно";
    this->year = year;
}
void Date::addDays(int days)
{
	while (days + day > DaysOfMonth[month - 1])
	{
		days -= DaysOfMonth[month - 1];
		if (month == 12) 
		{
			year++;
			month = 1;
		} 
		else month++;
	}
	day += days;
}
bool Date::operator ==(const Date &date) const
{
    if (day == date.day && month == date.month && year == date.year) return true;
    else return false;
}
bool Date::operator <(const Date &date) const
{
    if (year < date.year) return true;
    else if (year == date.year && month < date.month) return true;
    else if (year == date.year && month == date.month && day < date.day) return true;
    else return false;
}
bool Date::operator >(const Date &date) const
{
    if (year > date.year) return true;
    else if (year == date.year && month > date.month) return true;
    else if (year == date.year && month == date.month && day > date.day) return true;
    else return false;
}