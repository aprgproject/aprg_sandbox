#include "ThreeDimensionsHelper.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

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
    //put math here
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
    CoefficientRatios coefficientRatios(
                getRatioOfEachCoefficient(
                Coefficients(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()),
                Coefficients(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient())));

    return areCoefficientsRatiosParallel(coefficientRatios);
}

bool arePlanesParallel(Plane const& plane1, Plane const& plane2)
{
    CoefficientRatios coefficientRatios(
                getRatioOfEachCoefficient(
                Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));

    return areCoefficientsRatiosParallel(coefficientRatios);
}

bool areLinesPerpendicular(Line const& line1, Line const& line2)
{
    Coefficients coefficients(
                getProductOfEachCoefficient(
                Coefficients(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient()),
                Coefficients(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient())));

    return areCoefficientsProductPerpendicular(coefficients);
}

bool arePlanesPerpendicular(Plane const& plane1, Plane const& plane2)
{
    Coefficients coefficients(
                getProductOfEachCoefficient(
                Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));

    return areCoefficientsProductPerpendicular(coefficients);
}

bool areCoefficientsRatiosParallel(CoefficientRatios const& coefficientRatios)
{
    vector<AlbaRatio> coefficientRatiosInVector{coefficientRatios.getX(), coefficientRatios.getY(), coefficientRatios.getZ()};    AlbaOptional<double> previousRatioOfCoefficient;
    bool isParallel(true);
    for(AlbaRatio const coefficientRatio : coefficientRatiosInVector)
    {        if(coefficientRatio.isOnlyOneValueZero())
        {
            isParallel=false;
        }
        else if(coefficientRatio.hasValidRatio())
        {
            double validCoefficientRatio(coefficientRatio.getValidRatioIfPossible());
            if(previousRatioOfCoefficient.hasContent())
            {
                isParallel = isAlmostEqual(previousRatioOfCoefficient.getConstReference(), validCoefficientRatio);
            }
            previousRatioOfCoefficient.setValue(validCoefficientRatio);
        }
        if(!isParallel)
        {
            break;
        }
    }
    return isParallel;
}

bool areCoefficientsProductPerpendicular(Coefficients const& coefficients)
{
    return coefficients.getX() + coefficients.getY() + coefficients.getZ() == 0;
}

double getDistance(Point const& point1, Point const& point2)
{
    Point delta(point2 - point1);    return getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(delta.getX(), delta.getY(), delta.getZ());
}

double getDistance(Line const& line, Point const& point){
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
        Coefficients directionVector1(line1.getACoefficient(), line1.getBCoefficient(), line1.getCCoefficient());
        Coefficients directionVector2(line2.getACoefficient(), line2.getBCoefficient(), line2.getCCoefficient());
        Coefficients perpendicularCoefficients(getCrossProduct(directionVector1, directionVector2));

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
        CoefficientRatios coefficientRatios(
                    getRatioOfEachCoefficient(
                    Coefficients(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient()),
                    Coefficients(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient())));
        vector<AlbaRatio> coefficientRatiosInVector{coefficientRatios.getX(), coefficientRatios.getY(), coefficientRatios.getZ()};
        AlbaOptional<double> commonRatioOptional;
        for(AlbaRatio const coefficientRatio : coefficientRatiosInVector)
        {
            if(coefficientRatio.hasValidRatio())
            {
                commonRatioOptional.setValue(coefficientRatio.getValidRatioIfPossible());
                break;
            }
        }
        if(commonRatioOptional.hasContent())
        {
            double commonRatio = commonRatioOptional.getConstReference();
            Plane reducedFormPlane1(plane1.getACoefficient()/commonRatio, plane1.getBCoefficient()/commonRatio, plane1.getCCoefficient()/commonRatio, plane1.getDCoefficient()/commonRatio);
            Plane reducedFormPlane2(plane2.getACoefficient()/commonRatio, plane2.getBCoefficient()/commonRatio, plane2.getCCoefficient()/commonRatio, plane2.getDCoefficient()/commonRatio);
            distance = getAbsoluteValue(reducedFormPlane1.getDCoefficient()-reducedFormPlane2.getDCoefficient())
                    /getSquareRootOfXSquaredPlusYSquaredPlusZSquared(reducedFormPlane1.getACoefficient(), reducedFormPlane1.getBCoefficient(), reducedFormPlane1.getCCoefficient());
        }
    }
    return distance;
}

