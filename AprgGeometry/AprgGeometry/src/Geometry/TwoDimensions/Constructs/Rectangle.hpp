#pragma once

#include <Geometry/TwoDimensions/Constructs/Quadrilateral.hpp>

namespace alba
{

namespace TwoDimensions
{

class Rectangle : public Quadrilateral
{
public:
    Rectangle();
    Rectangle(Point const& topLeft, Point const& bottomRight);

private:
    friend std::ostream & operator<<(std::ostream & out, Rectangle const& rectangle);

};

}
}