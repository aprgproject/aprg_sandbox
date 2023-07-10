#pragma once

#include <Algorithm/Sort/QuickSorter/MediansHelper.hpp>
#include <Algorithm/Sort/QuickSorter/PivotType.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <cstdlib>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
int getPivotIndex(Values& values, int const lowIndex, int const highIndex, PivotType const pivotType) {
    switch (pivotType) {
        case PivotType::LowestIndex:
            return lowIndex;
        case PivotType::HighestIndex:
            return highIndex;
        case PivotType::RandomIndex:
            return AlbaUniformNonDeterministicRandomizer(lowIndex, highIndex).getRandomValue();
        case PivotType::MedianOfLowMidHighIndexes:
            return getIndexOfMedianOfLowMidHighIndexes(values, lowIndex, highIndex);
        case PivotType::MedianNinther:
            return getIndexOfMedianNinther(values, lowIndex, highIndex);
        case PivotType::MedianOfMedians:
            return getIndexOfMedianOfMedians(values, lowIndex, highIndex);
        default:
            return lowIndex;
    }
}

template <typename Values>
int partitionAndGetPartitionIndex(Values& values, int const lowIndex, int const highIndex, PivotType const pivotType) {
    return partitionAndGetPartitionIndexUsingHoare(values, lowIndex, highIndex, pivotType);
}

template <typename Values>
int partitionAndGetPartitionIndexUsingHoare(
    Values& values, int const lowIndex, int const highIndex, PivotType const pivotType) {
    // This is Hoare partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme

    int indexWithPivotValue = getPivotIndex(values, lowIndex, highIndex, pivotType);
    auto pivotValue = values[indexWithPivotValue];
    // Put the pivot on low because so it will be first swapped.
    std::swap(values[lowIndex], values[indexWithPivotValue]);

    bool isPivotNotYetSwapped(true);
    int indexWithGreaterValue = lowIndex - 1;  // increment first in the loop below corrects the first index
    int indexWithLesserValue = highIndex + 1;  // decrement first in the loop below corrects the first index
    while (true) {
        // Important: This loops exits when it finds a value greater than pivotValue
        while (values[++indexWithGreaterValue] < pivotValue)
            ;
        // Important: This loops exits when it finds a value less than pivotValue
        while (pivotValue < values[--indexWithLesserValue])
            ;

        // Stop if the indexWithGreaterValue and indexWithLesserValue meet
        if (indexWithGreaterValue < indexWithLesserValue) {
            std::swap(values[indexWithGreaterValue], values[indexWithLesserValue]);
            // The portion below is different from the Hoare's implementation.
            // This is added because we need the partitionIndex.
            if (isPivotNotYetSwapped) {
                indexWithPivotValue = indexWithLesserValue;  // keep track of pivot
                isPivotNotYetSwapped = false;
            }
        } else {
            break;
        }
    }
    if (isPivotNotYetSwapped) {
        return lowIndex;  // return original position
    } else {
        // Swap at pivot at the border of the right partition.
        std::swap(values[indexWithPivotValue], values[indexWithGreaterValue]);
        return indexWithGreaterValue;  // return swapped position
    }
}

template <typename Values>
int partitionAndGetPartitionIndexUsingLomuto(
    Values& values, int const lowIndex, int const highIndex, PivotType const pivotType) {
    // This is based from Lomuto partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme

    int indexWithPivotValue = getPivotIndex(values, lowIndex, highIndex, pivotType);
    auto pivotValue = values[indexWithPivotValue];
    std::swap(values[highIndex], values[indexWithPivotValue]);

    // Notice this has preincrement inside the loop to offset the  -1 start it to lowIndex
    int partitionIndex = lowIndex - 1;
    for (int compareIndex = lowIndex; compareIndex < highIndex; compareIndex++) {
        if (values[compareIndex] <= pivotValue) {
            std::swap(values[++partitionIndex], values[compareIndex]);
        }
    }

    std::swap(values[++partitionIndex], values[highIndex]);
    return partitionIndex;
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInTwoDirections(
    typename Values::iterator const itLow, typename Values::iterator const itHigh) {
    // same algorithm with index version
    // This is Hoare partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme

    auto pivotValue(*itLow);  // pivot value is at itLow

    auto itWithGreaterValue = itLow;             // no minus one because first index is skipped
    auto itWithLesserValue = std::next(itHigh);  // plus one because inner loop has decrement first
    while (true) {
        while (*++itWithGreaterValue < pivotValue && itWithGreaterValue != itHigh)
            ;
        while (pivotValue < *--itWithLesserValue && itWithLesserValue != itLow)
            ;
        // check two positions because the iterators moves by two (one move back, one move forward)
        if (itWithGreaterValue != itWithLesserValue && itWithGreaterValue != std::next(itWithLesserValue)) {
            std::swap(*itWithGreaterValue, *itWithLesserValue);
        } else {
            break;
        }
    }

    std::swap(*itLow, *itWithLesserValue);  // put pivotValue at partition iterator
    return itWithLesserValue;
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInOneDirection(
    typename Values::iterator const itLow, typename Values::iterator const itHighPlusOne) {
    auto pivotValue(*itLow);  // pivot value is at itLow

    auto partitionIt = itLow;
    auto stopIt = itHighPlusOne;
    for (auto compareIt = std::next(itLow); compareIt != stopIt; compareIt++) {
        if (*compareIt <= pivotValue) {
            std::swap(*++partitionIt, *compareIt);
        }
    }

    std::swap(*itLow, *partitionIt);  // put pivotValue at partition iterator
    return partitionIt;
}

}  // namespace algorithm

}  // namespace alba

// A improvement idea is to randomly pick a pivot element.
// To implement randomized partition, we use a random function, rand() to generate index between l and r,
// swap the element at randomly generated index with the last element,
// and finally call the standard partition process which uses last element as pivot.
