#include <AprgUniqueProblems/GreedyAlgorithm/TaskAndDeadlines.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(TaskAndDeadlinesTest, GetTasksAsPossibleWorksOnExample1) {
    TaskAndDeadlines taskAndDeadlines;
    taskAndDeadlines.addTask("A", 4, 2);
    taskAndDeadlines.addTask("B", 3, 5);
    taskAndDeadlines.addTask("C", 2, 7);
    taskAndDeadlines.addTask("D", 4, 5);

    TaskAndDeadlines::TaskNames actualNames(taskAndDeadlines.getTasksOrderWithMaximumScore());
    TaskAndDeadlines::TaskNames expectedNames{"C", "B", "A", "D"};
    EXPECT_EQ(expectedNames, actualNames);
}
}  // namespace alba
