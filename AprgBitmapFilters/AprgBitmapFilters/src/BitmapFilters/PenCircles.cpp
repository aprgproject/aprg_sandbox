#include "PenCircles.hpp"

namespace alba
{

namespace AprgBitmap
{

PenCircles::PenCircleDetails::PenCircleDetails()
    : radius(0)
    , color(0u)
{}

PenCircles::PenCircleDetails::PenCircleDetails(
        double const radiusParameter,
        unsigned int const colorParameter)
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

PenCircles::PointToPenCircleDetailsMap & PenCircles::getPenCirclesReference()
{
    return m_penCircles;}

void PenCircles::addAsPenCircle(
        BitmapXY const& point,
        double const radius,        unsigned int const color)
{
    m_penCircles[point]=PenCircleDetails(radius, color);
}

void PenCircles::connectCircles(
        BitmapXY const& circle1Center,
        BitmapXY const& circle2Center)
{
    m_centerConnections.emplace_back(circle1Center, circle2Center);
}

void PenCircles::clear(){
    m_penCircles.clear();
}

}

}
