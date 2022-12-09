#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <string>
#include <deque>

namespace alba
{

class JobWithProfitAndDeadlines
{
public:

    struct Job
    {
        std::string jobName;
        unsigned int profit;
        unsigned int deadline;
    };

    using Jobs = std::deque<Job>;
    using JobNames = stringHelper::strings;

    JobNames getJobsOrderWithMaximumScore() const;

    void addJob(std::string const& eventName, unsigned int const startTime, unsigned int const endTime);

private:
    Jobs m_jobs;
};

}

// Given a set of n jobs where each job i has a deadline di >=1 and profit pi>=0.
// Only one job can be scheduled at a time. Each job takes 1 unit of time to complete.
// We earn the profit if and only if the job is completed by its deadline. The task is to find the subset of jobs that maximizes profit.

// Examples:
// -> Input: Four Jobs with following deadlines and profits
// ---> JobID Deadline Profit
// --->    a      4      20
// --->    b      1      10
// --->    c      1      40
// --->    d      1      30
// ---> Output: Following is maximum profit sequence of jobs: c, a

// -> Input: Five Jobs with following deadlines and profits
// ---> JobID Deadline Profit
// --->    a     2       100
// --->    b     1       19
// --->    c     2       27
// --->    d     1       25
// --->    e     3       15
// ---> Output: Following is maximum profit sequence of jobs: c, a, e

// Greedy Algorithm:
// -> Step 1: Sort all jobs in decreasing order of profit.
// -> Step 2: Initialize the result sequence as first job in sorted jobs.
// -> Step 3: Do following for remaining n-1 jobs
// ---> If the current job can fit in the current result sequence without missing the deadline, add current job to the result.
// ---> Else ignore the current job.

