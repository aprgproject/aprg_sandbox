#pragma once

#include <TwoDimensions/Polygon.hpp>

namespace alba
{

namespace TwoDimensions
{

using QuadrilateralPolygonParent = Polygon<4>;

class Quadrilateral : public QuadrilateralPolygonParent
{
    friend std::ostream & operator<<(std::ostream & out, Quadrilateral const& quadrilateral);
public:
    Quadrilateral();
    Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth);

    std::string getDisplayableString() const;
};

std::ostream & operator<<(std::ostream & out, Quadrilateral const& quadrilateral);

}
}
