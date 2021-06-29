#include "Rectangle.hpp"

using namespace std;

namespace alba
{
namespace TwoDimensions
{
Rectangle::Rectangle()
    : Quadrilateral()
{}

Rectangle::Rectangle(Point const& topLeft, Point const& bottomRight)
    : Quadrilateral{topLeft, Point(bottomRight.getX(), topLeft.getY()), bottomRight, Point(topLeft.getX(), bottomRight.getY())}
{}

string Rectangle::getDisplayableString() const
{
    std::stringstream ss;
    ss << "[" << m_vertices[0] << "][" << m_vertices[1] << "][" << m_vertices[2] << "][" << m_vertices[3] << "]";
    return ss.str();
}

ostream & operator<<(ostream & out, Rectangle const& rectangle)
{
    out << rectangle.getDisplayableString();
    return out;
}

}
}