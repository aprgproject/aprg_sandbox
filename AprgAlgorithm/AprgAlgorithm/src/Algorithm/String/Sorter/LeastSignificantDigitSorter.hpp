#pragma once

#include <Common/String/AlbaStringHelper.hpp>

namespace alba
{

namespace algorithm
{

template <typename FrequencyDataType>
class LeastSignificantDigitSorter
{
public:

    static constexpr unsigned int MAX_NUMBER_OF_CHARACTERS=256;
    using ArrayOfFrequencies = std::array<FrequencyDataType, MAX_NUMBER_OF_CHARACTERS+1>;

    void sortByLeastSignificantDigits(
            stringHelper::strings & stringsToSort,
            unsigned int const lowDigitIndex,
            unsigned int const highDigitIndex) const
    {
        for(int digitIndex=static_cast<int>(highDigitIndex); static_cast<int>(lowDigitIndex)<=digitIndex; digitIndex--)
        {
            // highest index so least signficant first;
            sortByLeastSignificantDigit(stringsToSort, static_cast<unsigned int>(digitIndex));
        }
    }

    void sortByLeastSignificantDigit(
            stringHelper::strings & stringsToSort,
            unsigned int const digitIndex) const
    {
        // This is called: "key indexed counting"
        // Character index starts in 1 because this array will be used to compute cumulates
        // For example (alphabet is a, b, c, d...), position translate to this:
        // 1) [0][a count][b count][c count]...
        // 2) [0][cumulate with a][cumulate with b][cumulate with c]...
        // 3) [a starting index][b starting index][c starting index][d starting index]...

        ArrayOfFrequencies newIndexes{};
        countTheFrequencyForEachCharacterAt(newIndexes, stringsToSort, digitIndex);
        computeCumulatesToGetNewIndexes(newIndexes);
        copyBackUsingNewIndexes(stringsToSort, newIndexes, digitIndex);
    }

private:
    void countTheFrequencyForEachCharacterAt(
            ArrayOfFrequencies & frequencyOfEachCharacter,
            stringHelper::strings const& stringsToSort,
            unsigned int const digitIndex) const
    {
        for(std::string const& stringToSort : stringsToSort)
        {
            frequencyOfEachCharacter[getCharacterAtIfPossible(stringToSort, digitIndex)+1]++;
        }
    }

    void computeCumulatesToGetNewIndexes(
            ArrayOfFrequencies & newIndexes) const
    {
        // By getting the partial sum of each character index, we will know the new string index to put each string with this character
        unsigned int newIndexesSize = newIndexes.size();
        for(unsigned int i=0; i+1U<newIndexesSize; i++)
        {
            newIndexes[i+1U] += newIndexes.at(i);
        }
    }

    void copyBackUsingNewIndexes(
            stringHelper::strings & stringsToSort,
            ArrayOfFrequencies & newIndexes,
            unsigned int const digitIndex) const
    {
        stringHelper::strings copiedStrings(stringsToSort); // copy first and then copy back to output in the new indexes;
        for(std::string const& copiedString : copiedStrings)
        {
            stringsToSort[newIndexes[getCharacterAtIfPossible(copiedString, digitIndex)]++] = copiedString;
        }
    }

    inline unsigned char getCharacterAtIfPossible(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        unsigned char result(0U);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }
};

// Proposition: Key indexed counting uses ~11N+4R array accesses to sort N items whose keys are integers between 0 and R-1
// Proposition: Key indexed counting uses extra space proportional to N+R.
// This is stable

// LSD string (radix) sort
// -> Consider characters from right to left
// -> Stably sort using dth character as the key (using key-indexed counting).

// Proposition: LSD sorts fixed length strings in ascending order
// Proof (by induction):
// -> After pass i, string are sorted by last i characters
// ---> If two strings differ on sort key, key indexed sort puts them in proper relative order.
// ---> If two strings agree on sort key, stability keeps them in proper relative order.

// Interview question: Sort a million 32-bit integers? -> LSD can be better because of fixed width

// LSD has history with punch cards

}

}
