#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class ShellSorter : public BaseSorter<Values>  // This is invented by Shell in 1959
{
public:
    ShellSorter() = default;

    void sort(Values& valuesToSort) const override {
        int skipValue(getSkipValue(valuesToSort.size()));
        while (skipValue >= 1) {
            sortWithSkipping(valuesToSort, skipValue);
            skipValue /= 3;  // Knuth approach. Integer divide by 3 results to the next value.
        }
    }

private:
    void sortWithSkipping(Values& valuesToSort, int const skipValue) const {
        // This is h-sorting. An h-sorted array is h interleaved sorted subsequences.
        // This is insertion sort but with skipping
        for (int i = skipValue; i < static_cast<int>(valuesToSort.size()); i++) {
            continuouslySwapDownIfStillOutOfOrderWithSkipping(valuesToSort, i, skipValue);
        }
    }

    void continuouslySwapDownIfStillOutOfOrderWithSkipping(
        Values& valuesToSort, int const startingIndex, int const skipValue) const {
        // Works similar to insertion sort (but with skipping)
        for (int i = startingIndex; i >= skipValue && valuesToSort[i] < valuesToSort[i - skipValue];
             i -= skipValue) {
            std::swap(valuesToSort[i], valuesToSort[i - skipValue]);
        }
    }

    int getSkipValue(int const size) const {
        // Knuth approach. This returns: 1, 4, 13, 40, 121, 364, 1093
        int result(1);
        while (result < size / 3) {
            result = 3 * result + 1;
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// The idea behind shell sort is insertion sort is inefficient because elements only move one position at a time.
// So in shell sort we can move elements several positions at a time.
// The way we gonna do it is by h-sorting the array. An h-sorted array is h interleaved sorted subsequences.

// Insertion sort works well with skipping because:
// At big skip value: the number of elements to sort is small
// At small skip value: since it was already sorted at big skip values, the elements is nearly in order (insertion sort
// works well with this input)

// Proposition: A g-sorted array remains g-sorted after h-sorting it. Intuitively its true but proving it is more
// challenging.

// How do we determine the skip value?
// -> Powers of two? -> No, its always even so it will have minimal effect.
// -> Shell's original idea: Powers of two minus one? -> Okay, but it can be better.
// -> Knuth: 3x+1 -> 1, 4, 13, 40, 121, 364 -> OK. Easy to compute.
// -> Sedgewick: Merging of (9x4i) - (9x2i) + 1. -> Results in 1, 5, 19, 41, 109, 209. Tough to beat in empirical
// studies, but nobody knows if its the best one.

// Proposition: The worst case number of compares used by shell sort with 3x+1 increments is O(N^(3/2))
// In reality its much lesser than that. But an accurate model has not yet been discovered.

// Why is shellsort important?
// -> Simple idea leading to substantial performance gains
// -> Useful in practice
// -> Fast unless array size is huge. (Even beats other efficient sorting algorithms for medium sized arrays)
// -> Tiny, fixed foot print for code (used in embedded systems/hardware sort systems).

// Simple algorithm, non trivial performance, interesting questions.
// Asymptotic growth rate?
// Best sequence of increments?
// Average case performance?
// People have been trying to answer this questions for 50 years.
// Some good algorithms are still waiting discovery.

// Not stable -> Proof by counter example: Long distance swap might move an item past some equal item

// Other discussions:
// ShellSort is mainly a variation of Insertion Sort.
// In insertion sort, we move elements only one position ahead.
// When an element has to be moved far ahead, many movements are involved.
// The idea of shellSort is to allow exchange of far items.
// In shellSort, we make the array h-sorted for a large value of h.
// We keep reducing the value of h until it becomes 1.
// An array is said to be h-sorted if all sublists of every h’th element is sorted.

// Time Complexity:
// Time complexity of above implementation of shellsort is O(n2).
// In the above implementation gap is reduce by half in every iteration.
// There are many other ways to reduce gap which lead to better time complexity.
