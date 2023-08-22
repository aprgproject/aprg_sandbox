#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

class CollectMaximumPointsInAGridUsingTwoTraversals {
public:
    using Index = int;
    using Value = int;
    using ValueGrid = matrix::AlbaMatrix<Value>;
    using ValueGrids = std::vector<ValueGrid>;
    static constexpr Value INVALID_COUNT = std::numeric_limits<Value>::max();
    static constexpr Value UNUSED_COUNT = INVALID_COUNT - 1;

    CollectMaximumPointsInAGridUsingTwoTraversals(ValueGrid const& inputGrid);

    Value getMaximumPointsUsingNaiveRecursion() const;
    Value getMaximumPointsUsingMemoizationDP() const;
    Value getMaximumPointsUsingIterativeDP() const;

private:
    Value getMaximumPointsUsingNaiveRecursion(Index const row, Index const columnLeft, Index const columnRight) const;
    Value getMaximumPointsUsingMemoizationDP(
        ValueGrids& valueGrids, Index const row, Index const columnLeft, Index const columnRight) const;
    ValueGrid m_inputGrid;
};

}  // namespace alba

// Collect maximum points in a grid using two traversals

// Given a matrix where every cell represents points.
// How to collect maximum points using two traversals under following conditions?
// Let the dimensions of given grid be R x C.
// 1) The first traversal starts from top left corner, i.e., (0, 0) and should reach left bottom corner, i.e., (R-1, 0).
// ---> The second traversal starts from top right corner, i.e., (0, C-1) and should reach bottom right corner, i.e.,
// (R-1, C-1) 2) From a point (i, j), we can move to (i+1, j+1) or (i+1, j-1) or (i+1, j) 3) A traversal gets all points
// of a particular cell through which it passes.
// ---> If one traversal has already collected points of a cell, then the other traversal gets no points if goes through
// that cell again.
