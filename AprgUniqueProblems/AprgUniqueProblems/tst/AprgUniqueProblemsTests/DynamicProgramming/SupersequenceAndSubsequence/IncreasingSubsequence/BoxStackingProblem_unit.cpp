#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/BoxStackingProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Boxes=BoxStackingProblem::Boxes;
}

TEST(BoxStackingProblemTest, GetLongestLengthWorksOnExample1)
{
    BoxStackingProblem queryForTest({{4U, 6U, 7U}, {1U, 2U, 3U}, {4U, 5U, 6U}, {10U, 12U, 32U}});

    EXPECT_EQ(60U, queryForTest.getMaximumStackedHeight());
}

TEST(BoxStackingProblemTest, GetLongestSubsequenceWorksOnExample1)
{
    BoxStackingProblem queryForTest({{4U, 6U, 7U}, {1U, 2U, 3U}, {4U, 5U, 6U}, {10U, 12U, 32U}});

    EXPECT_EQ((Boxes{{1U, 2U, 3U}, {2U, 3U, 1U}, {4U, 5U, 6U}, {5U, 6U, 4U}, {6U, 7U, 4U}, {10U, 12U, 32U}, {12U, 32U, 10U}}),
              queryForTest.getBoxesWithMaximumStackedHeight());
}

}
