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

    return isAlmostEqual(lengthOfSides[0], lengthOfSides[1])
             || isAlmostEqual(lengthOfSides[1], lengthOfSides[2])
             || isAlmostEqual(lengthOfSides[2], lengthOfSides[0]);
}

bool Triangle::isRightTriangle() const
{
    AlbaAngles anglesAtVertices(getAnglesAtVertices());
    return any_of(anglesAtVertices.cbegin(), anglesAtVertices.cend(), [](AlbaAngle const& angleAtVertex)
    {
        return isAlmostEqual(angleAtVertex.getDegrees(), static_cast<double>(90));
    });
}

string Triangle::getDisplayableString() const
{
    std::stringstream ss;
    ss << "[" << m_vertices[0] << "][" << m_vertices[1] << "][" << m_vertices[2] << "]";
    return ss.str();
}

ostream & operator<<(ostream & out, Triangle const& triangle)
{
    out << triangle.getDisplayableString();
    return out;
}

}
}
