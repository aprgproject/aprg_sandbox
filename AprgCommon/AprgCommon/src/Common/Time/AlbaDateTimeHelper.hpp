#pragma once

#include <string>

namespace alba
{

namespace dateTimeHelper
{
    bool isLeapYear(uint32_t const year);
    uint32_t getNumberOfDaysInAYear(uint32_t const year);
    uint32_t getNumberOfDaysInAMonth(uint32_t const monthIndex, uint32_t const year);
    uint32_t getNumberOfLeapYearsBeforeThisYear(uint32_t const year);
    uint32_t getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const monthIndex, uint32_t const year);
    uint32_t getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays);
    uint32_t getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays);
    uint32_t getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year);
    uint32_t getNumberOfDaysBeforeThisYear(uint32_t const year);
    uint32_t getTotalDays(uint32_t const years, uint32_t const monthIndex, uint32_t const days);
    uint32_t getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds);
    void reorganizeOverflowValues(uint32_t & totalDays, uint32_t & totalSeconds, uint32_t & totalMicroSeconds);
    void reorganizeUnderflowValues(int32_t & totalDays, int32_t & totalSeconds, int32_t & totalMicroSeconds);
    uint32_t retrieveAndRemoveYearsFromTotalDays(uint32_t & remainingDays);
    uint32_t retrieveAndRemoveMonthsFromTotalDays(uint32_t & remainingDays, uint32_t const year);
    uint32_t retrieveAndRemoveHoursFromTotalSeconds(uint32_t & remainingSeconds);
    uint32_t retrieveAndRemoveMinutesFromTotalSeconds(uint32_t & remainingSeconds);
}

}//namespace alba