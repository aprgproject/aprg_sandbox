#include "OutwardCircleTraversal.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{
namespace AprgBitmap
{
OutwardCircleTraversal::Coordinate::Coordinate(
        unsigned int const firstValue,
        unsigned int const secondValue)
    : coordinate1(firstValue)
    , coordinate2(secondValue)
{}

OutwardCircleTraversal::OutwardCircleTraversal(unsigned int const maxRadius)
    : m_maxRadius(maxRadius)
    , m_radiusToCoordinates()
{
    constructRadiusToCoordinates();
}

void OutwardCircleTraversal::constructRadiusToCoordinates()
{
    for(unsigned int i=0; i<=m_maxRadius; i++)
    {
        for(unsigned int j=i; j<=m_maxRadius; j++)
        {
            double radius(getSquareRootOfXSquaredPlusYSquared(static_cast<double>(i), static_cast<double>(j)));
            m_radiusToCoordinates.emplace(radius, Coordinate(i, j));
        }
    }
}

OutwardCircleTraversal::RadiusToCoordinates const& OutwardCircleTraversal::getRadiusToCoordinates() const
{
    return m_radiusToCoordinates;
}

}

}
