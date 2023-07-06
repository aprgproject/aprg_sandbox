#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <array>
#include <functional>

namespace alba {

namespace algorithm {

template <typename Values, int MAX_NUMBER_OF_VALUES>
class CountingSorterUsingCountPerValue : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using ArrayOfCountPerValue = std::array<int, MAX_NUMBER_OF_VALUES>;
    using ValueToIndexableValueFunction = std::function<int(Value const&)>;
    using IndexableValueToValueFunction = std::function<Value(int const)>;

    CountingSorterUsingCountPerValue() = delete;
    CountingSorterUsingCountPerValue(
        ValueToIndexableValueFunction const& valueToIndexableValueFunction,
        IndexableValueToValueFunction const& indexableValueToValueFunction)
        : m_valueToIndexableValueFunction(valueToIndexableValueFunction),
          m_indexableValueToValueFunction(indexableValueToValueFunction) {}

    void sort(Values& valuesToSort) const override {
        ArrayOfCountPerValue countPerValue{};  // important to initialize to zero
        for (auto const& value : valuesToSort) {
            countPerValue[m_valueToIndexableValueFunction(value)]++;  // count each value
        }
        auto it = valuesToSort.begin();
        // Linear because it runs on valuesToSort.size()
        for (int index = 0; index < static_cast<int>(countPerValue.size()); index++) {
            for (int currentCount = 0; currentCount < countPerValue[index]; currentCount++) {
                // put the value multiple times depending on the current count
                *(it++) = m_indexableValueToValueFunction(index);
            }
        }
    }

private:
    ValueToIndexableValueFunction m_valueToIndexableValueFunction;
    IndexableValueToValueFunction m_indexableValueToValueFunction;
};

}  // namespace algorithm

}  // namespace alba

// This is a linear algorithm
// This algorithm depends on values as indices so the max value corresponds to the space cost

// Counting sort
// The lower bound nlogn does not apply to algorithms that do not compare array elements but use some other information.

// An example of such an algorithm is counting sort that sorts an array in O(n) time
// assuming that every element in the array is an integer between 0... c and c = O(n).
// The algorithm creates a bookkeeping array, whose indices are elements of the original array.
// The algorithm iterates through the original array and calculates how many times each element appears in the array.

// Construction of the bookkeeping array takes O(n) time.
// After this, the sorted array can be created in O(n) time because the number of
// occurrences of each element can be retrieved from the bookkeeping array.

// Thus, the total time complexity of counting sort is O(n).
// Counting sort is a very efficient algorithm but it can only be used when the constant c is small enough,
// so that the array elements can be used as indices in the bookkeeping array.

// Improvement: Index compression (IMPLEMENTED ABOVE) is used to handle non-indexable values (such as negative
// integers).
