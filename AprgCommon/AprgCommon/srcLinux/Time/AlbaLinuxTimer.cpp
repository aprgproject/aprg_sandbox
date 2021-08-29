#include "AlbaLinuxTimer.hpp"

#include <Time/AlbaDateTimeConstants.hpp>
#include <Time/AlbaLinuxTimeHelper.hpp>
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

void AlbaLinuxTimer::sleep(unsigned int const milliSeconds)
{
    alba::sleep(milliSeconds);
}

unsigned int AlbaLinuxTimer::getElapsedTimeInMilliseconds() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE))
            + (difference.getSeconds()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND))
            + difference.getMicroSeconds());
    return elapsedTime;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInSeconds() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE))
            + difference.getSeconds());
    return elapsedTime;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInMinutes() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR))
            + difference.getMinutes());
    return elapsedTime;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInHours() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_timeSpec1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_timeSpec2));
    AlbaDateTime difference(time2-time1);
    return static_cast<unsigned int>(difference.getHours());
}

}//namespace alba
