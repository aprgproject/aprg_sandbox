#include <Algorithm/Search/RangeQuery/TwoDimensions/RangeQueryForTwoDimensionsWithAccumulator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = unsigned int;
using RangeQueryForTest = RangeQueryForTwoDimensionsWithAccumulator<unsigned int>;
using ValueMatrixForTest = RangeQueryForTest::ValueMatrix;
RangeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
RangeQueryForTest::AccumulatorFunction minusAccumulator = minus<>();
}  // namespace

TEST(RangeQueryForTwoDimensionsWithAccumulatorTest, GetValueOn2DIntervalWorksOnExample1) {
    ValueMatrixForTest valueMatrix(4U, 4U, {7U, 6U, 1U, 6U, 8U, 7U, 5U, 2U, 3U, 9U, 7U, 1U, 8U, 5U, 3U, 8U});
    RangeQueryForTest sumRangeQuery(valueMatrix, plusAccumulator, minusAccumulator);

    // starts with (0,0)
    EXPECT_EQ(7U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 0U, 0U, 0U));
    EXPECT_EQ(28U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 0U, 1U, 1U));
    EXPECT_EQ(53U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 0U, 2U, 2U));
    EXPECT_EQ(86U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 0U, 3U, 3U));

    // starts with (0,1)
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 1U, 0U, 0U));
    EXPECT_EQ(15U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 1U, 1U, 1U));
    EXPECT_EQ(39U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 1U, 2U, 2U));
    EXPECT_EQ(66U, sumRangeQuery.getAccumulatedValueOn2DInterval(0U, 1U, 3U, 3U));

    // starts with (1,0)
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 0U, 0U, 0U));
    EXPECT_EQ(13U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 0U, 1U, 1U));
    EXPECT_EQ(35U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 0U, 2U, 2U));
    EXPECT_EQ(60U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 0U, 3U, 3U));

    // starts with (1,1)
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 1U, 0U, 0U));
    EXPECT_EQ(7U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 1U, 1U, 1U));
    EXPECT_EQ(28U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 1U, 2U, 2U));
    EXPECT_EQ(47U, sumRangeQuery.getAccumulatedValueOn2DInterval(1U, 1U, 3U, 3U));
}

}  // namespace algorithm

}  // namespace alba
