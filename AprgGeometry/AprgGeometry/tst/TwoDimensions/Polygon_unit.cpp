#include <TwoDimensions/Polygon.hpp>
#include <TwoDimensions/Quadrilateral.hpp>
#include <TwoDimensions/Triangle.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(PolygonTest, PolygonCanBeCreated)
{
    Polygon<3> polygon{Point(1,1), Point(2,3), Point(0,17)};
}

TEST(TriangleTest, TriangleCanBeCreated)
{
    Triangle triangle(Point(1,1), Point(2,3), Point(0,17));
}

TEST(TriangleTest, QuadilateralCanBeCreated)
{
    Quadrilateral quadrilateral(Point(1,1), Point(2,3), Point(0,17), Point(-100, 4));
}
