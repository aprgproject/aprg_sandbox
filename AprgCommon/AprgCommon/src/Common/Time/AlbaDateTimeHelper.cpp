#include "AlbaDateTimeHelper.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <cmath>

using namespace alba::AlbaDateTimeConstants;
using namespace std;

namespace alba
{

bool dateTimeHelper::isLeapYear(uint32_t const year)
{
    bool result(true);
    if (year%4 != 0) result = false;
    else if (year%100 != 0) result = true;
    else if (year%400 != 0) result = false;
    return result;
}

uint32_t dateTimeHelper::getNumberOfDaysInAYear(uint32_t const year)
{
    uint32_t numberOfDays=0;
    if(isLeapYear(year))
    {
        numberOfDays=NUMBER_OF_DAYS_IN_LEAP_YEAR;
    }
    else
    {
        numberOfDays=NUMBER_OF_DAYS_IN_NON_LEAP_YEAR;
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getNumberOfDaysInAMonth(uint32_t const monthIndex, uint32_t const year)
{
    uint32_t numberOfDays=31;
    if(monthIndex==3 || monthIndex==5 || monthIndex==8 || monthIndex==10)
    {
        numberOfDays=30;
    }
    else if(monthIndex==1)
    {
        if(isLeapYear(year))
        {
            numberOfDays=29;
        }
        else
        {
            numberOfDays=28;
        }
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getNumberOfLeapYearsBeforeThisYear(uint32_t const year)
{
    unsigned numberOfLeapYears(0);
    if(year>0)
    {
        unsigned beforeThisYear = year-1;
        numberOfLeapYears = (beforeThisYear/4)-(beforeThisYear/100)+(beforeThisYear/400)+1;
    }
    return numberOfLeapYears;
}

uint32_t dateTimeHelper::getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const monthIndex, uint32_t const year)
{
    uint32_t numberOfDays=0;
    switch(monthIndex)
    {
    case 0: numberOfDays=0; break;
    case 1: numberOfDays=31; break;
    case 2: numberOfDays=59; break;
    case 3: numberOfDays=90; break;
    case 4: numberOfDays=120; break;
    case 5: numberOfDays=151; break;
    case 6: numberOfDays=181; break;
    case 7: numberOfDays=212; break;
    case 8: numberOfDays=243; break;
    case 9: numberOfDays=273; break;
    case 10: numberOfDays=304; break;
    case 11: numberOfDays=334; break;
    default : numberOfDays=0; break;
    }
    if(monthIndex>1 && year!=0 && isLeapYear(year))
    {
        numberOfDays++;
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays)
{
    uint32_t monthIndex=0;
    if(numberOfDays>334)
    {
        monthIndex=11;
    }
    else if(numberOfDays>304)
    {
        monthIndex=10;
    }
    else if(numberOfDays>273)
    {
        monthIndex=9;
    }
    else if(numberOfDays>243)
    {
        monthIndex=8;
    }
    else if(numberOfDays>212)
    {
        monthIndex=7;
    }
    else if(numberOfDays>181)
    {
        monthIndex=6;
    }
    else if(numberOfDays>151)
    {
        monthIndex=5;
    }
    else if(numberOfDays>120)
    {
        monthIndex=4;
    }
    else if(numberOfDays>90)
    {
        monthIndex=3;
    }
    else if(numberOfDays>59)
    {
        monthIndex=2;
    }
    else if(numberOfDays>31)
    {
        monthIndex=1;
    }
    return monthIndex;
}

uint32_t dateTimeHelper::getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays)
{
    uint32_t monthIndex=0;
    if(numberOfDays>335)
    {
        monthIndex=11;
    }
    else if(numberOfDays>305)
    {
        monthIndex=10;
    }
    else if(numberOfDays>274)
    {
        monthIndex=9;
    }
    else if(numberOfDays>244)
    {
        monthIndex=8;
    }
    else if(numberOfDays>213)
    {
        monthIndex=7;
    }
    else if(numberOfDays>182)
    {
        monthIndex=6;
    }
    else if(numberOfDays>152)
    {
        monthIndex=5;
    }
    else if(numberOfDays>121)
    {
        monthIndex=4;
    }
    else if(numberOfDays>91)
    {
        monthIndex=3;
    }
    else if(numberOfDays>60)
    {
        monthIndex=2;
    }
    else if(numberOfDays>31)
    {
        monthIndex=1;
    }
    return monthIndex;
}

uint32_t dateTimeHelper::getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year)
{
    uint32_t monthIndex=0;
    if(isLeapYear(year))
    {
        monthIndex=getMonthFromNumberOfDaysInALeapYear(numberOfDays);
    }
    else
    {
        monthIndex=getMonthFromNumberOfDaysInANonLeapYear(numberOfDays);
    }
    return monthIndex;
}

uint32_t dateTimeHelper::getNumberOfDaysBeforeThisYear(uint32_t const year)
{
    uint32_t numberOfDays=0;
    if(year>0)
    {
        numberOfDays = year*NUMBER_OF_DAYS_IN_NON_LEAP_YEAR + getNumberOfLeapYearsBeforeThisYear(year);
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getTotalDays(uint32_t const years, uint32_t const monthIndex, uint32_t const days)
{
    return getNumberOfDaysBeforeThisYear(years) + getNumberOfDaysInTheYearBeforeThisMonth(monthIndex, years) + days;
}

uint32_t dateTimeHelper::getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds)
{
    return (hours*NUMBER_OF_SECONDS_IN_AN_HOUR) + (minutes*NUMBER_OF_SECONDS_IN_A_MINUTE) + seconds;
}

void dateTimeHelper::reorganizeOverflowValues(uint32_t & totalDays, uint32_t & totalSeconds, uint32_t & totalMicroSeconds)
{
    totalSeconds += totalMicroSeconds/NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalMicroSeconds = totalMicroSeconds%NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalDays += totalSeconds/NUMBER_OF_SECONDS_IN_A_DAY;
    totalSeconds = totalSeconds%NUMBER_OF_SECONDS_IN_A_DAY;
}

void dateTimeHelper::reorganizeUnderflowValues(int32_t & totalDays, int32_t & totalSeconds, int32_t & totalMicroSeconds)
{
    if(totalMicroSeconds<0)
    {
        int32_t neededSeconds = static_cast<int32_t>((ceil((static_cast<double>(-1)*totalMicroSeconds)/NUMBER_OF_MICROSECONDS_IN_A_SECOND)));
        totalSeconds -= neededSeconds;
        totalMicroSeconds += neededSeconds * static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    }
    if(totalSeconds<0)
    {
        int32_t neededDays = static_cast<int32_t>((ceil((static_cast<double>(-1)*totalSeconds)/NUMBER_OF_SECONDS_IN_A_DAY)));
        totalDays -= neededDays;
        totalSeconds += neededDays * static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY);
    }
}

uint32_t dateTimeHelper::retrieveAndRemoveYearsFromTotalDays(uint32_t & remainingDays)
{
    uint32_t years(remainingDays/NUMBER_OF_DAYS_IN_NON_LEAP_YEAR);
    int32_t remainingDaysTemp = static_cast<int32_t>(remainingDays)-static_cast<int32_t>(getNumberOfDaysBeforeThisYear(years));
    while(remainingDaysTemp<=0 && years>0)
    {
        years--;
        remainingDaysTemp += static_cast<int32_t>(getNumberOfDaysInAYear(years));
    }
    remainingDays=static_cast<uint32_t>(remainingDaysTemp);
    return years;
}

uint32_t dateTimeHelper::retrieveAndRemoveMonthsFromTotalDays(uint32_t & remainingDays, uint32_t const year)
{
    uint32_t monthIndex(getMonthFromNumberOfDays(remainingDays, year));
    remainingDays-=getNumberOfDaysInTheYearBeforeThisMonth(monthIndex, year);
    return monthIndex;
}

uint32_t dateTimeHelper::retrieveAndRemoveHoursFromTotalSeconds(uint32_t & remainingSeconds)
{
    uint32_t hours = remainingSeconds/NUMBER_OF_SECONDS_IN_AN_HOUR;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_AN_HOUR;
    return hours;
}

uint32_t dateTimeHelper::retrieveAndRemoveMinutesFromTotalSeconds(uint32_t & remainingSeconds)
{
    uint32_t minutes = remainingSeconds/NUMBER_OF_SECONDS_IN_A_MINUTE;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_A_MINUTE;
    return minutes;
}

}//namespace alba
