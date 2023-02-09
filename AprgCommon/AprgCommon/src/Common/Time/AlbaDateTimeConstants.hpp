#pragma once

namespace alba
{

namespace AlbaDateTimeConstants
{

constexpr unsigned int NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND = 1000;

constexpr unsigned int NUMBER_OF_MICROSECONDS_IN_A_MILLISECOND = 1000;
constexpr unsigned int NUMBER_OF_MICROSECONDS_IN_A_SECOND = 1000000;

constexpr unsigned int NUMBER_OF_MILLISECONDS_IN_A_SECOND = 1000;
constexpr unsigned int NUMBER_OF_MILLISECONDS_IN_A_MINUTE = 60000;
constexpr unsigned int NUMBER_OF_MILLISECONDS_IN_AN_HOUR = 3600000;

constexpr unsigned int NUMBER_OF_SECONDS_IN_AN_HOUR = 3600;
constexpr unsigned int NUMBER_OF_SECONDS_IN_A_MINUTE = 60;
constexpr unsigned int NUMBER_OF_SECONDS_IN_A_DAY = 86400;

constexpr unsigned int NUMBER_OF_MINUTES_IN_AN_HOUR = 60;

constexpr unsigned int NUMBER_OF_DAYS_IN_NON_LEAP_YEAR = 365;
constexpr unsigned int NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;

}

// enum class version:
// enum class AlbaDateTimeConstants : unsigned int
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

}//namespace alba
