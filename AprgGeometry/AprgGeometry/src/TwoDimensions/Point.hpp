#pragma once

#include <Container/AlbaXY.hpp>

#include <vector>

namespace alba
{

namespace TwoDimensions
{

using PointParent = AlbaXY<double>;

class Point : public PointParent
{
    friend std::ostream & operator<<(std::ostream & out, Point const& point);
public:
    Point();
    Point(PointParent const& pointParent);    Point(double const xValue, double const yValue);
};

using Points = std::vector<Point>;

std::ostream & operator<<(std::ostream & out, Point const& point);

}
}