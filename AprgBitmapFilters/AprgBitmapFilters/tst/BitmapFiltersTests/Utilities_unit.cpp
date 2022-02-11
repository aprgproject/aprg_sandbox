#include <BitmapFilters/Utilities.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

TEST(UtilitiesTest, ConvertBitmapXYToPointWorks)
{
    BitmapXY bitmapXY1;
    BitmapXY bitmapXY2(12, 34);

    Point point1(convertBitmapXYToPoint(bitmapXY1));
    Point point2(convertBitmapXYToPoint(bitmapXY2));

    EXPECT_EQ(Point(0,0), point1);
    EXPECT_EQ(Point(12,34), point2);
}

TEST(UtilitiesTest, ConvertPointToBitmapXYWorks)
{
    Point point1;
    Point point2(1.4, 1.4);
    Point point3(1.5, 1.5);

    BitmapXY bitmapXY1(convertPointToBitmapXY(point1));
    BitmapXY bitmapXY2(convertPointToBitmapXY(point2));
    BitmapXY bitmapXY3(convertPointToBitmapXY(point3));

    EXPECT_EQ(BitmapXY(0,0), bitmapXY1);
    EXPECT_EQ(BitmapXY(1,1), bitmapXY2);
    EXPECT_EQ(BitmapXY(2,2), bitmapXY3);
}

}

}
