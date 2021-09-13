#include <Math/Number/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

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

TEST(AlbaNumberIntervalTest, CreateAllRealValuesIntervalWorks)
{
    AlbaNumberInterval interval(createAllRealValuesInterval());

    EXPECT_EQ(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), interval.getLowerEndpoint());
    EXPECT_EQ(createOpenEndpoint(AlbaNumber::Value::PositiveInfinity), interval.getHigherEndpoint());
}


}
