#include <Common/Container/AlbaXY.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using IntXY = AlbaXY<int>;
}

TEST(AlbaXYTest, DefaultValuesAreZero)
{
    IntXY xy;
    EXPECT_EQ(0, xy.getX());
    EXPECT_EQ(0, xy.getY());
}

TEST(AlbaXYTest, ValuesAreSetAtConstruction)
{
    IntXY xy(-5,5);
    EXPECT_EQ(-5, xy.getX());
    EXPECT_EQ(5, xy.getY());
}

TEST(AlbaXYTest, EqualityOperatorWorks)
{
    IntXY xy(-5,5);

    EXPECT_TRUE(IntXY(-5,5) == xy);
    EXPECT_FALSE(IntXY(-5,-5) == xy);
    EXPECT_FALSE(IntXY(5,-5) == xy);
    EXPECT_FALSE(IntXY(5,5) == xy);
}

TEST(AlbaXYTest, NonEqualityOperatorWorks)
{
    IntXY xy(-5,5);

    EXPECT_FALSE(IntXY(-5,5) != xy);
    EXPECT_TRUE(IntXY(-5,-5) != xy);
    EXPECT_TRUE(IntXY(5,-5) != xy);
    EXPECT_TRUE(IntXY(5,5) != xy);
}

TEST(AlbaXYTest, LessThanOperatorWorks)
{
    IntXY xy(-5,5);

    EXPECT_FALSE(IntXY(-5,5) < xy);
    EXPECT_TRUE(IntXY(-6,5) < xy);
    EXPECT_FALSE(IntXY(-4,5) < xy);
    EXPECT_TRUE(IntXY(-5,4) < xy);
    EXPECT_FALSE(IntXY(-5,6) < xy);
}

TEST(AlbaXYTest, PlusUnaryOperatorWorks)
{
    EXPECT_EQ(IntXY(1,2), +IntXY(1,2));
}

TEST(AlbaXYTest, MinusUnaryOperatorWorks)
{
    EXPECT_EQ(IntXY(-1,-2), -IntXY(1,2));
}

TEST(AlbaXYTest, PlusBinaryOperatorWorks)
{
    EXPECT_EQ(IntXY(4,-2), (IntXY(1,2)+IntXY(3,-4)));
}

TEST(AlbaXYTest, MinusBinaryOperatorWorks)
{
    EXPECT_EQ(IntXY(-2,6), (IntXY(1,2)-IntXY(3,-4)));
}

TEST(AlbaXYTest, MultiplyBinaryOperatorWorks)
{
    EXPECT_EQ(IntXY(35,-70), (IntXY(5,-10)*7));
}

TEST(AlbaXYTest, DivideBinaryOperatorWorks)
{
    EXPECT_EQ(IntXY(1,-2), (IntXY(5,-10)/5));
}

TEST(AlbaXYTest, PlusAssignmentOperatorWorks)
{
    IntXY xyzToTest(1,2);

    xyzToTest+=IntXY(3,-4);

    EXPECT_EQ(IntXY(4,-2), xyzToTest);
}

TEST(AlbaXYTest, MinusAssignmentOperatorWorks)
{
    IntXY xyzToTest(1,2);

    xyzToTest-=IntXY(3,-4);

    EXPECT_EQ(IntXY(-2,6), xyzToTest);
}

TEST(AlbaXYTest, IsEmptyWorks)
{
    EXPECT_TRUE(IntXY().isEmpty());
    EXPECT_FALSE(IntXY(-5,5).isEmpty());
}

TEST(AlbaXYTest, GetXWorks)
{
    IntXY xy(-5,5);

    EXPECT_EQ(-5, xy.getX());
}

TEST(AlbaXYTest, GetYWorks)
{
    IntXY xy(-5,5);

    EXPECT_EQ(5, xy.getY());
}

TEST(AlbaXYTest, GetXTimesYWorks)
{
    IntXY xy(-5,5);

    EXPECT_EQ(-25, xy.getXTimesY());
}

TEST(AlbaXYTest, SetXWorks)
{
    IntXY xy(-5,5);

    xy.setX(23);

    EXPECT_EQ(IntXY(23,5), xy);
}

TEST(AlbaXYTest, SetYWorks)
{
    IntXY xy(-5,5);

    xy.setY(45);

    EXPECT_EQ(IntXY(-5,45), xy);
}

TEST(AlbaXYTest, SetXAndYWorks)
{
    IntXY xy(-5,5);

    xy.setXAndY(23,45);

    EXPECT_EQ(IntXY(23,45), xy);
}

TEST(AlbaXYTest, SaveMinimumXAndYWorks)
{
    IntXY xy;

    xy.saveMinimumXAndY(IntXY(-5,5));
    xy.saveMinimumXAndY(IntXY(5,-5));
    xy.saveMinimumXAndY(IntXY(-5,-5));
    xy.saveMinimumXAndY(IntXY(5,5));

    EXPECT_EQ(IntXY(-5,-5), xy);
}

TEST(AlbaXYTest, SaveMaximumXAndYWorks)
{
    IntXY xy;

    xy.saveMaximumXAndY(IntXY(-5,5));
    xy.saveMaximumXAndY(IntXY(5,-5));
    xy.saveMaximumXAndY(IntXY(-5,-5));
    xy.saveMaximumXAndY(IntXY(5,5));

    EXPECT_EQ(IntXY(5,5), xy);
}

TEST(AlbaXYTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    IntXY xy(-5,5);

    ss<<xy;

    EXPECT_EQ("(-5,5)", ss.str());
}

}
