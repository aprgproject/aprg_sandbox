#include <AprgUniqueProblems/GreedyAlgorithm/JobWithProfitAndDeadlines.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(JobWithProfitAndDeadlinesTest, GetJobsAsPossibleWorksOnExample1) {
    JobWithProfitAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addJob("A", 20, 4);
    taskAndDeadlines.addJob("B", 10, 1);
    taskAndDeadlines.addJob("C", 40, 1);
    taskAndDeadlines.addJob("D", 30, 1);

    JobWithProfitAndDeadlines::JobNames actualNames(taskAndDeadlines.getJobsOrderWithMaximumProfit());

    JobWithProfitAndDeadlines::JobNames expectedNames{"C", "A"};
    EXPECT_EQ(expectedNames, actualNames);
}

TEST(JobWithProfitAndDeadlinesTest, GetJobsAsPossibleWorksOnExample2) {
    JobWithProfitAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addJob("A", 100, 2);
    taskAndDeadlines.addJob("B", 19, 1);
    taskAndDeadlines.addJob("C", 27, 2);
    taskAndDeadlines.addJob("D", 25, 1);
    taskAndDeadlines.addJob("E", 15, 3);

    JobWithProfitAndDeadlines::JobNames actualNames(taskAndDeadlines.getJobsOrderWithMaximumProfit());

    JobWithProfitAndDeadlines::JobNames expectedNames{"A", "C", "E"};
    EXPECT_EQ(expectedNames, actualNames);
}

}  // namespace alba
