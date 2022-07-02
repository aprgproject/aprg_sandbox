#include "TaskAndDeadlines.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

TaskAndDeadlines::TaskNames TaskAndDeadlines::getTasksOrderWithMaximumScore() const
{
    // Surprisingly, the optimal solution to the problem does not depend on the deadlines at all,
    // but a correct greedy strategy is to simply perform the tasks sorted by their durations in increasing order.

    // Let a and b be the duration
    // If a>b then gives b points less and Y gives a points more, so the total score increases by a-b > 0.
    // In an optimal solution, for any two consecutive tasks, it must hold that the shorter task comes before the longer task.
    //Thus, the tasks must be performed sorted by their durations.

    TaskNames result;

    Tasks taskToSchedule(m_tasks);
    sort(taskToSchedule.begin(), taskToSchedule.end(), [](Task const& task1, Task const& task2) // sort by duration
    {
        return task1.duration < task2.duration;
    });

    result.reserve(taskToSchedule.size());
    transform(taskToSchedule.cbegin(), taskToSchedule.cend(), back_inserter(result), [](Task const& task) // get names
    {
        return task.taskName;
    });

    return result;
}

void TaskAndDeadlines::addTask(string const& taskName, unsigned int const duration, unsigned int const deadline)
{
    m_tasks.emplace_back(Task{taskName, duration, deadline});
}

}
