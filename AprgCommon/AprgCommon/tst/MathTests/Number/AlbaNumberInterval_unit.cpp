#include <Math/Number/AlbaNumberInterval.hpp>
#include <Math/Number/AlbaNumberIntervalHelpers.hpp>

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
