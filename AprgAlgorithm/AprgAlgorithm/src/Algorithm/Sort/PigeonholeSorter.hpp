#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class PigeonholeSorter : public BaseSorter<Values>
{
public:
    using Value = typename Values::value_type;
    using Hole = std::vector<Value>;
    using Holes = std::vector<Hole>;

    PigeonholeSorter() = default;

    void sort(Values & valuesToSort) const override
    {
        auto minmaxItPair = std::minmax_element(valuesToSort.cbegin(), valuesToSort.cend());
        Value minimumValue = *(minmaxItPair.first);
        Value maximumValue = *(minmaxItPair.second);
        Value range = maximumValue - minimumValue + 1; // Find range

        // Create an array of vectors.
        // Size of array range.
        // Each vector represents a hole that is going to contain matching elements.
        Holes holes(range);

        // Traverse through input array and put every element in its respective hole
        for (Value const& value : valuesToSort)
        {
            holes[value-minimumValue].emplace_back(value);
        }

        // Traverse through all holes one by one.
        // For every hole, take its elements and put in array.
        auto itCopy = valuesToSort.begin();
        for(Hole const& hole : holes)
        {
            itCopy = std::copy(hole.cbegin(), hole.cend(), itCopy);
        }
    }
};

}

}


// Pigeonhole sorting is a sorting algorithm that is suitable
// for sorting lists of elements where the number of elements and the number of possible key values are approximately the same.

// It requires O(n + Range) time where n is number of elements in input array and ‘Range’ is number of possible values in array.
// Working of Algorithm :
// Step 1) Find minimum and maximum values in array. Let the minimum and maximum values be ‘min’ and ‘max’ respectively. Also find range as ‘max-min+1’.
// Step 2) Set up an array of initially empty “pigeonholes” the same size as of the range.
// Step 3) Visit each element of the array and then put each element in its pigeonhole. An element arr[i] is put in hole at index arr[i] – min.
// Step 4) Start the loop all over the pigeonhole array in order and put the elements from non- empty holes back into the original array.

// Comparison with Counting Sort :
// It is similar to counting sort, but differs in that it "moves items twice: once to the bucket array and again to the final destination".

// Pigeonhole sort has limited use as requirements are rarely met.
// For arrays where range is much larger than n, bucket sort is a generalization that is more efficient in space and time.
