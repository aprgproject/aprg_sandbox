#pragma once

#include <chrono>

namespace alba
{

using LibrarySystemTime = std::chrono::time_point<std::chrono::system_clock>;
// From [https://en.cppreference.com/w/cpp/chrono/system_clock]:
// Class std::chrono::system_clock represents the system-wide real time wall clock.
// It may not be monotonic: on most systems, the system time can be adjusted at any moment.
// It is the only C++ clock that has the ability to map its time points to C-style time.
// std::chrono::system_clock meets the requirements of TrivialClock.

using LibrarySteadyTime = std::chrono::time_point<std::chrono::steady_clock>;
// From [https://en.cppreference.com/w/cpp/chrono/steady_clock]:
// Class std::chrono::steady_clock represents a monotonic clock.
// The time points of this clock cannot decrease as physical time moves forward and the time between ticks of this clock is constant.
// This clock is not related to wall clock time (for example, it can be time since last reboot), and is most suitable for measuring intervals.

}//namespace alba
