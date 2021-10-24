#include <TwoDimensions/Rectangle.hpp>

#include <gtest/gtest.h>

using namespace alba::Dimensionless;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(RectangleTest, GetPointsWorks)
{
    Rectangle retangle(Point(-1,1), Point(1,-1));
    Points points(retangle.getPoints(1));
    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-1,1), points.at(0));
    EXPECT_EQ(Point(0,1), points.at(1));    EXPECT_EQ(Point(1,1), points.at(2));
    EXPECT_EQ(Point(1,0), points.at(3));
    EXPECT_EQ(Point(1,-1), points.at(4));
    EXPECT_EQ(Point(0,-1), points.at(5));
    EXPECT_EQ(Point(-1,-1), points.at(6));
    EXPECT_EQ(Point(-1,0), points.at(7));
}

}

}
