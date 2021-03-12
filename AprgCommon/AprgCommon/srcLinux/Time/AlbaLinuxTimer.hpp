#pragma once

#include <ctime>

namespace alba
{

class AlbaLinuxTimer
{
public:
    AlbaLinuxTimer();
    void resetTimer();
    void stopTimer();
    void sleep(unsigned int const milliSeconds);

    unsigned int getElapsedTimeInMilliseconds() const;
    unsigned int getElapsedTimeInSeconds() const;
    unsigned int getElapsedTimeInMinutes() const;
    unsigned int getElapsedTimeInHours() const;

private:
    struct timespec m_timeSpec1;
    struct timespec m_timeSpec2;
};

}//namespace alba
