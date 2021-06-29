#include "Quadrilateral.hpp"

using namespace std;

namespace alba
{

namespace TwoDimensions
{

Quadrilateral::Quadrilateral()
    : QuadrilateralPolygonParent()
{}

Quadrilateral::Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth)
    : QuadrilateralPolygonParent{first, second, third, fourth}
{}

string Quadrilateral::getDisplayableString() const
{
    std::stringstream ss;
    ss << "[" << m_vertices[0] << "][" << m_vertices[1] << "][" << m_vertices[2] << "][" << m_vertices[3] << "]";
    return ss.str();
}

ostream & operator<<(ostream & out, Quadrilateral const& quadrilateral)
{
    out << quadrilateral.getDisplayableString();
    return out;
}

}
}
