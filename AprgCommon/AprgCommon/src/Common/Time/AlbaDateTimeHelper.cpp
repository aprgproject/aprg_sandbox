#include "AlbaDateTimeHelper.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <cmath>

using namespace alba::AlbaDateTimeConstants;
using namespace std;

namespace alba
{

bool dateTimeHelper::isLeapYear(unsigned int const year)
{
    bool result(true);
    if (year%4 != 0) result = false;
    else if (year%100 != 0) result = true;
    else if (year%400 != 0) result = false;
    return result;
}

unsigned int dateTimeHelper::getNumberOfDaysInAYear(unsigned int const year)
{
    unsigned int numberOfDays=0;
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

unsigned int dateTimeHelper::getNumberOfDaysInAMonth(unsigned int const monthIndex, unsigned int const year)
{
    unsigned int numberOfDays=31;
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

unsigned int dateTimeHelper::getNumberOfLeapYearsBeforeThisYear(unsigned int const year)
{
    unsigned numberOfLeapYears(0);
    if(year>0)
    {
        unsigned beforeThisYear = year-1;
        numberOfLeapYears = (beforeThisYear/4)-(beforeThisYear/100)+(beforeThisYear/400)+1;
    }
    return numberOfLeapYears;
}

unsigned int dateTimeHelper::getNumberOfDaysInTheYearBeforeThisMonth(unsigned int const monthIndex, unsigned int const year)
{
    unsigned int numberOfDays=0;
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

unsigned int dateTimeHelper::getMonthFromNumberOfDaysInANonLeapYear(unsigned int const numberOfDays)
{
    unsigned int monthIndex=0;
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

unsigned int dateTimeHelper::getMonthFromNumberOfDaysInALeapYear(unsigned int const numberOfDays)
{
    unsigned int monthIndex=0;
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

unsigned int dateTimeHelper::getMonthFromNumberOfDays(unsigned int const numberOfDays, unsigned int const year)
{
    unsigned int monthIndex=0;
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

unsigned int dateTimeHelper::getNumberOfDaysBeforeThisYear(unsigned int const year)
{
    unsigned int numberOfDays=0;
    if(year>0)
    {
        numberOfDays = year*NUMBER_OF_DAYS_IN_NON_LEAP_YEAR + getNumberOfLeapYearsBeforeThisYear(year);
    }
    return numberOfDays;
}

unsigned int dateTimeHelper::getTotalDays(unsigned int const years, unsigned int const monthIndex, unsigned int const days)
{
    return getNumberOfDaysBeforeThisYear(years) + getNumberOfDaysInTheYearBeforeThisMonth(monthIndex, years) + days;
}

unsigned int dateTimeHelper::getTotalSeconds(unsigned int const hours, unsigned int const minutes, unsigned int const seconds)
{
    return (hours*NUMBER_OF_SECONDS_IN_AN_HOUR) + (minutes*NUMBER_OF_SECONDS_IN_A_MINUTE) + seconds;
}

void dateTimeHelper::reorganizeOverflowValues(unsigned int & totalDays, unsigned int & totalSeconds, unsigned int & totalMicroSeconds)
{
    totalSeconds += totalMicroSeconds/NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalMicroSeconds = totalMicroSeconds%NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalDays += totalSeconds/NUMBER_OF_SECONDS_IN_A_DAY;
    totalSeconds = totalSeconds%NUMBER_OF_SECONDS_IN_A_DAY;
}

void dateTimeHelper::reorganizeUnderflowValues(int & totalDays, int & totalSeconds, int & totalMicroSeconds)
{
    if(totalMicroSeconds<0)
    {
        int neededSeconds = static_cast<int>((ceil((static_cast<double>(-1)*totalMicroSeconds)/NUMBER_OF_MICROSECONDS_IN_A_SECOND)));
        totalSeconds -= neededSeconds;
        totalMicroSeconds += neededSeconds * static_cast<int>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    }
    if(totalSeconds<0)
    {
        int neededDays = static_cast<int>((ceil((static_cast<double>(-1)*totalSeconds)/NUMBER_OF_SECONDS_IN_A_DAY)));
        totalDays -= neededDays;
        totalSeconds += neededDays * static_cast<int>(NUMBER_OF_SECONDS_IN_A_DAY);
    }
}

unsigned int dateTimeHelper::retrieveAndRemoveYearsFromTotalDays(unsigned int & remainingDays)
{
    unsigned int years(remainingDays/NUMBER_OF_DAYS_IN_NON_LEAP_YEAR);
    int remainingDaysTemp = static_cast<int>(remainingDays)-static_cast<int>(getNumberOfDaysBeforeThisYear(years));
    while(remainingDaysTemp<=0 && years>0)
    {
        years--;
        remainingDaysTemp += static_cast<int>(getNumberOfDaysInAYear(years));
    }
    remainingDays=static_cast<unsigned int>(remainingDaysTemp);
    return years;
}

unsigned int dateTimeHelper::retrieveAndRemoveMonthsFromTotalDays(unsigned int & remainingDays, unsigned int const year)
{
    unsigned int monthIndex(getMonthFromNumberOfDays(remainingDays, year));
    remainingDays-=getNumberOfDaysInTheYearBeforeThisMonth(monthIndex, year);
    return monthIndex;
}

unsigned int dateTimeHelper::retrieveAndRemoveHoursFromTotalSeconds(unsigned int & remainingSeconds)
{
    unsigned int hours = remainingSeconds/NUMBER_OF_SECONDS_IN_AN_HOUR;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_AN_HOUR;
    return hours;
}

unsigned int dateTimeHelper::retrieveAndRemoveMinutesFromTotalSeconds(unsigned int & remainingSeconds)
{
    unsigned int minutes = remainingSeconds/NUMBER_OF_SECONDS_IN_A_MINUTE;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_A_MINUTE;
    return minutes;
}

}//namespace alba
