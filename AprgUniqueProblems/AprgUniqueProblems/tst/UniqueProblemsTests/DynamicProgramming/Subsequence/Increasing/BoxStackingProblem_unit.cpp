#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/BoxStackingProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Boxes = BoxStackingProblem::Boxes;
}

TEST(BoxStackingProblemTest, GetLongestLengthWorksOnExample1) {
    BoxStackingProblem queryForTest({{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}});

    EXPECT_EQ(60, queryForTest.getMaximumStackedHeight());
}

TEST(BoxStackingProblemTest, GetLongestSubsequenceWorksOnExample1) {
    BoxStackingProblem queryForTest({{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}});

    EXPECT_EQ(
        (Boxes{{1, 2, 3}, {2, 3, 1}, {4, 5, 6}, {5, 6, 4}, {6, 7, 4}, {10, 12, 32}, {12, 32, 10}}),
        queryForTest.getBoxesWithMaximumStackedHeight());
}

}  // namespace alba
