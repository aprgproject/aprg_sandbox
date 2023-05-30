#include <AprgUniqueProblems/GreedyAlgorithm/SweepLine/MaximumEmployeeCount.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MaximumEmployeeCountTest, GetMaximumCountOfEmployeesAtATimeWorks) {
    MaximumEmployeeCount maximumEmployeeCount;

    maximumEmployeeCount.addEmployeeSchedule(10, 15);
    maximumEmployeeCount.addEmployeeSchedule(6, 12);
    maximumEmployeeCount.addEmployeeSchedule(14, 16);
    maximumEmployeeCount.addEmployeeSchedule(5, 13);

    EXPECT_EQ(3, maximumEmployeeCount.getMaximumCountOfEmployeesAtATime());
}

}  // namespace alba
