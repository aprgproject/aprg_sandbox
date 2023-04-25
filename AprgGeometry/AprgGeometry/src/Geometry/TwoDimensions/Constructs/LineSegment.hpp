#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

namespace alba {

namespace TwoDimensions {

using LineSegment = std::pair<Point, Point>;
using LineSegments = std::vector<LineSegment>;

}  // namespace TwoDimensions

}  // namespace alba
