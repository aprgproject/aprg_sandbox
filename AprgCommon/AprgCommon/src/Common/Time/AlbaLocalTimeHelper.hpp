#pragma once

#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaDateTime.hpp>
#include <Common/Time/AlbaLibraryTimeTypes.hpp>

#include <chrono>

namespace alba
{

using LibrarySteadyTime = std::chrono::time_point<std::chrono::steady_clock>;

void sleepFor(unsigned int const milliSeconds);
void sleepUntil(AlbaDateTime const& awakeTime);

LibrarySteadyTime getSteadyTimeNow();
LibrarySystemTime getSystemTimeNow();
AlbaDateTime convertSystemTimeToAlbaDateTime(LibrarySystemTime const& inputTime);
LibrarySystemTime convertAlbaDateTimeToSystemTime(AlbaDateTime const& inputTime);
AlbaDateTime getCurrentDateTime();

template <typename LibraryTime>
AlbaDateTime convertSinceEpochTimeToAlbaDateTime(LibraryTime const& inputTime)
{
    auto microsecondsSinceEpoch = std::chrono::time_point_cast<std::chrono::microseconds>(inputTime).time_since_epoch().count();
    uint32_t remainingMicroSeconds = microsecondsSinceEpoch % AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    uint32_t remainingSeconds = microsecondsSinceEpoch / AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_SECOND;
    uint32_t remainingDays = remainingSeconds / AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_DAY;
    remainingSeconds = remainingSeconds % AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_DAY;

    return AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(remainingDays, remainingSeconds, remainingMicroSeconds);

    // NOTE: To convert this to local time, you have to:
    // -> Add offset for epoch (Jan 1, 1970 00:00:00)
    // -> Add offset for GMT timezone (so its better to make localtime figure this out)
}


}//namespace alba