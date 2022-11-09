#include <Geometry/ThreeDimensions/Utilities/ThreeDimensionsUtilities.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions::threeDimensionsUtilities;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnLineWithSlope)
{
    Point pointOnLine(-2,2,-2);
    Point pointNotOnLine(2,2,2);
    Line line(Point(0,0,0), Point(-1,1,-1));

    EXPECT_TRUE(isPointInLine(pointOnLine, line));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, line));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnHorizontalLine)
{
    Point pointOnLine(6,3,-12);
    Point pointNotOnLine(6,0,-12);
    Line horizontalLine(Point(-2,3,4), Point(2,3,-4));

    EXPECT_TRUE(isPointInLine(pointOnLine, horizontalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, horizontalLine));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnVerticalLine)
{
    Point pointOnLine(2,9,-18);
    Point pointNotOnLine(0,9,-18);
    Line verticalLine(Point(2,-3, 6), Point(2,3, -6));

    EXPECT_TRUE(isPointInLine(pointOnLine, verticalLine));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, verticalLine));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnLineParallelWithZAxis)
{
    Point pointOnLine(6,-12,6);
    Point pointNotOnLine(6,-12,0);
    Line lineParallelInZAxis(Point(-2,4,6), Point(2,-4,6));

    EXPECT_TRUE(isPointInLine(pointOnLine, lineParallelInZAxis));
    EXPECT_FALSE(isPointInLine(pointNotOnLine, lineParallelInZAxis));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnEmptyPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane;

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnInvalidPlane)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(1,-1,1);
    Plane plane(Point(3,3,3), Point(3,3,3), Point(3,3,3));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_TRUE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnPlaneWithConstantZ)
{
    Point pointOnLine(1,1,0);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,0), Point(-2,2,0), Point(2,-1,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnPlaneWithConstantY)
{
    Point pointOnLine(1,0,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,0,1), Point(-2,0,2), Point(2,0,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnPlaneWithConstantX)
{
    Point pointOnLine(0,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(0,1,1), Point(0,-2,2), Point(0,2,-1));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, PointCanBeCheckedIfItsOnPlaneWithSlope)
{
    Point pointOnLine(1,1,1);
    Point pointNotOnLine(5,5,5);
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isPointInPlane(pointOnLine, plane));
    EXPECT_FALSE(isPointInPlane(pointNotOnLine, plane));
}

TEST(ThreeDimensionsUtilitiesTest, LineCanBeCheckedIfItsOnPlaneWithSlope)
{
    Line lineOnPlane(Point(1,1,1), Point(2,0,2));
    Line lineNotOnPlane(Point(1,1,1), Point(2,2,2));
    Plane plane(Point(1,1,1), Point(2,0,2), Point(3,3,0));

    EXPECT_TRUE(isLineInPlane(lineOnPlane, plane));
    EXPECT_FALSE(isLineInPlane(lineNotOnPlane, plane));
}

TEST(ThreeDimensionsUtilitiesTest, LineCanBeCheckedIfItsParallel)
{
    EXPECT_TRUE(areLinesParallel(Line(Point(5,5,1), Point(5,5,2)), Line(Point(6,6,78), Point(6,6,108))));
    EXPECT_FALSE(areLinesParallel(Line(Point(5,5,1), Point(5,5,2)), Line(Point(6,78,6), Point(6,108,6))));

    EXPECT_TRUE(areLinesParallel(Line(Point(0,0,0), Point(1,1,1)), Line(Point(5,0,0), Point(6,1,1))));
    EXPECT_FALSE(areLinesParallel(Line(Point(0,0,0), Point(1,1,1)), Line(Point(5,0,0), Point(6,1,7))));
}

TEST(ThreeDimensionsUtilitiesTest, PlaneCanBeCheckedIfItsParallel)
{
    EXPECT_FALSE(arePlanesParallel(Plane(5,1,2,1), Plane(1,-7,1,1)));
    EXPECT_TRUE(arePlanesParallel(Plane(1,1,1,1), Plane(3,3,3,5)));
}

TEST(ThreeDimensionsUtilitiesTest, LineCanBeCheckedIfItsPerpendicular)
{
    EXPECT_FALSE(areLinesPerpendicular(Line(1,1,1,Point(1,1,1)), Line(1,1,1,Point(1,1,1))));
    EXPECT_TRUE(areLinesPerpendicular(Line(5,1,2,Point(1,1,1)), Line(1,-7,1,Point(1,1,1))));
}

TEST(ThreeDimensionsUtilitiesTest, PlaneCanBeCheckedIfItsPerpendicular)
{
    EXPECT_FALSE(arePlanesPerpendicular(Plane(1,1,1,1), Plane(1,1,1,1)));
    EXPECT_TRUE(arePlanesPerpendicular(Plane(5,1,2,1), Plane(1,-7,1,1)));
    EXPECT_TRUE(arePlanesPerpendicular(Plane(2,1,-4,-5), Plane(1,2,1,-2)));
}

