#include "AlbaLocalTimeHelper.hpp"

#include <chrono>
#include <thread>

using namespace alba::AlbaDateTimeConstants;
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

namespace alba
{

void sleepFor(unsigned int const milliSeconds)
{
    sleep_for(chrono::milliseconds(milliSeconds));
}

void sleepUntil(AlbaDateTime const& awakeTime)
{
    sleep_until(convertAlbaDateTimeToSystemTime(awakeTime));
}

LibrarySteadyTime getSteadyTimeNow()
{
    return steady_clock::now();
}

LibrarySystemTime getSystemTimeNow()
{
    return system_clock::now();
}

AlbaDateTime convertSystemTimeToAlbaDateTime(LibrarySystemTime const& inputTime)
{
    // No std::chrono::year_month_day yet (its in C++20), so let use time_t

    constexpr unsigned int YEAR_OFFSET = 1900;
    constexpr unsigned int MONTH_OFFSET = 1;

    time_t currentTimeT = system_clock::to_time_t(inputTime);
    auto localTime = *localtime(&currentTimeT); // not thread safe
    AlbaDateTime result(
                    localTime.tm_year+YEAR_OFFSET,
                    localTime.tm_mon+MONTH_OFFSET,
                    localTime.tm_mday,
                    localTime.tm_hour,
                    localTime.tm_min,
                    localTime.tm_sec,
                    time_point_cast<microseconds>(inputTime).time_since_epoch().count() % NUMBER_OF_MICROSECONDS_IN_A_SECOND);
    result.reorganizeValues();
    return result;
}

LibrarySystemTime convertAlbaDateTimeToSystemTime(AlbaDateTime const& inputTime)
{
    constexpr int YEAR_OFFSET = 1900;
    constexpr int MONTH_OFFSET = 1;

    LibrarySystemTime result;
    std::tm timeInformation{}; // dont brace initialize values
    timeInformation.tm_sec = static_cast<int>(inputTime.getSeconds());
    timeInformation.tm_min = static_cast<int>(inputTime.getMinutes());
    timeInformation.tm_hour = static_cast<int>(inputTime.getHours());
    timeInformation.tm_mday = static_cast<int>(inputTime.getDays());
    timeInformation.tm_mon = static_cast<int>(inputTime.getMonths())-MONTH_OFFSET;
    timeInformation.tm_year = static_cast<int>(inputTime.getYears())-YEAR_OFFSET;

    time_t timeWithoutMicroSeconds = mktime(&timeInformation);
    if(timeWithoutMicroSeconds != -1) // mktime returns -1 if cannot be represented
    {
        result = system_clock::from_time_t(timeWithoutMicroSeconds) + microseconds(inputTime.getMicroSeconds());
    }
    return result;
}

AlbaDateTime getCurrentDateTime()
{
    return convertSystemTimeToAlbaDateTime(getSystemTimeNow());
}

}//namespace alba