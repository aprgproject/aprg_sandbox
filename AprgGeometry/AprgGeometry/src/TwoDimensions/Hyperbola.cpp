#include "Hyperbola.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace TwoDimensions
{

Hyperbola::Hyperbola()
    : m_center()
    , m_aValue(0)
    , m_bValue(0)
{}

Hyperbola::Hyperbola(Point const& center, double const aCoefficient, double const bCoefficient)
    : m_center(center)
    , m_aValue(aCoefficient)
    , m_bValue(bCoefficient)
{}

bool Hyperbola::operator==(Hyperbola const& hyperbola) const
{
    return (m_center == hyperbola.m_center)
            && isAlmostEqual(m_aValue, hyperbola.m_aValue)
            && isAlmostEqual(m_bValue, hyperbola.m_bValue);
}

bool Hyperbola::operator!=(Hyperbola const& hyperbola) const
{
    return !((*this)==hyperbola);
}

Point Hyperbola::getCenter() const
{
    return m_center;
}

double Hyperbola::getAValue() const
{
    return m_aValue;
}

double Hyperbola::getBValue() const
{
    return m_bValue;
}

double Hyperbola::getCValue() const
{
    return getSquareRootOfXSquaredPlusYSquared(m_aValue, m_bValue);
}

double Hyperbola::getEccentricity() const
{
    return pow(1 + (pow(m_bValue, 2)/pow(m_aValue, 2)), 0.5);
}

double Hyperbola::getSemiLactusRectum() const
{
    return pow(m_bValue, 2)/m_aValue;
}

Points Hyperbola::getPointsForShape(double const interval) const
{
    Points result;
    Points pointsInFirstQuarter(getPointsInTraversingXAndY(1, 1, interval));
    Points pointsInFourthQuarter(getPointsInTraversingXAndY(1, -1, interval));
    Points pointsInSecondQuarter(getPointsInTraversingXAndY(-1, 1, interval));
    Points pointsInThirdQuarter(getPointsInTraversingXAndY(-1, -1, interval));
    copy(pointsInFirstQuarter.cbegin(), pointsInFirstQuarter.cend()-1, back_inserter(result));
    copy(pointsInFourthQuarter.cbegin(), pointsInFourthQuarter.cend(), back_inserter(result));
    copy(pointsInSecondQuarter.cbegin(), pointsInSecondQuarter.cend()-1, back_inserter(result));
    copy(pointsInThirdQuarter.cbegin(), pointsInThirdQuarter.cend(), back_inserter(result));
    return result;
}

double Hyperbola::calculateYFromX(double const x, double const signOfRoot) const
{
    return pow(pow((x-m_center.getX())/m_aValue, 2) - 1, 0.5)*signOfRoot*m_bValue + m_center.getY();
}

double Hyperbola::calculateXFromY(double const y, double const signOfRoot) const
{
    return pow(1 + pow((y-m_center.getY())/m_bValue, 2), 0.5)*signOfRoot*m_aValue + m_center.getX();
}

double Hyperbola::calculateYFromXWithoutCenter(double const x, double const signOfRoot) const
{
    return pow(pow(x/m_aValue, 2) - 1, 0.5)*signOfRoot*m_bValue;
}

double Hyperbola::calculateXFromYWithoutCenter(double const y, double const signOfRoot) const
{
    return pow(1 + pow(y/m_bValue, 2), 0.5)*signOfRoot*m_aValue;
}

Points Hyperbola::getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    Points pointsFromTraversingX(getPointsInTraversingX(signOfX, signOfY, interval));
    Points pointsFromTraversingY(getPointsInTraversingY(signOfX, signOfY, interval));
    if(signOfX>0 && signOfY>0) //first quarter
    {
        result = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX>0 && signOfY<0) //fourth quarter
    {
        result = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY>0) //second quarter
    {
        result = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY<0) //third quarter
    {
        result = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    return result;
}

Points Hyperbola::getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    AlbaRange<double> yRange(m_center.getY(), m_center.getY()+(m_bValue*signOfY), interval);
    yRange.traverse([&](double const yValue)
    {
        result.emplace_back(calculateXFromY(yValue, signOfX), yValue);
    });
    return result;
}

Points Hyperbola::getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    double stepValue(m_aValue*signOfX);
    AlbaRange<double> xRange(m_center.getX()+stepValue, m_center.getX()+2*stepValue, interval); // whats with the 2 step value? it should configurable
    xRange.traverse([&](double const xValue)
    {
        result.emplace_back(xValue, calculateYFromX(xValue, signOfY));
    });
    return result;
}

}
}
