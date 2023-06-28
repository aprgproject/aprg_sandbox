#include <Geometry/TwoDimensions/Constructs/Rectangle.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace TwoDimensions {

TEST(RectangleTest, GetPointsWorks) {
    Rectangle retangle(Point(-1, 1), Point(1, -1));
    Points points(retangle.getPoints(1));

    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-1, 1), points[0]);
    EXPECT_EQ(Point(0, 1), points[1]);
    EXPECT_EQ(Point(1, 1), points[2]);
    EXPECT_EQ(Point(1, 0), points[3]);
    EXPECT_EQ(Point(1, -1), points[4]);
    EXPECT_EQ(Point(0, -1), points[5]);
    EXPECT_EQ(Point(-1, -1), points[6]);
    EXPECT_EQ(Point(-1, 0), points[7]);
}

}  // namespace TwoDimensions

}  // namespace alba
