#pragma once

#include <Common/Container/AlbaXYZ.hpp>

#include <vector>

namespace alba {

class BoxStackingProblem {
public:
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    using Box = AlbaXYZ<int>;
    using Boxes = std::vector<Box>;
    using IndexToIndex = std::vector<Index>;
    using IndexToValue = std::vector<Value>;

    BoxStackingProblem(Boxes const& sequence);

    Index getMaximumStackedHeight() const;
    Boxes getBoxesWithMaximumStackedHeight() const;

private:
    Boxes getAllPossibleBoxes() const;
    Boxes m_boxes;
};

}  // namespace alba

// VARIANT OF: Longest Increasing Subsequence

// Box Stacking Problem
// You are given a set of n types of rectangular 3-D boxes,
// where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers).
// You want to create a stack of boxes which is as tall as possible,
// but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box
// are each strictly larger than those of the 2-D base of the higher box.
// Of course, you can rotate a box so that any side functions as its base.
// It is also allowable to use multiple instances of the same type of box.

// The Box Stacking problem is a variation of LIS problem.
// We need to build a maximum height stack.
// Following are the key points to note in the problem statement:
// -> 1) A box can be placed on top of another box only if both width
// ---> and depth of the upper placed box are smaller than width and depth of the lower box respectively.
// -> 2) We can rotate boxes such that width is smaller than depth.
// ---> For example, if there is a box with dimensions {1x2x3} where 1 is height, 2×3 is base,
// ---> then there can be three possibilities, {1x2x3}, {2x1x3} and {3x1x2}
// -> 3) We can use multiple instances of boxes.
// ---> What it means is, we can have two different rotations of a box as part of our maximum height stack.
//
// Dynamic programming using tabulation
// -> 1) Generate all 3 rotations of all boxes.
// ---> The size of rotation array becomes 3 times the size of the original array.
// ---> For simplicity, we consider width as always smaller than or equal to depth.
// -> 2) Sort the above generated 3n boxes in decreasing order of base area.
// -> 3) After sorting the boxes, the problem is same as LIS with following optimal substructure property.
// ---> MSH(i) = Maximum possible Stack Height with box i at top of stack
// ---> MSH(i) = { Max ( MSH(j) ) + height(i) } where j < i and width(j) > width(i) and depth(j) > depth(i).
// -> If there is no such j then MSH(i) = height(i)
// -> 4) To get overall maximum height, we return max(MSH(i)) where 0 < i < n
