#pragma once

#include <string>

namespace alba
{

namespace dateTimeHelper
{
    bool isLeapYear(unsigned int const year);
    unsigned int getNumberOfDaysInAYear(unsigned int const year);
    unsigned int getNumberOfDaysInAMonth(unsigned int const monthIndex, unsigned int const year);
    unsigned int getNumberOfLeapYearsBeforeThisYear(unsigned int const year);
    unsigned int getNumberOfDaysInTheYearBeforeThisMonth(unsigned int const monthIndex, unsigned int const year);
    unsigned int getMonthFromNumberOfDaysInANonLeapYear(unsigned int const numberOfDays);
    unsigned int getMonthFromNumberOfDaysInALeapYear(unsigned int const numberOfDays);
    unsigned int getMonthFromNumberOfDays(unsigned int const numberOfDays, unsigned int const year);
    unsigned int getNumberOfDaysBeforeThisYear(unsigned int const year);
    unsigned int getTotalDays(unsigned int const years, unsigned int const monthIndex, unsigned int const days);
    unsigned int getTotalSeconds(unsigned int const hours, unsigned int const minutes, unsigned int const seconds);
    void reorganizeOverflowValues(unsigned int & totalDays, unsigned int & totalSeconds, unsigned int & totalMicroSeconds);
    void reorganizeUnderflowValues(int & totalDays, int & totalSeconds, int & totalMicroSeconds);
    unsigned int retrieveAndRemoveYearsFromTotalDays(unsigned int & remainingDays);
    unsigned int retrieveAndRemoveMonthsFromTotalDays(unsigned int & remainingDays, unsigned int const year);
    unsigned int retrieveAndRemoveHoursFromTotalSeconds(unsigned int & remainingSeconds);
    unsigned int retrieveAndRemoveMinutesFromTotalSeconds(unsigned int & remainingSeconds);
}

}//namespace alba
