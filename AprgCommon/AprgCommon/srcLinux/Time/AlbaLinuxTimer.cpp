#include "AlbaLinuxTimer.hpp"

#include <Time/AlbaDateTimeConstants.hpp>
#include <Time/AlbaLinuxTimeHelper.hpp>

#include <unistd.h>

namespace alba
{

AlbaLinuxTimer::AlbaLinuxTimer()
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
    struct tm * timeInfo1, * timeInfo2;
    timeInfo1 = localtime(&(m_timeSpec1.tv_sec));
    timeInfo2 = localtime(&(m_timeSpec1.tv_sec));
    unsigned int difference =
            static_cast<unsigned int>(
            (timeInfo2->tm_hour - timeInfo1->tm_hour)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR)
            + (timeInfo2->tm_min - timeInfo1->tm_min)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE)
            + (timeInfo2->tm_sec - timeInfo1->tm_sec)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND)
            + (m_timeSpec2.tv_nsec - m_timeSpec1.tv_nsec)/static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND));
    return difference;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInSeconds() const
{
    struct tm * timeInfo1, * timeInfo2;
    timeInfo1 = localtime(&(m_timeSpec1.tv_sec));
    timeInfo2 = localtime(&(m_timeSpec1.tv_sec));
    unsigned int difference =
            static_cast<unsigned int>(
            (timeInfo2->tm_hour - timeInfo1->tm_hour)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR)
            + (timeInfo2->tm_min - timeInfo1->tm_min)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE)
            + (timeInfo2->tm_sec - timeInfo1->tm_sec));
    return difference;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInMinutes() const
{
    struct tm * timeInfo1, * timeInfo2;
    timeInfo1 = localtime(&(m_timeSpec1.tv_sec));
    timeInfo2 = localtime(&(m_timeSpec1.tv_sec));
    unsigned int difference =
            static_cast<unsigned int>(
            (timeInfo2->tm_hour - timeInfo1->tm_hour)*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR)
            + (timeInfo2->tm_min - timeInfo1->tm_min));
    return difference;
}

unsigned int AlbaLinuxTimer::getElapsedTimeInHours() const
{
    struct tm * timeInfo1, * timeInfo2;
    timeInfo1 = localtime(&(m_timeSpec1.tv_sec));
    timeInfo2 = localtime(&(m_timeSpec1.tv_sec));
    return static_cast<unsigned int>(timeInfo2->tm_hour - timeInfo1->tm_hour);
}

}//namespace alba
