#include <Algorithm/Search/GetFreeIndex/GetPreviousFreeIndexWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using IndexForTest = int;
using QueryForTest = GetPreviousFreeIndexWithUnionFind<IndexForTest>;
}  // namespace

TEST(GetPreviousFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorksWithZeroSize) {
    QueryForTest query(0);

    EXPECT_EQ(0, query.getPreviousFreeIndexAt(0));
    EXPECT_EQ(0, query.getPreviousFreeIndexAt(1));
    EXPECT_EQ(0, query.getPreviousFreeIndexAt(2));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorks) {
    QueryForTest query(28);

    EXPECT_EQ(0, query.getPreviousFreeIndexAt(0));
    EXPECT_EQ(1, query.getPreviousFreeIndexAt(1));
    EXPECT_EQ(2, query.getPreviousFreeIndexAt(2));
    EXPECT_EQ(14, query.getPreviousFreeIndexAt(14));
    EXPECT_EQ(15, query.getPreviousFreeIndexAt(15));
    EXPECT_EQ(16, query.getPreviousFreeIndexAt(16));
    EXPECT_EQ(26, query.getPreviousFreeIndexAt(26));
    EXPECT_EQ(27, query.getPreviousFreeIndexAt(27));
    EXPECT_EQ(0, query.getPreviousFreeIndexAt(28));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, SetAsNotFreeWorks) {
    QueryForTest query(28);

    query.setAsNotFree(14);
    query.setAsNotFree(15);
    query.setAsNotFree(16);

    EXPECT_EQ(0, query.getPreviousFreeIndexAt(0));
    EXPECT_EQ(1, query.getPreviousFreeIndexAt(1));
    EXPECT_EQ(2, query.getPreviousFreeIndexAt(2));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(13));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(14));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(15));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(16));
    EXPECT_EQ(17, query.getPreviousFreeIndexAt(17));
    EXPECT_EQ(26, query.getPreviousFreeIndexAt(26));
    EXPECT_EQ(27, query.getPreviousFreeIndexAt(27));
    EXPECT_EQ(0, query.getPreviousFreeIndexAt(28));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, SetAsFreeWorks) {
    QueryForTest query(28);
    query.setAsNotFree(14);
    query.setAsNotFree(15);
    query.setAsNotFree(16);

    query.setAsFree(15);

    EXPECT_EQ(0, query.getPreviousFreeIndexAt(0));
    EXPECT_EQ(1, query.getPreviousFreeIndexAt(1));
    EXPECT_EQ(2, query.getPreviousFreeIndexAt(2));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(13));
    EXPECT_EQ(13, query.getPreviousFreeIndexAt(14));
    EXPECT_EQ(15, query.getPreviousFreeIndexAt(15));
    EXPECT_EQ(15, query.getPreviousFreeIndexAt(16));
    EXPECT_EQ(17, query.getPreviousFreeIndexAt(17));
    EXPECT_EQ(26, query.getPreviousFreeIndexAt(26));
    EXPECT_EQ(27, query.getPreviousFreeIndexAt(27));
    EXPECT_EQ(0, query.getPreviousFreeIndexAt(28));
}

}  // namespace algorithm

}  // namespace alba
