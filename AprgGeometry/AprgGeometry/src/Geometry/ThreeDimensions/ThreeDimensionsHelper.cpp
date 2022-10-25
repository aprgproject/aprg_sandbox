#include "ThreeDimensionsHelper.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

namespace threeDimensionsHelper
{
//Internal functions

double calculateMultiplierForIntersection(
        double const firstCoordinateCoefficientLine1,
        double const firstCoordinateCoefficientLine2,
        double const secondCoordinateCoefficientLine1,
        double const secondCoordinateCoefficientLine2,
        double const firstCoordinateInitialValueLine1,
        double const firstCoordinateInitialValueLine2,
        double const secondCoordinateInitialValueLine1,
        double const secondCoordinateInitialValueLine2)
{
    //put math here
    double denominator = (firstCoordinateCoefficientLine2*secondCoordinateCoefficientLine1) - (firstCoordinateCoefficientLine1*secondCoordinateCoefficientLine2);
    double numerator = ((firstCoordinateInitialValueLine1-firstCoordinateInitialValueLine2)*secondCoordinateCoefficientLine1)
            - ((secondCoordinateInitialValueLine1-secondCoordinateInitialValueLine2)*firstCoordinateCoefficientLine1);
    return numerator / denominator;
}

double calculateCrossProductTerm(
        double const firstCoordinateCoefficient1,
        double const firstCoordinateCoefficient2,
        double const secondCoordinateCoefficient1,
        double const secondCoordinateCoefficient2)
{
    return (firstCoordinateCoefficient1*secondCoordinateCoefficient2)-(secondCoordinateCoefficient1*firstCoordinateCoefficient2);
}

bool isCoordinateValuesInLineEqual(
        double const coordinateValueToCompare,
        AlbaOptional<double> const& coordinateOptionalToCompare1,
        double const coordinate2Value,
        double const coordinate2InitialValue,
        AlbaOptional<double> const& coordinateOptionalToCompare2,
        double const coordinate3Value,
        double const coordinate3InitialValue)
{
    bool result(false);
    if(coordinateOptionalToCompare1.hasContent())
    {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare1.getConstReference());
    }
    else if(coordinateOptionalToCompare2.hasContent())
    {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare2.getConstReference());
    }
    else
    {
        result = isAlmostEqual(coordinate2Value, coordinate2InitialValue)
                && isAlmostEqual(coordinate3Value, coordinate3InitialValue);
    }
    return result;
}

bool isCoordinateValuesInPlaneEqual(
        double const coordinateValueToCompare,
        AlbaOptional<double> const& coordinateOptionalToCompare)
{
    bool result(false);
    if(coordinateOptionalToCompare.hasContent())
    {
        result = isAlmostEqual(coordinateValueToCompare, coordinateOptionalToCompare.getConstReference());
    }
    else
    {
        result = true;
    }
    return result;
}

double getCoordinateinLineIntersection(
        double const coefficientOfCommonCoordinate1,
        double const coefficientOfCommonCoordinate2,
        double const coefficientOfCoordinateToDetermine1,
        double const coefficientOfCoordinateToDetermine2,
        double const dCoefficient1,
        double const dCoefficient2)
{
    //yCoordinateIntersection calculation is (a1d2-a2d1)/(a2b1-a1b2)
    double numerator = (coefficientOfCommonCoordinate1*dCoefficient2) - (coefficientOfCommonCoordinate2*dCoefficient1);
    double denominator = (coefficientOfCommonCoordinate2*coefficientOfCoordinateToDetermine1) - (coefficientOfCommonCoordinate1*coefficientOfCoordinateToDetermine2);
    return numerator/denominator;
}

//end of internal functions


//external functions

double getMagnitude(Coordinate const coordinate)
{
    return getSquareRootOfXSquaredPlusYSquaredPlusZSquared(coordinate.getX(), coordinate.getY(), coordinate.getZ());
}

double getDotProduct(Coordinate const coordinate1, Coordinate const coordinate2)
{
    return coordinate1.getX()*coordinate2.getX()+
            coordinate1.getY()*coordinate2.getY()+
            coordinate1.getZ()*coordinate2.getZ();
}

