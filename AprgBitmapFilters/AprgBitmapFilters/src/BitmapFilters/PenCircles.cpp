#include "PenCircles.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;

namespace alba
{

namespace AprgBitmap
{

PenCircles::PenCircleDetails::PenCircleDetails()
    : radius(0)
    , color(0U)
{}

PenCircles::PenCircleDetails::PenCircleDetails(
        double const radiusParameter,
        uint32_t const colorParameter)
    : radius(radiusParameter)
    , color(colorParameter)
{}

bool PenCircles::isPenCircle(BitmapXY const& point) const
{
    return m_penCircles.find(point)!=m_penCircles.cend();
}

PenCircles::PenCircleDetails PenCircles::getPenCircleDetails(
        BitmapXY const& point) const
{
    PenCircleDetails penCircleDetails;
    PointToPenCircleDetailsMap::const_iterator it = m_penCircles.find(point);
    if(it!=m_penCircles.cend())
    {
        penCircleDetails = it->second;
    }
    return penCircleDetails;
}

PenCircles::PointToPenCircleDetailsMap const& PenCircles::getPenCircles() const
{
    return m_penCircles;
}

PenCircles::CircleCenterConnections const& PenCircles::getCenterConnections() const
{
    return m_centerConnections;
}

PenCircles::PointAndPenCircleDetailsPairs PenCircles::getNearestPenCirclesToAPoint(
        BitmapXY const& point,
        unsigned int const distance) const
{
    PointAndPenCircleDetailsPairs result;
    unsigned int minX=static_cast<unsigned int>(clampLowerBound(convertToIntegerThenSubtract(point.getX(), distance), 0));
    unsigned int maxX=point.getX()+distance;
    unsigned int minY=static_cast<unsigned int>(clampLowerBound(convertToIntegerThenSubtract(point.getY(), distance), 0));
    unsigned int maxY=point.getY()+distance;
    for(auto const& pointAndPenCircleDetailsPair : m_penCircles)
    {
        BitmapXY const& centerPoint(pointAndPenCircleDetailsPair.first);
        if(minX <= centerPoint.getX() && centerPoint.getX() <= maxX
                && minY <= centerPoint.getY() && centerPoint.getY() <= maxY)
        {
            result.emplace_back(pointAndPenCircleDetailsPair);
        }
    }
    return result;
}

PenCircles::PointToPenCircleDetailsMap & PenCircles::getPenCirclesReference()
{
    return m_penCircles;
}

void PenCircles::addAsPenCircle(
        BitmapXY const& point,
        double const radius,
        uint32_t const color)
{
    m_penCircles[point] = PenCircleDetails(radius, color);
}

void PenCircles::removePenCircleAt(
        BitmapXY const& circleCenter)
{
    m_penCircles.erase(circleCenter);
}

void PenCircles::connectCircles(
        BitmapXY const& circle1Center,
        BitmapXY const& circle2Center)
{
    if(circle1Center < circle2Center)
    {
        m_centerConnections.emplace(circle1Center, circle2Center);
    }
    else if(circle2Center < circle1Center)
    {
        m_centerConnections.emplace(circle2Center, circle1Center);
    }
}

void PenCircles::clear()
{
    m_penCircles.clear();
}


}

}
