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
    void sleep(unsigned int const milliSeconds);

    unsigned int getElapsedTimeInMicroseconds() const;
    unsigned int getElapsedTimeInMilliseconds() const;
    unsigned int getElapsedTimeInSeconds() const;
    unsigned int getElapsedTimeInMinutes() const;    unsigned int getElapsedTimeInHours() const;
    AlbaDateTime getDifferenceBetweenTimes() const;

private:    SYSTEMTIME m_time1;
    SYSTEMTIME m_time2;
};

}//namespace alba
