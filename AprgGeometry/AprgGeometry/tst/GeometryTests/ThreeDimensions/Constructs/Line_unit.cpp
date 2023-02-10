#include <Geometry/ThreeDimensions/Constructs/Line.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(ThreeDimensionsLineTest, EmptyLine)
{
    Line line;

    EXPECT_TRUE(line.isInvalid());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_FALSE(line.getXInitialValue());
    EXPECT_FALSE(line.getYInitialValue());
    EXPECT_FALSE(line.getZInitialValue());
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
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_EQ(0, line.getXInitialValue());
    EXPECT_EQ(0, line.getYInitialValue());
    EXPECT_EQ(0, line.getZInitialValue());
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
    EXPECT_EQ(4, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-8, line.getCCoefficient());
    EXPECT_EQ(3, line.getXInitialValue());
    EXPECT_EQ(3, line.getYInitialValue());
    EXPECT_EQ(-6, line.getZInitialValue());
    EXPECT_FALSE(line.calculateXFromY(1));
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(-0.5, line.calculateXFromZ(1).value());
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(3, line.calculateYFromX(1).value());
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(3, line.calculateYFromZ(1).value());
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(-2, line.calculateZFromX(1).value());
    EXPECT_FALSE(line.calculateZFromY(1));
}

TEST(ThreeDimensionsLineTest, VerticalLine)
{
    Line line(Point(2,-3, 6), Point(2,3, -6));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(6, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());
    EXPECT_EQ(2, line.getXInitialValue());
    EXPECT_EQ(2, line.getYInitialValue());
    EXPECT_EQ(-4, line.getZInitialValue());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(2, line.calculateXFromY(1).value());
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(2, line.calculateXFromZ(1).value());
    EXPECT_FALSE(line.calculateYFromX(1));
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(-0.5, line.calculateYFromZ(1).value());
    EXPECT_FALSE(line.calculateZFromX(1));
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(-2, line.calculateZFromY(1).value());
}

TEST(ThreeDimensionsLineTest, ParallelWithZAxis)
{
    Line line(Point(-2,4,6), Point(2,-4,6));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(4, line.getACoefficient());
    EXPECT_EQ(-8, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_EQ(6, line.getXInitialValue());
    EXPECT_EQ(-12, line.getYInitialValue());
    EXPECT_EQ(6, line.getZInitialValue());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(-0.5, line.calculateXFromY(1).value());
    EXPECT_FALSE(line.calculateXFromZ(1));
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(-2, line.calculateYFromX(1).value());
    EXPECT_FALSE(line.calculateYFromZ(1));
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(6, line.calculateZFromX(1).value());
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(6, line.calculateZFromY(1).value());
}

TEST(ThreeDimensionsLineTest, LineNotParallelWithXYZAxis)
{
    Line line(Point(2,4,5), Point(3,3,3));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(-1, line.getACoefficient());
    EXPECT_EQ(1, line.getBCoefficient());
    EXPECT_EQ(2, line.getCCoefficient());
    EXPECT_EQ(7.5, line.getXInitialValue());
    EXPECT_EQ(-1.5, line.getYInitialValue());
    EXPECT_EQ(-6, line.getZInitialValue());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(5, line.calculateXFromY(1).value());
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(4, line.calculateXFromZ(1).value());
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(5, line.calculateYFromX(1).value());
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(2, line.calculateYFromZ(1).value());
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(7, line.calculateZFromX(1).value());
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(-1, line.calculateZFromY(1).value());
}

TEST(ThreeDimensionsLineTest, LineWithSlopeSet)
{
    Line line(3, 2, 1, Point(1,2,3));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(3, line.getACoefficient());
    EXPECT_EQ(2, line.getBCoefficient());
    EXPECT_EQ(1, line.getCCoefficient());
    EXPECT_EQ(-2, line.getXInitialValue());
    EXPECT_EQ(0, line.getYInitialValue());
    EXPECT_EQ(2, line.getZInitialValue());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(-0.5, line.calculateXFromY(1).value());
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(-5, line.calculateXFromZ(1).value());
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(2, line.calculateYFromX(1).value());
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(-2, line.calculateYFromZ(1).value());
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(3, line.calculateZFromX(1).value());
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(2.5, line.calculateZFromY(1).value());
}

TEST(ThreeDimensionsLineTest, LineWithSumOfCoefficientsEqualToZero)
{
    Line line(-2, 1, 1, Point(1,0,0));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(-2, line.getACoefficient());
    EXPECT_EQ(1, line.getBCoefficient());
    EXPECT_EQ(1, line.getCCoefficient());
    EXPECT_EQ(1, line.getXInitialValue());
    EXPECT_EQ(0, line.getYInitialValue());
    EXPECT_EQ(0, line.getZInitialValue());
    ASSERT_TRUE(line.calculateXFromY(1)); EXPECT_EQ(-1, line.calculateXFromY(1).value());
    ASSERT_TRUE(line.calculateXFromZ(1)); EXPECT_EQ(-1, line.calculateXFromZ(1).value());
    ASSERT_TRUE(line.calculateYFromX(1)); EXPECT_EQ(0, line.calculateYFromX(1).value());
    ASSERT_TRUE(line.calculateYFromZ(1)); EXPECT_EQ(1, line.calculateYFromZ(1).value());
    ASSERT_TRUE(line.calculateZFromX(1)); EXPECT_EQ(0, line.calculateZFromX(1).value());
    ASSERT_TRUE(line.calculateZFromY(1)); EXPECT_EQ(1, line.calculateZFromY(1).value());
}

TEST(ThreeDimensionsLineTest, LineWithSomeZeroCoefficientWorks)
{
    Line line(Point(0,40,0), Point(40,0,0));

    EXPECT_FALSE(line.isInvalid());
    EXPECT_EQ(40, line.getACoefficient());
    EXPECT_EQ(-40, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());
    EXPECT_EQ(40, line.getXInitialValue());
    EXPECT_EQ(0, line.getYInitialValue());
    EXPECT_EQ(0, line.getZInitialValue());
    EXPECT_TRUE(line.calculateXFromY(1));
    EXPECT_FALSE(line.calculateXFromZ(1));
    EXPECT_TRUE(line.calculateYFromX(1));
    EXPECT_FALSE(line.calculateYFromZ(1));
    EXPECT_TRUE(line.calculateZFromX(1));
    EXPECT_TRUE(line.calculateZFromY(1));
}

/*
//Think about this
TEST(ThreeDimensionsLineTest, LineCanBeComparedForEquality)
{
    EXPECT_EQ(Line(1,2,3), Line(10,20,30));
    EXPECT_NE(Line(1,2,3), Line(2,3,4));
}
*/

}

}
