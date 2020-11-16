#include "Line.hpp"

#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <algorithm>
#include <iterator>
#include <set>
using namespace std;

namespace alba{

Line::Line(Point const& first, Point const& second)
{
    double deltaY = second.getY() - first.getY();
    double deltaX = second.getX() - first.getX();
    m_type = determineLineTypeUsingDeltaXandDeltaY(deltaY, deltaX);
    switch(m_type)
    {
    case LineType::Horizontal:
        m_slope = 0;
        m_yIntercept = first.getY();
        m_xIntercept = 0;
        m_aCoefficient = 0;
        m_bCoefficient = -deltaX;
        m_cCoefficient = first.getY()*deltaX;
        break;
    case LineType::Vertical:
        m_slope = INFINITY;
        m_yIntercept = 0;
        m_xIntercept = first.getX();
        m_aCoefficient = deltaY;
        m_bCoefficient = 0;
        m_cCoefficient = -first.getX()*deltaY;
        break;
    default:
        m_slope = deltaY/deltaX;
        m_yIntercept = first.getY() - ((deltaY/deltaX)*first.getX());
        m_xIntercept = -1*m_yIntercept/m_slope;
        m_aCoefficient = deltaY;
        m_bCoefficient = -deltaX;
        m_cCoefficient = (first.getY()*deltaX)-(first.getX()*deltaY);
        break;
    }
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
        m_slope = INFINITY;
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

bool Line::operator==(Line const& line) const
{
    return (m_type == line.m_type) && (m_slope == line.m_slope) && (m_yIntercept == line.m_yIntercept) && (m_xIntercept == line.m_xIntercept);
}

bool Line::operator!=(Line const& line) const
{
    return !((*this)==line);
}

LineType Line::getType() const
{
    return m_type;}

double Line::getYIntercept() const
{
    return m_yIntercept;}

double Line::getXIntercept() const
{
    return m_xIntercept;
}

double Line::getSlope() const
{
    return m_slope;
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
    else
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
    return (x*m_slope) + m_yIntercept; //y=mx+b}

double Line::calculateXFromY(double const y) const
{
    return (y/m_slope) + m_xIntercept; //x=y/m+a}

void Line::getPointsForVerticalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    twoDimensionsHelper::traverseValues(first.getY(), second.getY(), interval, [&](double traverseValue)
    {
        points.emplace_back(Point(m_xIntercept, traverseValue));
    });}

void Line::getPointsForHorizontalLine(Points & points, Point const& first, Point const& second, double const interval) const
{
    twoDimensionsHelper::traverseValues(first.getX(), second.getX(), interval, [&](double traverseValue)
    {
        points.emplace_back(Point(traverseValue, m_yIntercept));
    });}

void Line::getPointsForLineWithSlope(Points & points, Point const& first, Point const& second, double const interval) const
{    bool isDirectionAscendingForX = first.getX() <= second.getX();
    double lowestXValue = min(min(first.getX(), second.getX()), min(calculateXFromY(first.getY()), calculateXFromY(second.getY())));
    double highestXValue = max(max(first.getX(), second.getX()), max(calculateXFromY(first.getY()), calculateXFromY(second.getY())));
    double startValueOfX = isDirectionAscendingForX ? lowestXValue : highestXValue;
    double endValueOfX = isDirectionAscendingForX ? highestXValue : lowestXValue;

    bool isDirectionAscendingForY = first.getY() <= second.getY();
    double lowestYValue = min(min(first.getY(), second.getY()), min(calculateYFromX(first.getX()), calculateYFromX(second.getX())));
    double highestYValue = max(max(first.getY(), second.getY()), max(calculateYFromX(first.getX()), calculateYFromX(second.getX())));
    double startValueOfY = isDirectionAscendingForY ? lowestYValue : highestYValue;
    double endValueOfY = isDirectionAscendingForY ? highestYValue : lowestYValue;

    Points pointsFromXCoordinate;
    twoDimensionsHelper::traverseValues(startValueOfX, endValueOfX, interval, [&](double traverseValueOfX)
    {
        pointsFromXCoordinate.emplace_back(Point(traverseValueOfX, calculateYFromX(traverseValueOfX)));
    });

    Points pointsFromYCoordinate;
    twoDimensionsHelper::traverseValues(startValueOfY, endValueOfY, interval, [&](double traverseValueOfY)
    {
        pointsFromYCoordinate.emplace_back(Point(calculateXFromY(traverseValueOfY), traverseValueOfY));
    });
    mergePointsFromPointsFromXAndY(points, pointsFromXCoordinate, pointsFromYCoordinate, isDirectionAscendingForX);
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
                if(iteratorForX->getX() == iteratorForY->getX())
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
                if(iteratorForX->getX() == iteratorForY->getX())
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

LineType Line::determineLineTypeUsingDeltaXandDeltaY(double const deltaY, double const deltaX) const
{
    bool isNegativeDeltaY = (deltaY<0);    bool isNegativeDeltaX = (deltaX<0);
    LineType lineType(LineType::Invalid);
    if(deltaY == 0 && deltaX == 0)
    {        lineType = LineType::Invalid;
    }
    else if(deltaY == 0)
    {
        lineType = LineType::Horizontal;
    }
    else if(deltaX == 0)
    {
        lineType = LineType::Vertical;
    }
    else if(isNegativeDeltaY == isNegativeDeltaX)
    {
        lineType = LineType::WithPositiveSlope;
    }
    else
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
    if(aCoefficient == 0 && bCoefficient == 0)
    {
        lineType = LineType::Invalid;
    }
    else if(aCoefficient == 0)
    {
        lineType = LineType::Horizontal;
    }
    else if(bCoefficient == 0)
    {
        lineType = LineType::Vertical;
    }
    else if(isNegativeA == isNegativeB)
    {
        lineType = LineType::WithNegativeSlope;
    }
    else
    {
        lineType = LineType::WithPositiveSlope;
    }
    return lineType;
}

}
