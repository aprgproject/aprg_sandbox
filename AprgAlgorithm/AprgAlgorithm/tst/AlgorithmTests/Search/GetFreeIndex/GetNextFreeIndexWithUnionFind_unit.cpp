#include <Algorithm/Search/GetFreeIndex/GetNextFreeIndexWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using IndexForTest = int;
using QueryForTest = GetNextFreeIndexWithUnionFind<IndexForTest>;
}  // namespace

TEST(GetNextFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorksWithZeroSize) {
    QueryForTest query(0);

    EXPECT_EQ(0, query.getNextFreeIndexAt(0));
    EXPECT_EQ(0, query.getNextFreeIndexAt(1));
    EXPECT_EQ(0, query.getNextFreeIndexAt(2));
}

TEST(GetNextFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorks) {
    QueryForTest query(28);

    EXPECT_EQ(0, query.getNextFreeIndexAt(0));
    EXPECT_EQ(1, query.getNextFreeIndexAt(1));
    EXPECT_EQ(2, query.getNextFreeIndexAt(2));
    EXPECT_EQ(14, query.getNextFreeIndexAt(14));
    EXPECT_EQ(15, query.getNextFreeIndexAt(15));
    EXPECT_EQ(16, query.getNextFreeIndexAt(16));
    EXPECT_EQ(26, query.getNextFreeIndexAt(26));
    EXPECT_EQ(27, query.getNextFreeIndexAt(27));
    EXPECT_EQ(0, query.getNextFreeIndexAt(28));
}

TEST(GetNextFreeIndexWithUnionFindTest, SetAsNotFreeWorks) {
    QueryForTest query(28);

    query.setAsNotFree(14);
    query.setAsNotFree(15);
    query.setAsNotFree(16);

    EXPECT_EQ(0, query.getNextFreeIndexAt(0));
    EXPECT_EQ(1, query.getNextFreeIndexAt(1));
    EXPECT_EQ(2, query.getNextFreeIndexAt(2));
    EXPECT_EQ(13, query.getNextFreeIndexAt(13));
    EXPECT_EQ(17, query.getNextFreeIndexAt(14));
    EXPECT_EQ(17, query.getNextFreeIndexAt(15));
    EXPECT_EQ(17, query.getNextFreeIndexAt(16));
    EXPECT_EQ(17, query.getNextFreeIndexAt(17));
    EXPECT_EQ(26, query.getNextFreeIndexAt(26));
    EXPECT_EQ(27, query.getNextFreeIndexAt(27));
    EXPECT_EQ(0, query.getNextFreeIndexAt(28));
}

TEST(GetNextFreeIndexWithUnionFindTest, SetAsFreeWorks) {
    QueryForTest query(28);
    query.setAsNotFree(14);
    query.setAsNotFree(15);
    query.setAsNotFree(16);

    query.setAsFree(15);

    EXPECT_EQ(0, query.getNextFreeIndexAt(0));
    EXPECT_EQ(1, query.getNextFreeIndexAt(1));
    EXPECT_EQ(2, query.getNextFreeIndexAt(2));
    EXPECT_EQ(13, query.getNextFreeIndexAt(13));
    EXPECT_EQ(15, query.getNextFreeIndexAt(14));
    EXPECT_EQ(15, query.getNextFreeIndexAt(15));
    EXPECT_EQ(17, query.getNextFreeIndexAt(16));
    EXPECT_EQ(17, query.getNextFreeIndexAt(17));
    EXPECT_EQ(26, query.getNextFreeIndexAt(26));
    EXPECT_EQ(27, query.getNextFreeIndexAt(27));
    EXPECT_EQ(0, query.getNextFreeIndexAt(28));
}

}  // namespace algorithm

}  // namespace alba
