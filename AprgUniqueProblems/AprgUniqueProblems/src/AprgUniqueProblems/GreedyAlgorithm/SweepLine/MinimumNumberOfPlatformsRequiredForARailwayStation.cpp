#include "MinimumNumberOfPlatformsRequiredForARailwayStation.hpp"

using namespace std;

namespace alba {

bool MinimumNumberOfPlatformsRequiredForARailwayStation::Event::operator<(Event const& event) const {
    bool result(false);
    if (time != event.time) {
        result = time < event.time;  // sweep through x
    } else {
        result = static_cast<int>(eventType) < static_cast<int>(event.eventType);
    }
    return result;
}

int MinimumNumberOfPlatformsRequiredForARailwayStation::getMinimumNumberOfPlatforms() const {
    // sweep line algorithm

    int minimumNumberOfPlatforms(0);
    int numberOfWaitingTrains(0);
    for (Event const& event : m_sortedEvents) {
        if (EventType::ArrivalToThePlatform == event.eventType) {
            numberOfWaitingTrains++;
            minimumNumberOfPlatforms = max(minimumNumberOfPlatforms, numberOfWaitingTrains);
        } else if (EventType::DepartureFromThePlatform == event.eventType) {
            numberOfWaitingTrains--;
        }
    }
    return minimumNumberOfPlatforms;
}

void MinimumNumberOfPlatformsRequiredForARailwayStation::addTrainSchedule(int const startTime, int const endTime) {
    m_sortedEvents.emplace(Event{startTime, EventType::ArrivalToThePlatform});
    m_sortedEvents.emplace(Event{endTime, EventType::DepartureFromThePlatform});
}

}  // namespace alba
