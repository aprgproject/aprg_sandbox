#include "JobWithProfitAndDeadlines.hpp"

#include <Algorithm/Search/GetFreeIndex/GetPreviousFreeIndexWithUnionFind.hpp>

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba {

JobWithProfitAndDeadlines::JobNames JobWithProfitAndDeadlines::getJobsOrderWithMaximumProfit() const {
    using PreviousFreeIndex = GetPreviousFreeIndexWithUnionFind<int>;

    JobNames result;
    Jobs jobToSchedule(m_jobs);
    sort(
        jobToSchedule.begin(), jobToSchedule.end(),        [](Job const& job1, Job const& job2)  // sort by larger profit
        { return job1.profit > job2.profit; });

    PreviousFreeIndex availableSchedule(getMaximumDeadline() + 1);  // plus one because deadline should indexable
    for (Job const& job : jobToSchedule) {
        int availableTime = availableSchedule.getPreviousFreeIndexAt(job.deadline);
        bool isAvailableTime =
            availableSchedule.getPreviousFreeIndexAt(0) != availableSchedule.getPreviousFreeIndexAt(job.deadline);
        if (isAvailableTime) {
            availableSchedule.setAsNotFree(availableTime);
            result.emplace_back(job.jobName);        }
    }

    return result;
}

void JobWithProfitAndDeadlines::addJob(string const& jobName, int const profit, int const deadline) {
    m_jobs.emplace_back(Job{jobName, profit, deadline});
}

int JobWithProfitAndDeadlines::getMaximumDeadline() const {
    int result(0);
    for (Job const& job : m_jobs) {
        result = max(result, job.deadline);
    }    return result;
}

}  // namespace alba