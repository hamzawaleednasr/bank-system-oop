#pragma once

#include <ctime>
#include <string>
#include <chrono>
#include <sstream>

using namespace std;

class date
{
public:
    short year, month, day;
    date()
    {
        time_t now = time(0);
        tm timeInfoStorage;
        localtime_s(&timeInfoStorage, &now);

        year = timeInfoStorage.tm_year + 1900;
        month = timeInfoStorage.tm_mon + 1;
        day = timeInfoStorage.tm_mday;

    }
    date(string date)
    {
        // parse date string in format "dd/mm/yyyy"
        size_t p1 = date.find('/');
        size_t p2 = date.find('/', p1 == string::npos ? string::npos : p1 + 1);
        string sday, smonth, syear;
        if (p1 != string::npos && p2 != string::npos)
        {
            sday = date.substr(0, p1);
            smonth = date.substr(p1 + 1, p2 - p1 - 1);
            syear = date.substr(p2 + 1);
        }
        else
        {
            sday = "0"; smonth = "0"; syear = "0";
        }

        year = stoi(syear);
        month = stoi(smonth);
        day = stoi(sday);
    }
    date(short year, short month, short day) : year(year), month(month), day(day) {}
    date(short days, short year) : year(year)
    {
        date temp = getDateFromDayNumber(days, year);

        month = temp.month;
        day = temp.day;
    }

    static std::string getTimeNow()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};
        #ifdef _WIN32
            localtime_s(&localTime, &time);
        #else
            localtime_r(&time, &localTime);
        #endif

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    static date getDateFromDayNumber(int dayNumber, int year)
    {
        date date;
        short remainingDays = dayNumber;
        short monthDays = 0;

        date.year = year;
        date.month = 1;

        while (true)
        {
            monthDays = numberOfDaysInMonth(year, date.month);

            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                date.month++;
            }
            else
            {
                date.day = remainingDays;
                break;
            }
        }

        return date;
    }

    // instance mutator: set this object's month/day from a day number within its year
    void setDateFromDayNumber(int dayNumber)
    {
        date temp = getDateFromDayNumber(dayNumber, year);
        month = temp.month;
        day = temp.day;
    }

    static bool isLeap(int year)
    {
        return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
    }

    bool isLeap()
    {
        return isLeap(year);
    }

    static string getMonthName(int monthNumber)
    {
        switch (monthNumber)
        {
        case 1:
            return "Jan";
        case 2:
            return "Feb";
        case 3:
            return "Mar";
        case 4:
            return "Apr";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "Aug";
        case 9:
            return "Sep";
        case 10:
            return "Oct";
        case 11:
            return "Nov";
        case 12:
            return "Dec";
        }
    }

    string getMonthName()
    {
        return getMonthName(month);
    }

    static int numberOfDaysInMonth(int year, int month)
    {

        if (month > 12 || month < 1)
            return 0;

        if (month == 2)
            return isLeap(year) ? 29 : 28;

        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;

        return 31;
    }

    int numberOfDaysInMonth()
    {
        return numberOfDaysInMonth(year, month);
    }

    // total days from beginning of a year (static) and instance wrapper
    static int totalDaysFromTheBeginningOfYear(int year, int month, int day)
    {
        int days = 0;

        for (int i = 1; i <= month - 1; i++)
        {
            days += numberOfDaysInMonth(year, i);
        }

        days += day;

        return days;
    }

    int totalDaysFromTheBeginningOfYear()
    {
        return totalDaysFromTheBeginningOfYear(year, month, day);
    }

    static int dayNumber(int year, int month, int day)
    {
        int a = ceil((14 - month) / 12);
        int y = year - a;
        int m = month + 12 * a - 2;

        return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    }

    int dayNumber()
    {
        return dayNumber(year, month, day);
    }

    static string toString(date dt)
    {
        string y = to_string(dt.year);
        string m = (dt.month < 10 ? "0" : "") + to_string(dt.month);
        string d = (dt.day < 10 ? "0" : "") + to_string(dt.day);
        return y + "-" + m + "-" + d;
    }

    // add days to a date (static) and instance wrapper
    static date addDaysToDate(int addingDays, date d)
    {
        int remainingDays = addingDays + totalDaysFromTheBeginningOfYear(d.year, d.month, d.day);
        short monthDays = 0;

        d.month = 1;

        while (true)
        {
            monthDays = numberOfDaysInMonth(d.year, d.month);

            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                d.month++;

                if (d.month > 12)
                {
                    d.month = 1;
                    d.year++;
                }
            }
            else
            {
                d.day = remainingDays;
                break;
            }
        }

        return d;
    }

    void addDays(int addingDays)
    {
        date tmp = addDaysToDate(addingDays, *this);
        year = tmp.year;
        month = tmp.month;
        day = tmp.day;
    }

    static bool isTwoDatesEqual(const date& date1, const date& date2)
    {
        return (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
    }

    bool isEqual(const date& other)
    {
        return isTwoDatesEqual(*this, other);
    }

    static bool isMonthTheLast(int month)
    {
        return month == 12;
    }

    bool isMonthTheLast()
    {
        return isMonthTheLast(month);
    }

    static bool isDayTheLast(const date& d)
    {
        return d.day == numberOfDaysInMonth(d.year, d.month);
    }

    bool isDayTheLast()
    {
        return isDayTheLast(*this);
    }

    static bool isDate1BeforeDate2(const date& date1, const date& date2)
    {
        if (date1.year != date2.year)
            return date1.year < date2.year;

        if (date1.month != date2.month)
            return date1.month < date2.month;

        return date1.day < date2.day;
    }

    // instance name made concise for comparing this object to another
    bool isDateBeforeDate2(const date& other)
    {
        return isDate1BeforeDate2(*this, other);
    }

    static int daysBetweenTwoDates(const date& date1, const date& date2)
    {
        int days = 0;

        if (!isDate1BeforeDate2(date1, date2))
            return 0;

        date tmp = date1;
        while (true)
        {
            days += numberOfDaysInMonth(tmp.year, tmp.month);
            tmp.month++;

            if (tmp.month > 12)
            {
                tmp.month = 1;
                tmp.year++;
            }
            if (tmp.year == date2.year && tmp.month == date2.month)
            {
                days += date2.day;
                days -= tmp.day;
                break;
            }
        }

        return days;
    }

    int daysBetween(const date& other)
    {
        return daysBetweenTwoDates(*this, other);
    }

    static int ageInDays(const date& birthDate)
    {
        // get current date
        time_t now_t = time(0);
        tm timeInfoStorage;
        localtime_s(&timeInfoStorage, &now_t);
        date now;
        now.year = timeInfoStorage.tm_year + 1900;
        now.month = timeInfoStorage.tm_mon + 1;
        now.day = timeInfoStorage.tm_mday;

        return daysBetweenTwoDates(birthDate, now);
    }

    int ageInDays()
    {
        return ageInDays(*this);
    }
};