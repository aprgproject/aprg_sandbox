#include "MinimumNumberOfPlatformsRequiredForARailwayStation.hpp"

using namespace std;

namespace alba
{

bool MinimumNumberOfPlatformsRequiredForARailwayStation::Event::operator<(Event const& event) const
{
    bool result(false);
    if(time != event.time)
    {
        result = time < event.time; // sweep through x
    }
    else
    {
        result = static_cast<unsigned int>(eventType) < static_cast<unsigned int>(event.eventType);
    }
    return result;
}

unsigned int MinimumNumberOfPlatformsRequiredForARailwayStation::getMinimumNumberOfPlatforms() const
{
    // sweep line algorithm

    unsigned int minimumNumberOfPlatforms(0U);
    unsigned int numberOfWaitingTrains(0U);
    for(Event const& event : m_sortedEvents)
    {
        if(EventType::ArrivalToThePlatform == event.eventType)
        {
            numberOfWaitingTrains++;
            minimumNumberOfPlatforms = max(minimumNumberOfPlatforms, numberOfWaitingTrains);
        }
        else if(EventType::DepartureFromThePlatform == event.eventType)
        {
            numberOfWaitingTrains--;
        }
    }
    return minimumNumberOfPlatforms;
}

void MinimumNumberOfPlatformsRequiredForARailwayStation::addTrainSchedule(unsigned int const startTime, unsigned int const endTime)
{
    m_sortedEvents.emplace(Event{startTime, EventType::ArrivalToThePlatform});
    m_sortedEvents.emplace(Event{endTime, EventType::DepartureFromThePlatform});
}

}
