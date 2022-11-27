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
            unsigned int lowIndexWithEqualValue = lowStringIndex, i = lowStringIndex+1, highIndexWithEqualValue = highStringIndex;
            std::string const& partitionString(stringsToSort.at(lowStringIndex));
            bool shouldEqualPartProceed(isDigitValid(partitionString, digitIndex));
            char partitionDigit(getCharacterAtIfPossible(partitionString, digitIndex)); // use digit at lowStringIndex as partition
            while(i <= highIndexWithEqualValue)
            {
                char currentDigit(getCharacterAtIfPossible(stringsToSort.at(i), digitIndex));
                if(currentDigit < partitionDigit)
                {
                    std::swap(stringsToSort[lowIndexWithEqualValue++], stringsToSort[i]);
                }
                else if(currentDigit > partitionDigit)
                {
                    std::swap(stringsToSort[i], stringsToSort[highIndexWithEqualValue--]);
                }
                else
                {
                    i++;
                }
            }
            sort(stringsToSort, lowStringIndex, lowIndexWithEqualValue-1, digitIndex); // sort lower part
            if(shouldEqualPartProceed)
            {
                sort(stringsToSort, lowIndexWithEqualValue, highIndexWithEqualValue, digitIndex+1); // sort equal part
            }
            sort(stringsToSort, highIndexWithEqualValue+1, highStringIndex, digitIndex); // sort higher part
        }
    }

private:
    char getCharacterAtIfPossible(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        char result(0U);
        if(digitIndex < currentString.length())
        {
            result = currentString.at(digitIndex);
        }
        return result;
    }

    bool isDigitValid(
            std::string const& currentString,
            unsigned int const digitIndex) const
    {
        return digitIndex < currentString.length();
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
