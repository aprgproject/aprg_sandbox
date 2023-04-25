#include <Algorithm/Search/GetFreeIndex/GetAccumulatedNextFreeIndexWithSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using IndexForTest = unsigned int;
using IndexesForTest = vector<IndexForTest>;
using QueryForTest = GetAccumulatedNextFreeIndexWithSegmentTree<IndexesForTest>;
}  // namespace

TEST(GetAccumulatedNextFreeIndexWithSegmentTreeTest, GetNextFreeIndexAtWorksWithZeroSize) {
    QueryForTest query(0U);

    EXPECT_EQ(0U, query.getNextFreeIndexAt(0U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(1U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(2U));
}

TEST(GetAccumulatedNextFreeIndexWithSegmentTreeTest, GetNextFreeIndexAtWorks) {
    QueryForTest query(28U);

    EXPECT_EQ(0U, query.getNextFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getNextFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getNextFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getNextFreeIndexAt(14U));
    EXPECT_EQ(15U, query.getNextFreeIndexAt(15U));
    EXPECT_EQ(16U, query.getNextFreeIndexAt(16U));
    EXPECT_EQ(26U, query.getNextFreeIndexAt(26U));
    EXPECT_EQ(27U, query.getNextFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(28U));
}

TEST(GetAccumulatedNextFreeIndexWithSegmentTreeTest, SetAsNotFreeWorks) {
    QueryForTest query(28U);

    query.setAsNotFree(15U);

    EXPECT_EQ(0U, query.getNextFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getNextFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getNextFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getNextFreeIndexAt(14U));
    EXPECT_EQ(16U, query.getNextFreeIndexAt(15U));
    EXPECT_EQ(17U, query.getNextFreeIndexAt(16U));
    EXPECT_EQ(27U, query.getNextFreeIndexAt(26U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(28U));
}

TEST(GetAccumulatedNextFreeIndexWithSegmentTreeTest, SetAsFreeWorks) {
    QueryForTest query(28U);
    query.setAsNotFree(15U);

    query.setAsFree(15U);

    EXPECT_EQ(0U, query.getNextFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getNextFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getNextFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getNextFreeIndexAt(14U));
    EXPECT_EQ(15U, query.getNextFreeIndexAt(15U));
    EXPECT_EQ(16U, query.getNextFreeIndexAt(16U));
    EXPECT_EQ(26U, query.getNextFreeIndexAt(26U));
    EXPECT_EQ(27U, query.getNextFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getNextFreeIndexAt(28U));
}

}  // namespace algorithm

}  // namespace alba
