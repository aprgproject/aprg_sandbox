#include "Triangle.hpp"

namespace alba
{

Triangle::Triangle()
    : TriangleParent()
{}

Triangle::Triangle(Point const& first, Point const& second, Point const& third)
    : TriangleParent{first, second, third}
{}

}
