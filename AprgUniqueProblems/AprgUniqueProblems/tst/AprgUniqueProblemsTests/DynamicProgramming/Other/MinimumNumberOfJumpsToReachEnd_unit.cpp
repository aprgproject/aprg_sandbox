#include <AprgUniqueProblems/DynamicProgramming/Other/MinimumNumberOfJumpsToReachEnd.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Counts = MinimumNumberOfJumpsToReachEnd::Counts;
}

TEST(MinimumNumberOfJumpsToReachEndTest, GetMinimumNumberOfJumpsOnExample1) {
    MinimumNumberOfJumpsToReachEnd queryForTest({1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9});

    EXPECT_EQ(3, queryForTest.getMinimumNumberOfJumpsUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfJumpsUsingMemoizationDP());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfJumpsUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfJumpsUsingIterativeDPAndTimeEfficient());
}

TEST(MinimumNumberOfJumpsToReachEndTest, GetPathOfMinimumNumberOfJumpsOnExample1) {
    MinimumNumberOfJumpsToReachEnd queryForTest({1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9});

    EXPECT_EQ((Counts{1, 3, 8, 9}), queryForTest.getPathOfMinimumNumberOfJumps());
}

}  // namespace alba
