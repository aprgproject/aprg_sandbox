#include <AprgUniqueProblems/GreedyAlgorithm/JobWithProfitAndDeadlines.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(JobWithProfitAndDeadlinesTest, GetJobsAsPossibleWorksOnExample1) {
    JobWithProfitAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addJob("A", 20U, 4U);
    taskAndDeadlines.addJob("B", 10U, 1U);
    taskAndDeadlines.addJob("C", 40U, 1U);
    taskAndDeadlines.addJob("D", 30U, 1U);

    JobWithProfitAndDeadlines::JobNames actualNames(taskAndDeadlines.getJobsOrderWithMaximumProfit());

    JobWithProfitAndDeadlines::JobNames expectedNames{"C", "A"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(JobWithProfitAndDeadlinesTest, GetJobsAsPossibleWorksOnExample2) {
    JobWithProfitAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addJob("A", 100U, 2U);
    taskAndDeadlines.addJob("B", 19U, 1U);
    taskAndDeadlines.addJob("C", 27U, 2U);
    taskAndDeadlines.addJob("D", 25U, 1U);
    taskAndDeadlines.addJob("E", 15U, 3U);

    JobWithProfitAndDeadlines::JobNames actualNames(taskAndDeadlines.getJobsOrderWithMaximumProfit());

    JobWithProfitAndDeadlines::JobNames expectedNames{"A", "C", "E"};
    EXPECT_EQ(expectedNames, actualNames);
}

}  // namespace alba
