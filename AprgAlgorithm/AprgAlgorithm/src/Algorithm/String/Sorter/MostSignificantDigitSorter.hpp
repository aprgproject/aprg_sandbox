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
            convertFrequenciesToIndexes(newIndexes);
            copyBackUsingNewIndexes(stringsToSort, newIndexes, lowStringIndex, highStringIndex, digitIndex);
            sortForEachCharacterValue(stringsToSort, newIndexes, lowStringIndex, digitIndex);
        }
    }

private:
    void saveFrequencyForEachCharacterAt(
            ArrayOfFrequencies & frequencyOfEachCharacter,
            stringHelper::strings const& stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        unsigned int limit(std::min(highStringIndex+1, stringsToSort.size()));
        for(unsigned int i=lowStringIndex; i<limit; i++)
        {
            frequencyOfEachCharacter[getCharacterAtIfPossible(stringsToSort.at(i), digitIndex)+2]++;
        }
    }

    void convertFrequenciesToIndexes(
            ArrayOfFrequencies & newIndexes) const
    {
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
        stringHelper::strings copiedStrings(stringsToSort);
        unsigned int limit(std::min(highStringIndex+1, stringsToSort.size()));
        for(unsigned int i=lowStringIndex; i<limit; i++)
        {
            unsigned int replaceIndex = lowStringIndex + newIndexes[getCharacterAtIfPossible(copiedStrings.at(i), digitIndex)+1]++;
            stringsToSort[replaceIndex] = copiedStrings.at(i);
        }
    }

    void sortForEachCharacterValue(
            stringHelper::strings& stringsToSort,
            ArrayOfFrequencies const& newIndexes,
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
            if(newLowStringIndex<newHighStringIndex)
            {
                sortByMostSignificantDigit(
                            stringsToSort,
                            newLowStringIndex,
                            newHighStringIndex,
                            digitIndex+1);
            }
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

}

}
