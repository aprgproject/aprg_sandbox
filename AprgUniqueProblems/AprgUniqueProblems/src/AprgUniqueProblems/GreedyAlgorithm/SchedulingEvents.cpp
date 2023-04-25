#include "SchedulingEvents.hpp"

#include <algorithm>

using namespace std;

namespace alba {

SchedulingEvents::EventNames SchedulingEvents::getAsMuchEventsAsPossible() const {
    // Algorithm 1: The first idea is to select as short events as possible.
    // -> No, what if short event is intersects between two long events.
    // Algorithm 2: Another idea is to always select the next possible event that begins as early as possible.
    // -> No, what if early event is a long event and intersects with multiple short events
    // Algorithm 3: The third idea is to always select the next possible event that ends as early as possible.
    // -> Yes!

    EventNames result;

    if (!m_events.empty()) {
        Events eventsToSchedule(m_events);
        sort(
            eventsToSchedule.begin(), eventsToSchedule.end(),
            [](Event const& event1, Event const& event2)  // sort by end time
            {
                if (event1.endTime != event2.endTime) {
                    return event1.endTime < event2.endTime;  // sort on events that end early
                } else {
                    return event1.startTime < event2.startTime;  // stylistic choice, prioritize longest events first
                }
            });

        Event selectedEvent(eventsToSchedule.front());
        result.emplace_back(selectedEvent.eventName);
        for (Event const& eventToSchedule : eventsToSchedule) {
            if (selectedEvent.endTime <= eventToSchedule.startTime)  // select next earliest event that can start
            {
                selectedEvent = eventToSchedule;
                result.emplace_back(selectedEvent.eventName);
            }
        }
    }
    return result;
}

void SchedulingEvents::addEvent(string const& eventName, unsigned int const startTime, unsigned int const endTime) {
    m_events.emplace_back(Event{eventName, startTime, endTime});
}

}  // namespace alba
