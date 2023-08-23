#include <UniqueProblems/BitManipulation/SmallestOfThreeIntegersWithoutComparisonOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SmallestOfThreeIntegersWithoutComparisonOperatorsTest, GetSmallestWorksOnExample1) {
    SmallestOfThreeIntegersWithoutComparisonOperators solution;

    EXPECT_EQ(0U, solution.getSmallest(0U, 0U, 0U));
    EXPECT_EQ(0U, solution.getSmallest(0U, 1U, 0U));
    EXPECT_EQ(1U, solution.getSmallest(1U, 1U, 1U));
    EXPECT_EQ(12U, solution.getSmallest(12U, 13U, 14U));
    EXPECT_EQ(12U, solution.getSmallest(14U, 13U, 12U));
}

}  // namespace alba
