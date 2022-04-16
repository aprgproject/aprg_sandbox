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
        for(unsigned int digitIndex=highDigitIndex+1; digitIndex>lowDigitIndex; digitIndex--)
        {
            sortByLeastSignificantDigit(stringsToSort, digitIndex-1);
        }
    }

    void sortByLeastSignificantDigit(
            stringHelper::strings & stringsToSort,
            unsigned int const digitIndex) const
    {
        ArrayOfFrequencies newIndexes{};
        saveFrequencyForEachCharacterAt(newIndexes, stringsToSort, digitIndex);
        convertFrequenciesToIndexes(newIndexes);
        copyBackUsingNewIndexes(stringsToSort, newIndexes, digitIndex);
    }

private:
    void saveFrequencyForEachCharacterAt(
            ArrayOfFrequencies & frequencyOfEachCharacter,
            stringHelper::strings const& stringsToSort,
            unsigned int const digitIndex) const
    {
        unsigned int numberOfStrings(stringsToSort.size());
        for(unsigned int i=0; i<numberOfStrings; i++)
        {
            frequencyOfEachCharacter[getCharacterAtIfPossible(stringsToSort.at(i), digitIndex)+1]++;
        }
    }
    void convertFrequenciesToIndexes(
            ArrayOfFrequencies & newIndexes) const
    {        unsigned int newIndexesSize = newIndexes.size();
        for(unsigned int i=0; i<newIndexesSize; i++)
        {
            newIndexes[i+1] += newIndexes.at(i);
        }
    }

    void copyBackUsingNewIndexes(
            stringHelper::strings & stringsToSort,
            ArrayOfFrequencies & newIndexes,
            unsigned int const digitIndex) const
    {
        stringHelper::strings copiedStrings(stringsToSort);
        unsigned int numberOfStrings(stringsToSort.size());
        for(unsigned int i=0; i<numberOfStrings; i++)
        {
            stringsToSort[newIndexes[getCharacterAtIfPossible(copiedStrings.at(i), digitIndex)]++] = copiedStrings.at(i);
        }
    }
    unsigned char getCharacterAtIfPossible(
            std::string const& currentString,
            unsigned int const digitIndex) const    {
        unsigned char result(0U);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }

};

}

}
