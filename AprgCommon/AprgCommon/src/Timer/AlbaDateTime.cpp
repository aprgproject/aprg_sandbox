#include "AlbaDateTime.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Debug/AlbaDebug.hpp>

#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

namespace alba
{

AlbaDateTime::AlbaDateTime()
    : m_yearMonthDay(0)
    , m_hourMinuteSecond(0)
    , m_microseconds(0)
{}

AlbaDateTime::AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
    : m_yearMonthDay(mergeYearMonthDay(years, months, days))
    , m_hourMinuteSecond(mergeHourMinuteSecond(hours, minutes, seconds))
    , m_microseconds(microseconds)
{}

void AlbaDateTime::setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
{
    m_yearMonthDay = mergeYearMonthDay(years, months, days);
    m_hourMinuteSecond = mergeHourMinuteSecond(hours, minutes, seconds);
    m_microseconds = microseconds;

}

bool AlbaDateTime::isEmpty() const
{
    return (m_yearMonthDay|m_hourMinuteSecond|m_microseconds)==0;
}

unsigned int AlbaDateTime::getYears() const
{
    return ((unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<3>(m_yearMonthDay)<<AlbaBitConstants::BYTE_SIZE_IN_BITS) | AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<2>(m_yearMonthDay);
}

unsigned int AlbaDateTime::getMonths() const
{
    return (unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<1>(m_yearMonthDay);
}

unsigned int AlbaDateTime::getDays() const
{
    return (unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<0>(m_yearMonthDay);
}

unsigned int AlbaDateTime::getHours() const
{
    return (unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<2>(m_hourMinuteSecond);
}

unsigned int AlbaDateTime::getMinutes() const
{
    return (unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<1>(m_hourMinuteSecond);
}

unsigned int AlbaDateTime::getSeconds() const
{
    return (unsigned int)AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<0>(m_hourMinuteSecond);
}

unsigned int AlbaDateTime::getTotalDays() const
{

}

unsigned int AlbaDateTime::getMicroSeconds() const
{
    return m_microseconds;
}

string AlbaDateTime::getPrintableStringFormat1() const
{
    stringstream ss;
    ss << setfill('0');    ss << setw(4) << getYears() << "-";
    ss << setw(2) << getMonths() << "-";
    ss << setw(2) << getDays() << " ";
    ss << setw(2) << getHours() << ":";
    ss << setw(2) << getMinutes() << ":";
    ss << setw(2) << getSeconds() << ".";
    ss << setw(6) << getMicroSeconds();
    return ss.str();}

bool AlbaDateTime::operator<(AlbaDateTime const& btsLogTimeToCompare) const
{
    bool result(false);
    if(m_yearMonthDay < btsLogTimeToCompare.m_yearMonthDay) result = true;
    else if(m_yearMonthDay > btsLogTimeToCompare.m_yearMonthDay) result = false;
    else if(m_hourMinuteSecond < btsLogTimeToCompare.m_hourMinuteSecond) result = true;
    else if(m_hourMinuteSecond > btsLogTimeToCompare.m_hourMinuteSecond) result = false;
    else if(m_microseconds < btsLogTimeToCompare.m_microseconds) result = true;
    else if(m_microseconds > btsLogTimeToCompare.m_microseconds) result = false;
    return result;
}

bool AlbaDateTime::operator>(AlbaDateTime const& btsLogTimeToCompare) const
{
    bool result(false);
    if(m_yearMonthDay < btsLogTimeToCompare.m_yearMonthDay) result = false;
    else if(m_yearMonthDay > btsLogTimeToCompare.m_yearMonthDay) result = true;
    else if(m_hourMinuteSecond < btsLogTimeToCompare.m_hourMinuteSecond) result = false;
    else if(m_hourMinuteSecond > btsLogTimeToCompare.m_hourMinuteSecond) result = true;
    else if(m_microseconds < btsLogTimeToCompare.m_microseconds) result = false;
    else if(m_microseconds > btsLogTimeToCompare.m_microseconds) result = true;
    return result;
}

bool AlbaDateTime::operator==(AlbaDateTime const& btsLogTimeToCompare) const
{
    bool result(true);
    if(m_yearMonthDay != btsLogTimeToCompare.m_yearMonthDay) result = false;
    else if(m_hourMinuteSecond != btsLogTimeToCompare.m_hourMinuteSecond) result = false;
    else if(m_microseconds != btsLogTimeToCompare.m_microseconds) result = false;
    return result;
}

bool AlbaDateTime::operator!=(AlbaDateTime const& btsLogTimeToCompare) const{
    return !((*this)==btsLogTimeToCompare);
}

AlbaDateTime AlbaDateTime::operator+(AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime dateTimeCopy(*this);
    dateTimeCopy.m_yearMonthDay += secondDateTime.m_yearMonthDay;
    dateTimeCopy.m_hourMinuteSecond += secondDateTime.m_hourMinuteSecond;
    dateTimeCopy.m_microseconds += secondDateTime.m_microseconds;
    dateTimeCopy.reorganizeOverflowValues();
    return dateTimeCopy;
}

AlbaDateTime AlbaDateTime::operator-(AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime dateTimeCopy(*this);
    dateTimeCopy.m_yearMonthDay += secondDateTime.m_yearMonthDay;
    dateTimeCopy.m_hourMinuteSecond += secondDateTime.m_hourMinuteSecond;
    dateTimeCopy.m_microseconds += secondDateTime.m_microseconds;
    return dateTimeCopy;
}

bool AlbaDateTime::isLeapYear(unsigned int const year) const
{
    bool result(true);
    if (year%4 != 0) result = false;
    else if (year%100 != 0) result = true;
    else if (year%400 != 0) result = false;
    return result;
}

unsigned int AlbaDateTime::getMaximumDaysInAMonth(unsigned int const monthIndex, unsigned int const year) const
{
    unsigned int maximumDaysOfTheMonth=31;
    if(monthIndex==3 || monthIndex==5 || monthIndex==8 || monthIndex==10)
    {
        maximumDaysOfTheMonth=30;
    }
    else if(monthIndex==1)
    {
        if(isLeapYear(year))
        {
            maximumDaysOfTheMonth=29;
        }
        else
        {
            maximumDaysOfTheMonth=28;
        }
    }
    return maximumDaysOfTheMonth;
}

unsigned int AlbaDateTime::getNumberOfLeapYearsBeforeThisYear(unsigned int const year)
{
    unsigned numberOfLeapYears(0);
    if(year>0)
    {
        unsigned beforeThisYear = year-1;
        numberOfLeapYears = (beforeThisYear/4)-(beforeThisYear/100)+(beforeThisYear/400)+1;
    }
    return numberOfLeapYears;
}

unsigned int AlbaDateTime::getDaysInTheYearBeforeThisMonth(unsigned int const monthIndex, unsigned int const year) const
{
    unsigned int maximumDaysOfTheMonth=0;
    switch(monthIndex)
    {
    case 0: maximumDaysOfTheMonth=0; break;
    case 1: maximumDaysOfTheMonth=31; break;
    case 2: maximumDaysOfTheMonth=59; break;
    case 3: maximumDaysOfTheMonth=90; break;
    case 4: maximumDaysOfTheMonth=120; break;
    case 5: maximumDaysOfTheMonth=151; break;
    case 6: maximumDaysOfTheMonth=181; break;
    case 7: maximumDaysOfTheMonth=212; break;
    case 8: maximumDaysOfTheMonth=243; break;
    case 9: maximumDaysOfTheMonth=273; break;
    case 10: maximumDaysOfTheMonth=304; break;
    case 11: maximumDaysOfTheMonth=334; break;
    default : maximumDaysOfTheMonth=0; break;
    }
    return maximumDaysOfTheMonth;
}

unsigned int AlbaDateTime::mergeYearMonthDay(unsigned short int const years, unsigned char const months, unsigned char const days) const
{
    return ((unsigned int)years<<(AlbaBitConstants::BYTE_SIZE_IN_BITS*2)) | ((unsigned int)months<<AlbaBitConstants::BYTE_SIZE_IN_BITS) | days;
}

unsigned int AlbaDateTime::mergeHourMinuteSecond(unsigned char const hours, unsigned char const minutes, unsigned char const seconds) const
{
    return ((unsigned int)hours<<(AlbaBitConstants::BYTE_SIZE_IN_BITS*2)) | ((unsigned int)minutes<<AlbaBitConstants::BYTE_SIZE_IN_BITS) | seconds;
}

void AlbaDateTime::reorganizeOverflowValues()
{
    unsigned int years(getYears());
    unsigned int months(getMonths());
    unsigned int days(getDays());
    unsigned int hours(getHours());
    unsigned int minutes(getMinutes());
    unsigned int seconds(getSeconds());
    unsigned int microseconds(getMicroSeconds());

    seconds += microseconds/1000000;
    microseconds = microseconds%1000000;
    minutes += seconds/60;
    seconds = seconds%60;
    hours += minutes/60;
    minutes = minutes%60;
    days += hours/24;
    hours = hours%24;

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = years - 1900;
    timeinfo->tm_mon = months - 1;
    timeinfo->tm_mday = days;
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    mktime ( timeinfo );
    ALBA_DEBUG_PRINT1(getPrintableStringFormat1());
    setTime(timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday, hours, minutes, seconds, microseconds);
    ALBA_DEBUG_PRINT1(getPrintableStringFormat1());
}

void AlbaDateTime::reorganizeUnderflowValues()
{
    /*while(m_microseconds < 0)    {
        m_seconds--;
        m_microseconds += 1000000;
    }
    while(m_seconds < 0)
    {
        m_days--;
        m_seconds += 86400;
    }*/
}

}//namespace alba
