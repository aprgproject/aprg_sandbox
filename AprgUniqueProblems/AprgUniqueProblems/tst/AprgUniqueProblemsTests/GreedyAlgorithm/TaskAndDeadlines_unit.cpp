#include <AprgUniqueProblems/GreedyAlgorithm/TaskAndDeadlines.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(TaskAndDeadlinesTest, GetTasksAsPossibleWorksOnExample1) {
    TaskAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addTask("A", 4U, 2U);
    taskAndDeadlines.addTask("B", 3U, 5U);
    taskAndDeadlines.addTask("C", 2U, 7U);
    taskAndDeadlines.addTask("D", 4U, 5U);

    TaskAndDeadlines::TaskNames actualNames(taskAndDeadlines.getTasksOrderWithMaximumScore());

    TaskAndDeadlines::TaskNames expectedNames{"C", "B", "A", "D"};
    EXPECT_EQ(expectedNames, actualNames);
}

}  // namespace alba
