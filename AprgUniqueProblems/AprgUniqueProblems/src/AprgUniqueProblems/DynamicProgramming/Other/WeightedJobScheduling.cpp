#include "WeightedJobScheduling.hpp"

#include <algorithm>

using namespace std;

namespace alba {

namespace {

auto endTimeJobComparator = [](WeightedJobScheduling::Job const& job1,
                               WeightedJobScheduling::Job const& job2)  // sort by end time
{
    return (job1.endTime != job2.endTime) ? job1.endTime < job2.endTime  // sort on jobs that end early
                                          : job1.profit > job2.profit;   // stylistic choice, put higher profits works
};

auto endTimeJobAndTimeComparator = [](WeightedJobScheduling::Job const& job, WeightedJobScheduling::Time const time) {
    return job.endTime < time;
};

}  // namespace

WeightedJobScheduling::WeightedJobScheduling(Jobs const& jobs) : m_jobs(jobs) {}

WeightedJobScheduling::Profit WeightedJobScheduling::getMaxProfitByMonitoringTimeStampsUsingIterativeDP() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Profit result(0);
    if (!m_jobs.empty()) {
        Times timeStamps;
        timeStamps.reserve(m_jobs.size() * 2);
        for (Job const& job : m_jobs) {
            timeStamps.emplace_back(job.startTime);
            timeStamps.emplace_back(job.endTime);
        }
        sort(timeStamps.begin(), timeStamps.end());
        timeStamps.erase(unique(timeStamps.begin(), timeStamps.end()));

        Profits maxProfitsAtTime(timeStamps.size(), 0U);

        Jobs jobsSortedByEndTime(m_jobs);
        sort(jobsSortedByEndTime.begin(), jobsSortedByEndTime.end(), endTimeJobComparator);

        for (Job const& job : jobsSortedByEndTime) {
            Index timeIndexBeforeJob =
                distance(timeStamps.begin(), find(timeStamps.begin(), timeStamps.end(), job.startTime));
            Index timeIndexAfterJob =
                distance(timeStamps.begin(), find(timeStamps.begin(), timeStamps.end(), job.endTime));
            Profit profitBeforeJob = maxProfitsAtTime.at(timeIndexBeforeJob);
            Profit profitAfterJob = maxProfitsAtTime.at(timeIndexAfterJob);
            Profit profitIfJobIsDone = profitBeforeJob + job.profit;
            Profit maxProfitForJob = max(profitIfJobIsDone, profitAfterJob);
            for (Index timeToUpdate = timeIndexAfterJob; timeToUpdate < timeStamps.size(); timeToUpdate++) {
                maxProfitsAtTime[timeToUpdate] = max(maxProfitsAtTime.at(timeToUpdate), maxProfitForJob);
            }
        }
        result = maxProfitsAtTime.back();
    }
    return result;
}

WeightedJobScheduling::Profit WeightedJobScheduling::getMaxProfitByMonitoringJobsUsingIterativeDP() const {
    // Time Complexity: O(n*log(n))
    // Auxiliary Space: O(n)

    Profit result(0);
    if (!m_jobs.empty()) {
        Jobs jobsSortedByEndTime(m_jobs);
        sort(jobsSortedByEndTime.begin(), jobsSortedByEndTime.end(), endTimeJobComparator);

        Profits maxProfitsAtJob(m_jobs.size(), 0U);
        maxProfitsAtJob.front() = jobsSortedByEndTime.front().profit;

        for (Index jobIndex = 1; jobIndex < jobsSortedByEndTime.size(); jobIndex++) {
            Job const& currentJob(jobsSortedByEndTime.at(jobIndex));
            Profit currentProfit = currentJob.profit;
            auto itLatestNonConflictingJob = lower_bound(
                jobsSortedByEndTime.begin(), jobsSortedByEndTime.begin() + jobIndex, currentJob.startTime,
                endTimeJobAndTimeComparator);
            if (itLatestNonConflictingJob != jobsSortedByEndTime.end()) {
                currentProfit += maxProfitsAtJob.at(distance(jobsSortedByEndTime.begin(), itLatestNonConflictingJob));
            }
            maxProfitsAtJob[jobIndex] = max(maxProfitsAtJob.at(jobIndex - 1), currentProfit);
        }

        result = maxProfitsAtJob.back();
    }
    return result;
}

}  // namespace alba
