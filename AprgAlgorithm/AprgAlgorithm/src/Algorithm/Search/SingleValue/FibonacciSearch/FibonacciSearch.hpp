#pragma once

#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithTwoIndices.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
class FibonacciSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    FibonacciSearch(Values const& values)  // values can be unsorted
        : m_sortedValues(values) {}

    Index getIndexOfValue(Value const& valueToCheck) {
        // This is different from whats is described below (wikipedia entry)
        Index previousFibonacci(0);
        Index currentFibonacci(1);
        while (currentFibonacci < static_cast<Index>(m_sortedValues.size()) &&
               m_sortedValues.at(currentFibonacci) < valueToCheck) {
            Index nextFibonacci = currentFibonacci + previousFibonacci;
            previousFibonacci = currentFibonacci;
            currentFibonacci = nextFibonacci;
        }

        BinarySearchWithTwoIndices<Values> binarySearch(m_sortedValues);  // perform binary search on that block
        return binarySearch.getIndexOfValue(
            previousFibonacci, std::min(currentFibonacci, static_cast<int>(m_sortedValues.size()) - 1), valueToCheck);
    }

private:
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// -> Fibonacci search technique:
// ---> This search a sorted sequence using a divide and conquer algorithm that narrows down possible locations with the
// aid of Fibonacci numbers.
// -----> The Fibonacci search technique is a method of searching a sorted array using a divide and conquer algorithm
// that narrows down possible locations with the aid of Fibonacci numbers.
// -----> Compared to binary search where the sorted array is divided into two equal-sized parts, one of which is
// examined further,
// -----> Fibonacci search divides the array into two parts that have sizes that are consecutive Fibonacci numbers.
// -----> On average, this leads to about 4% more comparisons to be executed,
// -----> but it has the advantage that one only needs addition and subtraction to calculate the indices of the accessed
// array elements,
// -----> while classical binary search needs bit-shift (see Bitwise operation), division or multiplication,
// -----> operations that were less common at the time Fibonacci search was first published.
// -----> Fibonacci search has an average- and worst-case complexity of O(log n) (see Big O notation).
// ---> The Fibonacci sequence has the property that a number is the sum of its two predecessors.
// -----> Therefore the sequence can be computed by repeated addition.
// -----> The ratio of two consecutive numbers approaches the Golden ratio, 1.618... Binary search works by dividing the
// seek area in equal parts (1:1).
// ----->  Fibonacci search can divide it into parts approaching 1:1.618 while using the simpler operations.
// ---> If the elements being searched have non-uniform access memory storage (i. e., the time needed to access a
// storage location varies depending on the location accessed),
// -----> the Fibonacci search may have the advantage over binary search in slightly reducing the average time needed to
// access a storage location.
// -----> If the machine executing the search has a direct mapped CPU cache, binary search may lead to more cache misses
// because the elements that are accessed often tend to gather in only a few cache lines;
// -----> this is mitigated by splitting the array in parts that do not tend to be powers of two. If the data is stored
// on a magnetic tape where seek time depends on the current head position,
// -----> a tradeoff between longer seek time and more comparisons may lead to a search algorithm that is skewed
// similarly to Fibonacci search.
// -----> Algorithm
// -------> Let k be defined as an element in F, the array of Fibonacci numbers. n = Fm is the array size.
// -------> If n is not a Fibonacci number, let Fm be the smallest number in F that is greater than n.
// -------> The array of Fibonacci numbers is defined where Fk+2 = Fk+1 + Fk, when k ≥ 0, F1 = 1, and F0 = 1.
// -------> To test whether an item is in the list of ordered numbers, follow these steps:
// ---------> (1) Set k = m.
// ---------> (2) If k = 0, stop. There is no match; the item is not in the array.
// ---------> (3) Compare the item against element in Fk−1.
// ---------> (4) If the item matches, stop.
// ---------> (5) If the item is less than entry Fk−1, discard the elements from positions Fk−1 + 1 to n. Set k = k − 1
// and return to step 2.
// ---------> (6) If the item is greater than entry Fk−1, discard the elements from positions 1 to Fk−1. Renumber the
// remaining elements from 1 to Fk−2, set k = k − 2, and return to step 2.
// -------> Alternative implementation (from "Sorting and Searching" by Knuth[4]):
// -------> Given a table of records R1, R2, ..., RN whose keys are in increasing order K1 < K2 < ... < KN, the
// algorithm searches for a given argument K. Assume N+1 = Fk+1
// ---------> Step 1. [Initialize] i ← Fk, p ← Fk-1, q ← Fk-2 (throughout the algorithm, p and q will be consecutive
// Fibonacci numbers)
// ---------> Step 2. [Compare] If K < Ki, go to Step 3; if K > Ki go to Step 4; and if K = Ki, the algorithm terminates
// successfully.
// ---------> Step 3. [Decrease i] If q=0, the algorithm terminates unsuccessfully.
// -----------> Otherwise set (i, p, q) ← (i - q, q, p - q) (which moves p and q one position back in the Fibonacci
// sequence); then return to Step 2
// ---------> Step 4. [Increase i] If p=1, the algorithm terminates unsuccessfully.
// -----------> Otherwise set (i,p,q) ← (i + q, p - q, 2q - p) (which moves p and q two positions back in the Fibonacci
// sequence); and return to Step 2
// -------> The two variants of the algorithm presented above always divide the current interval into a larger and a
// smaller subinterval.
// -------> The original algorithm,[1] however, would divide the new interval into a smaller and a larger subinterval in
// Step 4.
// -------> This has the advantage that the new i is closer to the old i and is more suitable for accelerating searching
// on magnetic tape.
// ---> Note: Fibonacci search is derived from Golden section search, an algorithm by Jack Kiefer (1953) to search for
// the maximum or minimum of a unimodal function in an interval.
