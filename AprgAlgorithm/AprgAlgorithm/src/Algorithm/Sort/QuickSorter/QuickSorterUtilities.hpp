#pragma once

#include <Algorithm/Sort/QuickSorter/MediansHelper.hpp>
#include <Algorithm/Sort/QuickSorter/PivotType.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <cstdlib>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
typename Values::value_type getPivotValue(
    Values& values, int const lowestIndex, int const highestIndex, PivotType const pivotType) {
    switch (pivotType) {
        case PivotType::ValueAtLowestIndex:
            return values.at(lowestIndex);
        case PivotType::ValueAtHighestIndex:
            return values.at(highestIndex);
        case PivotType::ValueAtRandomIndex:
            return values.at(AlbaUniformNonDeterministicRandomizer(lowestIndex, highestIndex).getRandomValue());
        case PivotType::ValueAtMedianOfLowMidHigh:
            return getMedianOfLowMidHigh(values, lowestIndex, highestIndex);
        case PivotType::ValueAtMedianNinther:
            return getMedianOfNinther(values, lowestIndex, highestIndex);
        case PivotType::ValueAtMedianOfMedians:
            return getMedianOfMedians<Values>(values, lowestIndex, highestIndex);
        default:
            return values.at(lowestIndex);
    }
}

template <typename Values>
int partitionAndGetPartitionIndex(
    Values& values, int const lowestIndex, int const highestIndex, PivotType const pivotType) {
    // This is Hoare partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme

    auto pivotValue = getPivotValue(values, lowestIndex, highestIndex, pivotType);
    // Getting the index of the pivot value is an UGLY WORKAROUND, but we want to have multiple purposes
    int indexWithPivotValue = getIndexOfValue(values, lowestIndex, highestIndex, pivotValue);
    std::swap(values[lowestIndex], values[indexWithPivotValue]);

    int indexWithGreaterValue = lowestIndex;
    int indexWithLesserValue = highestIndex + 1;
    while (true) {
        // Notice that the loop has increment first
        // Important: This loops exits when it finds a value greater than pivotValue
        while (values.at(++indexWithGreaterValue) < pivotValue && indexWithGreaterValue < highestIndex)
            ;

        // Notice that the loop has decrement first
        // Important: This loops exits when it finds a value less than pivotValue
        while (pivotValue < values.at(--indexWithLesserValue) && indexWithLesserValue > lowestIndex)
            ;

        // stop if the indexWithGreaterValue and indexWithLesserValue meet
        // the loop breaks when indexWithLesserValue == indexWithGreaterValue, they both have the partitionIndex
        if (indexWithGreaterValue < indexWithLesserValue) {
            std::swap(values[indexWithGreaterValue], values[indexWithLesserValue]);
        } else {
            break;
        }
    }
    std::swap(values[lowestIndex], values[indexWithLesserValue]);
    return indexWithLesserValue;  // return partition index
}

template <typename Values>
int partitionAndGetPartitionIndexUsingLomuto(
    Values& values, int const lowestIndex, int const highestIndex, PivotType const pivotType) {
    // This is based from Lomuto partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme

    auto pivotValue = getPivotValue(values, lowestIndex, highestIndex, pivotType);
    // Getting the index of the pivot value is an UGLY WORKAROUND, but we want to have multiple purposes
    int indexWithPivotValue = getIndexOfValue(values, lowestIndex, highestIndex, pivotValue);
    std::swap(values[lowestIndex], values[indexWithPivotValue]);

    int partitionIndex = lowestIndex;
    for (int compareIndex = lowestIndex + 1; compareIndex <= highestIndex; compareIndex++) {
        if (values[compareIndex] <= pivotValue) {
            std::swap(values[++partitionIndex], values[compareIndex]);
            if (values[partitionIndex] == pivotValue) {
                indexWithPivotValue = partitionIndex;
            }
        }
    }
    std::swap(values[partitionIndex], values[lowestIndex]);
    return partitionIndex;
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInTwoDirections(
    typename Values::iterator const lowestIt, typename Values::iterator const highestIt) {
    // same algorithm with index version
    // This is Hoare partition scheme
    // https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme

    auto pivotValue(*lowestIt);  // pivot value is at lowestIt

    auto itWithGreaterValue = lowestIt;             // no minus one because first index is skipped
    auto itWithLesserValue = std::next(highestIt);  // plus one because inner loop has decrement first
    while (true) {
        while (*++itWithGreaterValue < pivotValue && itWithGreaterValue != highestIt)
            ;
        while (pivotValue < *--itWithLesserValue && itWithLesserValue != lowestIt)
            ;
        // check two positions because the iterators moves by two (one move back, one move forward)
        if (itWithGreaterValue != itWithLesserValue && itWithGreaterValue != std::next(itWithLesserValue)) {
            std::swap(*itWithGreaterValue, *itWithLesserValue);
        } else {
            break;
        }
    }
    std::swap(*lowestIt, *itWithLesserValue);  // put pivotValue at partition iterator
    return itWithLesserValue;                  // return partition iterator
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInOneDirection(
    typename Values::iterator const lowestIt, typename Values::iterator const highestItPlusOne) {
    auto pivotValue(*lowestIt);  // pivot value is at lowestIt
    auto partitionIt = lowestIt;
    auto stopIt = highestItPlusOne;
    for (auto compareIt = std::next(lowestIt); compareIt != stopIt; compareIt++) {
        if (*compareIt <= pivotValue) {
            std::swap(*++partitionIt, *compareIt);
        }
    }
    std::swap(*lowestIt, *partitionIt);  // put pivotValue at partition iterator
    return partitionIt;
}

}  // namespace algorithm

}  // namespace alba

// A improvement idea is to randomly pick a pivot element.
// To implement randomized partition, we use a random function, rand() to generate index between l and r,
// swap the element at randomly generated index with the last element,
// and finally call the standard partition process which uses last element as pivot.
