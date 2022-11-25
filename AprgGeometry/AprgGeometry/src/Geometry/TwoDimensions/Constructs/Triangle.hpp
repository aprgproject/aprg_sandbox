#pragma once

#include <Geometry/TwoDimensions/Constructs/Polygon.hpp>

namespace alba
{

namespace TwoDimensions
{

using TrianglePolygonParent = Polygon<3>;

class Triangle : public TrianglePolygonParent
{
public:
    Triangle();
    Triangle(Point const& first, Point const& second, Point const& third);
    bool isIsoceles() const;
    bool isRightTriangle() const;

private:
    friend std::ostream & operator<<(std::ostream & out, Triangle const& triangle);
};

}
}