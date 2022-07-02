#include <AprgUniqueProblems/RangeQueries/SumRangeQuery.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SumRangeQueryTest, GetSumFromStartAndEndWorksOnExample1)
{
    SumRangeQuery search({1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U});

    EXPECT_EQ(19, search.getSumFromStartAndEnd(3U, 6U));
}

}
