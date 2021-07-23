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

    std::string getDisplayableString() const;
};

std::ostream & operator<<(std::ostream & out, Rectangle const& rectangle);

}
}
