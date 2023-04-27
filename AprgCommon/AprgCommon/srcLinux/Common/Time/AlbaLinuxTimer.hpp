/*
#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <ctime>

namespace alba
{

class AlbaLinuxTimer
{
public:
    AlbaLinuxTimer();
    void resetTimer();
    void stopTimer();
    void sleep(size_t const milliSeconds);

    size_t getElapsedTimeInMilliseconds() const;
    size_t getElapsedTimeInSeconds() const;
    size_t getElapsedTimeInMinutes() const;
    size_t getElapsedTimeInHours() const;
    AlbaDateTime getDifferenceBetweenTimes() const;

private:
    timespec m_timeSpec1;
    timespec m_timeSpec2;
};

}//namespace alba
*/