Coordinate getCrossProduct(Coordinate const coordinate1, Coordinate const coordinate2)
{
    return Coordinate(
                calculateCrossProductTerm(coordinate1.getY(), coordinate2.getY(), coordinate1.getZ(), coordinate2.getZ()),
                calculateCrossProductTerm(coordinate1.getZ(), coordinate2.getZ(), coordinate1.getX(), coordinate2.getX()),
                calculateCrossProductTerm(coordinate1.getX(), coordinate2.getX(), coordinate1.getY(), coordinate2.getY()));
}

bool isPointInLine(Point const& point, Line const& line)
{
    return isCoordinateValuesInLineEqual(point.getX(), line.calculateXFromY(point.getY()), point.getY(), line.getYInitialValue(), line.calculateXFromZ(point.getZ()), point.getZ(), line.getZInitialValue())
            && isCoordinateValuesInLineEqual(point.getY(), line.calculateYFromX(point.getX()), point.getX(), line.getXInitialValue(), line.calculateYFromZ(point.getZ()), point.getZ(), line.getZInitialValue())
            && isCoordinateValuesInLineEqual(point.getZ(), line.calculateZFromX(point.getX()), point.getX(), line.getXInitialValue(), line.calculateZFromY(point.getY()), point.getY(), line.getYInitialValue());
}

bool isPointInPlane(Point const& point, Plane const& plane)
{
    return isCoordinateValuesInPlaneEqual(point.getX(), plane.calculateXFromYAndZ(point.getY(), point.getZ()))
            && isCoordinateValuesInPlaneEqual(point.getY(), plane.calculateYFromXAndZ(point.getX(), point.getZ()))
            && isCoordinateValuesInPlaneEqual(point.getZ(), plane.calculateZFromXAndY(point.getX(), point.getY()));
}

bool isLineInPlane(Line const& line, Plane const& plane)
{
    Point point1(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue());
    Point point2(point1 + Point(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()));
    return isPointInPlane(point1, plane) && isPointInPlane(point2, plane);
}

bool areLinesParallel(Line const& line1, Line const& line2)
{
    Coordinate line1Coefficients(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
    Coordinate line2Coefficients(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());

    return areCoefficientsParallel(line1Coefficients, line2Coefficients);
}

bool arePlanesParallel(Plane const& plane1, Plane const& plane2)
{
    Coordinate plane1Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient());
    Coordinate plane2Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient());
    return areCoefficientsParallel(plane1Coefficients, plane2Coefficients);
}

bool areLinesPerpendicular(Line const& line1, Line const& line2)
{
    Coordinate line1Coefficients(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
    Coordinate line2Coefficients(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());
    return areCoefficientsPerpendicular(line1Coefficients, line2Coefficients);
}

bool arePlanesPerpendicular(Plane const& plane1, Plane const& plane2)
{
    Coordinate plane1Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient());
    Coordinate plane2Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient());
    return areCoefficientsPerpendicular(plane1Coefficients, plane2Coefficients);
}

bool areCoefficientsParallel(Coordinate const& coefficients1, Coordinate const& coefficients2)
{
    return isAlmostEqual(
                getDotProduct(coefficients1, coefficients2),
                getMagnitude(coefficients1) * getMagnitude(coefficients2));
}

bool areCoefficientsPerpendicular(Coordinate const& coefficients1, Coordinate const& coefficients2)
{
    return isAlmostEqual(getDotProduct(coefficients1, coefficients2), 0.0);
}

double getDistance(Point const& point1, Point const& point2)
{
    Point delta(point2 - point1);
    return getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(delta.getX(), delta.getY(), delta.getZ());
}

double getDistance(Line const& line, Point const& point)
{
    Plane perpendicularPlane(getPerpendicularPlaneOfALineAndUsingAPointInThePlane(line, point));
    Point nearestPoint(getPointOfIntersectionOfAPlaneAndALine(perpendicularPlane, line));
    return getDistance(point, nearestPoint);
}

