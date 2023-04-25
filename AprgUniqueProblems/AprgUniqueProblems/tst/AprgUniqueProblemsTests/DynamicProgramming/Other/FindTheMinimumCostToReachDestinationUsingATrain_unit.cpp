#include <AprgUniqueProblems/DynamicProgramming/Other/FindTheMinimumCostToReachDestinationUsingATrain.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Value = FindTheMinimumCostToReachDestinationUsingATrain::Value;
using ValueMatrix = FindTheMinimumCostToReachDestinationUsingATrain::ValueMatrix;
constexpr Value UV = FindTheMinimumCostToReachDestinationUsingATrain::UNUSED_VALUE;
}  // namespace

TEST(FindTheMinimumCostToReachDestinationUsingATrainTest, GetMinimumPriceWorksOnEmpty) {
    ValueMatrix valueMatrix(0U, 0U);
    FindTheMinimumCostToReachDestinationUsingATrain queryForTest(valueMatrix);

    EXPECT_EQ(0U, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getMinimumCostUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getMinimumCostUsingIterativeDP());
}

TEST(FindTheMinimumCostToReachDestinationUsingATrainTest, GetMinimumPriceWorksOnExample1) {
    ValueMatrix valueMatrix(4U, 4U, {0, UV, UV, UV, 15, 0, UV, UV, 80, 40, 0, UV, 90, 50, 70, 0});
    FindTheMinimumCostToReachDestinationUsingATrain queryForTest(valueMatrix);

    EXPECT_EQ(65U, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(65U, queryForTest.getMinimumCostUsingMemoizationDP());
    EXPECT_EQ(65U, queryForTest.getMinimumCostUsingIterativeDP());
}

}  // namespace alba
