#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <deque>

namespace alba
{

class TaskAndDeadlines
{
public:
    // Let us now consider a problem where we are given n tasks with durations and deadlines and our task is to choose an order to perform the tasks.
    // For each task, we earn d-x points where d is the task’s deadline and x is the moment when we finish the task.
    // What is the largest possible total score we can obtain?

    struct Task
    {
        std::string taskName;
        unsigned int duration;
        unsigned int deadline;
    };

    using Tasks = std::deque<Task>;
    using TaskNames = stringHelper::strings;

    TaskNames getTasksOrderWithMaximumScore() const;

    void addTask(std::string const& eventName, unsigned int const startTime, unsigned int const endTime);

private:
    Tasks m_tasks;
};

}
