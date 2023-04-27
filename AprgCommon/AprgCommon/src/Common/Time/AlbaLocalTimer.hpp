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

    size_t getElapsedTimeInNanoseconds() const;
    size_t getElapsedTimeInMicroseconds() const;
    size_t getElapsedTimeInMilliseconds() const;
    size_t getElapsedTimeInSeconds() const;
    size_t getElapsedTimeInMinutes() const;
    size_t getElapsedTimeInHours() const;
    AlbaDateTime getDifferenceAsAlbaDateTime() const;

private:
    LibrarySteadyTime m_time1;
    LibrarySteadyTime m_time2;
};

}  // namespace alba
