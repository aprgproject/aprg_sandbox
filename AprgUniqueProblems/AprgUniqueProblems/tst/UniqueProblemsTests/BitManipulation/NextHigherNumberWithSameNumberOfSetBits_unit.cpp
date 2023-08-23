#include <UniqueProblems/BitManipulation/NextHigherNumberWithSameNumberOfSetBits.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(NextHigherNumberWithSameNumberOfSetBitsTest, GetNextHigherNumberWorksOnExample1) {
    NextHigherNumberWithSameNumberOfSetBits solution;

    EXPECT_EQ(0U, solution.getNextHigherNumber(0U));
    EXPECT_EQ(2U, solution.getNextHigherNumber(1U));
    EXPECT_EQ(4U, solution.getNextHigherNumber(2U));
    EXPECT_EQ(5U, solution.getNextHigherNumber(3U));
    EXPECT_EQ(83U, solution.getNextHigherNumber(78U));
    EXPECT_EQ(91U, solution.getNextHigherNumber(87U));
}

}  // namespace alba
