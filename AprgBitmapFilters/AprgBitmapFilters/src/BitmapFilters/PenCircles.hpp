#pragma once

#include <TwoDimensions/Circle.hpp>

#include <set>

namespace alba
{

namespace AprgBitmap
{

class PenCircles
{
public:
    using PenCirclesSet=std::set<TwoDimensions::Circle>;

    bool isPenCircle(TwoDimensions::Circle const& penPoint) const;
    PenCirclesSet const& getPenCircles() const;

    void addAsPenCircle(TwoDimensions::Circle const& penPoint);
    void removePenCircle(TwoDimensions::Circle const& penPoint);
    void clear();
private:
    PenCirclesSet m_penCircles;
};

}

}
