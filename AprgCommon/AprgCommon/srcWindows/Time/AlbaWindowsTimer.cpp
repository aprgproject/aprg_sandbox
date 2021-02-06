#include "AlbaWindowsTimer.hpp"

#include <Time/AlbaDateTimeConstants.hpp>

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
    Sleep(milliSeconds);
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMilliseconds() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_AN_HOUR;
    difference = difference + (m_time2.wMinute - m_time1.wMinute)*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_MINUTE;
    difference = difference + (m_time2.wSecond - m_time1.wSecond)*AlbaDateTimeConstants::NUMBER_OF_MILLISECONDS_IN_A_SECOND;
    difference = difference + (m_time2.wMilliseconds - m_time1.wMilliseconds);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInSeconds() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_AN_HOUR;
    difference = difference + (m_time2.wMinute - m_time1.wMinute)*AlbaDateTimeConstants::NUMBER_OF_SECONDS_IN_A_MINUTE;
    difference = difference + (m_time2.wSecond - m_time1.wSecond);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMinutes() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*AlbaDateTimeConstants::NUMBER_OF_MINUTES_IN_AN_HOUR;
    difference = difference + (m_time2.wMinute - m_time1.wMinute);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInHours() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour);
    return difference;
}

}//namespace alba
