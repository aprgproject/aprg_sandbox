#include <Common/Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaNumberIntervalTest, ConstructionForIntervalWorks)
{
    AlbaNumberInterval interval1(createOpenEndpoint(645), createCloseEndpoint(784));
    AlbaNumberInterval interval2(createCloseEndpoint(784), createOpenEndpoint(645));

    EXPECT_EQ(createOpenEndpoint(645), interval1.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(784), interval1.getHigherEndpoint());
    EXPECT_EQ(createOpenEndpoint(645), interval2.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(784), interval2.getHigherEndpoint());
}

TEST(AlbaNumberIntervalTest, EqualityForIntervalsWorks)
{
    AlbaNumberInterval interval1(createOpenEndpoint(451), createOpenEndpoint(658));
    AlbaNumberInterval interval2(createOpenEndpoint(451), createOpenEndpoint(658));
    AlbaNumberInterval interval3(createOpenEndpoint(999), createOpenEndpoint(658));
    AlbaNumberInterval interval4(createOpenEndpoint(451), createOpenEndpoint(999));
    AlbaNumberInterval interval5(createOpenEndpoint(999), createOpenEndpoint(999));

    EXPECT_TRUE(interval1==interval2);
    EXPECT_FALSE(interval1==interval3);
    EXPECT_FALSE(interval1==interval4);
    EXPECT_FALSE(interval1==interval5);
}

TEST(AlbaNumberIntervalTest, IsValueInsideTheIntervalWorks)
{
    AlbaNumberInterval openInterval(createOpenEndpoint(3), createOpenEndpoint(5));
    AlbaNumberInterval closeInterval(createCloseEndpoint(3), createCloseEndpoint(5));

    EXPECT_FALSE(openInterval.isValueInsideTheInterval(2));
    EXPECT_FALSE(openInterval.isValueInsideTheInterval(3));
    EXPECT_TRUE(openInterval.isValueInsideTheInterval(4));
    EXPECT_FALSE(openInterval.isValueInsideTheInterval(5));
    EXPECT_FALSE(openInterval.isValueInsideTheInterval(6));
    EXPECT_FALSE(closeInterval.isValueInsideTheInterval(2));
    EXPECT_TRUE(closeInterval.isValueInsideTheInterval(3));
    EXPECT_TRUE(closeInterval.isValueInsideTheInterval(4));
    EXPECT_TRUE(closeInterval.isValueInsideTheInterval(5));
    EXPECT_FALSE(closeInterval.isValueInsideTheInterval(6));
}

TEST(AlbaNumberIntervalTest, IsValueInsideTheIntervalExceptAtTheEndpointsWorks)
{
    AlbaNumberInterval openInterval(createOpenEndpoint(3), createOpenEndpoint(5));
    AlbaNumberInterval closeInterval(createCloseEndpoint(3), createCloseEndpoint(5));

    EXPECT_FALSE(openInterval.isValueInsideTheIntervalExceptAtTheEndpoints(2));
    EXPECT_FALSE(openInterval.isValueInsideTheIntervalExceptAtTheEndpoints(3));
    EXPECT_TRUE(openInterval.isValueInsideTheIntervalExceptAtTheEndpoints(4));
    EXPECT_FALSE(openInterval.isValueInsideTheIntervalExceptAtTheEndpoints(5));
    EXPECT_FALSE(openInterval.isValueInsideTheIntervalExceptAtTheEndpoints(6));
    EXPECT_FALSE(closeInterval.isValueInsideTheIntervalExceptAtTheEndpoints(2));
    EXPECT_FALSE(closeInterval.isValueInsideTheIntervalExceptAtTheEndpoints(3));
    EXPECT_TRUE(closeInterval.isValueInsideTheIntervalExceptAtTheEndpoints(4));
    EXPECT_FALSE(closeInterval.isValueInsideTheIntervalExceptAtTheEndpoints(5));
    EXPECT_FALSE(closeInterval.isValueInsideTheIntervalExceptAtTheEndpoints(6));
}

TEST(AlbaNumberIntervalTest, IsEndpointInsideTheIntervalWorks)
{
    AlbaNumberInterval openInterval(createOpenEndpoint(3), createOpenEndpoint(5));
    AlbaNumberInterval closeInterval(createCloseEndpoint(3), createCloseEndpoint(5));

    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createOpenEndpoint(2)));
    EXPECT_TRUE(openInterval.isEndpointInsideTheInterval(createOpenEndpoint(3)));
    EXPECT_TRUE(openInterval.isEndpointInsideTheInterval(createOpenEndpoint(4)));
    EXPECT_TRUE(openInterval.isEndpointInsideTheInterval(createOpenEndpoint(5)));
    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createOpenEndpoint(6)));
    EXPECT_FALSE(closeInterval.isEndpointInsideTheInterval(createOpenEndpoint(2)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createOpenEndpoint(3)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createOpenEndpoint(4)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createOpenEndpoint(5)));
    EXPECT_FALSE(closeInterval.isEndpointInsideTheInterval(createOpenEndpoint(6)));
    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createCloseEndpoint(2)));
    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createCloseEndpoint(3)));
    EXPECT_TRUE(openInterval.isEndpointInsideTheInterval(createCloseEndpoint(4)));
    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createCloseEndpoint(5)));
    EXPECT_FALSE(openInterval.isEndpointInsideTheInterval(createCloseEndpoint(6)));
    EXPECT_FALSE(closeInterval.isEndpointInsideTheInterval(createCloseEndpoint(2)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createCloseEndpoint(3)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createCloseEndpoint(4)));
    EXPECT_TRUE(closeInterval.isEndpointInsideTheInterval(createCloseEndpoint(5)));
    EXPECT_FALSE(closeInterval.isEndpointInsideTheInterval(createCloseEndpoint(6)));
}

