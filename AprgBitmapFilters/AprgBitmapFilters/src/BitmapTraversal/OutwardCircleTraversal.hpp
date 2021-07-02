#pragma once

#include <functional>
#include <map>

namespace alba
{

namespace AprgBitmap
{

class OutwardCircleTraversal
{
public:
    using Coordinate=std::pair<unsigned int, unsigned int>;
    using RadiusToCoordinates=std::multimap<double, Coordinate>;
    using RadiusCoordinatesPair=std::pair<double, Coordinate>;

    OutwardCircleTraversal(unsigned int const maxRadius);

    RadiusToCoordinates const& getRadiusToCoordinates() const;

private:
    void constructRadiusToCoordinates();
    unsigned int const m_maxRadius;
    RadiusToCoordinates m_radiusToCoordinates;
};

}

}
