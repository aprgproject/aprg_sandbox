#pragma once

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
unsigned int partitionAndGetPartitionIndex(
        Values & valuesToSort,
        unsigned int const lowestIndex,
        unsigned int const highestIndex)
{
    unsigned int indexWithGreaterValue=lowestIndex; // inner loop has increment first so the first index is skipped
    unsigned int indexWithLesserValue=highestIndex+1; // there is a plus one because inner loop has decrement first
    auto partitionValue(valuesToSort.at(lowestIndex)); // use first item as the partition value (this is skipped)
    while(indexWithGreaterValue < indexWithLesserValue)
    {
        // take note that that loop has increment first
        // starting from lowest+1 to highest, find a value greater than partitionValue        while(valuesToSort.at(++indexWithGreaterValue) < partitionValue && indexWithGreaterValue < highestIndex);

        // take note that that loop has decrement first
        // starting from highest to lowest, find a value less than partitionValue        // actually this condition "indexWithLesserValue > lowestIndex" is redundant because partition value is at lowestIndex
        // so first condition will not be satisfied anyway
        while(partitionValue < valuesToSort.at(--indexWithLesserValue) && indexWithLesserValue > lowestIndex);

        // stop if the indexWithGreaterValue and indexWithLesserValue meet
        // since the loop stops when indexWithLesserValue and indexWithGreaterValue are equal, they both have the partitionIndex
        if(indexWithGreaterValue < indexWithLesserValue)
        {
            std::swap(valuesToSort[indexWithGreaterValue], valuesToSort[indexWithLesserValue]); // swap greater value with lower value
        }
    }
    std::swap(valuesToSort[lowestIndex], valuesToSort[indexWithLesserValue]); // put partitionValue at partitionIndex
    return indexWithLesserValue; // return partition index
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInOneDirection(
        typename Values::iterator const lowestIt,
        typename Values::iterator const highestItPlusOne)
{
    auto partitionIt=lowestIt;
    auto partitionValue(*lowestIt);
    auto checkIt=lowestIt;
    checkIt++;
    auto stopIt=highestItPlusOne;
    for(; checkIt!=stopIt; checkIt++)
    {
        if(*checkIt <= partitionValue)
        {
            partitionIt++;
            if(partitionIt != checkIt) // if there is gap between partitionIt and checkIt then swap
            {
                std::swap(*partitionIt, *checkIt);
            }
        }
    }
    std::swap(*lowestIt, *partitionIt);  // put partitionValue at partitionIndex
    return partitionIt;
}

template <typename Values>
typename Values::iterator partitionAndGetPartitionIteratorInTwoDirections(
        typename Values::iterator const lowestIt,
        typename Values::iterator const highestIt)
{
    // same algorithm with index version

    auto itWithGreaterValue=lowestIt;
    itWithGreaterValue++;
    auto itWithLesserValue=highestIt;
    auto partitionValue(*lowestIt);
    while(itWithGreaterValue != itWithLesserValue)
    {
        while(*itWithGreaterValue<partitionValue && itWithGreaterValue!=highestIt && itWithGreaterValue!=itWithLesserValue)
        {
            itWithGreaterValue++;
        }
        while(partitionValue<*itWithLesserValue && itWithLesserValue!=lowestIt && itWithGreaterValue!=itWithLesserValue)
        {
            itWithLesserValue--;
        }

        if(itWithGreaterValue != itWithLesserValue)
        {
            std::swap(*itWithGreaterValue, *itWithLesserValue);
            itWithGreaterValue++;
            if(itWithGreaterValue != itWithLesserValue)
            {
                itWithLesserValue--;
            }
        }
    }
    if(partitionValue<*itWithLesserValue)
    {
        itWithLesserValue--;
    }
    std::swap(*lowestIt, *itWithLesserValue); // put partitionValue at partitionIt
    return itWithLesserValue; // return partition iterator
}

}

}

// This can be improved by using a random index for the partition value.