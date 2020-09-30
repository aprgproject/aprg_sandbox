#pragma once

#include <windows.h>

namespace alba{

class AlbaWindowsTimer
{
public:
    AlbaWindowsTimer();
    void resetTimer();

    unsigned int getElapsedTimeInMilliseconds() const;
    unsigned int getElapsedTimeInSeconds() const;
    unsigned int getElapsedTimeInMinutes() const;
    unsigned int getElapsedTimeInHours() const;

private:
    SYSTEMTIME m_time1;
};

}//namespace alba