TEST(ThreeDimensionsUtilitiesTest, DistanceBetween2PointsCanBeCalculated)
{
    EXPECT_EQ(pow(3, 0.5), getDistance(Point(0,0,0), Point(1,1,1)));
}

TEST(ThreeDimensionsUtilitiesTest, DistanceBetweenPointAndLineCanBeCalculated)
{
    EXPECT_EQ(1, getDistance(Line(Point(0,0,0), Point(1,0,0)), Point(0,0,1)));
}

TEST(ThreeDimensionsUtilitiesTest, DistanceBetween2LinesCanBeCalculated)
{
    EXPECT_EQ(5, getDistance(Line(Point(0,0,0), Point(1,0,0)), Line(Point(0,5,0), Point(1,5,0))));
    EXPECT_EQ(8, getDistance(Line(Point(0,0,2), Point(1,1,2)), Line(Point(0,0,10), Point(-1,-1,10))));
}

TEST(ThreeDimensionsUtilitiesTest, DistanceBetween2PlanesCanBeCalculated)
{
    EXPECT_EQ(15, getDistance(Plane(Point(1,1,5), Point(-1,1,5), Point(-1,-1,5)), Plane(Point(1,1,20), Point(-1,1,20), Point(-1,-1,20))));
}

TEST(ThreeDimensionsUtilitiesTest, GetConsineOfAngleUsing2DeltasWorks)
{
    Vector deltaVector1{2, 4, 8};
    Vector deltaVector2{16, 32, 64};
    EXPECT_DOUBLE_EQ(1, getCosineOfAngleUsing2Deltas(deltaVector1, deltaVector2));
}

TEST(ThreeDimensionsUtilitiesTest, MidpointBetweenTwoPointsCanBeCalculated)
{
    EXPECT_EQ(Point(0,0,0), getMidpoint(Point(0,0,0), Point(0,0,0)));
    EXPECT_EQ(Point(2,2,2), getMidpoint(Point(1,1,1), Point(3,3,3)));
    EXPECT_EQ(Point(-450,-900,-1350), getMidpoint(Point(100,200,300), Point(-1000,-2000,-3000)));
}

TEST(ThreeDimensionsUtilitiesTest, GetPointOfIntersectionOfTwoLinesWorks)
{
    Line line1(Point(2,4,6), Point(3,3,3));
    Line line2(Point(4,4,4), Point(3,3,3));

    EXPECT_EQ(Point(3,3,3), getPointOfIntersectionOfTwoLines(line1, line2));
}

TEST(ThreeDimensionsUtilitiesTest, GetPointOfIntersectionOfAPlaneAndALineWorks)
{
    Plane inputPlane(Point(1,0,0), Point(0,1,0), Point(0,0,1));
    Line inputLine(Point(0,0,0), Point(1,1,1));
    Point expectedPoint(getPointOfIntersectionOfAPlaneAndALine(inputPlane, inputLine));

    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getX());
    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getY());
    EXPECT_EQ(static_cast<double>(1)/3, expectedPoint.getZ());
}

TEST(TwoDimensionsUtilitiesTest, getTheInnerAngleUsingThreePointsWorks)
{
    EXPECT_EQ(0, getTheInnerAngleUsingThreePoints(Point(0,0,0), Point(0,0,1), Point(0,0,1)).getDegrees());
    EXPECT_EQ(90, getTheInnerAngleUsingThreePoints(Point(0,0,0), Point(0,0,1), Point(0,1,0)).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheInnerAngleUsingThreePoints(Point(0,0,0), Point(0,0,1), Point(0,1,1)).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetSmallerAngleBetweenTwoLinesWorks)
{
    EXPECT_EQ(0, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,0,1))).getDegrees());
    EXPECT_EQ(90, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheSmallerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,1,1))).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetLargerAngleBetweenTwoLinesWorks)
{
    EXPECT_EQ(180, getTheLargerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,0,1))).getDegrees());
    EXPECT_EQ(90, getTheLargerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,1,0))).getDegrees());
    EXPECT_DOUBLE_EQ(135, getTheLargerAngleBetweenTwoLines(Line(Point(0,0,0), Point(0,0,1)), Line(Point(0,0,0), Point(0,1,1))).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetTheSmallerDihedralAngleBetweenTwoPlanesWorks)
{
    EXPECT_EQ(0, getTheSmallerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0))).getDegrees());
    EXPECT_EQ(90, getTheSmallerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(0,0,1), Point(1,0,1))).getDegrees());
    EXPECT_DOUBLE_EQ(45, getTheSmallerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(0,1,1), Point(1,1,1))).getDegrees());
}

