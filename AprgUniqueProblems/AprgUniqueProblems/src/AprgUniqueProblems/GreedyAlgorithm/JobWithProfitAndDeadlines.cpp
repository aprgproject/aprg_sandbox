#include "JobWithProfitAndDeadlines.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

JobWithProfitAndDeadlines::JobNames JobWithProfitAndDeadlines::getJobsOrderWithMaximumScore() const
{
    JobNames result;

    Jobs jobToSchedule(m_jobs);
    sort(jobToSchedule.begin(), jobToSchedule.end(), [](Job const& job1, Job const& job2) // sort by duration
    {
        return job1.profit < job2.profit;
    });

    result.reserve(jobToSchedule.size());
    transform(jobToSchedule.cbegin(), jobToSchedule.cend(), back_inserter(result), [](Job const& job) // get names
    {
        return job.jobName;
    });

    return result;
}

void JobWithProfitAndDeadlines::addJob(string const& jobName, unsigned int const duration, unsigned int const deadline)
{
    m_jobs.emplace_back(Job{jobName, duration, deadline});
}

}
