#include "ThreeDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>
#include <cassert>

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
        double const firstCoordinateCoefficient1,
        double const firstCoordinateCoefficient2,
        double const secondCoordinateCoefficient1,
        double const secondCoordinateCoefficient2,
        double const firstCoordinateInitialValue1,
        double const firstCoordinateInitialValue2,
        double const secondCoordinateInitialValue1,
        double const secondCoordinateInitialValue2)
{
    double denominator = (firstCoordinateCoefficient2*secondCoordinateCoefficient1) - (firstCoordinateCoefficient1*secondCoordinateCoefficient2);
    double numerator = ((firstCoordinateInitialValue1-firstCoordinateInitialValue2)*secondCoordinateCoefficient1)
            - ((secondCoordinateInitialValue1-secondCoordinateInitialValue2)*firstCoordinateCoefficient1);
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
        result = isConsideredEqual(coordinateValueToCompare, coordinateOptionalToCompare1.getConstReference());
    }
    else if(coordinateOptionalToCompare2.hasContent())
    {
        result = isConsideredEqual(coordinateValueToCompare, coordinateOptionalToCompare2.getConstReference());
    }
    else
    {
        result = isConsideredEqual(coordinate2Value, coordinate2InitialValue)
                && isConsideredEqual(coordinate3Value, coordinate3InitialValue);
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
        result = isConsideredEqual(coordinateValueToCompare, coordinateOptionalToCompare.getConstReference());
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
    double numerator = (coefficientOfCommonCoordinate1*dCoefficient2) - (coefficientOfCommonCoordinate2*dCoefficient1);
    double denominator = (coefficientOfCommonCoordinate2*coefficientOfCoordinateToDetermine1) - (coefficientOfCommonCoordinate1*coefficientOfCoordinateToDetermine2);
    return numerator/denominator;
}

//external functions

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
    Point point2(line.getXInitialValue()+line.getACoefficient(), line.getYInitialValue()+line.getBCoefficient(), line.getZInitialValue()+line.getCCoefficient());
    return isPointInPlane(point1, plane) && isPointInPlane(point2, plane);
}

Point getIntersection(Line const& line1, Line const& line2)
{
    double multiplier1 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getBCoefficient(), line2.getBCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getYInitialValue(), line2.getYInitialValue());
    double multiplier2 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getCCoefficient(), line2.getCCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getZInitialValue(), line2.getZInitialValue());
    double multiplier3 = calculateMultiplierForIntersection(line1.getCCoefficient(), line2.getCCoefficient(), line1.getACoefficient(), line2.getACoefficient(), line1.getZInitialValue(), line2.getZInitialValue(), line1.getXInitialValue(), line2.getXInitialValue());
    assert(isConsideredEqual(multiplier1, multiplier2));
    assert(isConsideredEqual(multiplier1, multiplier3));
    assert(isConsideredEqual(multiplier2, multiplier3));
    return Point(
                line1.getXInitialValue()+(multiplier1*line1.getACoefficient()),
                line1.getYInitialValue()+(multiplier1*line1.getBCoefficient()),
                line1.getZInitialValue()+(multiplier1*line1.getCCoefficient()));
}

Coefficients getCrossProduct(Coefficients const coefficients1, Coefficients const coefficients2)
{
    return Coefficients(
                calculateCrossProductTerm(coefficients1.getY(), coefficients2.getY(), coefficients1.getZ(), coefficients2.getZ()),
                calculateCrossProductTerm(coefficients1.getZ(), coefficients2.getZ(), coefficients1.getX(), coefficients2.getX()),
                calculateCrossProductTerm(coefficients1.getX(), coefficients2.getX(), coefficients1.getY(), coefficients2.getY())
                );
}

Line getLineWithSameSlope(Line const& line, Point const& point)
{
    return Line(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), point);
}

double getDistance(Point const& point1, Point const& point2)
{
    double deltaX = point2.getX() - point1.getX();
    double deltaY = point2.getY() - point1.getY();
    double deltaZ = point2.getZ() - point1.getZ();
    return getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(deltaX, deltaY, deltaZ);
}

Point getMidpoint(Point const& point1, Point const& point2)
{
    return Point((point1.getX()+point2.getX())/2, (point1.getY()+point2.getY())/2, (point1.getZ()+point2.getZ())/2);
}

Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    Coefficients perpendicularCoefficients(
                getCrossProduct(Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                                Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));
    double yCoordinateIntersection = getCoordinateinLineIntersection(plane1.getACoefficient(), plane2.getACoefficient(), plane1.getBCoefficient(), plane2.getBCoefficient(), plane1.getDCoefficient(), plane2.getDCoefficient());
    //yCoordinateIntersection calculation is (a1d2-a2d1)/(a2b1-a1b2)
    double xCoordinateIntersection = plane1.calculateXFromYAndZ(yCoordinateIntersection, 0.0).getConstReference();
    Point point1(xCoordinateIntersection, yCoordinateIntersection, 0.0);
    Point point2(point1.getX()+perpendicularCoefficients.getX(), point1.getY()+perpendicularCoefficients.getY(), point1.getZ()+perpendicularCoefficients.getZ());
    return Line(point1, point2);
}

}
}
}
