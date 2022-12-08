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

// This is same as a Activity Selection problem.
// This is the problem statement for the Activity Selection problem.
// You are given n activities with their start and finish times.
// Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

// Example 1 : Consider the following 3 activities sorted by by finish time.
// -> start[]  =  {10, 12, 20};
// -> finish[] =  {20, 25, 30};
// A person can perform at most two activities.
// The maximum set of activities that can be executed  is {0, 2} [ These are indexes in start[] and finish[] ]

// Example 2 : Consider the following 6 activities sorted by by finish time.
// -> start[]  =  {1, 3, 0, 5, 8, 5};
// -> finish[] =  {2, 4, 6, 7, 9, 9};
// A person can perform at most four activities.
// The maximum set of activities that can be executed is {0, 1, 3, 4} [ These are indexes in start[] and finish[] ]

// The greedy choice is to always pick the next activity whose finish time is least among the remaining activities
// and the start time is more than or equal to the finish time of the previously selected activity.
// We can sort the activities according to their finishing time so that we always consider the next activity as minimum finishing time activity.
// 1) Sort the activities according to their finishing time
// 2) Select the first activity from the sorted array and print it.
// 3) Do the following for the remaining activities in the sorted array.
// ---> a) If the start time of this activity is greater than or equal to the finish time of the previously selected activity then select this activity and print it.

// How does Greedy Choice work for Activities sorted according to finish time?
// Let the given set of activities be S = {1, 2, 3, ...n} and activities are sorted by finish time.
// The greedy choice is to always pick activity 1.
// How come activity 1 always provides one of the optimal solutions.
// We can prove it by showing that if there is another solution B with the first activity other than 1,
// then there is also a solution A of the same size with activity 1 as the first activity.
// Let the first activity selected by B be k, then there always exist A = {B – {k}} U {1}.
// (Note that the activities in B are independent and k has the smallest finishing time among all. Since k is not 1, finish(k) >= finish(1)).

// How to implement when given activities are not sorted?
// We create a structure/class for activities.
// We sort all activities by finish time (Refer sort in C++ STL).
// Once we have activities sorted, we apply the same algorithm.

// Time Complexity: It takes O(n log n) time if input activities may not be sorted.
// It takes O(n) time when it is given that input activities are always sorted.