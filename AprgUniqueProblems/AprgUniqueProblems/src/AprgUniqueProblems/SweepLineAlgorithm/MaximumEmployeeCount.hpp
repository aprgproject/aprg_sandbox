#pragma once

#include <set>
#include <string>

namespace alba
{

class MaximumEmployeeCount
{
public:
    // As an example, consider the following problem:
    // There is a company that has n employees, and we know for each employee their arrival and leaving times on a certain day.

    // Our task is to calculate the maximum number of employees that were in the office at the same time.
    // The problem can be solved by modeling the situation so that each employee
    // is assigned two events that correspond to their arrival and leaving times.
    // After sorting the events, we go through them and keep track of the number of people in the office.

    // The running time of the algorithm is O(nlogn), because sorting the events takes O(nlogn) time
    // and the rest of the algorithm takes O(n) time.


    // sweepline approach

    enum class EventType
    {
        StartOfDayOfEmployee = 1,        EndOfDayOfEmployee = 2
    };

    struct Event    {
        unsigned int time;
        EventType eventType;
        bool operator<(Event const& event) const;
    };

    unsigned int getMaximumCountOfEmployeesAtATime() const;
    void addEmployeeSchedule(unsigned int const startTime, unsigned int const endTime); // assumption is every entry is unique

private:


    std::multiset<Event> m_events;
};

}
