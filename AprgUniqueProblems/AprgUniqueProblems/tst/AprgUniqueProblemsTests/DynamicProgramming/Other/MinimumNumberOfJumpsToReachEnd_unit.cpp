#include <AprgUniqueProblems/DynamicProgramming/Other/MinimumNumberOfJumpsToReachEnd.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Counts = MinimumNumberOfJumpsToReachEnd::Counts;
}

TEST(MinimumNumberOfJumpsToReachEndTest, GetMinimumNumberOfJumpsOnExample1)
{
    MinimumNumberOfJumpsToReachEnd queryForTest({1U, 3U, 5U, 8U, 9U, 2U, 6U, 7U, 6U, 8U, 9U});

    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfJumpsUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfJumpsUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfJumpsUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfJumpsUsingIterativeDPAndTimeEfficient());
}

TEST(MinimumNumberOfJumpsToReachEndTest, GetPathOfMinimumNumberOfJumpsOnExample1){
    MinimumNumberOfJumpsToReachEnd queryForTest({1U, 3U, 5U, 8U, 9U, 2U, 6U, 7U, 6U, 8U, 9U});

    EXPECT_EQ((Counts{1U, 3U, 8U, 9U}), queryForTest.getPathOfMinimumNumberOfJumps());
}

}
