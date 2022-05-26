#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <deque>

namespace alba
{

class SchedulingEvents
{
public:
    // Many scheduling problems can be solved using greedy algorithms.
    // A classic problem is as follows:
    // Given n events with their starting and ending times, find a schedule that includes as many events as possible.

    struct Event
    {
        std::string eventName;
        unsigned int startTime;
        unsigned int endTime;
    };

    using Events = std::deque<Event>;
    using EventNames = stringHelper::strings;

    EventNames getAsMuchEventsAsPossible() const;

    void addEvent(std::string const& eventName, unsigned int const startTime, unsigned int const endTime);

private:
    Events m_events;
};

}
