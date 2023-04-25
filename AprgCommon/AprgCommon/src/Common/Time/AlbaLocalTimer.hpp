#pragma once

#include <Common/Time/AlbaDateTime.hpp>
#include <Common/Time/AlbaLibraryTimeTypes.hpp>

#include <chrono>
#include <string>

namespace alba {

class AlbaLocalTimer {
public:
    AlbaLocalTimer();
    void resetTimer();
    void stopTimer();

    unsigned int getElapsedTimeInNanoseconds() const;
    unsigned int getElapsedTimeInMicroseconds() const;
    unsigned int getElapsedTimeInMilliseconds() const;
    unsigned int getElapsedTimeInSeconds() const;
    unsigned int getElapsedTimeInMinutes() const;
    unsigned int getElapsedTimeInHours() const;
    AlbaDateTime getDifferenceAsAlbaDateTime() const;

private:
    LibrarySteadyTime m_time1;
    LibrarySteadyTime m_time2;
};

}  // namespace alba
