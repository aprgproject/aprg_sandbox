#include <TwoDimensions/Line.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions;
using namespace std;

TEST(LineTest, EmptyLine)
{
    Line line;

    EXPECT_EQ(LineType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-10,-10), Point(10,10), 1));
    ASSERT_TRUE(points.empty());
}

TEST(LineTest, InvalidLine)
{
    Line line(Point(3,3), Point(3,3));

    EXPECT_EQ(LineType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-10,-10), Point(10,10), 1));
    ASSERT_TRUE(points.empty());
}

TEST(LineTest, HorizontalLine)
{
    Line line(Point(-2,3), Point(2,3));

    EXPECT_EQ(LineType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getSlope());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(-4, line.getBCoefficient());
    EXPECT_EQ(12, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(LineTest, VerticalLine)
{
    Line line(Point(2,-3), Point(2,3));

    EXPECT_EQ(LineType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(INFINITY, line.getSlope());
    EXPECT_EQ(6, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());

    Points points(line.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);
    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(LineTest, LineWithSlope)
{
    Line line(Point(-2,-3), Point(2,3));

    EXPECT_EQ(LineType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(1.5, line.getSlope());
    EXPECT_EQ(6, line.getACoefficient());
    EXPECT_EQ(-4, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);
    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(LineTest, HorizontalLineWithPointsReversed)
{
    Line line(Point(2,3), Point(-2,3));

    EXPECT_EQ(LineType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getSlope());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(4, line.getBCoefficient());
    EXPECT_EQ(-12, line.getCCoefficient());

    Points points(line.getPoints(Point(2,10), Point(-2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(-1,3), points[3]);
    EXPECT_EQ(Point(-2,3), points[4]);
}

TEST(LineTest, VerticalLineWithPointsReversed)
{
    Line line(Point(2,3), Point(2,-3));

    EXPECT_EQ(LineType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(INFINITY, line.getSlope());
    EXPECT_EQ(-6, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(12, line.getCCoefficient());

    Points points(line.getPoints(Point(10,3), Point(-10,-3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(2,2), points[1]);
    EXPECT_EQ(Point(2,1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,-1), points[4]);
    EXPECT_EQ(Point(2,-2), points[5]);
    EXPECT_EQ(Point(2,-3), points[6]);
}

TEST(LineTest, LineWithSlopeWithPointsReversed)
{
    Line line(Point(2,3), Point(-2,-3));

    EXPECT_EQ(LineType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(1.5, line.getSlope());
    EXPECT_EQ(-6, line.getACoefficient());
    EXPECT_EQ(4, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(2,3), Point(-2,-3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(2,3), points[0]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[1]);
    EXPECT_EQ(Point(1,1.5), points[2]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[5]);
    EXPECT_EQ(Point(-1,-1.5), points[6]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[7]);
    EXPECT_EQ(Point(-2,-3), points[8.]);
}

TEST(LineTest, LineWithNegativeSlope)
{
    Line line(Point(2,0), Point(0,2));

    EXPECT_EQ(LineType::WithNegativeSlope, line.getType());
    EXPECT_EQ(2, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(-1, line.getSlope());
    EXPECT_EQ(2, line.getACoefficient());
    EXPECT_EQ(2, line.getBCoefficient());
    EXPECT_EQ(-4, line.getCCoefficient());

    Points points(line.getPoints(Point(2,0), Point(0,2), 1));
    ASSERT_EQ(3u, points.size());
    EXPECT_EQ(Point(2,0), points[0]);
    EXPECT_EQ(Point(1,1), points[1]);
    EXPECT_EQ(Point(0,2), points[2]);
}

TEST(LineTest, InvalidLineConstructedByCoefficients)
{
    Line line(0,0,10);

    EXPECT_EQ(LineType::Invalid, line.getType());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(10, line.getCCoefficient());
}

TEST(LineTest, HorizontalLineConstructedByCoefficients)
{
    Line line(0,-1,3);

    EXPECT_EQ(LineType::Horizontal, line.getType());
    EXPECT_EQ(3, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(0, line.getSlope());
    EXPECT_EQ(0, line.getACoefficient());
    EXPECT_EQ(-1, line.getBCoefficient());
    EXPECT_EQ(3, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,10), Point(2,-10), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-2,3), points[0]);
    EXPECT_EQ(Point(-1,3), points[1]);
    EXPECT_EQ(Point(0,3), points[2]);
    EXPECT_EQ(Point(1,3), points[3]);
    EXPECT_EQ(Point(2,3), points[4]);
}

TEST(LineTest, VerticalLineConstructedByCoefficients)
{
    Line line(1,0,-2);

    EXPECT_EQ(LineType::Vertical, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(2, line.getXIntercept());
    EXPECT_EQ(INFINITY, line.getSlope());
    EXPECT_EQ(1, line.getACoefficient());
    EXPECT_EQ(0, line.getBCoefficient());
    EXPECT_EQ(-2, line.getCCoefficient());

    Points points(line.getPoints(Point(10,-3), Point(-10,3), 1));
    ASSERT_EQ(7u, points.size());
    EXPECT_EQ(Point(2,-3), points[0]);
    EXPECT_EQ(Point(2,-2), points[1]);
    EXPECT_EQ(Point(2,-1), points[2]);
    EXPECT_EQ(Point(2,0), points[3]);
    EXPECT_EQ(Point(2,1), points[4]);
    EXPECT_EQ(Point(2,2), points[5]);
    EXPECT_EQ(Point(2,3), points[6]);
}

TEST(LineTest, LineWithSlopeConstructedByCoefficients)
{
    Line line(3,-2,0);

    EXPECT_EQ(LineType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(1.5, line.getSlope());
    EXPECT_EQ(3, line.getACoefficient());
    EXPECT_EQ(-2, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-3), Point(2,3), 1));
    ASSERT_EQ(9u, points.size());
    EXPECT_EQ(Point(-2,-3), points[0]);
    EXPECT_EQ(Point(-1.33333333333333333,-2), points[1]);
    EXPECT_EQ(Point(-1,-1.5), points[2]);
    EXPECT_EQ(Point(-0.66666666666666666,-1), points[3]);
    EXPECT_EQ(Point(0,0), points[4]);
    EXPECT_EQ(Point(0.66666666666666666,1), points[5]);
    EXPECT_EQ(Point(1,1.5), points[6]);
    EXPECT_EQ(Point(1.33333333333333333,2), points[7]);
    EXPECT_EQ(Point(2,3), points[8]);
}

TEST(LineTest, PointsAreCorrectForLineWithSteepSlope)
{
    Line line(-5,1,0);

    EXPECT_EQ(LineType::WithPositiveSlope, line.getType());
    EXPECT_EQ(0, line.getYIntercept());
    EXPECT_EQ(0, line.getXIntercept());
    EXPECT_EQ(5, line.getSlope());
    EXPECT_EQ(-5, line.getACoefficient());
    EXPECT_EQ(1, line.getBCoefficient());
    EXPECT_EQ(0, line.getCCoefficient());

    Points points(line.getPoints(Point(-2,-2), Point(2,2), 1));
    ASSERT_EQ(5u, points.size());
    EXPECT_EQ(Point(-0.4,-2), points[0]);
    EXPECT_EQ(Point(-0.2,-1), points[1]);
    EXPECT_EQ(Point(0,0), points[2]);
    EXPECT_EQ(Point(0.2,1), points[3]);
    EXPECT_EQ(Point(0.4,2), points[4]);
}

TEST(LineTest, LineWithExtremeSlopeWithManyPoints)
{
    Line line(1,0.229085,-868.451);

    EXPECT_EQ(LineType::WithNegativeSlope, line.getType());
    EXPECT_EQ(3790.9553222602962705, line.getYIntercept());
    EXPECT_EQ(868.451, line.getXIntercept());
    EXPECT_EQ(-4.3651919593164105748, line.getSlope());
    EXPECT_EQ(1, line.getACoefficient());
    EXPECT_EQ(0.229085, line.getBCoefficient());
    EXPECT_EQ(-868.451, line.getCCoefficient());

    Points points(line.getPoints(Point(0,0), Point(3194,3966), 1));
    ASSERT_EQ(4659u, points.size());
}

TEST(LineTest, LineCanBeComparedForEquality)
{
    EXPECT_EQ(Line(1,2,3), Line(10,20,30));
    EXPECT_NE(Line(1,2,3), Line(2,3,4));
}
