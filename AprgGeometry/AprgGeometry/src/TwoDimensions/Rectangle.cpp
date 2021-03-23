#include "Rectangle.hpp"

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

}
}
