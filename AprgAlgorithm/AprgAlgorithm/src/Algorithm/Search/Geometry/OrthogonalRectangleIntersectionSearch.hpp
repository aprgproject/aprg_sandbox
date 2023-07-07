#pragma once

#include <Algorithm/Search/Interval/IntervalSearchTree.hpp>

#include <map>
#include <set>  // lets just use set when we can
#include <vector>

namespace alba {

namespace algorithm {

template <typename Unit>
class OrthogonalRectangleIntersectionSearch {
public:
    using Point = std::pair<Unit, Unit>;
    using PairOfUnits = std::pair<Unit, Unit>;
    using Rectangle = std::pair<Point, Point>;
    using Rectangles = std::vector<Rectangle>;
    using IntervalWithUnit = Interval<Unit>;
    enum class EventType { StartOfRectangle = 1, EndOfRectangle = 2 };
    struct Event {
        Unit xLocation;
        IntervalWithUnit yInterval;
        Rectangle rectangle;
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

    Rectangles getIntersectingRectangles() const {
        // sweep line algorithm
        std::set<Rectangle> intersectingRectangles;
        std::map<PairOfUnits, Rectangle> intervalToRectangleMap;
        IntervalSearchTree<Unit> intervalSearchTree;
        for (Event const& event : m_events) {
            if (EventType::StartOfRectangle == event.eventType) {
                auto intervals(intervalSearchTree.getIntersectingIntervalsOf(event.yInterval));
                if (!intervals.empty()) {
                    intersectingRectangles.emplace(event.rectangle);
                    for (auto const& interval : intervals) {
                        auto it = intervalToRectangleMap.find({interval.start, interval.end});
                        if (it != intervalToRectangleMap.cend()) {
                            intersectingRectangles.emplace(it->second);
                        }
                    }
                }

                intervalSearchTree.put(event.yInterval);
                intervalToRectangleMap.emplace(
                    PairOfUnits{event.yInterval.start, event.yInterval.end}, event.rectangle);
            } else if (EventType::EndOfRectangle == event.eventType) {
                intervalSearchTree.deleteBasedOnKey(event.yInterval);
                intervalToRectangleMap.erase({event.yInterval.start, event.yInterval.end});
            }
        }
        return Rectangles(intersectingRectangles.cbegin(), intersectingRectangles.cend());
    }

    void addRectangle(Rectangle const& rectangle) {
        Unit xLow(std::min(rectangle.first.first, rectangle.second.first));
        Unit xHigh(std::max(rectangle.first.first, rectangle.second.first));
        IntervalWithUnit yInterval{rectangle.first.second, rectangle.second.second};
        m_events.emplace(Event{xLow, yInterval, rectangle, EventType::StartOfRectangle});
        m_events.emplace(Event{xHigh, yInterval, rectangle, EventType::EndOfRectangle});
    }

private:
    std::multiset<Event> m_events;
};

}  // namespace algorithm

}  // namespace alba
