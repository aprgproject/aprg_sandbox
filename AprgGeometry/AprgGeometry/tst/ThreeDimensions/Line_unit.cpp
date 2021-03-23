#include <ThreeDimensions/Line.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions;
using namespace std;


TEST(ThreeDimensionsLineTest, EmptyLine)
{
    Line line;

    EXPECT_TRUE(line.isInvalid());
    EXPECT_FALSE(line.getXInitialValue());
    EXPECT_FALSE(line.getYInitialValue());
    EXPECT_FALSE(line.getZInitialValue());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_FALSE(line.calculateXFromY(1));
    EXPECT_FALSE(line.calculateXFromZ(1));
    EXPECT_FALSE(line.calculateYFromX(1));
    EXPECT_FALSE(line.calculateYFromZ(1));
    EXPECT_FALSE(line.calculateZFromX(1));
    EXPECT_FALSE(line.calculateZFromY(1));
}

TEST(ThreeDimensionsLineTest, InvalidLine)
{
    Line line(Point(3,3,3), Point(3,3,3));

    EXPECT_TRUE(line.isInvalid());
    EXPECT_FALSE(line.getXInitialValue());
    EXPECT_FALSE(line.getYInitialValue());
    EXPECT_FALSE(line.getZInitialValue());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_FALSE(line.calculateXFromY(1));
    EXPECT_FALSE(line.calculateXFromZ(1));
    EXPECT_FALSE(line.calculateYFromX(1));
    EXPECT_FALSE(line.calculateYFromZ(1));
    EXPECT_FALSE(line.calculateZFromX(1));
    EXPECT_FALSE(line.calculateZFromY(1));
}

TEST(ThreeDimensionsLineTest, HorizontalLine)
{
    Line line(Point(-2,3,4), Point(2,3,-4));

    EXPECT_FALSE(line.isInvalid());
    ASSERT_TRUE(line.getXInitialValue()); EXPECT_EQ(0, line.getXInitialValue().getConstReference());
    ASSERT_TRUE(line.getYInitialValue()); EXPECT_EQ(3, line.getYInitialValue().getConstReference());
    ASSERT_TRUE(line.getZInitialValue()); EXPECT_EQ(0, line.getZInitialValue().getConstReference());
    EXPECT_EQ(4, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-8, line.getCCoefficient());
    EXPECT_FALSE(line.calculateXFromY(1));
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(-0.5, line.calculateXFromZ(1).getConstReference());
    EXPECT_FALSE(line.calculateYFromX(1));
    EXPECT_FALSE(line.calculateYFromZ(1));
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(-2, line.calculateZFromX(1).getConstReference());
    EXPECT_FALSE(line.calculateZFromY(1));
}

TEST(ThreeDimensionsLineTest, VerticalLine)
{
    Line line(Point(2,-3, 6), Point(2,3, -6));

    EXPECT_FALSE(line.isInvalid());
    ASSERT_TRUE(line.getXInitialValue()); EXPECT_EQ(2, line.getXInitialValue().getConstReference());
    ASSERT_TRUE(line.getYInitialValue()); EXPECT_EQ(0, line.getYInitialValue().getConstReference());
    ASSERT_TRUE(line.getZInitialValue()); EXPECT_EQ(0, line.getZInitialValue().getConstReference());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(6, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());
    EXPECT_FALSE(line.calculateXFromY(1));
    EXPECT_FALSE(line.calculateXFromZ(1));
    EXPECT_FALSE(line.calculateYFromX(1));
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(-0.5, line.calculateYFromZ(1).getConstReference());
    EXPECT_FALSE(line.calculateZFromX(1));
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(-2, line.calculateZFromY(1).getConstReference());
}

TEST(ThreeDimensionsLineTest, ParallelWithZAxis)
{
    Line line(Point(-2,4,6), Point(2,-4,6));

    EXPECT_FALSE(line.isInvalid());
    ASSERT_TRUE(line.getXInitialValue()); EXPECT_EQ(0, line.getXInitialValue().getConstReference());
    ASSERT_TRUE(line.getYInitialValue()); EXPECT_EQ(0, line.getYInitialValue().getConstReference());
    ASSERT_TRUE(line.getZInitialValue()); EXPECT_EQ(6, line.getZInitialValue().getConstReference());
    EXPECT_EQ(4, line.getACoefficient());
    EXPECT_EQ(-8, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(-0.5, line.calculateXFromY(1).getConstReference());
    EXPECT_FALSE(line.calculateXFromZ(1));
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(-2, line.calculateYFromX(1).getConstReference());
    EXPECT_FALSE(line.calculateYFromZ(1));
    EXPECT_FALSE(line.calculateZFromX(1));
    EXPECT_FALSE(line.calculateZFromY(1));
}

TEST(ThreeDimensionsLineTest, LineWithSlope)
{
    Line line(Point(-2,-4,-8), Point(2,4,8));

    EXPECT_FALSE(line.isInvalid());
    ASSERT_TRUE(line.getXInitialValue()); EXPECT_EQ(0, line.getXInitialValue().getConstReference());
    ASSERT_TRUE(line.getYInitialValue()); EXPECT_EQ(0, line.getYInitialValue().getConstReference());
    ASSERT_TRUE(line.getZInitialValue()); EXPECT_EQ(0, line.getZInitialValue().getConstReference());
    EXPECT_EQ(4, line.getACoefficient());
    EXPECT_EQ(8, line.getBCoefficient());
    EXPECT_EQ(16, line.getCCoefficient());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(0.5, line.calculateXFromY(1).getConstReference());
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(0.25, line.calculateXFromZ(1).getConstReference());
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(2, line.calculateYFromX(1).getConstReference());
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(0.5, line.calculateYFromZ(1).getConstReference());
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(4, line.calculateZFromX(1).getConstReference());
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(2, line.calculateZFromY(1).getConstReference());
}

/*
//Think about this
TEST(ThreeDimensionsLineTest, LineCanBeComparedForEquality)
{
    EXPECT_EQ(Line(1,2,3), Line(10,20,30));
    EXPECT_NE(Line(1,2,3), Line(2,3,4));
}
*/

