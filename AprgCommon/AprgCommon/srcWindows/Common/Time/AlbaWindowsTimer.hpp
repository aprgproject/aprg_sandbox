/*
#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <windows.h>

#include <string>

namespace alba
{

class AlbaWindowsTimer
{
public:
    AlbaWindowsTimer();
    void resetTimer();
    void stopTimer();
    void sleep(size_t const milliSeconds);

    size_t getElapsedTimeInMicroseconds() const;
    size_t getElapsedTimeInMilliseconds() const;
    size_t getElapsedTimeInSeconds() const;
    size_t getElapsedTimeInMinutes() const;
    size_t getElapsedTimeInHours() const;
    AlbaDateTime getDifferenceBetweenTimes() const;

private:
    SYSTEMTIME m_time1;
    SYSTEMTIME m_time2;
};

}//namespace alba
*/
