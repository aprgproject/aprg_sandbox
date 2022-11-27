#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <array>
#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values, unsigned int MAX_NUMBER_OF_VALUES>
class CountingSorterUsingCountPerValue : public BaseSorter<Values>
{
public:
    using Value = typename Values::value_type;
    using ArrayOfCountPerValue = std::array<unsigned int, MAX_NUMBER_OF_VALUES>;
    using ValueToIndexableValueFunction = std::function<unsigned int(Value const&)>;
    using IndexableValueToValueFunction = std::function<Value(unsigned int const)>;

    CountingSorterUsingCountPerValue() = delete;
    CountingSorterUsingCountPerValue(
            ValueToIndexableValueFunction const& valueToIndexableValueFunction,
            IndexableValueToValueFunction const& indexableValueToValueFunction)
        : m_valueToIndexableValueFunction(valueToIndexableValueFunction)
        , m_indexableValueToValueFunction(indexableValueToValueFunction)
    {}

    void sort(Values & valuesToSort) const override
    {
        ArrayOfCountPerValue countPerValue{}; // important to initialize to zero
        for(auto const& value : valuesToSort)
        {
            countPerValue[m_valueToIndexableValueFunction(value)]++; // count each value
        }

        unsigned int i=0;
        for(unsigned int indexableValue=0; indexableValue<countPerValue.size(); indexableValue++) // Linear because i runs on valuesToSort.size()
        {
            for(unsigned int currentCount=0; currentCount<countPerValue.at(indexableValue); currentCount++)
            {
                valuesToSort[i++] = m_indexableValueToValueFunction(indexableValue); // put the value multiple times depending on the current count
            }
        }
    }

private:
    ValueToIndexableValueFunction m_valueToIndexableValueFunction;
    IndexableValueToValueFunction m_indexableValueToValueFunction;
};

}

}

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

// Improvement: Index compression (IMPLEMENTED ABOVE) is used to handle non-indexable values (such as negative integers).
