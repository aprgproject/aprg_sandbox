#include <Geometry/TwoDimensions/Triangle.hpp>

#include <gtest/gtest.h>
#include <cmath>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(TriangleTest, TriangleCanBeCreated)
{
    Triangle triangle(Point(1,1), Point(2,3), Point(0,17));
}

TEST(TriangleTest, GetLengthOfSidesAreCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    array<double, 3> lengthOfSides(triangle.getLengthOfSides());

    EXPECT_DOUBLE_EQ(4, lengthOfSides.at(0));
    EXPECT_DOUBLE_EQ(5.6568542494923806, lengthOfSides.at(1));
    EXPECT_DOUBLE_EQ(4, lengthOfSides.at(2));
}

TEST(TriangleTest, GetAnglesAreCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    AlbaAngles angles(triangle.getAnglesAtVertices());

    ASSERT_EQ(3U, angles.size());
    EXPECT_DOUBLE_EQ(90, angles.at(0).getDegrees());
    EXPECT_DOUBLE_EQ(45, angles.at(1).getDegrees());
    EXPECT_DOUBLE_EQ(45, angles.at(2).getDegrees());
}

TEST(TriangleTest, GetSumOfAnglesIsCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_DOUBLE_EQ(180, triangle.getSumOfAngles().getDegrees());
}

TEST(TriangleTest, IsEquilateralWorks)
{
    Triangle regularTriangle(Point(1,0), Point(-1,0), Point(0,sqrt(3)));
    Triangle nonRegularTriangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_TRUE(regularTriangle.isEquilateral());
    EXPECT_FALSE(nonRegularTriangle.isEquilateral());
}

TEST(TriangleTest, IsEquiangularWorksCorrect)
{
    Triangle regularTriangle(Point(1,0), Point(-1,0), Point(0,sqrt(3)));
    Triangle nonRegularTriangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_TRUE(regularTriangle.isEquiangular());
    EXPECT_FALSE(nonRegularTriangle.isEquiangular());
}

TEST(TriangleTest, IsRegularWorksCorrect)
{
    Triangle regularTriangle(Point(1,0), Point(-1,0), Point(0,sqrt(3)));
    Triangle nonRegularTriangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_TRUE(regularTriangle.isRegular());
    EXPECT_FALSE(nonRegularTriangle.isRegular());
}

TEST(TriangleTest, IsIsocelesWorksCorrect)
{
    Triangle regularTriangle(Point(1,0), Point(-1,0), Point(0,sqrt(3)));
    Triangle isocelesTriangle(Point(0,0), Point(0,4), Point(4,0));
    Triangle nonIsocelesTriangle(Point(0,0), Point(0,4), Point(5,0));

    EXPECT_TRUE(regularTriangle.isIsoceles());
    EXPECT_TRUE(isocelesTriangle.isIsoceles());
    EXPECT_FALSE(nonIsocelesTriangle.isIsoceles());
}

TEST(TriangleTest, IsRightTriangleWorksCorrect)
{
    Triangle regularTriangle(Point(1,0), Point(-1,0), Point(0,sqrt(3)));
    Triangle rightTriangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_FALSE(regularTriangle.isRightTriangle());
    EXPECT_TRUE(rightTriangle.isRightTriangle());
}

TEST(TriangleTest, GetPointsWorks)
{
    Triangle triangle(Point(0,0), Point(3,3), Point(0,6));
    Points points(triangle.getPoints(1));

    ASSERT_EQ(12U, points.size());
    EXPECT_EQ(Point(0,0), points.at(0));
    EXPECT_EQ(Point(1,1), points.at(1));
    EXPECT_EQ(Point(2,2), points.at(2));
    EXPECT_EQ(Point(3,3), points.at(3));
    EXPECT_EQ(Point(2,4), points.at(4));
    EXPECT_EQ(Point(1,5), points.at(5));
    EXPECT_EQ(Point(0,6), points.at(6));
    EXPECT_EQ(Point(0,5), points.at(7));
    EXPECT_EQ(Point(0,4), points.at(8));
    EXPECT_EQ(Point(0,3), points.at(9));
    EXPECT_EQ(Point(0,2), points.at(10));
    EXPECT_EQ(Point(0,1), points.at(11));
}

}

}
