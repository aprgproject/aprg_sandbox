#include <ThreeDimensions/ThreeDimensionsHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions::threeDimensionsHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnLineWithSlope)
{
    Point pointOnLine(-2,2,-2);
    Point pointNotOnLine(2,2,2);
    Line line(Point(0,0,0), Point(-1,1,-1));

    EXPECT_TRUE(isPointInLine(pointOnLine, line));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, line));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnHorizontalLine)
{
    Point pointOnLine(6,3,-12);
    Point pointNotOnLine(6,0,-12);
    Line horizontalLine(Point(-2,3,4), Point(2,3,-4));

    EXPECT_TRUE(isPointInLine(pointOnLine, horizontalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, horizontalLine));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnVerticalLine)
{
    Point pointOnLine(2,9,-18);
    Point pointNotOnLine(0,9,-18);
    Line verticalLine(Point(2,-3, 6), Point(2,3, -6));

    EXPECT_TRUE(isPointInLine(pointOnLine, verticalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, verticalLine));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnLineParallelWithZAxis)
{
    Point pointOnLine(6,-12,6);
    Point pointNotOnLine(6,-12,0);
    Line lineParallelInZAxis(Point(-2,4,6), Point(2,-4,6));

    EXPECT_TRUE(isPointInLine(pointOnLine, lineParallelInZAxis));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, lineParallelInZAxis));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnEmptyPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane;

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnInvalidPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane(Point(3,3,3), Point(3,3,3), Point(3,3,3));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantZ)
{
    Point pointOnLine(1,1,0);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,0), Point(-2,2,0), Point(2,-1,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantY)
{
    Point pointOnLine(1,0,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,0,1), Point(-2,0,2), Point(2,0,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithConstantX)
{
    Point pointOnLine(0,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(0,1,1), Point(0,-2,2), Point(0,2,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, PointCanBeCheckedIfItsOnPlaneWithSlope)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsHelperTest, LineCanBeCheckedIfItsOnPlaneWithSlope)
{
    Line lineOnPlane(Point(1,1,1), Point(2,0,2));
    Line lineNotOnPlane(Point(1,1,1), Point(2,2,2));
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isLineInPlane(lineOnPlane, plane));
    EXPECT_FALSE(isLineInPlane(lineNotOnPlane, plane));
}

TEST(ThreeDimensionsHelperTest, DistanceBetween2PointsCanBeCalculated)
{
    EXPECT_EQ(pow(3, 0.5), getDistance(Point(0,0,0), Point(1,1,1)));
}

TEST(ThreeDimensionsHelperTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(1, getDistance(Line(Point(0,0,0), Point(1,0,0)), Point(0,0,1)));
}

TEST(ThreeDimensionsHelperTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0,0), getMidpoint(Point(0,0,0), Point(0,0,0)));
    EXPECT_EQ(Point(2,2,2), getMidpoint(Point(1,1,1), Point(3,3,3)));
    EXPECT_EQ(Point(-450,-900,-1350), getMidpoint(Point(100,200,300), Point(-1000,-2000,-3000)));
}

TEST(ThreeDimensionsHelperTest, GetCrossProductWorksCorrectly)
{
    Coefficients input1(1,2,3);
    Coefficients input2(4,5,6);
    Coefficients expectedCoefficients(getCrossProduct(input1, input2));

    EXPECT_EQ(-3, expectedCoefficients.getX());
    EXPECT_EQ(6, expectedCoefficients.getY());
    EXPECT_EQ(-3, expectedCoefficients.getZ());
}

TEST(ThreeDimensionsHelperTest, GetLineWithSameSlopeAndPoint)
{
    Line lineInput(Point(0,0,0), Point(-1,1,1));
    Line expectedLine(getLineWithSameSlope(lineInput, Point(2,2,2)));

    EXPECT_EQ(-1, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(1, expectedLine.getCCoefficient());
    EXPECT_EQ(8, expectedLine.getXInitialValue());
    EXPECT_EQ(-4, expectedLine.getYInitialValue());
    EXPECT_EQ(-4, expectedLine.getZInitialValue());
}

TEST(ThreeDimensionsHelperTest, LineAndLineIntersectionCanBeFound)
{
    Line line1(Point(2,4,6), Point(3,3,3));
    Line line2(Point(4,4,4), Point(3,3,3));

    EXPECT_EQ(Point(3,3,3), getPointOfIntersectionOfTwoLines(line1, line2));
}

TEST(ThreeDimensionsHelperTest, GetLineOfIntersectionOfTwoPlaneWorksCorrectly)
{
    Plane input1(Point(1,0,0), Point(0,1,0), Point(0,0,1));
    Plane input2(Point(0,0,0), Point(1,1,1), Point(0,1,1));
    Line expectedLine(getLineOfIntersectionOfTwoPlanes(input1, input2));

    EXPECT_EQ(-2, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(1, expectedLine.getCCoefficient());
    EXPECT_EQ(1, expectedLine.getXInitialValue());
    EXPECT_EQ(0, expectedLine.getYInitialValue());
    EXPECT_EQ(0, expectedLine.getZInitialValue());
}

TEST(ThreeDimensionsHelperTest, GetPointOfIntersectionOfAPlaneAndALineWorksCorrectly)
{
    Plane inputPlane(Point(1,0,0), Point(0,1,0), Point(0,0,1));
    Line inputLine(Point(0,0,0), Point(1,1,1));
    Point expectedPoint(getPointOfIntersectionOfAPlaneAndALine(inputPlane, inputLine));

    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getX());
    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getY());
    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getZ());
}

TEST(ThreeDimensionsHelperTest, GetPerpendicularPlaneWithALineAndAPointWorksCorrectly)
{
    Plane expectedLine(getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line(Point(0,0,0), Point(1,1,1)), Point(1,0,0)));

    EXPECT_EQ(1, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(1, expectedLine.getCCoefficient());
    EXPECT_EQ(-1, expectedLine.getDCoefficient());
}

}

}
