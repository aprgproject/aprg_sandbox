#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

using namespace alba;
using namespace std;

TEST(TwoDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4), Point(3,3));
    Line line2(Point(4,4), Point(3,3));

    EXPECT_EQ(Point(3,3), twoDimensionsHelper::getIntersection(line1, line2));
}

TEST(TwoDimensionsHelperTest, VerticalLineAndHorizontalLineIntersectionCanBeFound)
{
    Line line1(Point(4,3), Point(3,3));
    Line line2(Point(3,4), Point(3,3));
    EXPECT_EQ(Point(3,3), twoDimensionsHelper::getIntersection(line1, line2));
}

TEST(TwoDimensionsHelperTest, DistanceBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(10, twoDimensionsHelper::getDistance(Point(-3,-4), Point(3,4)));
    EXPECT_EQ(5, twoDimensionsHelper::getDistance(Point(0,5), Point(0,0)));
    EXPECT_EQ(5, twoDimensionsHelper::getDistance(Point(5,0), Point(0,0)));
}

TEST(TwoDimensionsHelperTest, GetLineWithSameSlopeAndPoint)
{
    Line lineInput(Point(0,0), Point(-1,1));
    Line expectedLine(twoDimensionsHelper::getLineWithSameSlope(lineInput, Point(2,2)));

    EXPECT_EQ(4, expectedLine.getYIntercept());
    EXPECT_EQ(4, expectedLine.getXIntercept());
    EXPECT_EQ(-1, expectedLine.getSlope());
    EXPECT_EQ(1, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(-4, expectedLine.getCCoefficient());
}

TEST(TwoDimensionsHelperTest, GetLineWithInverseSlopeAndPoint)
{
    Line lineInput(Point(0,0), Point(1,1));
    Line expectedLine(twoDimensionsHelper::getLineWithInverseSlope(lineInput, Point(2,2)));

    EXPECT_EQ(4, expectedLine.getYIntercept());
    EXPECT_EQ(4, expectedLine.getXIntercept());
    EXPECT_EQ(-1, expectedLine.getSlope());
    EXPECT_EQ(-1, expectedLine.getACoefficient());
    EXPECT_EQ(-1, expectedLine.getBCoefficient());
    EXPECT_EQ(4, expectedLine.getCCoefficient());
}

TEST(TwoDimensionsHelperTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(2, twoDimensionsHelper::getDistance(Point(2,2), Line(0,-1,4)));
    EXPECT_EQ(2, twoDimensionsHelper::getDistance(Point(2,2), Line(-1,0,4)));
    EXPECT_EQ(2*pow(2, 0.5), twoDimensionsHelper::getDistance(Point(2,2), Line(1,1,0)));
}
