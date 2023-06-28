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
    // This is Hoare partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme

    int indexWithPivotValue = getPivotIndex(values, lowIndex, highIndex, pivotType);
    auto pivotValue = values[indexWithPivotValue];
    std::swap(values[lowIndex], values[indexWithPivotValue]);

    int indexWithGreaterValue = lowIndex;
    int indexWithLesserValue = highIndex + 1;
    while (true) {
        // Notice that the loop has increment first
        // Important: This loops exits when it finds a value greater than pivotValue
        while (values[++indexWithGreaterValue] < pivotValue && indexWithGreaterValue < highIndex)
            ;

        // Notice that the loop has decrement first
        // Important: This loops exits when it finds a value less than pivotValue
        while (pivotValue < values[--indexWithLesserValue] && indexWithLesserValue > lowIndex)
            ;

        // stop if the indexWithGreaterValue and indexWithLesserValue meet
        // the loop breaks when indexWithLesserValue == indexWithGreaterValue, they both have the partitionIndex
        if (indexWithGreaterValue < indexWithLesserValue) {
            std::swap(values[indexWithGreaterValue], values[indexWithLesserValue]);
        } else {
            break;
        }
    }

    std::swap(values[lowIndex], values[indexWithLesserValue]);
    return indexWithLesserValue;  // return partition index
}

template <typename Values>
int partitionAndGetPartitionIndexUsingLomuto(
    Values& values, int const lowIndex, int const highIndex, PivotType const pivotType) {
    // This is based from Lomuto partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme

    int indexWithPivotValue = getPivotIndex(values, lowIndex, highIndex, pivotType);
    auto pivotValue = values[indexWithPivotValue];
    std::swap(values[lowIndex], values[indexWithPivotValue]);

    int partitionIndex = lowIndex;
    for (int compareIndex = lowIndex + 1; compareIndex <= highIndex; compareIndex++) {
        if (values[compareIndex] < pivotValue) {
            std::swap(values[++partitionIndex], values[compareIndex]);
        }
    }

    std::swap(values[partitionIndex], values[lowIndex]);
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
    return itWithLesserValue;               // return partition iterator
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
