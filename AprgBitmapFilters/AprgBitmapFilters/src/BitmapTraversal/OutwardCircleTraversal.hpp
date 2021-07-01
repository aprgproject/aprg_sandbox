#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <TwoDimensions/Point.hpp>

#include <map>

namespace alba
{

namespace AprgBitmapTraversal
{

class OutwardCircleTraversal
{
public:
    OutwardCircleTraversal(unsigned int const maxRadius);

private:
    unsigned int const m_maxRadius;
    std::multimap<double, TwoDimensions::Point> m_radiusToCoordinates;
};

}

}
