#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <limits>
#include <map>
#include <set>

namespace alba {

namespace algorithm {
// The one on NearestPointSearch class is better(getNearestPointPair()).
template <typename Unit>
class NearestPointPairSearchUsingSweepLine {
public:
    using Point = std::pair<Unit, Unit>;
    using SetOfPoints = std::set<Point>;
    using PointPair = std::pair<Point, Point>;
    using SetOfUnits = std::set<Unit>;
    using UnitToSetOfUnitsMap = std::map<Unit, SetOfUnits>;

    PointPair getNearestPointPair() const {
        // sweep line algorithm
        PointPair result{};
        UnitToSetOfUnitsMap xToSetOfYs;
        Unit smallestDistance(std::numeric_limits<Unit>::max());
        for (Point const& point : m_setOfPoints) {
            xToSetOfYs[point.first].emplace(point.second);

            // delete all points that are further than the current smallest distance
            auto itXToDelete = xToSetOfYs.lower_bound(point.first - smallestDistance);
            xToSetOfYs.erase(xToSetOfYs.begin(), itXToDelete);

            for (auto const& xAndSetOfYPair : xToSetOfYs) {
                Unit const x(xAndSetOfYPair.first);
                SetOfUnits const& ys(xAndSetOfYPair.second);
                auto itYStart = ys.lower_bound(point.second - smallestDistance);
                auto itYEnd = ys.upper_bound(point.second + smallestDistance);

                for (auto itY = itYStart; itY != itYEnd; itY++) {
                    Point possibleNearPoint(x, *itY);
                    if (point != possibleNearPoint) {
                        Unit distance = getDistance(point, possibleNearPoint);
                        if (smallestDistance > distance) {
                            smallestDistance = distance;
                            result = {point, possibleNearPoint};
                        }
                    }
                }
            }
        }
        return result;
    }

    void addPoint(Point const& point) { m_setOfPoints.emplace(point); }

private:
    inline Unit getDistance(Point const& point1, Point const& point2) const {
        return mathHelper::getSquareRootOfXSquaredPlusYSquared(
            point1.first - point2.first, point1.second - point2.second);
    }

    SetOfPoints m_setOfPoints;
};

}  // namespace algorithm

}  // namespace alba

// Given a set of n points, our next problem is to find two points whose Euclidean distance is minimum.

// This is another example of a problem that can be solved in O(nlogn) time using a sweep line algorithm.
// We go through the points from left to right and maintain a value d: the minimum distance between two points seen so
// far.

// At each point, we find the nearest point to the left.
// If the distance is less than d, it is the new minimum distance and we update the value of d.

// If the current point is (x, y) and there is a point to the left within a distance of less than d,
// the x coordinate of such a point must be between [x-d, x] and the y coordinate must be between [y-d, y+d].
// Thus, it suffices to only consider points that are located in those ranges, which makes the algorithm efficient.

// The efficiency of the algorithm is based on the fact that the region always contains only O(1) points.
// We can go through those points in O(logn) time by maintaining a set of points whose x coordinate is between [x-d, x],
// in increasing order according to their y coordinates.

// The time complexity of the algorithm is O(nlogn), because we go through n points and find for each point the nearest
// point to the left in O(logn) time.
