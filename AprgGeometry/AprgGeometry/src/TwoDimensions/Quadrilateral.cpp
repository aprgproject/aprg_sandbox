#include "Quadrilateral.hpp"

namespace alba
{

Quadrilateral::Quadrilateral()
    : QuadrilateralPolygonParent()
{}

Quadrilateral::Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth)
    : QuadrilateralPolygonParent{first, second, third, fourth}
{}

}