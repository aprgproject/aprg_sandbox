#pragma once

#include <algorithm>

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
    while(true)
    {
        // take note that that loop has increment first
        // starting from lowest+1 to highest, find a value greater than partitionValue
        while(valuesToSort.at(++indexWithGreaterValue) < partitionValue && indexWithGreaterValue < highestIndex);

        // take note that that loop has decrement first
        // starting from highest to lowest, find a value less than partitionValue
        // actually this condition "indexWithLesserValue > lowestIndex" is redundant because partition value is at lowestIndex
        // so first condition will not be satisfied anyway
        while(partitionValue < valuesToSort.at(--indexWithLesserValue) && indexWithLesserValue > lowestIndex);

        if(indexWithGreaterValue >= indexWithLesserValue)
        {
            // stop if the indexWithGreaterValue and indexWithLesserValue meet
            // since the loop stops when indexWithLesserValue and indexWithGreaterValue are equal, they both have the partitionIndex
            break;
        }
        std::swap(valuesToSort[indexWithGreaterValue], valuesToSort[indexWithLesserValue]); // swap greater value with lower value
    }
    std::swap(valuesToSort[lowestIndex], valuesToSort[indexWithLesserValue]); // put partitionValue at partitionIndex
    return indexWithLesserValue; // return partition index
}

}

}

// This can be improved by using a random index for the partition value.
