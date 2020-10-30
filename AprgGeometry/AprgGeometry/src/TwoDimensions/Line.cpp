#include "Line.hpp"

#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

namespace alba
{

Line::Line(Point const& first, Point const& second)
{
    double deltaY = second.getY() - first.getY();
    double deltaX = second.getX() - first.getX();
    m_type = determineLineType(deltaY, deltaX);
    if(m_type == LineType::Horizontal)
    {
        m_slope = 0;
        m_yIntercept = first.getY();
        m_xIntercept = 0;
    }
    else if(m_type == LineType::Vertical)
    {
        m_slope = 0;
        m_yIntercept = 0;
        m_xIntercept = first.getX();
    }
    else
    {
        m_slope = deltaY/deltaX;
        m_yIntercept = first.getY() - ((deltaY/deltaX)*first.getX());
        m_xIntercept = -1*m_yIntercept/m_slope;
    }
}

LineType Line::getType() const
{
    return m_type;
}

double Line::getYIntercept() const
{
    return m_yIntercept;
}

double Line::getXIntercept() const
{
    return m_xIntercept;
}

double Line::getSlope() const
{
    return m_slope;
}

Points Line::getPoints(Point const& first, Point const& second, double const interval) const
{
    Points points;
    if(m_type == LineType::Vertical)
    {
        for(double iterator = first.getY(); iterator<=second.getY(); iterator+=interval)
        {
            points.emplace_back(Point(m_xIntercept, iterator));
        }
    }
    else if(m_type == LineType::Horizontal)
    {
        for(double iterator = first.getX(); iterator<=second.getX(); iterator+=interval)
        {
            points.emplace_back(Point(iterator, m_yIntercept));
        }
    }
    else
    {
        set<Point> sortedPoints;
        for(double iterator = first.getX(); iterator<=second.getX(); iterator+=interval)
        {
            sortedPoints.emplace(Point(iterator, calculateYFromX(iterator)));
        }
        for(double iterator = first.getY(); iterator<=second.getY(); iterator+=interval)
        {
            sortedPoints.emplace(Point(calculateXFromY(iterator), iterator));
        }
        copy(sortedPoints.begin(), sortedPoints.end(), back_inserter(points));
    }
    return points; //RVO
}

double Line::calculateYFromX(double const x) const
{
    return (x*m_slope) + m_yIntercept; //y=mx+b
}

double Line::calculateXFromY(double const y) const
{
    return (y/m_slope) + m_xIntercept; //x=y/m+a
}

LineType Line::determineLineType(double const deltaY, double const deltaX) const
{
    bool isNegativeDeltaY = (deltaY>0);
    bool isNegativeDeltaX = (deltaX>0);
    LineType lineType(LineType::Unknown);
    if(deltaY == 0)
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

}