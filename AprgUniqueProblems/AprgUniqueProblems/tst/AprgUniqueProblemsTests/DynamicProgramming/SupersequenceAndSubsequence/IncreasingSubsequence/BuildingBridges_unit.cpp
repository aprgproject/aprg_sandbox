#include <AprgUniqueProblems/DynamicProgramming/Subsequence/IncreasingSubsequence/BuildingBridges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Bridges=BuildingBridges::Bridges;
}

TEST(BuildingBridgesTest, GetLongestLengthWorksOnExample1)
{
    BuildingBridges queryForTest({{6U, 2U}, {4U, 3U}, {2U, 6U}, {1U, 5U}});

    EXPECT_EQ(2U, queryForTest.getNumberOfPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestLengthWorksOnExample2)
{
    BuildingBridges queryForTest({{8U, 1U}, {1U, 2U}, {4U, 3U}, {3U, 4U}, {5U, 5U}, {2U, 6U}, {6U, 7U}, {7U, 8U}});

    EXPECT_EQ(5U, queryForTest.getNumberOfPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestSubsequenceWorksOnExample1)
{
    BuildingBridges queryForTest({{6U, 2U}, {4U, 3U}, {2U, 6U}, {1U, 5U}});

    EXPECT_EQ((Bridges{{2U, 6U}, {1U, 5U}}), queryForTest.getPossibleBridges());
}

TEST(BuildingBridgesTest, GetLongestSubsequenceWorksOnExample2)
{
    BuildingBridges queryForTest({{8U, 1U}, {1U, 2U}, {4U, 3U}, {3U, 4U}, {5U, 5U}, {2U, 6U}, {6U, 7U}, {7U, 8U}});

    EXPECT_EQ((Bridges{{7U, 8U}, {6U, 7U}, {5U, 5U}, {4U, 3U}, {1U, 2U}}), queryForTest.getPossibleBridges());
}

}
