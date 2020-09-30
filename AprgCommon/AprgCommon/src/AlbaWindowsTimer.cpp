#include "AlbaWindowsTimer.hpp"

namespace alba{

AlbaWindowsTimer::AlbaWindowsTimer()
{
    GetSystemTime(&m_time1);
}

void AlbaWindowsTimer::resetTimer()
{
    GetSystemTime(&m_time1);
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMilliseconds() const
{
    SYSTEMTIME time2;
    GetSystemTime(&time2);
    unsigned int difference;
    difference = (time2.wHour - m_time1.wHour)*1000*60*60;
    difference = difference + (time2.wMinute - m_time1.wMinute)*1000*60;
    difference = difference + (time2.wSecond - m_time1.wSecond)*1000;
    difference = difference + (time2.wMilliseconds - m_time1.wMilliseconds);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInSeconds() const
{
    SYSTEMTIME time2;
    GetSystemTime(&time2);
    unsigned int difference;
    difference = (time2.wHour - m_time1.wHour)*60*60;
    difference = difference + (time2.wMinute - m_time1.wMinute)*60;
    difference = difference + (time2.wSecond - m_time1.wSecond);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInMinutes() const
{
    SYSTEMTIME time2;
    GetSystemTime(&time2);
    unsigned int difference;
    difference = (time2.wHour - m_time1.wHour)*60;
    difference = difference + (time2.wMinute - m_time1.wMinute);
    return difference;
}

unsigned int AlbaWindowsTimer::getElapsedTimeInHours() const
{
    SYSTEMTIME time2;
    GetSystemTime(&time2);
    unsigned int difference;
    difference = (time2.wHour - m_time1.wHour);
    return difference;
}

}//namespace alba
