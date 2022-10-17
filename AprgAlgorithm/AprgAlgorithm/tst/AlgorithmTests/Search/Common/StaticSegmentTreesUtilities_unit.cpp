#include <Algorithm/Search/Common/StaticSegmentTreeUtilities.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValusForTest = unsigned int;
using UtilitiesForTest = StaticSegmentTreeUtilities<ValusForTest>;
}

TEST(StaticSegmentTreeUtilitiesTest, IsALeftChildWorks)
{
    EXPECT_FALSE(UtilitiesForTest::isALeftChild(0U));
    EXPECT_TRUE(UtilitiesForTest::isALeftChild(1U));
    EXPECT_FALSE(UtilitiesForTest::isALeftChild(2U));
}

TEST(StaticSegmentTreeUtilitiesTest, IsARightChildWorks)
{
    EXPECT_TRUE(UtilitiesForTest::isARightChild(0U));
    EXPECT_FALSE(UtilitiesForTest::isARightChild(1U));
    EXPECT_TRUE(UtilitiesForTest::isARightChild(2U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetParentWorks)
{
    EXPECT_EQ(4294967295U, UtilitiesForTest::getParent(0U)); // -1 because it has no parent
    EXPECT_EQ(0U, UtilitiesForTest::getParent(1U));    EXPECT_EQ(0U, UtilitiesForTest::getParent(2U));
    EXPECT_EQ(21U, UtilitiesForTest::getParent(43U));
    EXPECT_EQ(21U, UtilitiesForTest::getParent(44U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetFirstChildWorks)
{
    EXPECT_EQ(1U, UtilitiesForTest::getFirstChild(0U));
    EXPECT_EQ(43U, UtilitiesForTest::getFirstChild(21U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetSecondChildWorks)
{
    EXPECT_EQ(2U, UtilitiesForTest::getSecondChild(0U));
    EXPECT_EQ(44U, UtilitiesForTest::getSecondChild(21U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetCeilOfLogarithmOfChildrenWorks)
{
    EXPECT_EQ(31U, UtilitiesForTest::getCeilOfLogarithmOfChildren(0U)); // Zero is not valid number of children
    EXPECT_EQ(0U, UtilitiesForTest::getCeilOfLogarithmOfChildren(1U));    EXPECT_EQ(1U, UtilitiesForTest::getCeilOfLogarithmOfChildren(2U));
    EXPECT_EQ(6U, UtilitiesForTest::getCeilOfLogarithmOfChildren(43U));
    EXPECT_EQ(6U, UtilitiesForTest::getCeilOfLogarithmOfChildren(44U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetChildrenRaiseToPowerWorks)
{
    EXPECT_EQ(1U, UtilitiesForTest::getChildrenRaiseToPower(0U));
    EXPECT_EQ(2U, UtilitiesForTest::getChildrenRaiseToPower(1U));    EXPECT_EQ(4U, UtilitiesForTest::getChildrenRaiseToPower(2U));
    EXPECT_EQ(1024U, UtilitiesForTest::getChildrenRaiseToPower(10U));
}

TEST(StaticSegmentTreeUtilitiesTest, GetMinimumNumberOfParentsWorks)
{
    EXPECT_EQ(0U, UtilitiesForTest::getMinimumNumberOfParents(0U)); // Zero is not valid number of children
    EXPECT_EQ(0U, UtilitiesForTest::getMinimumNumberOfParents(1U));    EXPECT_EQ(1U, UtilitiesForTest::getMinimumNumberOfParents(2U));
    EXPECT_EQ(3U, UtilitiesForTest::getMinimumNumberOfParents(3U));
    EXPECT_EQ(3U, UtilitiesForTest::getMinimumNumberOfParents(4U));
    EXPECT_EQ(63U, UtilitiesForTest::getMinimumNumberOfParents(43U));
    EXPECT_EQ(63U, UtilitiesForTest::getMinimumNumberOfParents(44U));
}

}

}
