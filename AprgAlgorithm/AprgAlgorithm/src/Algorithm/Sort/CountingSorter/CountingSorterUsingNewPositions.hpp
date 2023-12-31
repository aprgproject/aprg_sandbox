#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <array>
#include <functional>

namespace alba {

namespace algorithm {

template <typename Values, int MAX_NUMBER_OF_VALUES>
class CountingSorterUsingNewPositions : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using ArrayOfCountPerValue = std::array<int, MAX_NUMBER_OF_VALUES>;
    using ValueToIndexableValueFunction = std::function<int(Value const&)>;

    CountingSorterUsingNewPositions() = delete;
    CountingSorterUsingNewPositions(ValueToIndexableValueFunction const& valueToIndexableValueFunction)
        : m_valueToIndexableValueFunction(valueToIndexableValueFunction) {}

    void sort(Values& valuesToSort) const override {
        ArrayOfCountPerValue correctPositions{};  // important to initialize to zero
        for (auto const& value : valuesToSort) {
            correctPositions[m_valueToIndexableValueFunction(value)]++;  // count each value
        }

        // Change count[i] so that count[i] now contains actual position of this character in output array
        for (int c = 1; c < static_cast<int>(correctPositions.size()); c++) {
            correctPositions[c] += correctPositions[c - 1];
        }

        Values copiedValues(valuesToSort);
        // For stable algorithm, reverse the traversal in copied values
        for (int i = copiedValues.size() - 1; i >= 0; i--) {
            auto indexableValue(m_valueToIndexableValueFunction(copiedValues[i]));
            valuesToSort[--correctPositions[indexableValue]] = copiedValues[i];
        }
    }

private:
    ValueToIndexableValueFunction m_valueToIndexableValueFunction;
};

}  // namespace algorithm

}  // namespace alba

// Counting sort is a sorting technique based on keys between a specific range.

// It works by counting the number of objects having distinct key values (similar to hashing).
// Then doing some arithmetic to calculate the position of each object in the output sequence.
// Let us understand it with the help of an example.

// Example:
// For simplicity, consider the data in the range 0 to 9.
// Input data: 1, 4, 1, 2, 7, 5, 2
// 1) Take a count array to store the count of each unique object.
// Index:     0  1  2  3  4  5  6  7  8  9
// Count:     0  2  2  0   1  1  0  1  0  0
// 2) Modify the count array such that each element at each index stores the sum of previous counts.
// Index:     0  1  2  3  4  5  6  7  8  9
// Count:     0  2  4  4  5  6  6  7  7  7
// The modified count array indicates the position of each object in the output sequence.
// 3) Output each object from the input sequence followed by decreasing its count by 1.
// Process the input data: 1, 4, 1, 2, 7, 5, 2. Position of 1 is 2.
// Put data 1 at index 2 in output.
// Decrease count by 1 to place next data 1 at an index 1 smaller than this index

// Time Complexity: O(n+k) where n is the number of elements in input array and k is the range of input.
// Auxiliary Space: O(n+k)

// The problem with the previous counting sort was that we could not sort the elements if we have negative numbers in
// it. Because there are no negative array indices. So what we do is, we find the minimum element and we will store
// count of that minimum element at zero index. Its better to have index compression (IMPLEMENTED ABOVE)

// Points to be noted:
// 1. Counting sort is efficient if the range of input data is not significantly greater than the number of objects to
// be sorted.
// -> Consider the situation where the input sequence is between range 1 to 10K and the data is 10, 5, 10K, 5K.
// 2. It is not a comparison based sorting. It running time complexity is O(n) with space proportional to the range of
// data.
// 3. It is often used as a sub-routine to another sorting algorithm like radix sort.
// 4. Counting sort uses a partial hashing to count the occurrence of the data object in O(1).
// 5. Counting sort can be extended to work for negative inputs also.
