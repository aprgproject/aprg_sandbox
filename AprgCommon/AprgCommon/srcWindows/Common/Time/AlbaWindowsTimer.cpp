/*
#include "AlbaWindowsTimer.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaWindowsTimeHelper.hpp>

using namespace std;

namespace alba
{

AlbaWindowsTimer::AlbaWindowsTimer()
{
    resetTimer();
}

void AlbaWindowsTimer::resetTimer()
{
    GetSystemTime(&m_time1);
    m_time2 = m_time1;
}

void AlbaWindowsTimer::stopTimer()
{
    GetSystemTime(&m_time2);
}

void AlbaWindowsTimer::sleep(size_t const milliSeconds)
{
    alba::sleep(milliSeconds);
}

size_t AlbaWindowsTimer::getElapsedTimeInMicroseconds() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    return difference.getSeconds()*AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_SECOND +
difference.getMicroSeconds();
}

size_t AlbaWindowsTimer::getElapsedTimeInMilliseconds() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    size_t elapsedTime =
            difference.getHours()*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR
            + difference.getMinutes()*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE
            + difference.getSeconds()*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND
            + difference.getMicroSeconds()/AlbaDateTimeConstants::NUMBER_OF_MICROSECONDS_IN_A_MILLISECOND;
    return elapsedTime;
}

size_t AlbaWindowsTimer::getElapsedTimeInSeconds() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    size_t elapsedTime =
            difference.getHours()*AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR
            + difference.getMinutes()*AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE
            + difference.getSeconds();
    return elapsedTime;
}

size_t AlbaWindowsTimer::getElapsedTimeInMinutes() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    size_t elapsedTime =
            difference.getHours()*AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR
            + difference.getMinutes();
    return elapsedTime;
}

size_t AlbaWindowsTimer::getElapsedTimeInHours() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    return difference.getHours();
}

AlbaDateTime AlbaWindowsTimer::getDifferenceBetweenTimes() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_time1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_time2));
    return AlbaDateTime(time2-time1);
}

}//namespace alba
*/
