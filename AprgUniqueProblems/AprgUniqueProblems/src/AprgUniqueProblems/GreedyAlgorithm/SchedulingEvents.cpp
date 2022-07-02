#include "SchedulingEvents.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

SchedulingEvents::EventNames SchedulingEvents::getAsMuchEventsAsPossible() const
{
    // Algorithm 1: The first idea is to select as short events as possible.
    // -> No, what if short event is intersects between two long events.
    // Algorithm 2: Another idea is to always select the next possible event that begins as early as possible.
    // -> No, what if early event is a long event and intersects with multiple short events
    // Algorithm 3: The third idea is to always select the next possible event that ends as early as possible.
    // -> Yes!

    EventNames result;

    Events eventsToSchedule(m_events);
    sort(eventsToSchedule.begin(), eventsToSchedule.end(), [](Event const& event1, Event const& event2) // sort by start time
    {
        return event1.startTime < event2.startTime;
    });

    while(!eventsToSchedule.empty())
    {
        auto it = min_element(eventsToSchedule.begin(), eventsToSchedule.end(), [](Event const& event1, Event const& event2)
        {return event1.endTime < event2.endTime;});

        unsigned int endTimeOfSelectedEvent = it->endTime;
        result.emplace_back(it->eventName); // select event that ends earliest

        eventsToSchedule.erase(eventsToSchedule.begin(), it+1); // remove the selected event and all events before the selected event
        eventsToSchedule.erase(remove_if(eventsToSchedule.begin(), eventsToSchedule.end(),
                                         [endTimeOfSelectedEvent](Event const& event) // remove all intersecting events
        {
            return event.startTime < endTimeOfSelectedEvent;
        }), eventsToSchedule.cend());
    }
    return result;
}

void SchedulingEvents::addEvent(string const& eventName, unsigned int const startTime, unsigned int const endTime)
{
    m_events.emplace_back(Event{eventName, startTime, endTime});
}

}
