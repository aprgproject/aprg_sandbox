#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

namespace TwoDimensions
{

using TrianglePolygonParent = Polygon<3>;

class Triangle : public TrianglePolygonParent
{
public:
    Triangle();
    Triangle(Point const& first, Point const& second, Point const& third);

};

}
}
