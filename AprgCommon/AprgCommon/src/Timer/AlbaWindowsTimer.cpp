#include <Timer/AlbaWindowsTimer.hpp>

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

unsigned int AlbaWindowsTimer::getElapsedTimeInMilliseconds() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*1000*60*60;
    difference = difference + (m_time2.wMinute - m_time1.wMinute)*1000*60;
    difference = difference + (m_time2.wSecond - m_time1.wSecond)*1000;
    difference = difference + (m_time2.wMilliseconds - m_time1.wMilliseconds);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInSeconds() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*60*60;
    difference = difference + (m_time2.wMinute - m_time1.wMinute)*60;
    difference = difference + (m_time2.wSecond - m_time1.wSecond);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMinutes() const
{
    unsigned int difference;
    difference = (m_time2.wHour - m_time1.wHour)*60;
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
