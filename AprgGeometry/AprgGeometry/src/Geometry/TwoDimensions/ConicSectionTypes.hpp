#pragma once

#include <Geometry/TwoDimensions/Polygon.hpp>

namespace alba
{
namespace TwoDimensions
{

enum class ConicSectionType
{
    Unknown,
    Point,
    Line,
    Circle,
    Parabola,
    Ellipse,
    Hyperbola
};

}
}
