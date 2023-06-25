#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaNumberIntervalHelpersTest, IsValueInsideTheIntervalsWorks) {
    AlbaNumberIntervals intervals{
        AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(5)),
        AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(9))};

    EXPECT_FALSE(isValueInsideTheIntervals(2, intervals));
    EXPECT_FALSE(isValueInsideTheIntervals(3, intervals));
    EXPECT_TRUE(isValueInsideTheIntervals(4, intervals));
    EXPECT_FALSE(isValueInsideTheIntervals(5, intervals));
    EXPECT_FALSE(isValueInsideTheIntervals(6, intervals));
    EXPECT_TRUE(isValueInsideTheIntervals(7, intervals));
    EXPECT_TRUE(isValueInsideTheIntervals(8, intervals));
    EXPECT_TRUE(isValueInsideTheIntervals(9, intervals));
    EXPECT_FALSE(isValueInsideTheIntervals(10, intervals));
}

TEST(AlbaNumberIntervalHelpersTest, IsIntervalInsideTheIntervalsWorks) {
    AlbaNumberIntervals intervals{
        AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(5)),
        AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(9))};

    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(2), createCloseEndpoint(3)), intervals));
    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(3), createCloseEndpoint(4)), intervals));
    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(4), createCloseEndpoint(5)), intervals));
    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(5), createCloseEndpoint(6)), intervals));
    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(6), createCloseEndpoint(7)), intervals));
    EXPECT_TRUE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(7), createCloseEndpoint(8)), intervals));
    EXPECT_TRUE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(8), createCloseEndpoint(9)), intervals));
    EXPECT_FALSE(
        isIntervalInsideTheIntervals(AlbaNumberInterval(createCloseEndpoint(9), createCloseEndpoint(10)), intervals));
}

TEST(AlbaNumberIntervalHelpersTest, AreTheIntervalsInsideTheIntervalWorks) {
    AlbaNumberIntervals intervals{
        AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(5)),
        AlbaNumberInterval(createOpenEndpoint(7), createOpenEndpoint(9))};

    EXPECT_FALSE(
        areTheIntervalsInsideTheInterval(intervals, AlbaNumberInterval(createOpenEndpoint(2), createOpenEndpoint(8))));
    EXPECT_TRUE(
        areTheIntervalsInsideTheInterval(intervals, AlbaNumberInterval(createOpenEndpoint(3), createOpenEndpoint(9))));
    EXPECT_FALSE(
        areTheIntervalsInsideTheInterval(intervals, AlbaNumberInterval(createOpenEndpoint(4), createOpenEndpoint(10))));
}

TEST(AlbaNumberIntervalHelpersTest, GetEndpointTypeWithCheckingIfItsClosedWorks) {
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, getEndpointTypeWithCheckingIfItsClosed(true));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, getEndpointTypeWithCheckingIfItsClosed(false));
}

TEST(AlbaNumberIntervalHelpersTest, CreateOpenEndpointWorks) {
    AlbaNumberIntervalEndpoint endpoint(createOpenEndpoint(645));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_EQ(645, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreateCloseEndpointWorks) {
    AlbaNumberIntervalEndpoint endpoint(createCloseEndpoint(784));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreateEndpointWorks) {
    AlbaNumberIntervalEndpoint closeEndpoint(createEndpoint(true, 6541));
    AlbaNumberIntervalEndpoint openEndpoint(createEndpoint(false, 5416));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, closeEndpoint.getType());
    EXPECT_EQ(6541, closeEndpoint.getValue().getInteger());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, openEndpoint.getType());
    EXPECT_EQ(5416, openEndpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalHelpersTest, CreatePositiveInfinityOpenEndpointWorks) {
    AlbaNumberIntervalEndpoint endpoint(createPositiveInfinityOpenEndpoint());

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_TRUE(endpoint.getValue().isPositiveInfinity());
}

TEST(AlbaNumberIntervalHelpersTest, CreateNegativeInfinityOpenEndpointWorks) {
    AlbaNumberIntervalEndpoint endpoint(createNegativeInfinityOpenEndpoint());

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_TRUE(endpoint.getValue().isNegativeInfinity());
}

TEST(AlbaNumberIntervalTest, CreateAllRealValuesIntervalWorks) {
    AlbaNumberInterval interval(createAllRealValuesInterval());

    EXPECT_EQ(createNegativeInfinityOpenEndpoint(), interval.getLowerEndpoint());
    EXPECT_EQ(createPositiveInfinityOpenEndpoint(), interval.getHigherEndpoint());
}

TEST(AlbaNumberIntervalTest, GetNumbersInsideTheIntervalWorks) {
    AlbaNumbers numbers{1, 2, 3, 4, 5};
    AlbaNumberInterval interval(createCloseEndpoint(2), createCloseEndpoint(4));

    AlbaNumbers numbersToVerify(getNumbersInsideTheInterval(numbers, interval));
    ASSERT_EQ(3U, numbersToVerify.size());
    EXPECT_EQ(AlbaNumber(2), numbersToVerify[0]);
    EXPECT_EQ(AlbaNumber(3), numbersToVerify[1]);
    EXPECT_EQ(AlbaNumber(4), numbersToVerify[2]);
}

}  // namespace alba