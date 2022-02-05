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

void AlbaWindowsTimer::sleep(unsigned int const milliSeconds)
{
    alba::sleep(milliSeconds);
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMilliseconds() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE))
            + (difference.getSeconds()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND))
            + difference.getMicroSeconds());
    return elapsedTime;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInSeconds() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR))
            + (difference.getMinutes()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE))
            + difference.getSeconds());
    return elapsedTime;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMinutes() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    unsigned int elapsedTime =
            static_cast<unsigned int>(
            (difference.getHours()*static_cast<int>(AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR))
            + difference.getMinutes());
    return elapsedTime;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInHours() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    return static_cast<unsigned int>(difference.getHours());
}

AlbaDateTime AlbaWindowsTimer::getDifferenceBetweenTimes() const
{
    AlbaDateTime time1(convertSystemTimeToAlbaDateTime(m_time1));
    AlbaDateTime time2(convertSystemTimeToAlbaDateTime(m_time2));
    return AlbaDateTime(time2-time1);
}

}//namespace alba
