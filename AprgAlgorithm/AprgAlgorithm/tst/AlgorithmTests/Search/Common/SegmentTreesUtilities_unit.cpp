#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValusForTest = int;
using UtilitiesForTest = SegmentTreeUtilities<ValusForTest>;
}  // namespace

TEST(SegmentTreeUtilitiesTest, IsALeftChildWorks) {
    EXPECT_FALSE(UtilitiesForTest::isALeftChild(0));
    EXPECT_TRUE(UtilitiesForTest::isALeftChild(1));
    EXPECT_FALSE(UtilitiesForTest::isALeftChild(2));
}

TEST(SegmentTreeUtilitiesTest, IsARightChildWorks) {
    EXPECT_TRUE(UtilitiesForTest::isARightChild(0));
    EXPECT_FALSE(UtilitiesForTest::isARightChild(1));
    EXPECT_TRUE(UtilitiesForTest::isARightChild(2));
}

TEST(SegmentTreeUtilitiesTest, GetParentWorks) {
    EXPECT_EQ(-1, UtilitiesForTest::getParent(0));  // -1 because it has no parent
    EXPECT_EQ(0, UtilitiesForTest::getParent(1));
    EXPECT_EQ(0, UtilitiesForTest::getParent(2));
    EXPECT_EQ(21, UtilitiesForTest::getParent(43));
    EXPECT_EQ(21, UtilitiesForTest::getParent(44));
}

TEST(SegmentTreeUtilitiesTest, GetFirstChildWorks) {
    EXPECT_EQ(1, UtilitiesForTest::getLeftChild(0));
    EXPECT_EQ(43, UtilitiesForTest::getLeftChild(21));
}

TEST(SegmentTreeUtilitiesTest, GetSecondChildWorks) {
    EXPECT_EQ(2, UtilitiesForTest::getRightChild(0));
    EXPECT_EQ(44, UtilitiesForTest::getRightChild(21));
}

TEST(SegmentTreeUtilitiesTest, GetCeilOfLogarithmOfChildrenWorks) {
    EXPECT_EQ(0, UtilitiesForTest::getCeilOfLogarithmOfChildren(0));  // Zero is not valid number of children
    EXPECT_EQ(0, UtilitiesForTest::getCeilOfLogarithmOfChildren(1));
    EXPECT_EQ(1, UtilitiesForTest::getCeilOfLogarithmOfChildren(2));
    EXPECT_EQ(6, UtilitiesForTest::getCeilOfLogarithmOfChildren(43));
    EXPECT_EQ(6, UtilitiesForTest::getCeilOfLogarithmOfChildren(44));
}

TEST(SegmentTreeUtilitiesTest, GetChildrenRaiseToPowerWorks) {
    EXPECT_EQ(1, UtilitiesForTest::getChildrenRaiseToPower(0));
    EXPECT_EQ(2, UtilitiesForTest::getChildrenRaiseToPower(1));
    EXPECT_EQ(4, UtilitiesForTest::getChildrenRaiseToPower(2));
    EXPECT_EQ(1024, UtilitiesForTest::getChildrenRaiseToPower(10));
}

TEST(SegmentTreeUtilitiesTest, GetMinimumNumberOfParentsWorks) {
    EXPECT_EQ(0, UtilitiesForTest::getMinimumNumberOfParents(0));  // Zero is not valid number of children
    EXPECT_EQ(0, UtilitiesForTest::getMinimumNumberOfParents(1));
    EXPECT_EQ(1, UtilitiesForTest::getMinimumNumberOfParents(2));
    EXPECT_EQ(3, UtilitiesForTest::getMinimumNumberOfParents(3));
    EXPECT_EQ(3, UtilitiesForTest::getMinimumNumberOfParents(4));
    EXPECT_EQ(63, UtilitiesForTest::getMinimumNumberOfParents(43));
    EXPECT_EQ(63, UtilitiesForTest::getMinimumNumberOfParents(44));
}

}  // namespace algorithm

}  // namespace alba
