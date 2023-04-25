#pragma once

#include <Algorithm/Sort/QuickSorter/MedianOfMedians.hpp>
#include <Algorithm/Sort/QuickSorter/PivotType.hpp>

#include <cstdlib>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
unsigned int getIndexForPivotValue(
    Values& values, unsigned int const lowestIndex, unsigned int const highestIndex, PivotType const pivotType) {
    switch (pivotType) {
        case PivotType::ValueAtLowestIndex:
            return lowestIndex;
            break;
        case PivotType::ValueAtHighestIndex:
            return highestIndex;
            break;
        case PivotType::ValueAtRandomIndex:
            return lowestIndex + (rand() % (highestIndex + 1U - lowestIndex));
            break;
        case PivotType::ValueAtMedianOfMedians:
            return getIndexOfMedianOfMedians(values, lowestIndex, highestIndex);
            break;
        default:
            return lowestIndex;
            break;
    }
}

template <typename Values>
unsigned int partitionAndGetPartitionIndex(
    Values& values, unsigned int const lowestIndex, unsigned int const highestIndex, PivotType const pivotType) {
    unsigned int indexForPivotValue = getIndexForPivotValue(values, lowestIndex, highestIndex, pivotType);
    auto pivotValue = values.at(indexForPivotValue);
    if (indexForPivotValue != lowestIndex) {
        std::swap(
            values[indexForPivotValue], values[lowestIndex]);  // put it as lowest index so it would not be affected
    }

    unsigned int indexWithGreaterValue = lowestIndex;  // inner loop has increment first so the first index is skipped
    unsigned int indexWithLesserValue = highestIndex + 1;  // there is a plus one because inner loop has decrement first
    while (true) {
        // take note that that loop has increment first
        // starting from lowest+1 to highest, find a value greater than pivotValue
        while (values.at(++indexWithGreaterValue) < pivotValue && indexWithGreaterValue < highestIndex)
            ;

        // take note that that loop has decrement first
        // starting from highest to lowest, find a value less than pivotValue
        // actually this condition "indexWithLesserValue > lowestIndex" is redundant because partition value is at
        // lowestIndex so first condition will not be satisfied anyway
        while (pivotValue < values.at(--indexWithLesserValue) && indexWithLesserValue > lowestIndex)
            ;

        // stop if the indexWithGreaterValue and indexWithLesserValue meet
        // since the loop stops when indexWithLesserValue and indexWithGreaterValue are equal, they both have the
        // partitionIndex
        if (indexWithGreaterValue < indexWithLesserValue) {
            std::swap(
                values[indexWithGreaterValue], values[indexWithLesserValue]);  // swap greater value with lower value
        } else {
            break;
        }
    }
    std::swap(values[lowestIndex], values[indexWithLesserValue]);  // put pivotValue at partitionIndex
    return indexWithLesserValue;                                   // return partition index
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInOneDirection(
    typename Values::iterator const lowestIt, typename Values::iterator const highestItPlusOne) {
    auto pivotValue(*lowestIt);  // pivot value is at lowestIt
    auto partitionIt = lowestIt;
    auto checkIt = lowestIt;
    checkIt++;
    auto stopIt = highestItPlusOne;
    for (; checkIt != stopIt; checkIt++) {
        if (*checkIt <= pivotValue) {
            partitionIt++;
            if (partitionIt != checkIt)  // if there is gap between partitionIt and checkIt then swap
            {
                std::swap(*partitionIt, *checkIt);
            }
        }
    }
    std::swap(*lowestIt, *partitionIt);  // put pivotValue at partitionIndex
    return partitionIt;
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInTwoDirections(
    typename Values::iterator const lowestIt, typename Values::iterator const highestIt) {
    // same algorithm with index version

    auto pivotValue(*lowestIt);  // pivot value is at lowestIt

    auto itWithGreaterValue = lowestIt;
    itWithGreaterValue++;
    auto itWithLesserValue = highestIt;
    while (true) {
        while (*itWithGreaterValue < pivotValue && itWithGreaterValue != highestIt &&
               itWithGreaterValue != itWithLesserValue) {
            itWithGreaterValue++;
        }
        while (pivotValue < *itWithLesserValue && itWithLesserValue != lowestIt &&
               itWithGreaterValue != itWithLesserValue) {
            itWithLesserValue--;
        }

        if (itWithGreaterValue != itWithLesserValue) {
            std::swap(*itWithGreaterValue, *itWithLesserValue);
            itWithGreaterValue++;
            if (itWithGreaterValue != itWithLesserValue) {
                itWithLesserValue--;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (pivotValue < *itWithLesserValue) {
        itWithLesserValue--;
    }
    std::swap(*lowestIt, *itWithLesserValue);  // put pivotValue at partition iterator
    return itWithLesserValue;                  // return partition iterator
}

}  // namespace algorithm

}  // namespace alba
// A improvement idea is to randomly pick a pivot element.
// To implement randomized partition, we use a random function, rand() to generate index between l and r,
// swap the element at randomly generated index with the last element,
// and finally call the standard partition process which uses last element as pivot.
