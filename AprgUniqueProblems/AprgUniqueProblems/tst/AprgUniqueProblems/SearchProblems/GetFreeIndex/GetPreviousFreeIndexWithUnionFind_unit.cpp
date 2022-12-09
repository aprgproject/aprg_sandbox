#include <AprgUniqueProblems/SearchProblems/GetFreeIndex/GetPreviousFreeIndexWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using IndexForTest = unsigned int;
using QueryForTest = GetPreviousFreeIndexWithUnionFind<IndexForTest>;
}

TEST(GetPreviousFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorksWithZeroSize)
{
    QueryForTest query(0U);

    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(0U));
    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(1U));
    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(2U));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, GetNextFreeIndexAtWorks)
{
    QueryForTest query(28U);

    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getPreviousFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getPreviousFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getPreviousFreeIndexAt(14U));
    EXPECT_EQ(15U, query.getPreviousFreeIndexAt(15U));
    EXPECT_EQ(16U, query.getPreviousFreeIndexAt(16U));
    EXPECT_EQ(26U, query.getPreviousFreeIndexAt(26U));
    EXPECT_EQ(27U, query.getPreviousFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(28U));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, SetAsNotFreeWorks)
{
    QueryForTest query(28U);

    query.setAsNotFree(15U);

    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getPreviousFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getPreviousFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getPreviousFreeIndexAt(14U));
    EXPECT_EQ(14U, query.getPreviousFreeIndexAt(15U));
    EXPECT_EQ(16U, query.getPreviousFreeIndexAt(16U));
    EXPECT_EQ(26U, query.getPreviousFreeIndexAt(26U));
    EXPECT_EQ(27U, query.getPreviousFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(28U));
}

TEST(GetPreviousFreeIndexWithUnionFindTest, SetAsFreeWorks)
{
    QueryForTest query(28U);
    query.setAsNotFree(15U);

    query.setAsFree(15U);

    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(0U));
    EXPECT_EQ(1U, query.getPreviousFreeIndexAt(1U));
    EXPECT_EQ(2U, query.getPreviousFreeIndexAt(2U));
    EXPECT_EQ(14U, query.getPreviousFreeIndexAt(14U));
    EXPECT_EQ(15U, query.getPreviousFreeIndexAt(15U));
    EXPECT_EQ(16U, query.getPreviousFreeIndexAt(16U));
    EXPECT_EQ(26U, query.getPreviousFreeIndexAt(26U));
    EXPECT_EQ(27U, query.getPreviousFreeIndexAt(27U));
    EXPECT_EQ(0U, query.getPreviousFreeIndexAt(28U));
}

}

}
