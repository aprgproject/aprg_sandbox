#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <typename FrequencyDataType>
class MostSignificantDigitSorter
{
public:
    static constexpr unsigned int MAX_NUMBER_OF_CHARACTERS=256;
    static constexpr unsigned int CUTOFF_TO_SMALLER_SORT=0; // dont do smaller sorts
    using ArrayOfFrequencies = std::array<FrequencyDataType, MAX_NUMBER_OF_CHARACTERS+2>;

    void sortByMostSignificantDigit(stringHelper::strings & stringsToSort) const
    {
        sortByMostSignificantDigit(stringsToSort, 0U, stringsToSort.size()-1, 0U);
    }

    void sortByMostSignificantDigit(
            stringHelper::strings & stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        if(highStringIndex <= lowStringIndex + CUTOFF_TO_SMALLER_SORT)
        {
            std::sort(stringsToSort.begin()+lowStringIndex, stringsToSort.begin()+highStringIndex+1);
        }
        else
        {
            ArrayOfFrequencies newIndexes{};
            saveFrequencyForEachCharacterAt(newIndexes, stringsToSort, lowStringIndex, highStringIndex, digitIndex);
            computeCumulatesToGetNewIndexes(newIndexes);
            copyBackUsingNewIndexes(stringsToSort, newIndexes, lowStringIndex, highStringIndex, digitIndex);
            sortForEachCharacterValue(stringsToSort, newIndexes, lowStringIndex, digitIndex);
        }    }

private:
    void saveFrequencyForEachCharacterAt(            ArrayOfFrequencies & frequencyOfEachCharacter,
            stringHelper::strings const& stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        // Key indexed counting
        // Character index start at 2 because interval must be noted
        // For example (alphabet is a, b, c, d...), position translate to this:
        // 1) [0][0][a count][b count][c count]...
        // 2) [0][0][cumulate with a][cumulate with c][cumulate with c]...
        // 3) [0][a starting index][b starting index][c starting index][d starting index]...
        // 4) [a low index][b low index (a high index-1)][c low index (b high index-1)][d low index (c high index-1)]...
        unsigned int limit(std::min(highStringIndex+1, stringsToSort.size()));
        for(unsigned int i=lowStringIndex; i<limit; i++) // starts at low string index and ends at high string index
        {
            frequencyOfEachCharacter[getCharacterAtIfPossible(stringsToSort.at(i), digitIndex)+2]++;
        }
    }

    void computeCumulatesToGetNewIndexes(
            ArrayOfFrequencies & newIndexes) const
    {
        // By getting the partial sum of each character index, we will know the new string index to put each string with this character
        unsigned int newIndexesSize = newIndexes.size();
        for(unsigned int i=0; i<newIndexesSize; i++)
        {            newIndexes[i+1] += newIndexes.at(i);
        }
    }
    void copyBackUsingNewIndexes(
            stringHelper::strings & stringsToSort,
            ArrayOfFrequencies & newIndexes,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        stringHelper::strings copiedStrings(stringsToSort); // copy first and then copy back to output in the new indexes;
        unsigned int limit(std::min(highStringIndex+1, stringsToSort.size()));
        for(unsigned int i=lowStringIndex; i<limit; i++) // starts at low string index and ends at high string index
        {
            // replace index uses the character index before it
            unsigned int replaceIndex = lowStringIndex + newIndexes[getCharacterAtIfPossible(copiedStrings.at(i), digitIndex)+1]++;
            stringsToSort[replaceIndex] = copiedStrings.at(i);
        }    }

    void sortForEachCharacterValue(
            stringHelper::strings& stringsToSort,            ArrayOfFrequencies const& newIndexes,
            unsigned int const lowStringIndex,
            unsigned int const digitIndex) const
    {
        for(unsigned int i=0; i<MAX_NUMBER_OF_CHARACTERS; i++)
        {
            unsigned int newLowStringIndex(lowStringIndex+newIndexes.at(i));
            unsigned int newHighStringIndex(lowStringIndex+newIndexes.at(i+1));
            if(newHighStringIndex>0)
            {
                newHighStringIndex--;
            }
            // sort the sub arrays
            if(newLowStringIndex<newHighStringIndex)
            {
                sortByMostSignificantDigit(                            stringsToSort,
                            newLowStringIndex,
                            newHighStringIndex,
                            digitIndex+1);            }
        }
    }

    char getCharacterAtIfPossible(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        char result(-1);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }
};

// MSD string (radix) sort.
// -> Partition the array into R pieces according to first character (use key-index counting).
// -> Recursively sort all strings start with each character (Key-indexed counts delineate subarrays to sort)

// MSD string sort: potential for disastrous performance
// Observation 1: Mush too slow for small subarrays
// -> Each function calls needs its own count[] array.
// -> ASCII (256 counts): 100x slower than copy pass for N=2
// -> ASCII (65536 counts): 32000x slower for N=2
// Observation 2: Huge number of small subarrays because of recursion
// Solution: Cutoff to insertion sort for small subarrays.

// Peformance: Number of characters examined
// -> MSD examines just enough characters to sort the keys
// -> Number of characters examined depends on keys.
// -> Can be sublinear in input size

// MSD string sort vs quicksort for strings
// -> Disadvantages of MSD string sort.
// ---> Accesses memory "randomly" (cache inefficient)
// ---> Inner loop has a lot of instructions
// ---> Extra space for count[]
// ---> Extra space for aux[]
// -> Disadvantages of quicksort
// ---> Linearithmic number of string compares (not linear)
// ---> Has to rescan many characters in keys with long prefix matches
// Goal combine advantages of MSD and quick sort

}

}