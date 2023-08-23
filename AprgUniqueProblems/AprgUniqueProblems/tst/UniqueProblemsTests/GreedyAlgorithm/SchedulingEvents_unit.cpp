#include <UniqueProblems/GreedyAlgorithm/SchedulingEvents.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksOnExample1) {
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1, 3);
    schedulingEvents.addEvent("B", 2, 5);
    schedulingEvents.addEvent("C", 3, 9);
    schedulingEvents.addEvent("D", 6, 8);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "D"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksAndShortEventsAreNotImmediatelySelected) {
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1, 5);
    schedulingEvents.addEvent("B", 4, 6);
    schedulingEvents.addEvent("C", 6, 10);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "C"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksAndEarlyEventsAreNotImmediatelySelected) {
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1, 10);
    schedulingEvents.addEvent("B", 3, 4);
    schedulingEvents.addEvent("C", 4, 5);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"B", "C"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksOnExample2) {
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 10, 20);
    schedulingEvents.addEvent("B", 12, 25);
    schedulingEvents.addEvent("C", 20, 30);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "C"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(SchedulingEventsTest, GetAsMuchEventsAsPossibleWorksOnExample3) {
    SchedulingEvents schedulingEvents;
    schedulingEvents.addEvent("A", 1, 2);
    schedulingEvents.addEvent("B", 3, 4);
    schedulingEvents.addEvent("C", 0, 6);
    schedulingEvents.addEvent("D", 5, 7);
    schedulingEvents.addEvent("E", 8, 9);
    schedulingEvents.addEvent("F", 5, 9);

    SchedulingEvents::EventNames actualNames(schedulingEvents.getAsMuchEventsAsPossible());

    SchedulingEvents::EventNames expectedNames{"A", "B", "D", "E"};
    EXPECT_EQ(expectedNames, actualNames);
}

}  // namespace alba
