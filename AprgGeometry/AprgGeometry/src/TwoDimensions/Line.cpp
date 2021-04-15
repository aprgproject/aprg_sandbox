#include "Line.hpp"

#include <Container/AlbaRange.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

namespace alba
{

namespace TwoDimensions
{

Line::Line()
    : m_type(LineType::Invalid)
    , m_yIntercept(0)
    , m_xIntercept(0)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_slope(0)
{}

Line::Line(Point const& first, Point const& second)
    : m_type(LineType::Invalid)
    , m_yIntercept(0)
    , m_xIntercept(0)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_slope(0)
{
    double deltaY = second.getY() - first.getY();
    double deltaX = second.getX() - first.getX();
    setLineParametersBasedOnDeltas(deltaX, deltaY, first);
}

Line::Line(double const aCoefficient, double const bCoefficient, double const cCoefficient)
{
    m_aCoefficient = aCoefficient;
    m_bCoefficient = bCoefficient;
    m_cCoefficient = cCoefficient;
    m_type = determineLineTypeUsingCoefficients(aCoefficient, bCoefficient);
    switch(m_type)
    {
    case LineType::Horizontal:
        m_slope = 0;
        m_yIntercept = -cCoefficient/bCoefficient;
        m_xIntercept = 0;
        break;
    case LineType::Vertical:
        m_slope = static_cast<double>(INFINITY);
        m_yIntercept = 0;
        m_xIntercept = -cCoefficient/aCoefficient;
        break;
    default:
        m_slope = -aCoefficient/bCoefficient;
        m_yIntercept = -cCoefficient/bCoefficient;
        m_xIntercept = -cCoefficient/aCoefficient;
        break;
    }
}

Line::Line(double const aCoefficient, double const bCoefficient, Point const& point)
    : m_type(LineType::Invalid)
    , m_yIntercept(0)
    , m_xIntercept(0)
    , m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_slope(0)
{
    double deltaX = aCoefficient;
    double deltaY = bCoefficient;
    setLineParametersBasedOnDeltas(deltaX, deltaY, point);
}

bool Line::operator==(Line const& line) const
{
    return (m_type == line.m_type)
            && isAlmostEqual(m_slope, line.m_slope)
            && isAlmostEqual(m_yIntercept, line.m_yIntercept)
            && isAlmostEqual(m_xIntercept, line.m_xIntercept);
}

bool Line::operator!=(Line const& line) const{
    return !((*this)==line);
}
LineType Line::getType() const
{
    return m_type;
}

double Line::getXIntercept() const
{
    return m_xIntercept;
}

double Line::getYIntercept() const
{
    return m_yIntercept;
}

double Line::getSlope() const
{
    return m_slope;
}

double Line::getInverseSlope() const
{
    return -m_bCoefficient/m_aCoefficient;
}

double Line::getACoefficient() const
{
    return m_aCoefficient;
}

double Line::getBCoefficient() const
{
    return m_bCoefficient;
}

double Line::getCCoefficient() const
{
    return m_cCoefficient;
}

Points Line::getPoints(Point const& first, Point const& second, double const interval) const
{
    Points points;
    if(m_type == LineType::Vertical)
    {
        getPointsForVerticalLine(points, first, second, interval);
    }
    else if(m_type == LineType::Horizontal)
    {
        getPointsForHorizontalLine(points, first, second, interval);
    }
    else if(m_type == LineType::WithPositiveSlope || m_type == LineType::WithNegativeSlope)
    {
        getPointsForLineWithSlope(points, first, second, interval);
    }
    return points; //RVO
}

Points Line::getPointsWithoutLastPoint(Point const& first, Point const& second, double const interval) const
{
    Points pointsWithoutLastPoint(getPoints(first, second, interval));
    if(!pointsWithoutLastPoint.empty())
    {
        pointsWithoutLastPoint.pop_back();
    }
    return pointsWithoutLastPoint; //RVO
}

double Line::calculateYFromX(double const x) const
{
    return (x*m_slope) + m_yIntercept; //y=mx+b
}

double Line::calculateXFromY(double const y) const
{
    return (y/m_slope) + m_xIntercept; //x=y/m+a
}

void Line::setLineParametersBasedOnDeltas(double const deltaX, double const deltaY, Point const& point)
{
    m_type = determineLineTypeUsingDeltaXandDeltaY(deltaY, deltaX);
    switch(m_type)
    {
    case LineType::Horizontal:
        m_slope = 0;
        m_yIntercept = point.getY();
        m_xIntercept = 0;
        m_aCoefficient = 0;
        m_bCoefficient = -deltaX;
        m_cCoefficient = point.getY()*deltaX;
        break;
    case LineType::Vertical:
        m_slope = static_cast<double>(INFINITY);
        m_yIntercept = 0;
        m_xIntercept = point.getX();
        m_aCoefficient = deltaY;
        m_bCoefficient = 0;
        m_cCoefficient = -point.getX()*deltaY;
        break;
    default:
        m_slope = deltaY/deltaX;
        m_yIntercept = point.getY() - ((deltaY/deltaX)*point.getX());
        m_xIntercept = -1*m_yIntercept/m_slope;
        m_aCoefficient = deltaY;
        m_bCoefficient = -deltaX;
        m_cCoefficient = (point.getY()*deltaX)-(point.getX()*deltaY);
        break;
    }
}

void Line::getPointsForVerticalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getY(), second.getY(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(m_xIntercept, traverseValue);
    });
}