TEST(AlbaNumberIntervalTest, IsIntervalInsideTheIntervalWorks)
{
    AlbaNumberInterval openInterval(createOpenEndpoint(3), createOpenEndpoint(5));
    AlbaNumberInterval closeInterval(createCloseEndpoint(3), createCloseEndpoint(5));
    AlbaNumberInterval intervalToTest1(createOpenEndpoint(3), createOpenEndpoint(5));
    AlbaNumberInterval intervalToTest2(createCloseEndpoint(3), createCloseEndpoint(5));
    AlbaNumberInterval intervalToTest3(createOpenEndpoint(3), createOpenEndpoint(4));
    AlbaNumberInterval intervalToTest4(createCloseEndpoint(3), createCloseEndpoint(4));
    AlbaNumberInterval intervalToTest5(createOpenEndpoint(4), createOpenEndpoint(5));
    AlbaNumberInterval intervalToTest6(createCloseEndpoint(4), createCloseEndpoint(5));
    AlbaNumberInterval intervalToTest7(createOpenEndpoint(2), createOpenEndpoint(4));
    AlbaNumberInterval intervalToTest8(createOpenEndpoint(4), createOpenEndpoint(6));

    EXPECT_TRUE(openInterval.isIntervalInsideTheInterval(intervalToTest1));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest1));
    EXPECT_FALSE(openInterval.isIntervalInsideTheInterval(intervalToTest2));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest2));
    EXPECT_TRUE(openInterval.isIntervalInsideTheInterval(intervalToTest3));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest3));
    EXPECT_FALSE(openInterval.isIntervalInsideTheInterval(intervalToTest4));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest4));
    EXPECT_TRUE(openInterval.isIntervalInsideTheInterval(intervalToTest5));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest5));
    EXPECT_FALSE(openInterval.isIntervalInsideTheInterval(intervalToTest6));
    EXPECT_TRUE(closeInterval.isIntervalInsideTheInterval(intervalToTest6));
    EXPECT_FALSE(openInterval.isIntervalInsideTheInterval(intervalToTest7));
    EXPECT_FALSE(closeInterval.isIntervalInsideTheInterval(intervalToTest7));
    EXPECT_FALSE(openInterval.isIntervalInsideTheInterval(intervalToTest8));
    EXPECT_FALSE(closeInterval.isIntervalInsideTheInterval(intervalToTest8));
}

TEST(AlbaNumberIntervalTest, GetLowerEndpointWorks)
{
    AlbaNumberInterval interval(createOpenEndpoint(645), createCloseEndpoint(784));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, interval.getLowerEndpoint().getType());
    EXPECT_EQ(645, interval.getLowerEndpoint().getValue().getInteger());
}

TEST(AlbaNumberIntervalTest, GetHigherEndpointWorks)
{
    AlbaNumberInterval interval(createOpenEndpoint(645), createCloseEndpoint(784));

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, interval.getHigherEndpoint().getType());
    EXPECT_EQ(784, interval.getHigherEndpoint().getValue().getInteger());
}

TEST(AlbaNumberIntervalTest, GetDisplayableStringForIntervalWorks)
{
    AlbaNumberInterval interval(createOpenEndpoint(645), createCloseEndpoint(784));

    EXPECT_EQ("(645, 784]", interval.getDisplayableString());
}

TEST(AlbaNumberIntervalTest, SetNewEndpointWorks)
{
    AlbaNumberInterval interval1(createOpenEndpoint(645), createOpenEndpoint(784));
    AlbaNumberInterval interval2(createOpenEndpoint(645), createOpenEndpoint(784));
    AlbaNumberInterval interval3(createOpenEndpoint(645), createOpenEndpoint(784));
    AlbaNumberInterval interval4(createOpenEndpoint(645), createOpenEndpoint(784));

    interval1.setNewEndpoint(createCloseEndpoint(640));
    interval2.setNewEndpoint(createCloseEndpoint(790));
    interval3.setNewEndpoint(createCloseEndpoint(645));
    interval4.setNewEndpoint(createCloseEndpoint(784));

    EXPECT_EQ(createCloseEndpoint(640), interval1.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(784), interval1.getHigherEndpoint());
    EXPECT_EQ(createOpenEndpoint(645), interval2.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(790), interval2.getHigherEndpoint());
    EXPECT_EQ(createCloseEndpoint(645), interval3.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(784), interval3.getHigherEndpoint());
    EXPECT_EQ(createOpenEndpoint(645), interval4.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(784), interval4.getHigherEndpoint());
}

}
