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

TEST(TriangleTest, PointsInTriangleAreCorrect)
{
    Triangle triangle(Point(0,0), Point(3,3), Point(0,6));
    Points points(triangle.getPoints(1));
    cout<<"final vlaues:"<<endl;
    cout<<points[0].getDisplayableString()<<endl;
    cout<<points[1].getDisplayableString()<<endl;
    cout<<points[2].getDisplayableString()<<endl;
    cout<<points[3].getDisplayableString()<<endl;
    cout<<points[4].getDisplayableString()<<endl;
    cout<<points[5].getDisplayableString()<<endl;
    cout<<points[6].getDisplayableString()<<endl;
    cout<<points[7].getDisplayableString()<<endl;
    ASSERT_EQ(8u, points.size());
    EXPECT_EQ(Point(0,0), points[0]);
    EXPECT_EQ(Point(1,1), points[1]);
    EXPECT_EQ(Point(2,2), points[2]);
    EXPECT_EQ(Point(3,3), points[3]);
    EXPECT_EQ(Point(2,4), points[4]);
}

TEST(TriangleTest, QuadilateralCanBeCreated)
{
    Quadrilateral quadrilateral(Point(1,1), Point(2,3), Point(0,17), Point(-100, 4));}