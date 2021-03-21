#pragma once

#include <Container/AlbaXY.hpp>

#include <set>
#include <vector>

namespace alba
{

namespace TwoDimensions
{

using PointParent = AlbaXY<double>;

class Point : public PointParent{
public:
    Point();
    Point(double const xValue, double const yValue);
};

using Points = std::vector<Point>;

}
}