#include "Point.hpp"

namespace alba
{

namespace ThreeDimensions
{

Point::Point()
    : PointParent(0, 0, 0)
{}

Point::Point(PointParent const& pointParent)
    : PointParent(pointParent)
{}

Point::Point(double const xValue, double const yValue, double const zValue)
    : PointParent(xValue, yValue, zValue)
{}

}
}
