#include "Triangle.hpp"

namespace alba
{

namespace TwoDimensions
{

Triangle::Triangle()
    : TrianglePolygonParent()
{}

Triangle::Triangle(Point const& first, Point const& second, Point const& third)
    : TrianglePolygonParent{first, second, third}
{}

}
}
