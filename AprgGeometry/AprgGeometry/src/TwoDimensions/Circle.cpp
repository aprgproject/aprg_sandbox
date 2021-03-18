#include "Circle.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

Circle::Circle()
    : m_center()
    , m_radius(0)
    , m_radiusSquared(0)
{}

Circle::Circle(Point const& center, double const radius)
    : m_center(center)
    , m_radius(radius)
    , m_radiusSquared(radius*radius)
{}

bool Circle::operator==(Circle const& circle) const
{
    return (m_center == circle.m_center) && isConsideredEqual(m_radius, circle.m_radius);
}

bool Circle::operator!=(Circle const& circle) const
{
    return !((*this)==circle);
}

Point Circle::getCenter() const
{
    return m_center;
}

double Circle::getRadius() const
{
    return m_radius;
}

double Circle::getArea() const
{
    return getPi()*m_radiusSquared;
}

double Circle::getCircumference() const
{
    return getPi()*2*m_radius;
}

bool Circle::isInside(Point const& point) const
{
    return twoDimensionsHelper::getDistance(m_center, point) <= m_radius;
}

Points Circle::getPointsForCircumference(double const interval) const
{
    Points result;
    Points pointsInFirstQuarter(getPointsInTraversingXAndY(1, 1, interval));
    Points pointsInSecondQuarter(getPointsInTraversingXAndY(-1, 1, interval));
    Points pointsInThirdQuarter(getPointsInTraversingXAndY(-1, -1, interval));
    Points pointsInFourthQuarter(getPointsInTraversingXAndY(1, -1, interval));
    copy(pointsInFirstQuarter.cbegin(), pointsInFirstQuarter.cend()-1, back_inserter(result));
    copy(pointsInSecondQuarter.cbegin(), pointsInSecondQuarter.cend()-1, back_inserter(result));
    copy(pointsInThirdQuarter.cbegin(), pointsInThirdQuarter.cend()-1, back_inserter(result));
    copy(pointsInFourthQuarter.cbegin(), pointsInFourthQuarter.cend()-1, back_inserter(result));
    return result;
}

void Circle::traverseArea(double const interval, TraverseOperation const& traverseOperation)
{
    for(unsigned int y=0; y<=m_radius; y+=interval)
    {
        double xAtTheEdgeOfCircle(calculateXFromYWithoutCenter(y, 1));
        for(unsigned int x=0; x<=xAtTheEdgeOfCircle; x+=interval)
        {
            if(x==0 && y==0)
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

double Circle::calculateYFromX(double const x, double const signOfRoot) const
{
    return pow(m_radiusSquared - pow(x-m_center.getX(), 2), 0.5)*signOfRoot + m_center.getY();
}

double Circle::calculateXFromY(double const y, double const signOfRoot) const
{
    return pow(m_radiusSquared - pow(y-m_center.getY(), 2), 0.5)*signOfRoot + m_center.getX();
}

double Circle::calculateYFromXWithoutCenter(double const x, double const signOfRoot) const
{
    return pow(m_radiusSquared - pow(x, 2), 0.5)*signOfRoot;
}

double Circle::calculateXFromYWithoutCenter(double const y, double const signOfRoot) const
{
    return pow(m_radiusSquared - pow(y, 2), 0.5)*signOfRoot;
}

Points Circle::getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    Points pointsFromTraversingX(getPointsInTraversingX(signOfX, signOfY, interval));
    Points pointsFromTraversingY(getPointsInTraversingY(signOfX, signOfY, interval));
    if(signOfX>0 && signOfY>0)
    {
        result = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY>0)
    {
        result = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX<0 && signOfY<0)
    {
        result = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    else if(signOfX>0 && signOfY<0)
    {
        result = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    return result;
}

Points Circle::getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    AlbaRange<double> yRange(m_center.getY(), m_center.getY()+(m_radius*signOfY), interval);
    yRange.traverse([&](double const yValue)
    {
        result.emplace_back(calculateXFromY(yValue, signOfX), yValue);
    });
    return result;
}

Points Circle::getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const
{
    Points result;
    AlbaRange<double> xRange(m_center.getX(), m_center.getX()+(m_radius*signOfX), interval);
    xRange.traverse([&](double const xValue)
    {
        result.emplace_back(xValue, calculateYFromX(xValue, signOfY));
    });
    return result;
}

}
