#include "AlbaDateTimeHelper.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <array>
#include <cmath>

using namespace alba::AlbaDateTimeConstants;
using namespace alba::mathHelper;
using namespace std;

namespace alba::dateTimeHelper {

bool isLeapYear(uint32_t const year) {
    bool result(true);
    if (!isDivisible(year, 4U))
        result = false;
    else if (!isDivisible(year, 100U))
        result = true;
    else if (!isDivisible(year, 400U))
        result = false;
    return result;
}

uint32_t getNumberOfDaysInAYear(uint32_t const year) {
    return isLeapYear(year) ? NUMBER_OF_DAYS_IN_LEAP_YEAR : NUMBER_OF_DAYS_IN_NON_LEAP_YEAR;
}

uint32_t getNumberOfDaysInAMonth(uint32_t const month, uint32_t const year) {
    uint32_t numberOfDays(0);
    if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) {
        numberOfDays = 30;
    } else if (month == FEBRUARY) {
        if (isLeapYear(year)) {
            numberOfDays = 29;
        } else {
            numberOfDays = 28;
        }
    } else if (month > 0) {
        numberOfDays = 31;
    }
    return numberOfDays;
}

uint32_t getNumberOfLeapYearsBeforeThisYear(uint32_t const year) {
    uint32_t numberOfLeapYears(0);
    if (year > 0) {
        auto beforeThisYear = year - 1;
        numberOfLeapYears = (beforeThisYear / 4) - (beforeThisYear / 100) + (beforeThisYear / 400) + 1;
    }
    return numberOfLeapYears;
}

uint32_t getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const month, uint32_t const year) {
    uint32_t numberOfDays(0);
    switch (month) {
        case JANUARY:
            numberOfDays = 0;
            break;
        case FEBRUARY:
            numberOfDays = 31;
            break;
        case MARCH:
            numberOfDays = 59;
            break;
        case APRIL:
            numberOfDays = 90;
            break;
        case MAY:
            numberOfDays = 120;
            break;
        case JUNE:
            numberOfDays = 151;
            break;
        case JULY:
            numberOfDays = 181;
            break;
        case AUGUST:
            numberOfDays = 212;
            break;
        case SEPTEMBER:
            numberOfDays = 243;
            break;
        case OCTOBER:
            numberOfDays = 273;
            break;
        case NOVEMBER:
            numberOfDays = 304;
            break;
        case DECEMBER:
            numberOfDays = 334;
            break;
        default:
            numberOfDays = 0;
            break;
    }
    if (month > FEBRUARY && year > 0 && isLeapYear(year)) {
        numberOfDays++;
    }
    return numberOfDays;
}

uint32_t getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays) {
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    auto itMonth = lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(JANUARY) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays) {
    constexpr array<uint32_t, 11> accumulatedDaysForEachMonth{31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    auto itMonth = lower_bound(accumulatedDaysForEachMonth.cbegin(), accumulatedDaysForEachMonth.cend(), numberOfDays);
    return static_cast<uint32_t>(JANUARY) + distance(accumulatedDaysForEachMonth.cbegin(), itMonth);
}

uint32_t getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year) {
    uint32_t result(0);
    if (numberOfDays > 0) {
        result = isLeapYear(year) ? getMonthFromNumberOfDaysInALeapYear(numberOfDays)
                                  : getMonthFromNumberOfDaysInANonLeapYear(numberOfDays);
    }
    return result;
}

uint32_t getNumberOfDaysBeforeThisYear(uint32_t const year) {
    return year * NUMBER_OF_DAYS_IN_NON_LEAP_YEAR + getNumberOfLeapYearsBeforeThisYear(year);
}

uint32_t getTotalDays(uint32_t const years, uint32_t const month, uint32_t const days) {
    return getNumberOfDaysBeforeThisYear(years) + getNumberOfDaysInTheYearBeforeThisMonth(month, years) + days;
}

uint32_t getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds) {
    return (hours * NUMBER_OF_SECONDS_IN_AN_HOUR) + (minutes * NUMBER_OF_SECONDS_IN_A_MINUTE) + seconds;
}

DayOfTheWeek getDayOfTheWeek(uint32_t const years, uint32_t const month, uint32_t const days) {
    // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
    // Based from Sakamoto Methods
    // 1 <= month <= 12,  years > 1752 (in the U.K.)

    uint32_t yearValue = years;
    static constexpr uint32_t monthOffset[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    yearValue -= month < 3;
    return static_cast<DayOfTheWeek>(
        (yearValue + yearValue / 4 - yearValue / 100 + yearValue / 400 + monthOffset[month - 1] + days) % 7);
}

uint32_t getAndRemoveYearsFromNumberOfDays(uint32_t& remainingDays) {
    uint32_t years(remainingDays / NUMBER_OF_DAYS_IN_NON_LEAP_YEAR);
    int32_t remainingDaysTemp =
        static_cast<int32_t>(remainingDays) - static_cast<int32_t>(getNumberOfDaysBeforeThisYear(years));
    while (remainingDaysTemp <= 0 && years > 0) {
        years--;
        remainingDaysTemp += static_cast<int32_t>(getNumberOfDaysInAYear(years));
    }
    remainingDays = static_cast<uint32_t>(remainingDaysTemp);
    return years;
}

uint32_t getAndRemoveMonthsFromNumberOfDays(uint32_t& remainingDays, uint32_t const year) {
    uint32_t month(getMonthFromNumberOfDays(remainingDays, year));
    remainingDays -= getNumberOfDaysInTheYearBeforeThisMonth(month, year);
    return month;
}

uint32_t getAndRemoveHoursFromNumberOfSeconds(uint32_t& remainingSeconds) {
    uint32_t hours = remainingSeconds / NUMBER_OF_SECONDS_IN_AN_HOUR;
    remainingSeconds = remainingSeconds % NUMBER_OF_SECONDS_IN_AN_HOUR;
    return hours;
}

uint32_t getAndRemoveMinutesFromNumberOfSeconds(uint32_t& remainingSeconds) {
    uint32_t minutes = remainingSeconds / NUMBER_OF_SECONDS_IN_A_MINUTE;
    remainingSeconds = remainingSeconds % NUMBER_OF_SECONDS_IN_A_MINUTE;
    return minutes;
}

void reorganizeOverflowValues(uint32_t& totalDays, uint32_t& totalSeconds, uint32_t& totalMicroSeconds) {
    totalSeconds += totalMicroSeconds / NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalMicroSeconds = totalMicroSeconds % NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    totalDays += totalSeconds / NUMBER_OF_SECONDS_IN_A_DAY;
    totalSeconds = totalSeconds % NUMBER_OF_SECONDS_IN_A_DAY;
}

void reorganizeUnderflowValues(int32_t& totalDays, int32_t& totalSeconds, int32_t& totalMicroSeconds) {
    if (totalMicroSeconds < 0) {
        int32_t neededSeconds =
            (totalMicroSeconds * -1 + NUMBER_OF_MICROSECONDS_IN_A_SECOND - 1) / NUMBER_OF_MICROSECONDS_IN_A_SECOND;
        totalSeconds -= neededSeconds;
        totalMicroSeconds += neededSeconds * static_cast<int32_t>(NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    }
    if (totalSeconds < 0) {
        int32_t neededDays = (totalSeconds * -1 + NUMBER_OF_SECONDS_IN_A_DAY - 1) / NUMBER_OF_SECONDS_IN_A_DAY;
        totalDays -= neededDays;
        totalSeconds += neededDays * static_cast<int32_t>(NUMBER_OF_SECONDS_IN_A_DAY);
    }
}

}  // namespace alba::dateTimeHelper
