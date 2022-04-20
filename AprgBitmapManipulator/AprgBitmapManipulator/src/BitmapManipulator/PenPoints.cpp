#include "PenPoints.hpp"

namespace alba
{

namespace AprgBitmap
{

bool PenPoints::isPenPoint(BitmapXY const& penPoint) const
{
    return m_penPoints.find(penPoint)!=m_penPoints.cend();
}

PenPoints::PenPointsSet const& PenPoints::getPenPoints() const
{
    return m_penPoints;
}

void PenPoints::addAsPenPoint(BitmapXY const& penPoint)
{
    m_penPoints.emplace(penPoint);
}

void PenPoints::addAsPenPoints(BitmapXYs const& bitmapPoints)
{
    for(BitmapXY const& bitmapPoint : bitmapPoints)
    {
        addAsPenPoint(bitmapPoint);
    }
}

void PenPoints::removePenPoint(BitmapXY const& penPoint)
{
    m_penPoints.erase(penPoint);
}

void PenPoints::clear()
{
    m_penPoints.clear();
}


}

}
