#include "Point.hpp"

namespace alba
{

Point::Point()
    : PointParent(0, 0)
{}

Point::Point(double const xValue, double const yValue)
    : PointParent(xValue, yValue)
{}

}