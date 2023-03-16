#include "AlbaDateTimeHelper.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <array>
#include <cmath>

using namespace alba::AlbaDateTimeConstants;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

bool dateTimeHelper::isLeapYear(uint32_t const year)
{
    bool result(true);
    if (!isDivisible(year, 4U)) result = false;
    else if (!isDivisible(year, 100U)) result = true;
    else if (!isDivisible(year, 400U)) result = false;
    return result;
}

uint32_t dateTimeHelper::getNumberOfDaysInAYear(uint32_t const year)
{
    return isLeapYear(year) ? NUMBER_OF_DAYS_IN_LEAP_YEAR : NUMBER_OF_DAYS_IN_NON_LEAP_YEAR;
}

uint32_t dateTimeHelper::getNumberOfDaysInAMonth(uint32_t const month, uint32_t const year)
{
    uint32_t numberOfDays(0);
    if(month==April || month==June || month==September || month==November)
    {
        numberOfDays=30;
    }
    else if(month==February)
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
    else if(month>0)
    {
        numberOfDays=31;
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getNumberOfLeapYearsBeforeThisYear(uint32_t const year)
{
    uint32_t numberOfLeapYears(0);
    if(year>0)
    {
        unsigned beforeThisYear = year-1;
        numberOfLeapYears = (beforeThisYear/4)-(beforeThisYear/100)+(beforeThisYear/400)+1;
    }
    return numberOfLeapYears;
}

uint32_t dateTimeHelper::getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const month, uint32_t const year)
{
    uint32_t numberOfDays(0);
    switch(month)
    {
    case January: numberOfDays=0; break;
    case February: numberOfDays=31; break;
    case March: numberOfDays=59; break;
    case April: numberOfDays=90; break;
    case May: numberOfDays=120; break;
    case June: numberOfDays=151; break;
    case July: numberOfDays=181; break;
    case August: numberOfDays=212; break;
    case September: numberOfDays=243; break;
    case October: numberOfDays=273; break;
    case November: numberOfDays=304; break;
    case December: numberOfDays=334; break;
    default : numberOfDays=0; break;
    }
    if(month>February && year>0 && isLeapYear(year))
    {
        numberOfDays++;
    }
    return numberOfDays;
}

uint32_t dateTimeHelper::getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays)
{
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    auto itMonth = lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(January) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t dateTimeHelper::getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays)
{
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    auto itMonth = lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(January) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t dateTimeHelper::getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year)
{
    uint32_t result(0);
    if(numberOfDays>0)
    {
        result = isLeapYear(year) ? getMonthFromNumberOfDaysInALeapYear(numberOfDays)
                                 : getMonthFromNumberOfDaysInANonLeapYear(numberOfDays);
    }
    return result;
}

uint32_t dateTimeHelper::getNumberOfDaysBeforeThisYear(uint32_t const year)
{
    return year*NUMBER_OF_DAYS_IN_NON_LEAP_YEAR + getNumberOfLeapYearsBeforeThisYear(year);
}

uint32_t dateTimeHelper::getTotalDays(uint32_t const years, uint32_t const month, uint32_t const days)
{
    return getNumberOfDaysBeforeThisYear(years) + getNumberOfDaysInTheYearBeforeThisMonth(month, years) + days;
}

uint32_t dateTimeHelper::getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds)
{
    return (hours*NUMBER_OF_SECONDS_IN_AN_HOUR) + (minutes*NUMBER_OF_SECONDS_IN_A_MINUTE) + seconds;
}

uint32_t dateTimeHelper::getAndRemoveYearsFromNumberOfDays(uint32_t & remainingDays)
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

uint32_t dateTimeHelper::getAndRemoveMonthsFromNumberOfDays(uint32_t & remainingDays, uint32_t const year)
{
    uint32_t month(getMonthFromNumberOfDays(remainingDays, year));
    remainingDays-=getNumberOfDaysInTheYearBeforeThisMonth(month, year);
    return month;
}

uint32_t dateTimeHelper::getAndRemoveHoursFromNumberOfSeconds(uint32_t & remainingSeconds)
{
    uint32_t hours = remainingSeconds/NUMBER_OF_SECONDS_IN_AN_HOUR;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_AN_HOUR;
    return hours;
}

uint32_t dateTimeHelper::getAndRemoveMinutesFromNumberOfSeconds(uint32_t & remainingSeconds)
{
    uint32_t minutes = remainingSeconds/NUMBER_OF_SECONDS_IN_A_MINUTE;
    remainingSeconds = remainingSeconds%NUMBER_OF_SECONDS_IN_A_MINUTE;
    return minutes;
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
        int32_t neededSeconds = (totalMicroSeconds*-1 + NUMBER_OF_MICROSECONDS_IN_A_SECOND-1)/NUMBER_OF_MICROSECONDS_IN_A_SECOND;
        totalSeconds -= neededSeconds;
        totalMicroSeconds += neededSeconds * static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    }
    if(totalSeconds<0)
    {
        int32_t neededDays = (totalSeconds*-1 + NUMBER_OF_SECONDS_IN_A_DAY-1)/NUMBER_OF_SECONDS_IN_A_DAY;
        totalDays -= neededDays;
        totalSeconds += neededDays * static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY);
    }
}

}//namespace alba
