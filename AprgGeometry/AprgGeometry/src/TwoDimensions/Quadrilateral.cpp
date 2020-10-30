#include "Quadrilateral.hpp"

namespace alba
{

Quadrilateral::Quadrilateral()
    : QuadrilateralParent()
{}

Quadrilateral::Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth)
    : QuadrilateralParent{first, second, third, fourth}
{}

}
