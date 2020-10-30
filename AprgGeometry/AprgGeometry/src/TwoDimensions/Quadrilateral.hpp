#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

using QuadrilateralParent = Polygon<3>;

class Quadrilateral : public QuadrilateralParent
{
public:
    Quadrilateral();
    Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth);

};

}
