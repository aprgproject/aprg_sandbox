#include "Point.hpp"

using namespace std;

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

ostream & operator<<(ostream & out, Point const& point)
{
    out << dynamic_cast<PointParent const&>(point);
    return out;
}

}
}
