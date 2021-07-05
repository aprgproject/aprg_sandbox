#pragma once

#include <Time/AlbaDateTime.hpp>

#include <windows.h>

#include <string>

namespace alba
{
class AlbaWindowsTimer
{
public:    AlbaWindowsTimer();
    void resetTimer();
    void stopTimer();
    void sleep(unsigned int const milliSeconds);

    unsigned int getElapsedTimeInMilliseconds() const;
    unsigned int getElapsedTimeInSeconds() const;
    unsigned int getElapsedTimeInMinutes() const;
    unsigned int getElapsedTimeInHours() const;
    std::string getElapsedTimeDisplayableString() const;

private:
    AlbaDateTime getDifferenceBetweenTimes() const;
    SYSTEMTIME m_time1;
    SYSTEMTIME m_time2;
};
}//namespace alba