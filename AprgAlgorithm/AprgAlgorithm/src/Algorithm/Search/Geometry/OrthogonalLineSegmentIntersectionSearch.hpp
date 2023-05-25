#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>

#include <set>  // lets just use set when we can
#include <vector>

namespace alba {

namespace algorithm {

template <typename Unit>
class OrthogonalLineSegmentIntersectionSearch {
public:
    using Point = std::pair<Unit, Unit>;
    using Points = std::vector<Point>;
    enum class EventType {
        StartOfHorizontalLineSegment = 1,
        CheckVerticalLineSegment = 2,
        EndOfHorizontalLineSegment = 3
    };
    struct Event {
        Unit xLocation;
        Unit yLocation1;
        Unit yLocation2;
        EventType eventType;
        bool operator<(Event const& event) const {
            bool result(false);
            if (xLocation != event.xLocation) {
                result = xLocation < event.xLocation;  // sweep through x
            } else {
                result = static_cast<int>(eventType) < static_cast<int>(event.eventType);
            }
            return result;
        }
    };

    Points getIntersectingPoints() const {
        // sweep line algorithm
        Points result;
        std::set<Unit> yCheckInterval;
        for (Event const& event : m_events) {
            if (EventType::StartOfHorizontalLineSegment == event.eventType) {
                yCheckInterval.emplace(event.yLocation1);
            } else if (EventType::CheckVerticalLineSegment == event.eventType) {
                auto yLocationHits(
                    containerHelper::getItemsInBetweenForSet(yCheckInterval, event.yLocation1, event.yLocation2));
                for (auto const& yLocationHit : yLocationHits) {
                    result.emplace_back(Point{event.xLocation, yLocationHit});
                }
            } else if (EventType::EndOfHorizontalLineSegment == event.eventType) {
                yCheckInterval.erase(event.yLocation1);
            }
        }
        return result;
    }

    void addVerticalLine(Unit const& x, Unit const& y1, Unit const& y2) {
        Unit yLow(std::min(y1, y2));
        Unit yHigh(std::max(y1, y2));
        m_events.emplace(Event{x, yLow, yHigh, EventType::CheckVerticalLineSegment});
    }

    void addHorizontalLine(Unit const& y, Unit const& x1, Unit const& x2) {
        Unit xLow(std::min(x1, x2));
        Unit xHigh(std::max(x1, x2));
        m_events.emplace(Event{xLow, y, Unit{}, EventType::StartOfHorizontalLineSegment});
        m_events.emplace(Event{xHigh, y, Unit{}, EventType::EndOfHorizontalLineSegment});
    }

private:
    std::multiset<Event> m_events;
};

}  // namespace algorithm

}  // namespace alba

// Given a set of n line segments, each of them being either horizontal or vertical,
// consider the problem of counting the total number of intersection points.

// It is easy to solve the problem in O(n2) time, because we can go through all possible pairs of line segments and
// check if they intersect. However, we can solve the problem more efficiently in O(nlogn) time using a sweep line
// algorithm and a range query data structure. The idea is to process the endpoints of the line segments from left to
// right and focus on three types of events:
// -> (1) horizontal segment begins
// -> (2) horizontal segment ends
// -> (3) vertical segment

// We go through the events from left to right and use a data structure that maintains a set of y coordinates where
// there is an active horizontal segment. To store y coordinates of horizontal segments, we can use a binary indexed or
// segment tree, possibly with index compression. When such structures are used, processing each event takes O(logn)
// time, so the total running time of the algorithm is O(nlogn).
