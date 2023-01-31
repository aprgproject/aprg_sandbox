#include <AprgUniqueProblems/DynamicProgramming/Subsequence/IncreasingSubsequence/MaximumLengthChainOfPairs.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Values=MaximumLengthChainOfPairs::Pairs;
}

TEST(MaximumLengthChainOfPairsTest, GetLongestLengthWorksOnExample1)
{
    MaximumLengthChainOfPairs queryForTest({{5U, 24U}, {39U, 60U}, {15U, 28U}, {27U, 40U}, {50U, 90U}});

    EXPECT_EQ(3U, queryForTest.getLongestLength());
}

TEST(MaximumLengthChainOfPairsTest, GetLongestSubsequenceWorksOnExample1)
{
    MaximumLengthChainOfPairs queryForTest({{5U, 24U}, {39U, 60U}, {15U, 28U}, {27U, 40U}, {50U, 90U}});

    EXPECT_EQ((Values{{5U, 24U}, {27U, 40U}, {50U, 90U}}), queryForTest.getLongestSubsequence());
}

}