TEST(TwoDimensionsUtilitiesTest, GetTheLargerDihedralAngleBetweenTwoPlanesWorks)
{
    EXPECT_EQ(180, getTheLargerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0))).getDegrees());
    EXPECT_EQ(90, getTheLargerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(0,0,1), Point(1,0,1))).getDegrees());
    EXPECT_DOUBLE_EQ(135, getTheLargerDihedralAngleBetweenTwoPlanes(Plane(Point(0,0,0), Point(1,0,0), Point(1,1,0)), Plane(Point(0,0,0), Point(0,1,1), Point(1,1,1))).getDegrees());
}

TEST(ThreeDimensionsUtilitiesTest, GetLineWithSameSlopeAndPoint)
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

TEST(ThreeDimensionsUtilitiesTest, GetLineOfIntersectionOfTwoPlaneWorks)
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

TEST(ThreeDimensionsUtilitiesTest, GetPerpendicularLineOfPlaneWithAPointWorks)
{
    Plane planeInput(1, -1, 1, 0);
    Line expectedLine(getPerpendicularLineOfPlaneWithAPoint(planeInput, Point(0,0,0)));

    EXPECT_DOUBLE_EQ(1, expectedLine.getACoefficient());
    EXPECT_DOUBLE_EQ(-1, expectedLine.getBCoefficient());
    EXPECT_DOUBLE_EQ(1, expectedLine.getCCoefficient());
    EXPECT_DOUBLE_EQ(0, expectedLine.getXInitialValue());
    EXPECT_DOUBLE_EQ(0, expectedLine.getYInitialValue());
    EXPECT_DOUBLE_EQ(0, expectedLine.getZInitialValue());
}

TEST(ThreeDimensionsUtilitiesTest, GetProjectedLineInPlaneOfASkewedPlaneAndLineWorks)
{
    Plane planeInput(Point(1,0,0), Point(0,1,0), Point(0,0,1));
    Line lineInput(Point(0,0,0), Point(1,2,4));
    Line expectedLine(getProjectedLineInPlaneOfASkewedPlaneAndLine(planeInput, lineInput));

    EXPECT_EQ(4, expectedLine.getACoefficient());
    EXPECT_EQ(1, expectedLine.getBCoefficient());
    EXPECT_EQ(-5, expectedLine.getCCoefficient());
    EXPECT_DOUBLE_EQ(0.14285714285714285, expectedLine.getXInitialValue());
    EXPECT_DOUBLE_EQ(0.2857142857142857, expectedLine.getYInitialValue());
    EXPECT_DOUBLE_EQ(0.5714285714285714, expectedLine.getZInitialValue());
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneWithContainsALineAndAPointWorks)
{
    Plane expectedPlane(getPlaneWithContainsALineAndAPoint(Line(Point(0,0,0), Point(1,1,1)), Point(1,0,0)));

    EXPECT_EQ(0, expectedPlane.getACoefficient());
    EXPECT_EQ(1, expectedPlane.getBCoefficient());
    EXPECT_EQ(-1, expectedPlane.getCCoefficient());
    EXPECT_EQ(0, expectedPlane.getDCoefficient());
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneWithTwoIntersectingLinesWorks)
{
    Plane expectedPlane(getPlaneWithTwoIntersectingLines(Line(Point(0,0,0), Point(1,1,1)), Line(Point(0,0,0), Point(1,0,0))));

    EXPECT_EQ(0, expectedPlane.getACoefficient());
    EXPECT_EQ(1, expectedPlane.getBCoefficient());
    EXPECT_EQ(-1, expectedPlane.getCCoefficient());
    EXPECT_EQ(0, expectedPlane.getDCoefficient());
}

TEST(ThreeDimensionsUtilitiesTest, GetPlaneOfTwoDifferentLinesWithSameSlopeWorks)
{
    Plane expectedPlane(getPlaneOfTwoDifferentLinesWithSameSlope(Line(Point(0,0,0), Point(1,1,1)), Line(Point(0,0,1), Point(1,1,2))));
    EXPECT_EQ(1, expectedPlane.getACoefficient());
    EXPECT_EQ(-1, expectedPlane.getBCoefficient());
    EXPECT_EQ(0, expectedPlane.getCCoefficient());
    EXPECT_EQ(0, expectedPlane.getDCoefficient());
}

TEST(ThreeDimensionsUtilitiesTest, GetPerpendicularPlaneWithALineAndAPointWorks)
{
    Plane expectedPlane(getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line(Point(0,0,0), Point(1,1,1)), Point(1,0,0)));

    EXPECT_EQ(1, expectedPlane.getACoefficient());
    EXPECT_EQ(1, expectedPlane.getBCoefficient());
    EXPECT_EQ(1, expectedPlane.getCCoefficient());
    EXPECT_EQ(-1, expectedPlane.getDCoefficient());
}

}

}
