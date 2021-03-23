#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

namespace TwoDimensions
{

using QuadrilateralPolygonParent = Polygon<4>;

class Quadrilateral : public QuadrilateralPolygonParent
{
public:
    Quadrilateral();
    Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth);

};

}
}
