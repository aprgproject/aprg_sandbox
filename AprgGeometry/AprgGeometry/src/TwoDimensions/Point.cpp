#include "Point.hpp"

namespace alba
{

namespace TwoDimensions
{

Point::Point()
    : PointParent(0, 0)
{}

Point::Point(PointParent const& pointParent)
    : PointParent(pointParent)
{}

Point::Point(double const xValue, double const yValue)
    : PointParent(xValue, yValue)
{}

}
}
