#pragma once

#include <Algorithm/Search/UniqueProblems/Median/MedianOfSmallerSizes.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

#include <algorithm>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Values>
typename Values::value_type getMedianOfThree(
    typename Values::value_type const& value1, typename Values::value_type const& value2,
    typename Values::value_type const& value3) {
    auto low = value1;
    auto mid = value2;
    auto high = value3;
    if (low > high) {
        std::swap(low, high);
    }
    if (low > mid) {
        std::swap(low, mid);
    }
    if (mid > high) {
        std::swap(mid, high);
    }
    return mid;
}

template <typename Values>
typename Values::value_type getMedianOfSmallerSizes(Values const& values) {
    // As noted below: If the group has an even number of elements, take the larger of the two medians.
    return MedianOfSmallerSizes<Values>(values).getLargerMedian();
}

template <typename Values>
typename Values::value_type getMedianOfSmallerSizes(
    typename Values::const_iterator lowestIt, typename Values::const_iterator highestItPlusOne) {
    // As noted below: If the group has an even number of elements, take the larger of the two medians.
    return MedianOfSmallerSizes<Values>(lowestIt, highestItPlusOne).getLargerMedian();
}

template <typename Values>
typename Values::value_type getMedianOfLowMidHigh(Values const& values, int const lowestIndex, int const highestIndex) {
    return getMedianOfThree<Values>(
        values.at(lowestIndex), values.at(getMidpointOfIndexes(lowestIndex, highestIndex)), values.at(highestIndex));
}

template <typename Values>
typename Values::value_type getMedianOfNinther(Values const& values, int const lowestIndex, int const highestIndex) {
    Values nines;
    nines.reserve(9);
    int deltaSize = highestIndex - lowestIndex;
    for (int i = 0; i <= 8; i++) {
        nines.emplace_back(values.at(lowestIndex + i * deltaSize / 8));
    }

    return getMedianOfThree<Values>(
        getMedianOfThree<Values>(nines[0], nines[1], nines[2]), getMedianOfThree<Values>(nines[3], nines[4], nines[5]),
        getMedianOfThree<Values>(nines[6], nines[7], nines[8]));
}

template <typename Values>
typename Values::value_type getMedianOfMedians(
    typename Values::const_iterator lowestIt, typename Values::const_iterator highestItPlusOne) {
    if (lowestIt + 5 >= highestItPlusOne) {
        return getMedianOfSmallerSizes<Values>(lowestIt, highestItPlusOne);
    } else {
        using MediansContainer = std::vector<typename Values::value_type>;
        MediansContainer medians;
        medians.reserve(highestItPlusOne - lowestIt);  // reserve this much
        for (auto medianLowestIt = lowestIt; medianLowestIt < highestItPlusOne; medianLowestIt += 5) {
            auto medianHighestItPlusOne = std::min(medianLowestIt + 5, highestItPlusOne);
            medians.emplace_back(getMedianOfSmallerSizes<Values>(medianLowestIt, medianHighestItPlusOne));
        }
        return getMedianOfMedians<MediansContainer>(medians.cbegin(), medians.cend());
    }
}

template <typename Values>
typename Values::value_type getMedianOfMedians(Values const& values, int const lowestIndex, int const highestIndex) {
    auto lowestIt = values.cbegin() + lowestIndex;
    auto highestItPlusOne = values.cbegin() + highestIndex + 1;
    return getMedianOfMedians<Values>(lowestIt, highestItPlusOne);
}

template <typename Values>
int getIndexOfValue(
    Values const& values, int const lowestIndex, int const highestIndex, typename Values::value_type const& value) {
    auto lowestIt = values.cbegin() + lowestIndex;
    auto highestItPlusOne = values.cbegin() + highestIndex + 1;
    auto valueIt = std::find(lowestIt, highestItPlusOne, value);
    return std::distance(values.cbegin(), valueIt);
}

}  // namespace algorithm

}  // namespace alba

