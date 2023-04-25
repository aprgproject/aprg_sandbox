#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <vector>

namespace alba {

class WeightedJobScheduling {
public:
    using Index = unsigned int;
    using Time = unsigned int;
    using Profit = unsigned int;

    struct Job {
        Time startTime;
        Time endTime;
        Profit profit;
    };
    using Times = std::vector<Time>;
    using Profits = std::vector<Profit>;
    using Jobs = std::vector<Job>;

    WeightedJobScheduling(Jobs const& jobs);

    Profit getMaxProfitByMonitoringTimeStampsUsingIterativeDP() const;
    Profit getMaxProfitByMonitoringJobsUsingIterativeDP() const;

private:
    Jobs m_jobs;
};

}  // namespace alba

// Given N jobs where every job is represented by following three elements of it.
// -> Start Time
// -> Finish Time
// -> Profit or Value Associated

// Find the maximum profit subset of jobs such that no two jobs in the subset overlap.

// Example:
// Input: Number of Jobs n = 4
// -> Job Details {Start Time, Finish Time, Profit}
// -> Job 1:  {1, 2, 50}
// -> Job 2:  {3, 5, 20}
// -> Job 3:  {6, 19, 100}
// -> Job 4:  {2, 100, 200}
// ---> Output: The maximum profit is 250.
// ---> We can get the maximum profit by scheduling jobs 1 and 4.
// ---> Note that there is longer schedules possible Jobs 1, 2 and 3 but the profit with this schedule is 20+50+100
// which is less than 250.
