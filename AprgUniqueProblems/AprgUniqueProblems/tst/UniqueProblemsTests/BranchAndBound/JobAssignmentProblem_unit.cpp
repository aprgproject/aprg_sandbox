#include <UniqueProblems/BranchAndBound/JobAssignmentProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(JobAssignmentProblemTest, GetMinimalCostAndPrintAssignmentsWorksOnExample1) {
    JobAssignmentProblem::CostMatrix costMatrix(4, 4, {{9, 2, 7, 8, 6, 4, 3, 7, 5, 8, 1, 8, 7, 6, 9, 4}});
    JobAssignmentProblem queryForTest(costMatrix);

    EXPECT_EQ(13, queryForTest.getMinimalCostAndPrintAssignments());
}

}  // namespace alba
