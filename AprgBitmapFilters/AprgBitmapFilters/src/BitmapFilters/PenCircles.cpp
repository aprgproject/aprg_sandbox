#include "PenCircles.hpp"

using namespace alba::TwoDimensions;

namespace alba
{

namespace AprgBitmap
{

bool PenCircles::isPenCircle(Circle const& penPoint) const
{
    return m_penCircles.find(penPoint)!=m_penCircles.cend();
}

PenCircles::PenCirclesSet const& PenCircles::getPenCircles() const
{
    return m_penCircles;
}

void PenCircles::addAsPenCircle(Circle const& penPoint)
{
    m_penCircles.emplace(penPoint);
}

void PenCircles::removePenCircle(Circle const& penPoint)
{
    m_penCircles.erase(penPoint);
}

void PenCircles::clear()
{
    m_penCircles.clear();
}


}

}