// Quick selection in worst-case linear time
// Source: http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap10.htm

// We now examine a selection algorithm whose running time is O(n) in the worst case.
// Like RANDOMIZED-SELECT, the algorithm SELECT finds the desired element by recursively partitioning the input array.
// The idea behind the algorithm, however, is to guarantee a good split when the array is partitioned.
// SELECT uses the deterministic partitioning algorithm PARTITION from quicksort, modified to take the element to
// partition around as an input parameter.

// The SELECT algorithm determines the ith smallest of an input array of n elements by executing the following steps:
// 1. Divide the n elements of the input array into n/5 groups of 5 elements each and at most one group made up of the
// remaining n mod 5 elements.
// 2. Find the median of each of the n/5 groups by insertion sorting the elements of each group (of which there are 5 at
// most) and taking its middle element.
// -> (If the group has an even number of elements, take the larger of the two medians.)
// 3. Use SELECT recursively to find the median x of the n/5 medians found in step 2.
// 4. Partition the input array around the median-of-medians x using a modified version of PARTITION.
// -> Let k be the number of elements on the low side of the partition, so that n - k is the number of elements on the
// high side.
// 5. Use SELECT recursively to find the ith smallest element on the low side if i k, or the (i - k)th smallest element
// on the high side if i > k.

// To analyze the running time of SELECT, we first determine a lower bound on the number of elements that are greater
// than the partitioning element x. At least half of the medians found in step 2 are greater than or equal to the
// median-of-medians x. Thus, at least half of the n/5 groups contribute 3 elements that are greater than x, except for
// the one group that has fewer than 5 elements if 5 does not divide n exactly, and the one group containing x itself.
// Discounting these two groups, it follows that the number of elements greater than x is at least 3n/10 - 6.
// -> 3(ceil(1/2*n/5)-2) >= 3n/10 - 6

// Similarly, the number of elements that are less than x is at least 3n/10 - 6.
// Thus, in the worst case, SELECT is called recursively on at most 7n/10 + 6 elements in step 5.

// We can now develop a recurrence for the worst-case running time T(n) of the algorithm SELECT.
// Steps 1, 2, and 4 take O(n) time.
// Step 2 consists of O(n) calls of insertion sort on sets of size O(1).
// Step 3 takes time T(n/5), and step 5 takes time at most T(7n / 10 + 6), assuming that T is monotonically increasing.
// Note that 7n / 10 + 6 < n for n > 20 and that any input of 80 or fewer elements requires O(1) time.
// We can therefore obtain the recurrence:
// T(n) <= sigma(1)                        if n<=80
//      <= T(n/5) + T(7*n/10 + 6) + O(n)   if n>80

//  We show that the running time is linear by substitution.
// Assume that T(n) cn for some constant c and all n<=80.
// Substituting this inductive hypothesis into the right-hand side of the recurrence yields:
// T(n) <= c(n/5) + c(7n/10 + 6) + O(n)
//      <= cn/5 + c + 7cn/10 + 6c + O(n)
//      <= 9cn/10 + 7c + O(n)
//      <= cn
// since we can pick c large enough so that c(n / 10 - 7) is larger than the function described by the O(n) term for all
// n > 80. The worst-case running time of SELECT is therefore linear.

// As in a comparison sort, SELECT and RANDOMIZED-SELECT determine information about the relative order of elements only
// by comparing elements. Thus, the linear-time behavior is not a result of assumptions about the input, as was the case
// for the sorting algorithms. Sorting requires (n 1g n) time in the comparison model, even on average (see Problem
// 9-1), and thus the method of sorting and indexing presented in the introduction to this chapter is asymptotically
// inefficient.

// Note that the above algorithm is linear in worst case, but the constants are very high for this algorithm.
// Therefore, this algorithm doesn’t work well in practical situations, randomized quickSelect works much better and
// preferred.
