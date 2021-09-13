#include <Math/Number/AlbaNumberIntervalEndpoint.hpp>

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
    AlbaNumberIntervalEndpoint endpoint2(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint endpoint3(AlbaNumberIntervalEndpoint::Type::Open, 784);
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
    AlbaNumberIntervalEndpoint endpoint(AlbaNumberIntervalEndpoint::Type::Open, 784);

    endpoint.setType(AlbaNumberIntervalEndpoint::Type::Close);

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}


}
