#include "Ellipse.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/AlbaMathHelper.hpp>
#include <Geometry/TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

Ellipse::Ellipse()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
{}

Ellipse::Ellipse(Point const& center, double const aCoefficient, double const bCoefficient)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
{}

bool Ellipse::operator==(Ellipse const& ellipse) const
{
    return (m_center == ellipse.m_center)
            && isAlmostEqual(m_aValue, ellipse.m_aValue)
            && isAlmostEqual(m_bValue, ellipse.m_bValue);
}

bool Ellipse::operator!=(Ellipse const& ellipse) const
{
    return !((*this)==ellipse);
}

Point Ellipse::getCenter() const
{
    return m_center;
}

double Ellipse::getAValue() const
{
    return m_aValue;
}

double Ellipse::getBValue() const
{
    return m_bValue;
}

double Ellipse::getCValue() const
{
    // This is linear eccentricity
    // This is the distance from the center to a focus.
    double c=0;
    double aSquared(pow(m_aValue, 2));
    double bSquared(pow(m_bValue, 2));
    if(isAlmostEqual(aSquared, bSquared))
    {
        c=1;
    }
    if(aSquared > bSquared)
    {
        c = pow(aSquared-bSquared, 0.5);
    }
    else if(aSquared < bSquared)
    {
        c = pow(bSquared-aSquared, 0.5);
    }
    return c;
}

double Ellipse::getEccentricity() const
{
    // In mathematics, the eccentricity of a conic section is a non-negative real number that uniquely characterizes its shape.
    double eccentricity=0;
    double c(getCValue());
    if(isAlmostEqual(m_aValue, m_bValue))
    {
        eccentricity=1;
    }
    if(m_aValue > m_bValue)
    {
        eccentricity = c/getAValue();
    }
    else if(m_aValue < m_bValue)
    {
        eccentricity = c/getBValue();
    }
    return eccentricity;
}

double Ellipse::getSemiLatusRectum() const
{
    // The length of the chord through one focus, perpendicular to the major axis, is called the latus rectum.
    return pow(m_bValue, 2)/m_aValue;
}

double Ellipse::getArea() const
{
    return getPi()*m_aValue*m_bValue;
}

/*double Ellipse::getCircumference(unsigned int depthOfCalculation) const
{
    double h = pow(m_aValue-m_bValue, 2)/pow(m_aValue+m_bValue, 2);
    double totalFactor = 0;
    double currentFactor = 1;
    for(unsigned int i = 0; i<depthOfCalculation; i++)
    {
        totalFactor += currentFactor;
        currentFactor = currentFactor*h;
    }
    return getPi()*2*m_radius;
}*/

bool Ellipse::isInside(Point const& point) const
{
    return (pow((point.getX()-m_center.getX())/m_aValue, 2)) + (pow((point.getY()-m_center.getY())/m_bValue, 2)) <= 1;
}

Points Ellipse::getFoci() const
{
    Points foci;
    double a(m_aValue);
    double b(m_bValue);
    if(isAlmostEqual(a, b))
    {
        foci.emplace_back(m_center);
    }
    else if(a > b)
    {
        double c(getCValue());
        foci.emplace_back(m_center + Point(c, 0));
        foci.emplace_back(m_center - Point(c, 0));
    }
    else if(a < b)
    {
        double c(getCValue());
        foci.emplace_back(m_center + Point(0, c));
        foci.emplace_back(m_center - Point(0, c));
    }
    return foci;
}

Points Ellipse::getMajorVertices() const
{
    Points principalVertices;
    if(!isAlmostEqual(m_aValue, m_bValue))
    {
        if(m_aValue > m_bValue)
        {
            principalVertices.emplace_back(m_center + Point(m_aValue, 0));
            principalVertices.emplace_back(m_center - Point(m_aValue, 0));
        }
        else if(m_aValue < m_bValue)
        {
            principalVertices.emplace_back(m_center + Point(0, m_bValue));
            principalVertices.emplace_back(m_center - Point(0, m_bValue));
        }
    }
    return principalVertices;
}

Points Ellipse::getMinorVertices() const
{
    Points minorVertices;
    if(!isAlmostEqual(m_aValue, m_bValue))
    {
        if(m_aValue > m_bValue)
        {
            minorVertices.emplace_back(m_center + Point(0, m_bValue));
            minorVertices.emplace_back(m_center - Point(0, m_bValue));
        }
        else if(m_aValue < m_bValue)
        {
            minorVertices.emplace_back(m_center + Point(m_aValue, 0));
            minorVertices.emplace_back(m_center - Point(m_aValue, 0));
        }
    }
    return minorVertices;
}

