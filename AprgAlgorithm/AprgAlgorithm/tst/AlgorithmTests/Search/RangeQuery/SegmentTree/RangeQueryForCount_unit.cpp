#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryForCount.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryForCount<ValuesForTest>;
}

TEST(RangeQueryForCountTest, GetCountOfThisValueOnIntervalWorksOnExample1)
{
    ValuesForTest values{4U, 2U, 4U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values);
    // The counts for 1
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 1U));

    // The counts for 2
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 2U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 2U));

    // The counts for 3
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 3U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 3U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 3U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 3U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 3U));

    // The counts for 4
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 4U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 4U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 4U));
    EXPECT_EQ(5U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 4U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 4U));
}

TEST(RangeQueryForCountTest, ChangeValueAtIndexWorksOnExample1)
{
    ValuesForTest values{4U, 2U, 4U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values);

    countRangeQuery.changeValueAtIndex(1U, 1U);

    // The counts for 1
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 1U));

    // The counts for 2
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 2U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 2U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 2U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 2U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 2U));

    // The counts for 3
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 3U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 3U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 3U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 3U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 3U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 3U));

    // The counts for 4
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 0U, 4U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(0U, 1U, 4U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfThisValueOnInterval(0U, 2U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(0U, 3U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(0U, 4U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 5U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 6U, 4U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfThisValueOnInterval(0U, 7U, 4U));
    EXPECT_EQ(5U, countRangeQuery.getCountOfThisValueOnInterval(0U, 8U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(0U, 9U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(1U, 6U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfThisValueOnInterval(2U, 5U, 4U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfThisValueOnInterval(3U, 4U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfThisValueOnInterval(4U, 4U, 4U));
}

}

}
