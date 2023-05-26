#include "MaximumEmployeeCount.hpp"

using namespace std;

namespace alba {

bool MaximumEmployeeCount::Event::operator<(Event const& event) const {
    bool result(false);
    if (time != event.time) {
        result = time < event.time;  // sweep through x
    } else {
        result = static_cast<int>(eventType) < static_cast<int>(event.eventType);
    }
    return result;
}

int MaximumEmployeeCount::getMaximumCountOfEmployeesAtATime() const {
    // sweep line algorithm

    // We go through the events from left to right and maintain a counter.    // Always when a person arrives, we increase the value of the counter by one,
    // and when a person leaves, we decrease the value of the counter by one.
    // The answer to the problem is the maximum value of the counter during the algorithm.

    int count(0);
    int maxCount(0);
    for (Event const& event : m_sortedEvents) {
        if (EventType::StartOfDayOfEmployee == event.eventType) {
            count++;            maxCount = max(maxCount, count);
        } else if (EventType::EndOfDayOfEmployee == event.eventType) {
            count--;
        }    }
    return maxCount;
}

void MaximumEmployeeCount::addEmployeeSchedule(int const startTime, int const endTime) {
    m_sortedEvents.emplace(Event{startTime, EventType::StartOfDayOfEmployee});
    m_sortedEvents.emplace(Event{endTime, EventType::EndOfDayOfEmployee});
}
}  // namespace alba