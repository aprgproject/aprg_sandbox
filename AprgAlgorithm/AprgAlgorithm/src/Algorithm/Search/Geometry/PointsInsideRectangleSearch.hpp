#pragma once

#include <Algorithm/Search/Geometry/KdTree.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Key>
bool isEqualThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first == key2.first;
    } else {
        return key1.second == key2.second;
    }
}

template <typename Key>
bool isLessThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first < key2.first;
    } else {
        return key1.second < key2.second;
    }
}

template <typename Key>
bool isGreaterThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first > key2.first;
    } else {
        return key1.second > key2.second;
    }
}

template <typename Unit>
class PointsInsideRectangleSearch {
public:
    using Point = std::pair<Unit, Unit>;
    using Points = std::vector<Point>;
    using TwoDTree = KdTree<Point>;
    using NodeUniquePointer = typename TwoDTree::NodeUniquePointer;

    PointsInsideRectangleSearch(Point const& bottomLeft, Point const& topRight)
        : m_twoDTree(), m_rectangleBottomLeft(bottomLeft), m_rectangleTopRight(topRight) {}

    Points getPointsInsideTheRectangle() const {
        Points result{};
        NodeUniquePointer const& root(m_twoDTree.getRoot());
        if (root) {
            searchForPoints(root, result);
        }
        return result;
    }

    void addPoint(Point const& point) { m_twoDTree.put(point); }

private:
    void searchForPoints(NodeUniquePointer const& nodePointer, Points& pointsInsideRectangle) const {
        static int depth = 0;
        depth++;
        if (nodePointer) {
            Point const& currentPoint(nodePointer->key);
            if (isInsideRectangle(currentPoint)) {
                pointsInsideRectangle.emplace_back(currentPoint);
            }
            if (shouldGoToLeftChild(currentPoint, depth)) {
                searchForPoints(nodePointer->left, pointsInsideRectangle);
            }
            if (shouldGoToRightChild(currentPoint, depth)) {
                searchForPoints(nodePointer->right, pointsInsideRectangle);
            }
        }
        depth--;
    }

    inline bool shouldGoToLeftChild(Point const& point, int const depth) const {
        if (mathHelper::isOdd(depth)) {
            return m_rectangleBottomLeft.first < point.first;
        } else {
            return m_rectangleBottomLeft.second < point.second;
        }
    }

    inline bool shouldGoToRightChild(Point const& point, int const depth) const {
        if (mathHelper::isOdd(depth)) {
            return m_rectangleTopRight.first > point.first;
        } else {
            return m_rectangleTopRight.second > point.second;
        }
    }

    inline bool isInsideRectangle(Point const& point) const {
        return m_rectangleBottomLeft.first <= point.first && point.first <= m_rectangleTopRight.first &&
               m_rectangleBottomLeft.second <= point.second && point.second <= m_rectangleTopRight.second;
    }

    TwoDTree m_twoDTree;
    Point m_rectangleBottomLeft;
    Point m_rectangleTopRight;
};

}  // namespace algorithm

}  // namespace alba
