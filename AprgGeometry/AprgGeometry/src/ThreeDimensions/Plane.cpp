#include "Plane.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <cmath>
#include <iterator>
#include <set>

using namespace std;

namespace alba
{

Plane::Plane()
    : m_type(PlaneType::Invalid)
    , m_yIntercept(0)
    , m_xIntercept(0)
    , m_aCoefficient(0) //form: a*x + b*y + c
    , m_bCoefficient(0) //form: a*x + b*y + c
    , m_cCoefficient(0) //form: a*x + b*y + c
{}

Plane::Plane(Point const& first, Point const& second)
{
    double deltaY = second.getY() - first.getY();
    double deltaX = second.getX() - first.getX();
    m_type = determinePlaneTypeUsingDeltaXandDeltaY(deltaY, deltaX);
    switch(m_type)
    {
    case PlaneType::Horizontal:
        m_yIntercept = first.getY();
        m_xIntercept = 0;
        m_aCoefficient = 0;
        m_bCoefficient = -deltaX;
        m_cCoefficient = first.getY()*deltaX;
        break;
    case PlaneType::Vertical:
        m_yIntercept = 0;
        m_xIntercept = first.getX();
        m_aCoefficient = deltaY;
        m_bCoefficient = 0;
        m_cCoefficient = -first.getX()*deltaY;
        break;
    default:
        m_yIntercept = first.getY() - ((deltaY/deltaX)*first.getX());
        m_xIntercept = -1*m_yIntercept;
        m_aCoefficient = deltaY;
        m_bCoefficient = -deltaX;
        m_cCoefficient = (first.getY()*deltaX)-(first.getX()*deltaY);
        break;
    }
}

Plane::Plane(double const aCoefficient, double const bCoefficient, double const cCoefficient)
{
    m_aCoefficient = aCoefficient;
    m_bCoefficient = bCoefficient;
    m_cCoefficient = cCoefficient;
    m_type = determinePlaneTypeUsingCoefficients(aCoefficient, bCoefficient);
    switch(m_type)
    {
    case PlaneType::Horizontal:
        m_yIntercept = -cCoefficient/bCoefficient;
        m_xIntercept = 0;
        break;
    case PlaneType::Vertical:
        m_yIntercept = 0;
        m_xIntercept = -cCoefficient/aCoefficient;
        break;
    default:
        m_yIntercept = -cCoefficient/bCoefficient;
        m_xIntercept = -cCoefficient/aCoefficient;
        break;
    }
}

bool Plane::operator==(Plane const& line) const
{
    return (m_type == line.m_type)
            && isConsideredEqual(m_yIntercept, line.m_yIntercept)
            && isConsideredEqual(m_xIntercept, line.m_xIntercept);
}

bool Plane::operator!=(Plane const& line) const
{
    return !((*this)==line);
}

PlaneType Plane::getType() const
{
    return m_type;
}

double Plane::getYIntercept() const
{
    return m_yIntercept;
}

double Plane::getXIntercept() const
{
    return m_xIntercept;
}

double Plane::getInverseSlope() const
{
    return -m_bCoefficient/m_aCoefficient;
}

double Plane::getACoefficient() const
{
    return m_aCoefficient;
}

double Plane::getBCoefficient() const
{
    return m_bCoefficient;
}

double Plane::getCCoefficient() const
{
    return m_cCoefficient;
}

Points Plane::getPoints(Point const& first, Point const& second, double const interval) const
{
    Points points;
    if(m_type == PlaneType::Vertical)
    {
        getPointsForVerticalPlane(points, first, second, interval);
    }
    else if(m_type == PlaneType::Horizontal)
    {
        getPointsForHorizontalPlane(points, first, second, interval);
    }
    else if(m_type == PlaneType::WithPositiveSlope || m_type == PlaneType::WithNegativeSlope)
    {
        getPointsForPlaneWithSlope(points, first, second, interval);
    }
    return points; //RVO
}

Points Plane::getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const
{
    Points pointsWithoutLastPoint(getPoints(first, second, interval));
    if(!pointsWithoutLastPoint.empty())
    {
        pointsWithoutLastPoint.pop_back();
    }
    return pointsWithoutLastPoint; //RVO
}

double Plane::calculateYFromX(double const x) const
{
    return (x) + m_yIntercept; //y=mx+b
}

double Plane::calculateXFromY(double const y) const
{
    return (y) + m_xIntercept; //x=y/m+a
}

void Plane::getPointsForVerticalPlane(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getY(), second.getY(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(m_xIntercept, traverseValue);
    });
}

void Plane::getPointsForHorizontalPlane(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getX(), second.getX(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(traverseValue, m_yIntercept);
    });
}

