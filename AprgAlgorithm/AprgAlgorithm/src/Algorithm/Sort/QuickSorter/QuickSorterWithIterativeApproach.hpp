#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <stack>

namespace alba {

namespace algorithm {

template <typename Values>
class QuickSorterWithIterativeApproach : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;

    QuickSorterWithIterativeApproach(PivotType const pivotType) : m_pivotType(pivotType) {}

    void sort(Values& valuesToSort) const override {
        if (valuesToSort.size() > 1) {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not
            // sorted) std::shuffle should help
            sortWithIterativeApproach(valuesToSort, 0, valuesToSort.size() - 1);
        }
    }

private:
    void sortWithIterativeApproach(Values& valuesToSort, int const lowestIndex, int const highestIndex) const {
        std::stack<int> inputIndicesStack;
        inputIndicesStack.push(lowestIndex);
        inputIndicesStack.push(highestIndex);

        while (!inputIndicesStack.empty()) {
            int highIndex = inputIndicesStack.top();
            inputIndicesStack.pop();
            int lowIndex = inputIndicesStack.top();
            inputIndicesStack.pop();

            int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, lowIndex, highIndex, m_pivotType);
            if (lowIndex + 1 < partitionIndex) {
                inputIndicesStack.push(lowIndex);
                inputIndicesStack.push(partitionIndex - 1);
            }
            if (partitionIndex + 1 < highIndex) {
                inputIndicesStack.push(partitionIndex + 1);
                inputIndicesStack.push(highIndex);
            }
        }
    }

private:
    PivotType m_pivotType;
};

}  // namespace algorithm

}  // namespace alba

// The above mentioned optimizations for recursive quick sort can also be applied to iterative version.
// 1) Partition process is same in both recursive and iterative.
// -> The same techniques to choose optimal pivot can also be applied to iterative version.
// 2) To reduce the stack size, first push the indexes of smaller half.
// 3) Use insertion sort when the size reduces below a experimentally calculated threshold.
