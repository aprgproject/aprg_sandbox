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
    struct Coordinate
    {
        Coordinate(
                unsigned int const firstValue,
                unsigned int const secondValue);
        unsigned int coordinate1;
        unsigned int coordinate2;
    };
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
