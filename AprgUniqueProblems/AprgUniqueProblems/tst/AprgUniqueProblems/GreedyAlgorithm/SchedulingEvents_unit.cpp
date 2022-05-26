#include <AprgUniqueProblems/GreedyAlgorithm/SchedulingEvents.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksOnExample1)
{
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1U, 3U);
    schedulingEvents.addEvent("B", 2U, 5U);
    schedulingEvents.addEvent("C", 3U, 9U);
    schedulingEvents.addEvent("D", 6U, 8U);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "D"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksAndShortEventsAreNotImmediatelySelected)
{
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1U, 5U);
    schedulingEvents.addEvent("B", 4U, 6U);
    schedulingEvents.addEvent("C", 6U, 10U);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "C"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksAndEarlyEventsAreNotImmediatelySelected)
{
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1U, 10U);
    schedulingEvents.addEvent("B", 3U, 4U);
    schedulingEvents.addEvent("C", 4U, 5U);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"B", "C"};
    EXPECT_EQ(expectedNames, actualNames);
}

}
