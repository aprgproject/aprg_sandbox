#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <deque>
#include <string>

namespace alba {

class JobWithProfitAndDeadlines {
public:
    struct Job {
        std::string jobName;
        unsigned int profit;
        unsigned int deadline;
    };

    using Jobs = std::deque<Job>;
    using JobNames = stringHelper::strings;

    JobNames getJobsOrderWithMaximumProfit() const;

    void addJob(std::string const& jobName, unsigned int const profit, unsigned int const deadline);

private:
    unsigned int getMaximumDeadline() const;
    Jobs m_jobs;
};

}  // namespace alba

// Given a set of n jobs where each job i has a deadline di >=1 and profit pi>=0.
// Only one job can be scheduled at a time. Each job takes 1 unit of time to complete.
// We earn the profit if and only if the job is completed by its deadline. The task is to find the subset of jobs that
// maximizes profit.

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
// ---> If the current job can fit in the current result sequence without missing the deadline, add current job to the
// result.
// ---> Else ignore the current job.

// Using Disjoint Set for Job Sequencing
// All time slots are individual sets initially.
// We first find the maximum deadline of all jobs.
// Let the max deadline be m.
// We create m+1 individual sets.
// If a job is assigned a time slot of t where t >= 0, then the job is scheduled during [t-1, t].
// So a set with value X represents the time slot [X-1, X].
// We need to keep track of the greatest time slot available which can be allotted to a given job having deadline.
// We use the parent array of Disjoint Set Data structures for this purpose.
// The root of the tree is always the latest available slot.
// If for a deadline d, there is no slot available, then root would be 0.

// Initialize Disjoint Set: Creates initial disjoint sets.

// How come find returns the latest available time slot?
// Initially all time slots are individual slots.
// So the time slot returned is always maximum.
// When we assign a time slot ‘t’ to a job, we do union of ‘t’ with ‘t-1’ in a way that ‘t-1’ becomes parent of ‘t’.
// To do this we call union(t-1, t).
// This means that all future queries for time slot t would now return the latest time slot available for set
// represented by t-1.
