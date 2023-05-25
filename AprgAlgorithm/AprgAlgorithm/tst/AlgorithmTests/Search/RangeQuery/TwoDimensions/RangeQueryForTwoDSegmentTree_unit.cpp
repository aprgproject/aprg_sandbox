#include <Algorithm/Search/RangeQuery/TwoDimensions/RangeQueryForTwoDSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = int;
using RangeQueryForTest = RangeQueryForTwoDSegmentTree<int>;
using ValueMatrixForTest = RangeQueryForTest::ValueMatrix;
using Function = typename RangeQueryForTest::OneDFunction;
Function plusFunction = plus<>();
}  // namespace

TEST(RangeQueryForTwoDSegmentTreeTest, GetValueOn2DIntervalWorksOnExample1) {
    ValueMatrixForTest valueMatrix(4, 4, {7, 6, 1, 6, 8, 7, 5, 2, 3, 9, 7, 1, 8, 5, 3, 8});
    RangeQueryForTest sumRangeQuery(valueMatrix, plusFunction);

    // starts with (0,0)
    EXPECT_EQ(7, sumRangeQuery.getValueOn2DInterval(0, 0, 0, 0));
    EXPECT_EQ(28, sumRangeQuery.getValueOn2DInterval(0, 0, 1, 1));
    EXPECT_EQ(53, sumRangeQuery.getValueOn2DInterval(0, 0, 2, 2));
    EXPECT_EQ(86, sumRangeQuery.getValueOn2DInterval(0, 0, 3, 3));

    // starts with (0,1)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(0, 1, 0, 0));
    EXPECT_EQ(15, sumRangeQuery.getValueOn2DInterval(0, 1, 1, 1));
    EXPECT_EQ(39, sumRangeQuery.getValueOn2DInterval(0, 1, 2, 2));
    EXPECT_EQ(66, sumRangeQuery.getValueOn2DInterval(0, 1, 3, 3));

    // starts with (1,0)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(1, 0, 0, 0));
    EXPECT_EQ(13, sumRangeQuery.getValueOn2DInterval(1, 0, 1, 1));
    EXPECT_EQ(35, sumRangeQuery.getValueOn2DInterval(1, 0, 2, 2));
    EXPECT_EQ(60, sumRangeQuery.getValueOn2DInterval(1, 0, 3, 3));

    // starts with (1,1)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(1, 1, 0, 0));
    EXPECT_EQ(7, sumRangeQuery.getValueOn2DInterval(1, 1, 1, 1));
    EXPECT_EQ(28, sumRangeQuery.getValueOn2DInterval(1, 1, 2, 2));
    EXPECT_EQ(47, sumRangeQuery.getValueOn2DInterval(1, 1, 3, 3));
}

TEST(RangeQueryForTwoDSegmentTreeTest, ChangeValueAtWorksOnExample1) {
    ValueMatrixForTest valueMatrix(4, 4, {7, 6, 1, 6, 8, 7, 5, 2, 3, 9, 7, 1, 8, 5, 3, 8});
    RangeQueryForTest sumRangeQuery(valueMatrix, plusFunction);

    sumRangeQuery.changeValueAt(0, 0, 14);

    // starts with (0,0)
    EXPECT_EQ(14, sumRangeQuery.getValueOn2DInterval(0, 0, 0, 0));
    EXPECT_EQ(35, sumRangeQuery.getValueOn2DInterval(0, 0, 1, 1));
    EXPECT_EQ(60, sumRangeQuery.getValueOn2DInterval(0, 0, 2, 2));
    EXPECT_EQ(93, sumRangeQuery.getValueOn2DInterval(0, 0, 3, 3));

    // starts with (0,1)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(0, 1, 0, 0));
    EXPECT_EQ(15, sumRangeQuery.getValueOn2DInterval(0, 1, 1, 1));
    EXPECT_EQ(39, sumRangeQuery.getValueOn2DInterval(0, 1, 2, 2));
    EXPECT_EQ(66, sumRangeQuery.getValueOn2DInterval(0, 1, 3, 3));

    // starts with (1,0)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(1, 0, 0, 0));
    EXPECT_EQ(13, sumRangeQuery.getValueOn2DInterval(1, 0, 1, 1));
    EXPECT_EQ(35, sumRangeQuery.getValueOn2DInterval(1, 0, 2, 2));
    EXPECT_EQ(60, sumRangeQuery.getValueOn2DInterval(1, 0, 3, 3));

    // starts with (1,1)
    EXPECT_EQ(0, sumRangeQuery.getValueOn2DInterval(1, 1, 0, 0));
    EXPECT_EQ(7, sumRangeQuery.getValueOn2DInterval(1, 1, 1, 1));
    EXPECT_EQ(28, sumRangeQuery.getValueOn2DInterval(1, 1, 2, 2));
    EXPECT_EQ(47, sumRangeQuery.getValueOn2DInterval(1, 1, 3, 3));
}

}  // namespace algorithm

}  // namespace alba
