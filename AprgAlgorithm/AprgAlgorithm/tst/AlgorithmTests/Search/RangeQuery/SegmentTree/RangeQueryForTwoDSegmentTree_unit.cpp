#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryForTwoDSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using RangeQueryForTest = RangeQueryForTwoDSegmentTree<unsigned int>;
using ValueMatrixForTest = RangeQueryForTest::ValueMatrix;
using Function = typename RangeQueryForTest::OneDFunction;
Function plusFunction = plus<ValueForTest>();
}

TEST(RangeQueryForTwoDSegmentTreeTest, GetValueOn2DIntervalWorksOnExample1)
{
    ValueMatrixForTest valueMatrix(4U, 4U,
    {7U, 6U, 1U, 6U,
     8U, 7U, 5U, 2U,
     3U, 9U, 7U, 1U,
     8U, 5U, 3U, 8U});
    RangeQueryForTest countRangeQuery(valueMatrix, plusFunction);

    EXPECT_EQ(7U, countRangeQuery.getValueOn2DInterval(0U, 0U, 0U, 0U));
    EXPECT_EQ(28U, countRangeQuery.getValueOn2DInterval(0U, 0U, 1U, 1U));
    EXPECT_EQ(53U, countRangeQuery.getValueOn2DInterval(0U, 0U, 2U, 2U));
    EXPECT_EQ(86U, countRangeQuery.getValueOn2DInterval(0U, 0U, 3U, 3U));
}

}

}
