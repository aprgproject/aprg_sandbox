#include "Point.hpp"

using namespace std;

namespace alba
{

namespace TwoDimensions
{

Point::Point()
    : PointParent()
{}

Point::Point(PointParent const& pointParent)
    : PointParent(pointParent)
{}

Point::Point(double const xValue, double const yValue)
    : PointParent(xValue, yValue)
{}

ostream & operator<<(ostream & out, Point const& point)
{
    out << static_cast<PointParent const&>(point); // dont use dynamic_cast here (avoid RTTI)
    return out;
}

}
}
