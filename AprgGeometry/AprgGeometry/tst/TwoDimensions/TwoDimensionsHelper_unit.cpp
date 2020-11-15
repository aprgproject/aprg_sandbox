#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(TwoDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));

    EXPECT_EQ(Point(3,3), twoDimensionsHelper::getIntersection(line1, line2));
}

TEST(TwoDimensionsHelperTest, DistanceBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(10, twoDimensionsHelper::getDistance(Point(-3,-4), Point(3,4)));
}
