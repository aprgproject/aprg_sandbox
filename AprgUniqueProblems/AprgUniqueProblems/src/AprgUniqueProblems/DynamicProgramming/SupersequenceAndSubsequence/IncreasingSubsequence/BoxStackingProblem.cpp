#include "BoxStackingProblem.hpp"

#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/LongestIncreasingSubsequenceWithLinearithmicTime.hpp>

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba {

BoxStackingProblem::BoxStackingProblem(Boxes const& boxes) : m_boxes(boxes) {}

BoxStackingProblem::Index BoxStackingProblem::getMaximumStackedHeight() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Value result(0);
    if (!m_boxes.empty()) {
        Boxes possibleBoxes(getAllPossibleBoxes());
        Values partialHeights(possibleBoxes.size(), 0);
        for (Index index(0); index < static_cast<Index>(possibleBoxes.size()); index++) {
            Box const& rightBox(possibleBoxes[index]);
            Value& partialHeight(partialHeights[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {
                Box const& leftBox(possibleBoxes[lowerIndex]);
                if (leftBox.getX() < rightBox.getX() && leftBox.getY() < rightBox.getY()) {
                    partialHeight = max(partialHeight, partialHeights[lowerIndex]);
                }
            }
            partialHeight += possibleBoxes[index].getZ();
        }
        result = *max_element(partialHeights.cbegin(), partialHeights.cend());
    }    return result;
}

BoxStackingProblem::Boxes BoxStackingProblem::getBoxesWithMaximumStackedHeight() const {    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Boxes result;
    if (!m_boxes.empty()) {
        Boxes possibleBoxes(getAllPossibleBoxes());
        Values partialHeights(possibleBoxes.size(), 0);
        IndexToIndex indexToPreviousIndex(possibleBoxes.size());

        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index(0); index < static_cast<Index>(possibleBoxes.size()); index++) {
            Box const& rightBox(possibleBoxes[index]);
            Value& partialHeight(partialHeights[index]);
            Value& previousIndex(indexToPreviousIndex[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {
                Box const& leftBox(possibleBoxes[lowerIndex]);
                if (leftBox.getX() < rightBox.getX() && leftBox.getY() < rightBox.getY() &&
                    partialHeight < partialHeights[lowerIndex]) {
                    partialHeight = partialHeights[lowerIndex];
                    previousIndex = lowerIndex;
                }
            }
            partialHeight += possibleBoxes[index].getZ();
        }

        // construct longest sequence
        auto itMax = max_element(partialHeights.cbegin(), partialHeights.cend());
        Index indexOfMaxSum = distance(partialHeights.cbegin(), itMax);
        Index traverseIndex = indexOfMaxSum;
        for (; traverseIndex != indexToPreviousIndex[traverseIndex];
             traverseIndex = indexToPreviousIndex[traverseIndex]) {
            result.emplace_back(possibleBoxes[traverseIndex]);
        }
        result.emplace_back(possibleBoxes[traverseIndex]);
        reverse(result.begin(), result.end());
    }
    return result;}

BoxStackingProblem::Boxes BoxStackingProblem::getAllPossibleBoxes() const {
    Boxes result;    result.reserve(m_boxes.size() * 3);
    for (Box const& box : m_boxes) {
        result.emplace_back(min(box.getY(), box.getZ()), max(box.getY(), box.getZ()), box.getX());
        result.emplace_back(min(box.getX(), box.getZ()), max(box.getX(), box.getZ()), box.getY());
        result.emplace_back(min(box.getX(), box.getY()), max(box.getX(), box.getY()), box.getZ());
    }
    sort(result.begin(), result.end());
    return result;
}

}  // namespace alba