double getDistance(Line const& line1, Line const& line2)
{
    double distance(0);
    if(areLinesParallel(line1, line2))
    {
        Point pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
        Plane perpendicularPlane = getPerpendicularPlaneOfALineAndUsingAPointInThePlane(line1, pointInLine1);
        Point pointInLine2 = getPointOfIntersectionOfAPlaneAndALine(perpendicularPlane, line2);
        distance = getDistance(pointInLine1, pointInLine2);
    }
    else
    {
        Coordinate directionVector1(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
        Coordinate directionVector2(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());
        Coordinate perpendicularCoefficients(getCrossProduct(directionVector1, directionVector2));

        Point pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
        Point pointInLine2(line2.getXInitialValue(), line2.getYInitialValue(), line2.getZInitialValue());

        Plane plane1(perpendicularCoefficients.getX(), perpendicularCoefficients.getY(), perpendicularCoefficients.getZ(), pointInLine1);
        Plane plane2(perpendicularCoefficients.getX(), perpendicularCoefficients.getY(), perpendicularCoefficients.getZ(), pointInLine2);

        distance = getDistance(plane1, plane2);
    }
    return distance;
}

double getDistance(Plane const& plane1, Plane const& plane2)
{
    double distance(0);
    if(arePlanesParallel(plane1, plane2))
    {
        Line perpendicularLine(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient(), Point(0, 0, 0));
        Point point1(getPointOfIntersectionOfAPlaneAndALine(plane1, perpendicularLine));
        Point point2(getPointOfIntersectionOfAPlaneAndALine(plane2, perpendicularLine));
        distance = getDistance(point1, point2);
    }
    return distance;
}

double getCosineOfAngleUsing2Deltas(Coordinate const& delta1, Coordinate const& delta2)
{
    //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double numeratorPart = getDotProduct(delta1, delta2);
    double denominatorPart = getMagnitude(delta1) * getMagnitude(delta2);
    return numeratorPart/denominatorPart;
}

AlbaAngle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC)
{
    Point deltaBA(pointB-pointA);
    Point deltaCA(pointC-pointA);
    Coordinate coefficients1(deltaBA.getX(), deltaBA.getY(), deltaBA.getZ());
    Coordinate coefficients2(deltaCA.getX(), deltaCA.getY(), deltaCA.getZ());
    return AlbaAngle(AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(coefficients1, coefficients2)));
}

AlbaAngle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    AlbaAngle smallerAngle;
    if(areLinesParallel(line1, line2))
    {
        smallerAngle = AlbaAngle(AngleUnitType::Degrees, 0);
    }
    else
    {
        //absolute value is used to ensure lower angle
        //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
        Coordinate coefficients1(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
        Coordinate coefficients2(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());
        smallerAngle = AlbaAngle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(coefficients1, coefficients2))));
    }
    return smallerAngle;
}

AlbaAngle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    AlbaAngle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return AlbaAngle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
}

AlbaAngle getTheSmallerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    AlbaAngle smallerAngle;
    if(arePlanesParallel(plane1, plane2))
    {
        smallerAngle = AlbaAngle(AngleUnitType::Degrees, 0);
    }
    else
    {
        Coordinate coefficients1(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient());
        Coordinate coefficients2(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient());
        smallerAngle = AlbaAngle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(coefficients1, coefficients2))));
    }
    return smallerAngle;
}

AlbaAngle getTheLargerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    AlbaAngle smallerAngle(getTheSmallerDihedralAngleBetweenTwoPlanes(plane1, plane2));
    return AlbaAngle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
}

Point getMidpoint(Point const& point1, Point const& point2)
{
    return Point((point1.getX()+point2.getX())/2, (point1.getY()+point2.getY())/2, (point1.getZ()+point2.getZ())/2);
}

Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2)
{
    double multiplier1 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getBCoefficient(), line2.getBCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getYInitialValue(), line2.getYInitialValue());
    //double multiplier2 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getCCoefficient(), line2.getCCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getZInitialValue(), line2.getZInitialValue());
    //double multiplier3 = calculateMultiplierForIntersection(line1.getCCoefficient(), line2.getCCoefficient(), line1.getACoefficient(), line2.getACoefficient(), line1.getZInitialValue(), line2.getZInitialValue(), line1.getXInitialValue(), line2.getXInitialValue());
    //assert(isAlmostEqual(multiplier1, multiplier2));
    //assert(isAlmostEqual(multiplier1, multiplier3));
    //assert(isAlmostEqual(multiplier2, multiplier3));
    return Point(Point(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue())
                 + Point(multiplier1*line1.getACoefficient(), multiplier1*line1.getBCoefficient(), multiplier1*line1.getCCoefficient()));
}

