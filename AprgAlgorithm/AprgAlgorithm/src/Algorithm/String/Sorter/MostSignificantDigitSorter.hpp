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
    static constexpr unsigned int CUTOFF_TO_SMALLER_SORT=0; // switch to different sort when size is small
    using ArrayOfFrequencies = std::array<FrequencyDataType, MAX_NUMBER_OF_CHARACTERS+1U>;

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
        if(lowStringIndex < stringsToSort.size() && highStringIndex < stringsToSort.size() && lowStringIndex < highStringIndex)
        {
            sortByMostSignificantDigitInternal(stringsToSort, lowStringIndex, highStringIndex, digitIndex);
        }
    }

private:

    void sortByMostSignificantDigitInternal(
            stringHelper::strings & stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
            if(highStringIndex <= lowStringIndex + CUTOFF_TO_SMALLER_SORT)
            {
                sortForSmallerSizes(stringsToSort, lowStringIndex, highStringIndex);
            }
            else
            {
                sortByMostSignificantDigitUsingNewIndexes(stringsToSort, lowStringIndex, highStringIndex, digitIndex);
            }
    }

    void sortForSmallerSizes(
            stringHelper::strings & stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex) const
    {
        std::sort(stringsToSort.begin()+lowStringIndex, stringsToSort.begin()+highStringIndex+1U);
    }

    void sortByMostSignificantDigitUsingNewIndexes(
            stringHelper::strings & stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        ArrayOfFrequencies newIndexes{};
        // Key indexed counting
        // Character index start at 2 because interval must be noted
        // For example (alphabet is a, b, c, d...), position translate to this:
        // 1) [0][a count][b count][c count]...
        // 2) [0][cumulate with a][cumulate with b][cumulate with c]...
        // 3) [a starting index][b starting index][c starting index][d starting index]...

        bool areAllDigitsInvalid(true);
        saveFrequencyForEachCharacterAt(newIndexes, areAllDigitsInvalid, stringsToSort, lowStringIndex, highStringIndex, digitIndex);
        if(!areAllDigitsInvalid)
        {
            computeCumulatesToGetNewIndexes(newIndexes);
            copyBackUsingNewIndexes(stringsToSort, newIndexes, lowStringIndex, highStringIndex, digitIndex);
            sortForEachCharacterValue(stringsToSort, newIndexes, lowStringIndex, digitIndex);
        }
    }

    void saveFrequencyForEachCharacterAt(
            ArrayOfFrequencies & frequencyOfEachCharacter,
            bool & areAllDigitsInvalid,
            stringHelper::strings const& stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        unsigned int limit(std::min(highStringIndex+1, stringsToSort.size()));
        for(auto it=stringsToSort.cbegin()+lowStringIndex; it!=stringsToSort.cbegin()+limit; it++) // starts at low string index and ends at high string index
        {
            std::string const& stringToSort(*it);
            frequencyOfEachCharacter[getCharacterAtIfPossible(stringToSort, digitIndex)+1U]++;
            areAllDigitsInvalid &= isDigitInvalid(stringToSort, digitIndex);
        }
    }

    void computeCumulatesToGetNewIndexes(
            ArrayOfFrequencies & newIndexes) const
    {
        // By getting the partial sum of each character index, we will know the new string index to put each string with this character
        unsigned int newIndexesSize = newIndexes.size();
        for(unsigned int i=0; i<newIndexesSize; i++)
        {
            newIndexes[i+1] += newIndexes.at(i);
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
        unsigned int limit(std::min(highStringIndex+1, copiedStrings.size()));
        for(auto it=copiedStrings.cbegin()+lowStringIndex; it!=copiedStrings.cbegin()+limit; it++) // starts at low string index and ends at high string index
        {
            // replace index uses the character index before it
            std::string const& copiedString(*it);
            unsigned int replaceIndex = lowStringIndex + newIndexes[getCharacterAtIfPossible(copiedString, digitIndex)]++;
            stringsToSort[replaceIndex] = copiedString;
        }
    }

    void sortForEachCharacterValue(
            stringHelper::strings& stringsToSort,
            ArrayOfFrequencies const& newIndexes,
            unsigned int const lowStringIndex,
            unsigned int const digitIndex) const
    {
        unsigned int newLowStringIndex = lowStringIndex;
        for(unsigned int i=0; i<MAX_NUMBER_OF_CHARACTERS; i++)
        {
            unsigned int newHighStringIndex = lowStringIndex + newIndexes.at(i);
            newHighStringIndex -= newHighStringIndex > 0U ? 1U : 0U;
            if(newLowStringIndex < newHighStringIndex)
            {
                sortByMostSignificantDigitInternal(stringsToSort, newLowStringIndex, newHighStringIndex, digitIndex+1);
            }
            newLowStringIndex = newHighStringIndex+1U;
        }
    }

    char getCharacterAtIfPossible(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        char result(0);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }

    bool isDigitInvalid(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        return digitIndex >= currentString.length();
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
