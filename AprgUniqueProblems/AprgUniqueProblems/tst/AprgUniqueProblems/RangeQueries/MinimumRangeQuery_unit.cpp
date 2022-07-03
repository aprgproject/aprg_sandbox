#include <AprgUniqueProblems/RangeQueries/MinimumRangeQuery.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MinimumRangeQueryTest, GetMinimumFromStartToEndWorksOnExample1)
{
    MinimumRangeQuery search({5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U});

    EXPECT_EQ(5U, search.getMinimumFromStartToEnd(0U, 0U));
    EXPECT_EQ(5U, search.getMinimumFromStartToEnd(0U, 1U));
    EXPECT_EQ(4U, search.getMinimumFromStartToEnd(0U, 2U));
    EXPECT_EQ(4U, search.getMinimumFromStartToEnd(0U, 3U));
    EXPECT_EQ(4U, search.getMinimumFromStartToEnd(0U, 4U));
    EXPECT_EQ(1U, search.getMinimumFromStartToEnd(0U, 5U));
    EXPECT_EQ(1U, search.getMinimumFromStartToEnd(0U, 6U));
    EXPECT_EQ(1U, search.getMinimumFromStartToEnd(0U, 7U));
    EXPECT_EQ(1U, search.getMinimumFromStartToEnd(3U, 6U));
    EXPECT_EQ(4U, search.getMinimumFromStartToEnd(2U, 4U));
}

}
