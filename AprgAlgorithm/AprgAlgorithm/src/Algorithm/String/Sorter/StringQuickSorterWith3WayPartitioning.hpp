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
            // sort lower part
            sort(stringsToSort, lowStringIndex, indexForLessThan-1, digitIndex);
            if(v >= 0)
            {
                // sort equal part
                sort(stringsToSort, indexForLessThan, indexForGreaterThan, digitIndex+1);
            }
            // sort higher part
            sort(stringsToSort, indexForGreaterThan+1, highStringIndex, digitIndex);
        }
    }
private:
    char getCharacterAtIfPossible(
            std::string const& currentString,            unsigned int const digitIndex) const
    {
        char result(-1);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }
};

// Overview: Do 3 way partitioning on the dth character.
// -> Less overhead than R-way parition in MSD string sort
// -> Does not re-examine character equal to the partitioning char (but does re-examine characters not equal to the partitioning char)

// Standard quicksort vs 3-way string radix sort
// -> Standard quicksort
// ---> Uses ~2N ln (N) string compares on average
// ---> Costly for keys with long common prefixes (and this is a common case!)
// -> 3-way string radix sort
// ---> Uses ~2N ln (N) character compares on average for random strings
// ---> Avoids re-comparing long common prefixes

// MSD string sort vs 3-way string radix sort
// -> MSD string sort
// ---> Is cache inefficient
// ---> Too much memory storing count[]
// ---> Too much overhead reinitializing count[] and aux[]
// -> 3-way string radix sort
// ---> Has a short inner loop
// ---> Is cache-friendly
// ---> Is in-place
// Bottom line is 3 way string quicksort is method of choice for sorting strings.

}

}