#include <Geometry/ThreeDimensions/Point.hpp>

#include <gtest/gtest.h>

using namespace alba::ThreeDimensions;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(ThreeDimensionsPointTest, PointsCanBeCreated)
{
    Point point (100, 200, 300);
    EXPECT_EQ(100, point.getX());
    EXPECT_EQ(200, point.getY());
    EXPECT_EQ(300, point.getZ());
}

}

}