double getCosineOfAngleUsing2Deltas(Coefficients const& c1, Coefficients const& c2)
{
    //from cos theta = (dotproduct of coefficients v1 and v2)/(magnitude of v1 * magnitude of v2)
    double numeratorPart = getDotProduct(c1, c2);
    double denominatorPart = getSquareRootOfXSquaredPlusYSquaredPlusZSquared(c1.getX(), c1.getY(), c1.getZ()) *
            getSquareRootOfXSquaredPlusYSquaredPlusZSquared(c2.getX(), c2.getY(), c2.getZ());
    return numeratorPart/denominatorPart;
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

CoefficientRatios getRatioOfEachCoefficient(Coefficients const& first, Coefficients const& second)
{
    return CoefficientRatios(AlbaRatio(first.getX(), second.getX()), AlbaRatio(first.getY(), second.getY()), AlbaRatio(first.getZ(), second.getZ()));
}

Coefficients getProductOfEachCoefficient(Coefficients const& first, Coefficients const& second)
{
    return Coefficients(first.getX() * second.getX(), first.getY() * second.getY(), first.getZ() * second.getZ());
}

Angle getTheInnerAngleUsingThreePoints(Point const& pointA, Point const& pointB, Point const& pointC)
{
    Point deltaBA(pointB-pointA);    Point deltaCA(pointC-pointA);
    Coefficients c1(deltaBA.getX(), deltaBA.getY(), deltaBA.getZ());
    Coefficients c2(deltaCA.getX(), deltaCA.getY(), deltaCA.getZ());
    return Angle(AngleUnitType::Radians, acos(getCosineOfAngleUsing2Deltas(c1,c2)));}

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

Angle getTheSmallerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    Angle smallerAngle;
    if(arePlanesParallel(plane1, plane2))
    {
        smallerAngle = Angle(AngleUnitType::Degrees, 0);
    }
    else
    {
        Coefficients c1(plane1.getACoefficient(), plane1.getBCoefficient(), plane1.getCCoefficient());
        Coefficients c2(plane2.getACoefficient(), plane2.getBCoefficient(), plane2.getCCoefficient());
        smallerAngle = Angle(AngleUnitType::Radians, acos(getAbsoluteValue(getCosineOfAngleUsing2Deltas(c1,c2))));
    }
    return smallerAngle;
}

Angle getTheLargerDihedralAngleBetweenTwoPlanes(Plane const& plane1, Plane const& plane2)
{
    Angle smallerAngle(getTheSmallerDihedralAngleBetweenTwoPlanes(plane1, plane2));
    return Angle(AngleUnitType::Degrees, 180-smallerAngle.getDegrees());
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

Line getPerpendicularLineOfPlaneWithAPoint(Plane const& plane, Point const& point)
{
    return Line(plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient(), point.getX(), point.getY(), point.getZ());
}

Line getProjectedLineInPlaneOfASkewedPlaneAndLine(Plane const& plane, Line const& line)
{
    Coefficients planeCoefficients(plane.getACoefficient(), plane.getBCoefficient(), plane.getCCoefficient());    Coefficients lineCoefficients(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient());
    Coefficients perpendicularCoefficientsPlaneAndLine(getCrossProduct(planeCoefficients, lineCoefficients));
    Coefficients directionCoefficients(getCrossProduct(planeCoefficients, perpendicularCoefficientsPlaneAndLine));
    Point pointInLine(getPointOfIntersectionOfAPlaneAndALine(plane, line));    return Line(directionCoefficients.getX(), directionCoefficients.getY(), directionCoefficients.getZ(), pointInLine);
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
