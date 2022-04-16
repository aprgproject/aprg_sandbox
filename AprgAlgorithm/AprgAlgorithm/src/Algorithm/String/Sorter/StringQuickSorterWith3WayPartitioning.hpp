#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

class StringQuickSorterWith3WayPartitioning
{

public:
    void sort(stringHelper::strings & stringsToSort) const
    {
        // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
        sort(stringsToSort, 0U, stringsToSort.size()-1, 0U);
    }

    void sort(
            stringHelper::strings & stringsToSort,
            unsigned int const lowStringIndex,
            unsigned int const highStringIndex,
            unsigned int const digitIndex) const
    {
        if(lowStringIndex < highStringIndex)
        {
            unsigned int indexForLessThan = lowStringIndex, i = lowStringIndex+1, indexForGreaterThan = highStringIndex;
            char v(getCharacterAtIfPossible(stringsToSort.at(lowStringIndex), digitIndex));
            while(i <= indexForGreaterThan)
            {
                char t(getCharacterAtIfPossible(stringsToSort.at(i), digitIndex));
                if(t < v)
                {
                    std::swap(stringsToSort[indexForLessThan++], stringsToSort[i]);
                }
                else if(t > v)
                {
                    std::swap(stringsToSort[i], stringsToSort[indexForGreaterThan--]);
                }
                else
                {
                    i++;
                }
            }
            sort(stringsToSort, lowStringIndex, indexForLessThan-1, digitIndex);
            if(v >= 0)
            {
                sort(stringsToSort, indexForLessThan, indexForGreaterThan, digitIndex+1);
            }
            sort(stringsToSort, indexForGreaterThan+1, highStringIndex, digitIndex);
        }
    }

private:
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
