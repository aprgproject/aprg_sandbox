#include <UniqueProblems/DynamicProgramming/Other/FindTheMinimumCostToReachDestinationUsingATrain.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Value = FindTheMinimumCostToReachDestinationUsingATrain::Value;
using ValueMatrix = FindTheMinimumCostToReachDestinationUsingATrain::ValueMatrix;
constexpr Value UV = FindTheMinimumCostToReachDestinationUsingATrain::UNUSED_VALUE;
}  // namespace

TEST(FindTheMinimumCostToReachDestinationUsingATrainTest, GetMinimumPriceWorksOnEmpty) {
    ValueMatrix valueMatrix(0, 0);
    FindTheMinimumCostToReachDestinationUsingATrain queryForTest(valueMatrix);

    EXPECT_EQ(0, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getMinimumCostUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getMinimumCostUsingIterativeDP());
}

TEST(FindTheMinimumCostToReachDestinationUsingATrainTest, GetMinimumPriceWorksOnExample1) {
    ValueMatrix valueMatrix(4, 4, {0, UV, UV, UV, 15, 0, UV, UV, 80, 40, 0, UV, 90, 50, 70, 0});
    FindTheMinimumCostToReachDestinationUsingATrain queryForTest(valueMatrix);

    EXPECT_EQ(65, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(65, queryForTest.getMinimumCostUsingMemoizationDP());
    EXPECT_EQ(65, queryForTest.getMinimumCostUsingIterativeDP());
}

}  // namespace alba