void Line::getPointsForHorizontalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    AlbaRange<double> range(first.getX(), second.getX(), interval);
    range.traverse([&](double traverseValue)
    {
        points.emplace_back(traverseValue, m_yIntercept);
    });
}

void Line::getPointsForLineWithSlope(Points & points, Point const& first, Point const& second, double const interval) const
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


void Line::mergePointsFromPointsFromXAndY(Points & points, Points const& pointsFromXCoordinate, Points const& pointsFromYCoordinate, bool const isDirectionAscendingForX) const
{
    Points::const_iterator iteratorForX = pointsFromXCoordinate.cbegin();
    Points::const_iterator iteratorForY = pointsFromYCoordinate.cbegin();
    while(iteratorForX != pointsFromXCoordinate.cend() || iteratorForY != pointsFromYCoordinate.cend())
    {
        if(iteratorForX != pointsFromXCoordinate.cend() && iteratorForY != pointsFromYCoordinate.cend())
        {
            if(isDirectionAscendingForX)
            {
                if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;                }
                else if(iteratorForX->getX() < iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);                }
                else
                {
                    points.emplace_back(*iteratorForY++);
                }
            }
            else
            {
                if(isAlmostEqual(iteratorForX->getX(), iteratorForY->getX()))
                {
                    points.emplace_back(*iteratorForX++);
                    iteratorForY++;                }
                else if(iteratorForX->getX() > iteratorForY->getX())
                {
                    points.emplace_back(*iteratorForX++);                }
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

LineType Line::determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const
{
    bool isNegativeDeltaY = (deltaY<0);
    bool isNegativeDeltaX = (deltaX<0);
    LineType lineType(LineType::Invalid);
    if(isAlmostEqual(deltaY, 0.0) && isAlmostEqual(deltaX, 0.0))
    {
        lineType = LineType::Invalid;
    }
    else if(isAlmostEqual(deltaY, 0.0))
    {
        lineType = LineType::Horizontal;
    }
    else if(isAlmostEqual(deltaX, 0.0))
    {
        lineType = LineType::Vertical;
    }    else if(isNegativeDeltaY == isNegativeDeltaX)
    {
        lineType = LineType::WithPositiveSlope;
    }    else
    {
        lineType = LineType::WithNegativeSlope;
    }
    return lineType;
}

LineType Line::determineLineTypeUsingCoefficients(double const aCoefficient, double const bCoefficient) const
{
    bool isNegativeA = (aCoefficient<0);
    bool isNegativeB = (bCoefficient<0);
    LineType lineType(LineType::Invalid);
    if(isAlmostEqual(aCoefficient, 0.0) && isAlmostEqual(bCoefficient, 0.0))
    {
        lineType = LineType::Invalid;
    }
    else if(isAlmostEqual(aCoefficient, 0.0))
    {
        lineType = LineType::Horizontal;
    }
    else if(isAlmostEqual(bCoefficient, 0.0))
    {
        lineType = LineType::Vertical;
    }    else if(isNegativeA == isNegativeB)
    {
        lineType = LineType::WithNegativeSlope;
    }    else
    {
        lineType = LineType::WithPositiveSlope;
    }
    return lineType;
}

}
}