void Plane::getPointsForPlaneWithSlope(Points & points, Point const& first, Point const& second, double const interval) const
{
    Point minimumXAndY;
    Point maximumXAndY;
    Points pointsAtBorder;
    minimumXAndY.saveMinimumXAndY(first);
    minimumXAndY.saveMinimumXAndY(second);
    maximumXAndY.saveMaximumXAndY(first);
    maximumXAndY.saveMaximumXAndY(second);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(first.getX(), calculateYFromX(first.getX())), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(calculateXFromY(first.getY()), first.getY()), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(second.getX(), calculateYFromX(second.getX())), minimumXAndY, maximumXAndY);
    twoDimensionsHelper::addPointIfInsideTwoPoints(pointsAtBorder, Point(calculateXFromY(second.getY()), second.getY()), minimumXAndY, maximumXAndY);
    if(pointsAtBorder.size()>=2)
    {
        Point startingPoint(twoDimensionsHelper::popNearestPoint(pointsAtBorder, first));
        Point endPoint(twoDimensionsHelper::popNearestPoint(pointsAtBorder, second));
        bool isDirectionAscendingForX = startingPoint.getX() <= endPoint.getX();

        Points pointsFromXCoordinate;
        AlbaRange<double> rangeForX(startingPoint.getX(), endPoint.getX(), interval);
        rangeForX.traverse([&](double traverseValueOfX)
        {
            pointsFromXCoordinate.emplace_back(traverseValueOfX, calculateYFromX(traverseValueOfX));
        });

        Points pointsFromYCoordinate;
        AlbaRange<double> rangeForY(startingPoint.getY(), endPoint.getY(), interval);
        rangeForY.traverse([&](double traverseValueOfY)
        {
            pointsFromYCoordinate.emplace_back(calculateXFromY(traverseValueOfY), traverseValueOfY);
        });

        if(isDirectionAscendingForX)
        {
            points = twoDimensionsHelper::getMergedPointsInIncreasingX(pointsFromXCoordinate, pointsFromYCoordinate);
        }
        else
        {
            points = twoDimensionsHelper::getMergedPointsInDecreasingX(pointsFromXCoordinate, pointsFromYCoordinate);
        }
    }
}


void Plane::mergePointsFromPointsFromXAndY(Points & points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate, bool const isDirectionAscendingForX) const
{
    Points::const_iterator iteratorForX = pointsFromXCoordinate.cbegin();
    Points::const_iterator iteratorForY = pointsFromYCoordinate.cbegin();
    while(iteratorForX != pointsFromXCoordinate.cend() || iteratorForY != pointsFromYCoordinate.cend())
    {
        if(iteratorForX != pointsFromXCoordinate.cend() && iteratorForY != pointsFromYCoordinate.cend())
        {
            if(isDirectionAscendingForX)
            {
                if(isConsideredEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;
                }
                else if(iteratorForX->getX() < iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);
                }
                else
                {
                    points.emplace_back(*iteratorForY++);
                }
            }
            else
            {
                if(isConsideredEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;
                }
                else if(iteratorForX->getX() > iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);
                }
                else
                {
                    points.emplace_back(*iteratorForY++);
                }
            }
        }
        else if(iteratorForX != pointsFromXCoordinate.cend())
        {
            points.emplace_back(*iteratorForX++);
        }
        else if(iteratorForY != pointsFromYCoordinate.cend())
        {
            points.emplace_back(*iteratorForY++);
        }
    }
}

PlaneType Plane::determinePlaneTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const
{
    bool isNegativeDeltaY = (deltaY<0);
    bool isNegativeDeltaX = (deltaX<0);
    PlaneType lineType(PlaneType::Invalid);
    if(isConsideredEqual(deltaY, 0.0) && isConsideredEqual(deltaX, 0.0))
    {
        lineType = PlaneType::Invalid;
    }
    else if(isConsideredEqual(deltaY, 0.0))
    {
        lineType = PlaneType::Horizontal;
    }
    else if(isConsideredEqual(deltaX, 0.0))
    {
        lineType = PlaneType::Vertical;
    }
    else if(isNegativeDeltaY == isNegativeDeltaX)
    {
        lineType = PlaneType::WithPositiveSlope;
    }
    else
    {
        lineType = PlaneType::WithNegativeSlope;
    }
    return lineType;
}

PlaneType Plane::determinePlaneTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const
{
    bool isNegativeA = (aCoefficient<0);
    bool isNegativeB = (bCoefficient<0);
    PlaneType lineType(PlaneType::Invalid);
    if(isConsideredEqual(aCoefficient, 0.0) && isConsideredEqual(bCoefficient, 0.0))
    {
        lineType = PlaneType::Invalid;
    }
    else if(isConsideredEqual(aCoefficient, 0.0))
    {
        lineType = PlaneType::Horizontal;
    }
    else if(isConsideredEqual(bCoefficient, 0.0))
    {
        lineType = PlaneType::Vertical;
    }
    else if(isNegativeA == isNegativeB)
    {
        lineType = PlaneType::WithNegativeSlope;
    }
    else
    {
        lineType = PlaneType::WithPositiveSlope;
    }
    return lineType;
}

}
