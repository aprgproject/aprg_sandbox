/*
#include "AlbaLinuxTimer.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaLinuxTimeHelper.hpp>

#include <unistd.h>

namespace alba
{

AlbaLinuxTimer::AlbaLinuxTimer()
    : m_timeSpec1{}
    , m_timeSpec2{}
{
    resetTimer();
}

void AlbaLinuxTimer::resetTimer()
{
    clock_gettime(CLOCK_REALTIME, &m_timeSpec1);
    m_timeSpec2 = m_timeSpec1;
}

void AlbaLinuxTimer::stopTimer()
{
    clock_gettime(CLOCK_REALTIME, &m_timeSpec2);
}

void AlbaLinuxTimer::sleep(size_t const milliSeconds)
{
    alba::sleep(milliSeconds);
}

size_t AlbaLinuxTimer::getElapsedTimeInMilliseconds() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    size_t elapsedTime =
            static_cast<size_t>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE))
            + (difference.getSeconds()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND))
            + difference.getMicroSeconds());
    return elapsedTime;
}

size_t AlbaLinuxTimer::getElapsedTimeInSeconds() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    size_t elapsedTime =
            static_cast<size_t>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE))
            + difference.getSeconds());
    return elapsedTime;
}

size_t AlbaLinuxTimer::getElapsedTimeInMinutes() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    size_t elapsedTime =
            static_cast<size_t>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR))
            + difference.getMinutes());
    return elapsedTime;
}

size_t AlbaLinuxTimer::getElapsedTimeInHours() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    return static_cast<size_t>(difference.getHours());
}

AlbaDateTime AlbaLinuxTimer::getDifferenceBetweenTimes() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    return AlbaDateTime(time2-time1);
}

}//namespace alba
*/
