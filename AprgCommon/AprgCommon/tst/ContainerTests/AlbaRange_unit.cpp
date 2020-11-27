#include <Container/AlbaRange.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace alba;
using namespace std;

TEST(AlbaRangeTest, TraverseIsNotInfiniteWhenRangeIsEmpty)
{
    AlbaRange<int> range;
    vector<int> traversedValues;
    range.traverse([&](int const traverseValue)
    {
        traversedValues.emplace_back(traverseValue);
    });

    EXPECT_TRUE(range.isEmpty());
    EXPECT_EQ(0, range.getStartValue());
    EXPECT_EQ(0, range.getEndValue());
    EXPECT_EQ(0, range.getDelta());
    EXPECT_EQ(0, range.getInterval());
    EXPECT_EQ(0, range.getIntervalMagnitude());
    EXPECT_EQ(AlbaRangeType::Stop, range.getRangeType());
    ASSERT_TRUE(traversedValues.empty());
}
TEST(AlbaRangeTest, ForwardTraversalWorks)
{
    AlbaRange<int> range(1, 10, -1);    vector<int> traversedValues;
    range.traverse([&](int const traverseValue)
    {
        traversedValues.emplace_back(traverseValue);
    });

    EXPECT_FALSE(range.isEmpty());
    EXPECT_EQ(1, range.getStartValue());
    EXPECT_EQ(10, range.getEndValue());
    EXPECT_EQ(9, range.getDelta());
    EXPECT_EQ(1, range.getInterval());
    EXPECT_EQ(1, range.getIntervalMagnitude());
    EXPECT_EQ(AlbaRangeType::Forward, range.getRangeType());

    ASSERT_EQ(10, traversedValues.size());    EXPECT_EQ(1, traversedValues[0]);
    EXPECT_EQ(2, traversedValues[1]);
    EXPECT_EQ(3, traversedValues[2]);
    EXPECT_EQ(4, traversedValues[3]);    EXPECT_EQ(5, traversedValues[4]);
    EXPECT_EQ(6, traversedValues[5]);
    EXPECT_EQ(7, traversedValues[6]);
    EXPECT_EQ(8, traversedValues[7]);
    EXPECT_EQ(9, traversedValues[8]);
    EXPECT_EQ(10, traversedValues[9]);
}

TEST(AlbaRangeTest, BackwardTraversalWorks)
{
    AlbaRange<int> range(5, -5, -1);
    vector<int> traversedValues;
    range.traverse([&](int const traverseValue)
    {
        traversedValues.emplace_back(traverseValue);
    });

    EXPECT_FALSE(range.isEmpty());
    EXPECT_EQ(5, range.getStartValue());
    EXPECT_EQ(-5, range.getEndValue());
    EXPECT_EQ(10, range.getDelta());
    EXPECT_EQ(-1, range.getInterval());
    EXPECT_EQ(1, range.getIntervalMagnitude());
    EXPECT_EQ(AlbaRangeType::Backward, range.getRangeType());

    ASSERT_EQ(11, traversedValues.size());    EXPECT_EQ(5, traversedValues[0]);
    EXPECT_EQ(4, traversedValues[1]);
    EXPECT_EQ(3, traversedValues[2]);
    EXPECT_EQ(2, traversedValues[3]);
    EXPECT_EQ(1, traversedValues[4]);
    EXPECT_EQ(0, traversedValues[5]);
    EXPECT_EQ(-1, traversedValues[6]);
    EXPECT_EQ(-2, traversedValues[7]);
    EXPECT_EQ(-3, traversedValues[8]);
    EXPECT_EQ(-4, traversedValues[9]);
    EXPECT_EQ(-5, traversedValues[10]);
}

TEST(AlbaRangeTest, RangeCanBeChangedAfterCreation)
{
    AlbaRange<int> range(1, 10, -1);
    range.setStartValue(5);
    range.setEndValue(-5);
    vector<int> traversedValues;
    range.traverse([&](int const traverseValue)
    {
        traversedValues.emplace_back(traverseValue);
    });

    EXPECT_FALSE(range.isEmpty());
    EXPECT_EQ(5, range.getStartValue());
    EXPECT_EQ(-5, range.getEndValue());
    EXPECT_EQ(10, range.getDelta());
    EXPECT_EQ(-1, range.getInterval());
    EXPECT_EQ(1, range.getIntervalMagnitude());
    EXPECT_EQ(AlbaRangeType::Backward, range.getRangeType());

    ASSERT_EQ(11, traversedValues.size());    EXPECT_EQ(5, traversedValues[0]);
    EXPECT_EQ(4, traversedValues[1]);
    EXPECT_EQ(3, traversedValues[2]);
    EXPECT_EQ(2, traversedValues[3]);
    EXPECT_EQ(1, traversedValues[4]);
    EXPECT_EQ(0, traversedValues[5]);
    EXPECT_EQ(-1, traversedValues[6]);
    EXPECT_EQ(-2, traversedValues[7]);
    EXPECT_EQ(-3, traversedValues[8]);
    EXPECT_EQ(-4, traversedValues[9]);
    EXPECT_EQ(-5, traversedValues[10]);
}

TEST(AlbaRangeTest, MidpointCanBeCalculated)
{
    AlbaRange<int> range(0, 10, 1);

    EXPECT_EQ(5, range.getMidpointValue());
}