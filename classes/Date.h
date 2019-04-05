#ifndef DATE_H
#define DATE_H

class Date
{
public:
    static const int DaysOfMonth[12];
	Date();
    Date(int day, int month, int year);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
	void addDays(int days);
    bool operator ==(const Date &date) const;
    bool operator <(const Date &date) const;
    bool operator >(const Date &date) const;

private:
    int day;
    int month;
    int year;
};

#endif // DATE_H
