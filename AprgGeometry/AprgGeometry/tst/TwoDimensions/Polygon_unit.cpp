#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Polygon.hpp>
#include <TwoDimensions/Quadrilateral.hpp>
#include <TwoDimensions/Rectangle.hpp>
#include <TwoDimensions/Triangle.hpp>

#include <gtest/gtest.h>

using namespace alba::Dimensionless;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolygonTest, PolygonCanBeCreated)
{
    Polygon<3> polygon{Point(1,1), Point(2,3), Point(0,17)};
}

TEST(TriangleTest, TriangleCanBeCreated)
{
    Triangle triangle(Point(1,1), Point(2,3), Point(0,17));
}

TEST(TriangleTest, GetLengthOfSidesAreCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    array<double, 3> lengthOfSides(triangle.getLengthOfSides());

    EXPECT_DOUBLE_EQ(4, lengthOfSides[0]);
    EXPECT_DOUBLE_EQ(5.6568542494923806, lengthOfSides[1]);
    EXPECT_DOUBLE_EQ(4, lengthOfSides[2]);
}

TEST(TriangleTest, GetAnglesAreCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));
    Angles angles(triangle.getAnglesAtVertices());

    ASSERT_EQ(3u, angles.size());
    EXPECT_DOUBLE_EQ(90, angles[0].getDegrees());
    EXPECT_DOUBLE_EQ(45, angles[1].getDegrees());
    EXPECT_DOUBLE_EQ(45, angles[2].getDegrees());
}

TEST(TriangleTest, GetSumOfAnglesIsCorrect)
{
    Triangle triangle(Point(0,0), Point(0,4), Point(4,0));

    EXPECT_DOUBLE_EQ(180, triangle.getSumOfAngles().getDegrees());
}

TEST(TriangleTest, GetPointsAreCorrect)
{
    Triangle triangle(Point(0,0), Point(3,3), Point(0,6));
    Points points(triangle.getPoints(1));

    ASSERT_EQ(12u, points.size());
    EXPECT_EQ(Point(0,0), points[0]);
    EXPECT_EQ(Point(1,1), points[1]);
    EXPECT_EQ(Point(2,2), points[2]);
    EXPECT_EQ(Point(3,3), points[3]);
    EXPECT_EQ(Point(2,4), points[4]);
    EXPECT_EQ(Point(1,5), points[5]);
    EXPECT_EQ(Point(0,6), points[6]);
    EXPECT_EQ(Point(0,5), points[7]);
    EXPECT_EQ(Point(0,4), points[8]);
    EXPECT_EQ(Point(0,3), points[9]);
    EXPECT_EQ(Point(0,2), points[10]);
    EXPECT_EQ(Point(0,1), points[11]);
}

TEST(TriangleTest, QuadilateralCanBeCreated)
{
    Quadrilateral quadrilateral(Point(1,1), Point(2,3), Point(0,17), Point(-100, 4));
}

TEST(QuadrilateralTest, GetPointsAreCorrect)
{
    Quadrilateral quadrilateral(Point(-2,0), Point(0,-2), Point(2,0), Point(0,2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(-2,0), points[0]);
    EXPECT_EQ(Point(-1,-1), points[1]);
    EXPECT_EQ(Point(0,-2), points[2]);
    EXPECT_EQ(Point(1,-1), points[3]);
    EXPECT_EQ(Point(2,0), points[4]);
    EXPECT_EQ(Point(1,1), points[5]);
    EXPECT_EQ(Point(0,2), points[6]);
    EXPECT_EQ(Point(-1,1), points[7]);
}

TEST(RectangleTest, GetPointsAreCorrect)
{
    Rectangle retangle(Point(-1,1), Point(1,-1));
    Points points(retangle.getPoints(1));

    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(-1,1), points[0]);
    EXPECT_EQ(Point(0,1), points[1]);
    EXPECT_EQ(Point(1,1), points[2]);
    EXPECT_EQ(Point(1,0), points[3]);
    EXPECT_EQ(Point(1,-1), points[4]);
    EXPECT_EQ(Point(0,-1), points[5]);
    EXPECT_EQ(Point(-1,-1), points[6]);
    EXPECT_EQ(Point(-1,0), points[7]);
}

TEST(QuadrilateralTest, DISABLED_PointsInQuadilateralAreCorrectWhenOutOfOrderVerticesAreUsed)
{
    //how can this be done?
    Quadrilateral quadrilateral(Point(-2,0), Point(2,0), Point(0,2), Point(0,-2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(-2,0), points[0]);
    EXPECT_EQ(Point(-1,-1), points[1]);
    EXPECT_EQ(Point(0,-2), points[2]);
    EXPECT_EQ(Point(1,-1), points[3]);
    EXPECT_EQ(Point(2,0), points[4]);
    EXPECT_EQ(Point(1,1), points[5]);
    EXPECT_EQ(Point(0,2), points[6]);
    EXPECT_EQ(Point(-1,1), points[7]);
}

}

}
