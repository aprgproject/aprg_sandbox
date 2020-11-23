#pragma once

#include <string>
#include <ctime>

namespace alba
{

class AlbaDateTime
{
public:
    AlbaDateTime();
    AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
    void setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
    bool isEmpty() const;
    unsigned int  getYears() const;
    unsigned int  getMonths() const;
    unsigned int  getDays() const;
    unsigned int  getHours() const;
    unsigned int  getMinutes() const;
    unsigned int  getSeconds() const;
    unsigned int  getMicroSeconds() const;
    unsigned int  getTotalDays() const;
    std::string getPrintableStringFormat1() const; //YYYY-MM-DD HH:MM:SS.MMMMMM
    bool operator<(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator>(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator==(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator!=(AlbaDateTime const& btsLogTimeToCompare) const;
    AlbaDateTime operator+(AlbaDateTime const& btsLogTime) const;
    AlbaDateTime operator-(AlbaDateTime const& btsLogTime) const;
    bool isLeapYear(unsigned int const year) const;
    unsigned int getMaximumDaysInAMonth(unsigned int const monthIndex, unsigned int const year) const;
    unsigned int getNumberOfLeapYearsBeforeThisYear(unsigned int const year);
    unsigned int getDaysInTheYearBeforeThisMonth(unsigned int const monthIndex, unsigned int const year) const;
    unsigned int mergeYearMonthDay(unsigned short int const years, unsigned char const months, unsigned char const days) const;
    unsigned int mergeHourMinuteSecond(unsigned char const hours, unsigned char const minutes, unsigned char const seconds) const;
private:
    void reorganizeOverflowValues();
    void reorganizeUnderflowValues();
    unsigned int m_yearMonthDay;
    unsigned int m_hourMinuteSecond;
    unsigned int m_microseconds;
};

}//namespace alba
