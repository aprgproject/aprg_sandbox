#pragma once

#include <Container/AlbaXYZ.hpp>

#include <vector>

namespace alba
{

namespace ThreeDimensions
{

using PointParent = AlbaXYZ<double>;

class Point : public PointParent
{
public:
    Point();
    Point(PointParent const& pointParent);
    Point(double const xValue, double const yValue, double const zValue);
};

using Points = std::vector<Point>;

std::ostream & operator<<(std::ostream & out, Point const& point);

}
}
