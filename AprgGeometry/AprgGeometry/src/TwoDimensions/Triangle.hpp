#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

using TriangleParent = Polygon<3>;

class Triangle : public TriangleParent
{
public:
    Triangle();
    Triangle(Point const& first, Point const& second, Point const& third);

};

}
