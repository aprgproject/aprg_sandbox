#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaNumberIntervalHelpersTest, IsValueInsideTheIntervalsWorks)
{
    AlbaNumberIntervals intervals
    {AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(5)), AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(9))};

    EXPECT_FALSE(isValueInsideTheIntervals(intervals, 2));
    EXPECT_FALSE(isValueInsideTheIntervals(intervals, 3));
    EXPECT_TRUE(isValueInsideTheIntervals(intervals, 4));
    EXPECT_FALSE(isValueInsideTheIntervals(intervals, 5));
    EXPECT_FALSE(isValueInsideTheIntervals(intervals, 6));
    EXPECT_TRUE(isValueInsideTheIntervals(intervals, 7));
    EXPECT_TRUE(isValueInsideTheIntervals(intervals, 8));
    EXPECT_TRUE(isValueInsideTheIntervals(intervals, 9));
    EXPECT_FALSE(isValueInsideTheIntervals(intervals, 10));
}

TEST(AlbaNumberIntervalHelpersTest, IsIntervalInsideTheIntervalsWorks)
{
    AlbaNumberIntervals intervals
    {AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(5)), AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(9))};

    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(2), createCloseEndpoint(3))));
    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(3), createCloseEndpoint(4))));
    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(4), createCloseEndpoint(5))));
    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(5), createCloseEndpoint(6))));
    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(6), createCloseEndpoint(7))));
    EXPECT_TRUE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(8))));
    EXPECT_TRUE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(8), createCloseEndpoint(9))));
    EXPECT_FALSE(isIntervalInsideTheIntervals(intervals, AlbaNumberInterval(createCloseEndpoint(9), createCloseEndpoint(10))));
}

TEST(AlbaNumberIntervalHelpersTest, GetEndpointTypeWithCheckingIfItsClosedWorks)
{
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, getEndpointTypeWithCheckingIfItsClosed(true));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, getEndpointTypeWithCheckingIfItsClosed(false));
}

TEST(AlbaNumberIntervalHelpersTest, CreateOpenEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createOpenEndpoint(645));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_EQ(645, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreateCloseEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createCloseEndpoint(784));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreateEndpointWorks)
{
    AlbaNumberIntervalEndpoint closeEndpoint(createEndpoint(true, 6541));
    AlbaNumberIntervalEndpoint openEndpoint(createEndpoint(false, 5416));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, closeEndpoint.getType());
    EXPECT_EQ(6541, closeEndpoint.getValue().getInteger());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, openEndpoint.getType());
    EXPECT_EQ(5416, openEndpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreatePositiveInfinityOpenEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createPositiveInfinityOpenEndpoint());

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_TRUE(endpoint.getValue().isPositiveInfinity());
}

TEST(AlbaNumberIntervalHelpersTest, CreateNegativeInfinityOpenEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createNegativeInfinityOpenEndpoint());

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_TRUE(endpoint.getValue().isNegativeInfinity());
}

TEST(AlbaNumberIntervalTest, CreateAllRealValuesIntervalWorks)
{
    AlbaNumberInterval interval(createAllRealValuesInterval());

    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval.getHigherEndpoint());
}

TEST(AlbaNumberIntervalTest, GetNumbersInsideTheIntervalWorks)
{
    AlbaNumbers numbers{1, 2, 3, 4, 5};
    AlbaNumberInterval interval(createCloseEndpoint(2), createCloseEndpoint(4));

    AlbaNumbers numbersToVerify(getNumbersInsideTheInterval(numbers, interval));
    ASSERT_EQ(3U, numbersToVerify.size());
    EXPECT_EQ(AlbaNumber(2), numbersToVerify.at(0));
    EXPECT_EQ(AlbaNumber(3), numbersToVerify.at(1));
    EXPECT_EQ(AlbaNumber(4), numbersToVerify.at(2));

}


}