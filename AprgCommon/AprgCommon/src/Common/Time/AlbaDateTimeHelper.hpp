#pragma once

#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <cstdint>

namespace alba::dateTimeHelper {
// make to constexpr functions? nah, im too lazy

bool isLeapYear(uint32_t const year);uint32_t getNumberOfDaysInAYear(uint32_t const year);
uint32_t getNumberOfDaysInAMonth(uint32_t const month, uint32_t const year);
uint32_t getNumberOfLeapYearsBeforeThisYear(uint32_t const year);
uint32_t getNumberOfDaysInTheYearBeforeThisMonth(uint32_t const month, uint32_t const year);
uint32_t getMonthFromNumberOfDaysInANonLeapYear(uint32_t const numberOfDays);
uint32_t getMonthFromNumberOfDaysInALeapYear(uint32_t const numberOfDays);
uint32_t getMonthFromNumberOfDays(uint32_t const numberOfDays, uint32_t const year);
uint32_t getNumberOfDaysBeforeThisYear(uint32_t const year);
uint32_t getTotalDays(uint32_t const years, uint32_t const month, uint32_t const days);
uint32_t getTotalSeconds(uint32_t const hours, uint32_t const minutes, uint32_t const seconds);
AlbaDateTimeConstants::DayOfTheWeek getDayOfTheWeek(uint32_t const years, uint32_t const month, uint32_t const days);

uint32_t getAndRemoveYearsFromNumberOfDays(uint32_t& remainingDays);
uint32_t getAndRemoveMonthsFromNumberOfDays(uint32_t& remainingDays, uint32_t const year);uint32_t getAndRemoveHoursFromNumberOfSeconds(uint32_t& remainingSeconds);
uint32_t getAndRemoveMinutesFromNumberOfSeconds(uint32_t& remainingSeconds);

void reorganizeOverflowValues(uint32_t& totalDays, uint32_t& totalSeconds, uint32_t& totalMicroSeconds);void reorganizeUnderflowValues(int32_t& totalDays, int32_t& totalSeconds, int32_t& totalMicroSeconds);

}  // namespace alba::dateTimeHelper
