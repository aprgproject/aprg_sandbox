#include <TwoDimensions/Point.hpp>

#include <gtest/gtest.h>

using namespace alba::TwoDimensions;
using namespace std;

TEST(TwoDimensionsPointTest, PointsCanBeCreated)
{
    Point point (100, 200);
    EXPECT_EQ(100, point.getX());    EXPECT_EQ(200, point.getY());
}
