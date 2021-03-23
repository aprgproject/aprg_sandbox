#pragma once

#include <TwoDimensions/Quadrilateral.hpp>

namespace alba
{

namespace TwoDimensions
{

class Rectangle : public Quadrilateral
{
public:
    Rectangle();
    Rectangle(Point const& topLeft, Point const& bottomRight);

};

}
}
