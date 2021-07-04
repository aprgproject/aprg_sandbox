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

PenCircles::PointToPenCircleDetailsMap const& PenCircles::getPenCircles() const
{
    return m_penCircles;
}

PenCircles::PointToPenCircleDetailsMap & PenCircles::getPenCirclesReference()
{
    return m_penCircles;
}

void PenCircles::addAsPenCircle(
        BitmapXY const& point,
        double const radius,
        unsigned int const color)
{
    m_penCircles[point]=PenCircleDetails(radius, color);
}

void PenCircles::removePenCircle(BitmapXY const& point)
{
    m_penCircles.erase(point);
}

void PenCircles::clear(){
    m_penCircles.clear();
}


}

}
