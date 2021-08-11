#include <Math/AlbaNumberInterval.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaNumberIntervalEndpointTest, ConstructionForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint1.getType());
    EXPECT_EQ(645, endpoint1.getValue().getInteger());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint2.getType());
    EXPECT_EQ(784, endpoint2.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, EqualityForEndpointsWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Open, 645);    AlbaNumberIntervalEndpoint endpoint3(AlbaNumberIntervalEndpoint::Type::Open, 784);
    AlbaNumberIntervalEndpoint endpoint4(AlbaNumberIntervalEndpoint::Type::Close, 645);
    AlbaNumberIntervalEndpoint endpoint5(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_TRUE(endpoint1==endpoint2);
    EXPECT_FALSE(endpoint1==endpoint3);
    EXPECT_FALSE(endpoint1==endpoint4);
    EXPECT_FALSE(endpoint1==endpoint5);
}

TEST(AlbaNumberIntervalEndpointTest, IsOpenForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_TRUE(endpoint1.isOpen());
    EXPECT_FALSE(endpoint2.isOpen());
}

TEST(AlbaNumberIntervalEndpointTest, IsCloseForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_FALSE(endpoint1.isClose());
    EXPECT_TRUE(endpoint2.isClose());
}

TEST(AlbaNumberIntervalEndpointTest, GetTypeForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint1.getType());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint2.getType());
}

TEST(AlbaNumberIntervalEndpointTest, GetValueForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_EQ(645, endpoint1.getValue().getInteger());
    EXPECT_EQ(784, endpoint2.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, GetTypeStringForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_EQ("Open", endpoint1.getTypeString());
    EXPECT_EQ("Close", endpoint2.getTypeString());
}

TEST(AlbaNumberIntervalEndpointTest, GetDisplayableStringForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);
    EXPECT_EQ("(Open, 645)", endpoint1.getDisplayableString());
    EXPECT_EQ("(Close, 784)", endpoint2.getDisplayableString());
}

TEST(AlbaNumberIntervalEndpointTest, SetTypeForEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createOpenEndpoint(784));
    endpoint.setType(AlbaNumberIntervalEndpoint::Type::Close);

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}

TEST(AlbaNumberTest, ConstructionForIntervalWorks)
{
    AlbaNumberInterval interval1(createOpenEndpoint(645), createCloseEndpoint(784));
    AlbaNumberInterval interval2(createCloseEndpoint(784), createOpenEndpoint(645));
    EXPECT_EQ(createOpenEndpoint(645), interval1.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(784), interval1.getHigherEndpoint());
    EXPECT_EQ(createOpenEndpoint(645), interval2.getLowerEndpoint());
    EXPECT_EQ(createCloseEndpoint(784), interval2.getHigherEndpoint());
}

TEST(AlbaNumberIntervalEndpointTest, EqualityForIntervalsWorks)
{
    AlbaNumberInterval interval1(createOpenEndpoint(451), createOpenEndpoint(658));
    AlbaNumberInterval interval2(createOpenEndpoint(451), createOpenEndpoint(658));    AlbaNumberInterval interval3(createOpenEndpoint(999), createOpenEndpoint(658));
    AlbaNumberInterval interval4(createOpenEndpoint(451), createOpenEndpoint(999));
    AlbaNumberInterval interval5(createOpenEndpoint(999), createOpenEndpoint(999));
    EXPECT_TRUE(interval1==interval2);
    EXPECT_FALSE(interval1==interval3);
    EXPECT_FALSE(interval1==interval4);
    EXPECT_FALSE(interval1==interval5);
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
    AlbaNumberInterval interval2(createOpenEndpoint(645), createOpenEndpoint(784));    AlbaNumberInterval interval3(createOpenEndpoint(645), createOpenEndpoint(784));
    AlbaNumberInterval interval4(createOpenEndpoint(645), createOpenEndpoint(784));

    interval1.setNewEndpoint(createCloseEndpoint(640));    interval2.setNewEndpoint(createCloseEndpoint(790));
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

TEST(AlbaNumberIntervalEndpointTest, GetEndpointTypeWithCheckingIfItsClosedWorks)
{
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, getEndpointTypeWithCheckingIfItsClosed(true));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, getEndpointTypeWithCheckingIfItsClosed(false));}

TEST(AlbaNumberIntervalEndpointTest, CreateOpenEndpointWorks)
{    AlbaNumberIntervalEndpoint endpoint(createOpenEndpoint(645));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint.getType());
    EXPECT_EQ(645, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, CreateCloseEndpointWorks)
{
    AlbaNumberIntervalEndpoint endpoint(createCloseEndpoint(784));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, CreateEndpointWorks)
{
    AlbaNumberIntervalEndpoint closeEndpoint(createEndpoint(true, 6541));
    AlbaNumberIntervalEndpoint openEndpoint(createEndpoint(false, 5416));
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, closeEndpoint.getType());
    EXPECT_EQ(6541, closeEndpoint.getValue().getInteger());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, openEndpoint.getType());
    EXPECT_EQ(5416, openEndpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalTest, CreateAllRealValuesIntervalWorks)
{
    AlbaNumberInterval interval(createAllRealValuesInterval());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), interval.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::Value::PositiveInfinity), interval.getHigherEndpoint());
}

}
