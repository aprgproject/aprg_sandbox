#include "Triangle.hpp"

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

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

bool Triangle::isIsoceles() const
{
    Distances lengthOfSides(getLengthOfSides());

    return isAlmostEqual(lengthOfSides.at(0), lengthOfSides.at(1))
             || isAlmostEqual(lengthOfSides.at(1), lengthOfSides.at(2))
             || isAlmostEqual(lengthOfSides.at(2), lengthOfSides.at(0));
}

bool Triangle::isRightTriangle() const
{
    AlbaAngles anglesAtVertices(getAnglesAtVertices());
    return any_of(anglesAtVertices.cbegin(), anglesAtVertices.cend(), [](AlbaAngle const& angleAtVertex)
    {
        return isAlmostEqual(angleAtVertex.getDegrees(), static_cast<double>(90));
    });
}

ostream & operator<<(ostream & out, Triangle const& triangle)
{
    out << "[" << triangle.m_vertices.at(0)
        << "][" << triangle.m_vertices.at(1)
        << "][" << triangle.m_vertices.at(2)
        << "]";
    return out;
}

}
}