Line Ellipse::getMajorAxis() const
{
    Line result;
    Points vertices(getMajorVertices());
    if(2U == vertices.size())
    {
        result = Line(vertices.at(0), vertices.at(1));
    }
    return result;
}

Line Ellipse::getMinorAxis() const
{
    Line result;
    Points vertices(getMinorVertices());
    if(2U == vertices.size())
    {
        result = Line(vertices.at(0), vertices.at(1));
    }
    return result;
}

Points Ellipse::getPointsForCircumference(double const interval) const
{
    Points result;
    if(!isAlmostEqual(m_aValue, 0) && !isAlmostEqual(m_bValue, 0))
    {
        Points pointsInFirstQuarter(getPointsInTraversingXAndY(1, 1, interval));
        Points pointsInSecondQuarter(getPointsInTraversingXAndY(-1, 1, interval));
        Points pointsInThirdQuarter(getPointsInTraversingXAndY(-1, -1, interval));
        Points pointsInFourthQuarter(getPointsInTraversingXAndY(1, -1, interval));
        result.reserve(pointsInFirstQuarter.size()+pointsInSecondQuarter.size()+pointsInThirdQuarter.size()+pointsInFourthQuarter.size());
        copy(pointsInFirstQuarter.cbegin(), pointsInFirstQuarter.cend()-1, back_inserter(result));
        copy(pointsInSecondQuarter.cbegin(), pointsInSecondQuarter.cend()-1, back_inserter(result));
        copy(pointsInThirdQuarter.cbegin(), pointsInThirdQuarter.cend()-1, back_inserter(result));
        copy(pointsInFourthQuarter.cbegin(), pointsInFourthQuarter.cend()-1, back_inserter(result));
    }
    return result;
}

void Ellipse::traverseArea(double const interval, TraverseOperation const& traverseOperation) const
{
    for(double y=0; y<=m_bValue; y+=interval)
    {
        double xAtTheEdgeOfEllipse(calculateXFromYWithoutCenter(y, 1));
        for(double x=0; x<=xAtTheEdgeOfEllipse; x+=interval)
        {
            if(isAlmostEqual(x, 0) && isAlmostEqual(y, 0))
            {
                traverseOperation(m_center);
            }
            else
            {
                traverseOperation(Point(m_center.getX()+x, m_center.getY()+y));
                traverseOperation(Point(m_center.getX()-x, m_center.getY()+y));
                traverseOperation(Point(m_center.getX()+x, m_center.getY()-y));
                traverseOperation(Point(m_center.getX()-x, m_center.getY()-y));
            }
        }
    }
}

double Ellipse::calculateYFromX(double const x, double const signOfRoot) const
{
    return pow(1 - pow((x-m_center.getX())/m_aValue, 2), 0.5)*signOfRoot*m_bValue + m_center.getY();
}

double Ellipse::calculateXFromY(double const y, double const signOfRoot) const
{
    return pow(1 - pow((y-m_center.getY())/m_bValue, 2), 0.5)*signOfRoot*m_aValue + m_center.getX();
}

double Ellipse::calculateYFromXWithoutCenter(double const x, double const signOfRoot) const
{
    return pow(1 - pow(x/m_aValue, 2), 0.5)*signOfRoot*m_bValue;
}

double Ellipse::calculateXFromYWithoutCenter(double const y, double const signOfRoot) const
{
    return pow(1 - pow(y/m_bValue, 2), 0.5)*signOfRoot*m_aValue;
}

string Ellipse::getDisplayableString() const
{
    std::stringstream ss;
    ss << "(center: " << m_center.getDisplayableString() << " a: " << m_aValue << " b: " << m_bValue << ")";
    return ss.str();
}

Points Ellipse::getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    Points pointsFromTraversingX(getPointsInTraversingX(signOfX, signOfY, interval));
    Points pointsFromTraversingY(getPointsInTraversingY(signOfX, signOfY, interval));
    if(signOfX>0 && signOfY>0)
    {
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY>0)
    {
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY<0)
    {
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX>0 && signOfY<0)
    {
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    return result;
}

Points Ellipse::getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    AlbaValueRange<double> yRange(m_center.getY(), m_center.getY()+(m_bValue*signOfY), interval);
    yRange.traverse([&](double const yValue)
    {
        result.emplace_back(calculateXFromY(yValue, signOfX), yValue);
    });
    return result;
}

Points Ellipse::getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    AlbaValueRange<double> xRange(m_center.getX(), m_center.getX()+(m_aValue*signOfX), interval);
    xRange.traverse([&](double const xValue)
    {
        result.emplace_back(xValue, calculateYFromX(xValue, signOfY));
    });
    return result;
}

ostream & operator<<(ostream & out, Ellipse const& ellipse)
{
    out << ellipse.getDisplayableString();
    return out;
}

}
}
