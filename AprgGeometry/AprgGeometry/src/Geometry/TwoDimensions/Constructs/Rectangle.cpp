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

ostream & operator<<(ostream & out, Rectangle const& rectangle)
{
    out << "[" << rectangle.m_vertices.at(0)
        << "][" << rectangle.m_vertices.at(1)
        << "][" << rectangle.m_vertices.at(2)
        << "][" << rectangle.m_vertices.at(3)
        << "]";
    return out;
}

}
}
