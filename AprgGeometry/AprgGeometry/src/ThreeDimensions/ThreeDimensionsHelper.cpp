#include "ThreeDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>
#include <cassert>

using namespace alba::Dimensionless;
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
    vector<double> ratiosOfCoefficients;
    if(line1.getACoefficient()==0 || line2.getACoefficient()==0)
    {
        if(line1.getACoefficient() != line2.getACoefficient())
        {
            return false;
        }
    }
    else
    {
        ratiosOfCoefficients.emplace_back(line1.getACoefficient()/line2.getACoefficient());
    }
    if(line1.getBCoefficient()==0 || line2.getBCoefficient()==0)
    {
        if(line1.getBCoefficient() != line2.getBCoefficient())
        {
            return false;
        }
    }
    else
    {
        ratiosOfCoefficients.emplace_back(line1.getBCoefficient()/line2.getBCoefficient());
    }
    if(line1.getCCoefficient()==0 || line2.getCCoefficient()==0)
    {
        if(line1.getCCoefficient() != line2.getCCoefficient())
        {
            return false;
        }
    }
    else
    {
        ratiosOfCoefficients.emplace_back(line1.getCCoefficient()/line2.getCCoefficient());
    }
    bool result(true);
    AlbaOptional<double> previousRatioOfCoefficient;
    for(double const ratioOfCoefficient : ratiosOfCoefficients)
    {
        if(previousRatioOfCoefficient.hasContent())
        {
            result = previousRatioOfCoefficient.getConstReference() == ratioOfCoefficient;
            if(!result)
            {
                break;
            }
        }
        previousRatioOfCoefficient.setValue(ratioOfCoefficient);
    }
    return result;
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

double getCosineOfAngleUsing2Deltas(Coefficients const& c1, Coefficients const& c2)
{
    //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double numeratorPart = getDotProduct(c1, c2);
    double denominatorPart = getSquareRootOfXSquaredPlusYSquaredPlusZSquared(c1.getX(), c1.getY(), c1.getZ()) *
            getSquareRootOfXSquaredPlusYSquaredPlusZSquared(c2.getX(), c2.getY(), c2.getZ());
    return numeratorPart/denominatorPart;
}

Point getMidpoint(Point const& point1, Point const& point2)
{
    return Point((point1.getX()+point2.getX())/2, (point1.getY()+point2.getY())/2, (point1.getZ()+point2.getZ())/2);
}

Point getPointOfIntersectionOfTwoLines(Line const& line1, Line const& line2)
{
    double multiplier1 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getBCoefficient(), line2.getBCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getYInitialValue(), line2.getYInitialValue());
    double multiplier2 = calculateMultiplierForIntersection(line1.getACoefficient(), line2.getACoefficient(), line1.getCCoefficient(), line2.getCCoefficient(), line1.getXInitialValue(), line2.getXInitialValue(), line1.getZInitialValue(), line2.getZInitialValue());
    double multiplier3 = calculateMultiplierForIntersection(line1.getCCoefficient(), line2.getCCoefficient(), line1.getACoefficient(), line2.getACoefficient(), line1.getZInitialValue(), line2.getZInitialValue(), line1.getXInitialValue(), line2.getXInitialValue());
    assert(isAlmostEqual(multiplier1, multiplier2));
    assert(isAlmostEqual(multiplier1, multiplier3));
    assert(isAlmostEqual(multiplier2, multiplier3));
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

Angle getTheInnerAngleUsingThreePointsBAC(Point const& pointA, Point const& pointB, Point const& pointC)
{
    Point deltaBA(pointB-pointA);
    Point deltaCA(pointC-pointA);
    Coefficients c1(deltaBA.getX(), deltaBA.getY(), deltaBA.getZ());
    Coefficients c2(deltaCA.getX(), deltaCA.getY(), deltaCA.getZ());
    return Angle(AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(c1,c2)));
}

Angle getTheSmallerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    Angle smallerAngle;
    if(areLinesParallel(line1, line2))
    {
        smallerAngle = Angle(AngleUnitType::Degrees, 0);
    }
    else
    {
        //absolute value is used to ensure lower angle
        //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
        Coefficients c1(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
        Coefficients c2(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());
        smallerAngle = Angle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(c1,c2))));
    }
    return smallerAngle;
}

Angle getTheLargerAngleBetweenTwoLines(Line const& line1, Line const& line2)
{
    Angle smallerAngle(getTheSmallerAngleBetweenTwoLines(line1, line2));
    return Angle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
}

double getDotProduct(Coefficients const coefficients1, Coefficients const coefficients2)
{
    return coefficients1.getX()*coefficients2.getX()+
            coefficients1.getY()*coefficients2.getY()+
            coefficients1.getZ()*coefficients2.getZ();
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

Line getLineOfIntersectionOfTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    Coefficients perpendicularCoefficients(
                getCrossProduct(Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                                Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));
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

Plane getPerpendicularPlaneOfALineAndUsingAPointInThePlane(Line const& line, Point const& pointInPerpendicularPlane)
{
    return Plane(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient(), pointInPerpendicularPlane);
}

}
}
}
