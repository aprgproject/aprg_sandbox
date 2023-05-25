#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryForCount.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryForCount<ValuesForTest>;
}  // namespace

TEST(RangeQueryForCountTest, GetCountOfThisValueOnIntervalWorksOnExample1) {
    ValuesForTest values{4, 2, 4, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values);

    // The counts for 1
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 1));

    // The counts for 2
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 2));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 2));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 2));

    // The counts for 3
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 3));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 3));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 3));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 3));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 3));

    // The counts for 4
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 4));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 4));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 4));
    EXPECT_EQ(5, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 4));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 4));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 4));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 4));
}

TEST(RangeQueryForCountTest, ChangeValueAtIndexWorksOnExample1) {
    ValuesForTest values{4, 2, 4, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values);

    countRangeQuery.changeValueAtIndex(1, 1);

    // The counts for 1
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 1));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 1));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 1));

    // The counts for 2
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 2));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 2));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 2));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 2));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 2));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 2));

    // The counts for 3
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 3));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 3));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 3));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 3));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 3));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 3));

    // The counts for 4
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 0, 4));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(0, 1, 4));
    EXPECT_EQ(2, countRangeQuery.getCountOfThisValueOnInterval(0, 2, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(0, 3, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(0, 4, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 5, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 6, 4));
    EXPECT_EQ(4, countRangeQuery.getCountOfThisValueOnInterval(0, 7, 4));
    EXPECT_EQ(5, countRangeQuery.getCountOfThisValueOnInterval(0, 8, 4));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(0, 9, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(1, 6, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfThisValueOnInterval(2, 5, 4));
    EXPECT_EQ(1, countRangeQuery.getCountOfThisValueOnInterval(3, 4, 4));
    EXPECT_EQ(0, countRangeQuery.getCountOfThisValueOnInterval(4, 4, 4));
}

}  // namespace algorithm

}  // namespace alba