Point getPointOfIntersectionOfAPlaneAndALine(Plane const& plane, Line const& line)
{
    assert(!isLineInPlane(line, plane));
    // aplane(xinitial+aline*mult) + bplane(yinitial+bline*mult) + cplane(zinitial+cline*mult) + dplane = 0
    double multiplierInLineNumeratorPart = plane.getACoefficient()*line.getXInitialValue()
            + plane.getBCoefficient()*line.getYInitialValue()
            + plane.getCCoefficient()*line.getZInitialValue()
            + plane.getDCoefficient();
    double multiplierInLineDenominatorPart = plane.getACoefficient()*line.getACoefficient()
            + plane.getBCoefficient()*line.getBCoefficient()
            + plane.getCCoefficient()*line.getCCoefficient();
    double multiplier = multiplierInLineNumeratorPart/multiplierInLineDenominatorPart;
    return Point(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue())
            - Point(multiplier*line.getACoefficient(), multiplier*line.getBCoefficient(), multiplier*line.getCCoefficient());
}

Line getLineWithSameSlope(Line const& line, Point const& point)
{
    return Line(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), point);
}

Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    Coordinate perpendicularCoefficients(
                getCrossProduct(Coordinate(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                                Coordinate(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));
    double yCoordinateIntersection = getCoordinateinLineIntersection(plane1.getACoefficient(), plane2.getACoefficient(), plane1.getBCoefficient(), plane2.getBCoefficient(), plane1.getDCoefficient(), plane2.getDCoefficient());
    //formats a1x+b1y+z1c+d1 = 0
    //formats a2x+b2y+z2c+d2 = 0
    //assuming z=0
    //yCoordinateIntersection calculation is (a1d2-a2d1)/(a2b1-a1b2)
    double xCoordinateIntersection = plane1.calculateXFromYAndZ(yCoordinateIntersection, 0.0).getConstReference();
    Point point1(xCoordinateIntersection, yCoordinateIntersection, 0.0);
    Point point2(point1 + Point(perpendicularCoefficients.getX(), perpendicularCoefficients.getY(), perpendicularCoefficients.getZ()));
    return Line(point1, point2);
}

Line getPerpendicularLineOfPlaneWithAPoint(Plane const& plane, Point const& point)
{
    return Line(plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient(), point.getX(), point.getY(), point.getZ());
}

Line getProjectedLineInPlaneOfASkewedPlaneAndLine(Plane const& plane, Line const& line)
{
    Coordinate planeCoefficients(plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient());
    Coordinate lineCoefficients(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient());
    Coordinate perpendicularCoefficientsPlaneAndLine(getCrossProduct(planeCoefficients, lineCoefficients));
    Coordinate directionCoefficients(getCrossProduct(planeCoefficients, perpendicularCoefficientsPlaneAndLine));
    Point pointInLine(getPointOfIntersectionOfAPlaneAndALine(plane, line));
    return Line(directionCoefficients.getX(), directionCoefficients.getY(), directionCoefficients.getZ(), pointInLine);
}

Plane getPlaneWithContainsALineAndAPoint(Line const& line, Point const& point)
{
    Point point1InLine(line.getXInitialValue(), line.getYInitialValue(), line.getZInitialValue());
    Point point2InLine(point1InLine+Point(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient()));
    return Plane(point, point1InLine, point2InLine);
}

Plane getPlaneWithTwoIntersectingLines(Line const& line1, Line const& line2)
{
    Point pointOfIntersection(getPointOfIntersectionOfTwoLines(line1, line2));
    Point pointInLine1(pointOfIntersection+Point(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()));
    Point pointInLine2(pointOfIntersection+Point(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient()));
    return Plane(pointOfIntersection, pointInLine1, pointInLine2);
}

Plane getPlaneOfTwoDifferentLinesWithSameSlope(Line const& line1, Line const& line2)
{
    Point pointInLine1(line1.getXInitialValue(), line1.getYInitialValue(), line1.getZInitialValue());
    Point secondPointInLine1(pointInLine1+Point(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()));
    Point pointInLine2(line2.getXInitialValue(), line2.getYInitialValue(), line2.getZInitialValue());
    return Plane(pointInLine1, secondPointInLine1, pointInLine2);
}

Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane)
{
    return Plane(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), pointInPerpendicularPlane);
}

}
}
}
