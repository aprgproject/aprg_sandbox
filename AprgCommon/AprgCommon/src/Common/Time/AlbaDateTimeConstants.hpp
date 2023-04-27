#pragma once

#include <cstdint>

namespace alba::AlbaDateTimeConstants {

enum Month : uint32_t  // C98 Enum, let the AlbaDateTimeConstants take care of the scope to avoid pollution
{
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};

constexpr size_t NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND = 1'000;

constexpr size_t NUMBER_OF_MICROSECONDS_IN_A_MILLISECOND = 1'000;
constexpr size_t NUMBER_OF_MICROSECONDS_IN_A_SECOND = 1'000'000;

constexpr size_t NUMBER_OF_MILLISECONDS_IN_A_SECOND = 1'000;
constexpr size_t NUMBER_OF_MILLISECONDS_IN_A_MINUTE = 60'000;
constexpr size_t NUMBER_OF_MILLISECONDS_IN_AN_HOUR = 3'600'000;

constexpr size_t NUMBER_OF_SECONDS_IN_AN_HOUR = 3'600;
constexpr size_t NUMBER_OF_SECONDS_IN_A_MINUTE = 60;
constexpr size_t NUMBER_OF_SECONDS_IN_A_DAY = 86'400;

constexpr size_t NUMBER_OF_MINUTES_IN_AN_HOUR = 60;

constexpr size_t NUMBER_OF_DAYS_IN_NON_LEAP_YEAR = 365;
constexpr size_t NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;

}  // namespace alba::AlbaDateTimeConstants

// enum class version:
// enum class AlbaDateTimeConstants : size_t
// {
//     NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND = 1000,
//     NUMBER_OF_MICROSECONDS_IN_A_MILLISECOND = 1000,
//     NUMBER_OF_MICROSECONDS_IN_A_SECOND = 1000000,
//     NUMBER_OF_MILLISECONDS_IN_A_SECOND = 1000,
//     NUMBER_OF_MILLISECONDS_IN_A_MINUTE = 60000,
//     NUMBER_OF_MILLISECONDS_IN_AN_HOUR = 3600000,
//     NUMBER_OF_SECONDS_IN_AN_HOUR = 3600,
//     NUMBER_OF_SECONDS_IN_A_MINUTE = 60,
//     NUMBER_OF_SECONDS_IN_A_DAY = 86400,
//     NUMBER_OF_MINUTES_IN_AN_HOUR = 60,
//     NUMBER_OF_DAYS_IN_NON_LEAP_YEAR = 365,
//     NUMBER_OF_DAYS_IN_LEAP_YEAR = 366
// };
