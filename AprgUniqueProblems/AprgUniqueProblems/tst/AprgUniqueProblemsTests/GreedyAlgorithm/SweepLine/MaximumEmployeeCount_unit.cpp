#include <AprgUniqueProblems/GreedyAlgorithm/SweepLine/MaximumEmployeeCount.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MaximumEmployeeCountTest, GetMaximumCountOfEmployeesAtATimeWorks) {
    MaximumEmployeeCount maximumEmployeeCount;

    maximumEmployeeCount.addEmployeeSchedule(10U, 15U);
    maximumEmployeeCount.addEmployeeSchedule(6U, 12U);
    maximumEmployeeCount.addEmployeeSchedule(14U, 16U);
    maximumEmployeeCount.addEmployeeSchedule(5U, 13U);

    EXPECT_EQ(3U, maximumEmployeeCount.getMaximumCountOfEmployeesAtATime());
}

}  // namespace alba
