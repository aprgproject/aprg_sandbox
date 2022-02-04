#pragma once

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <typename Values>
void mergeTwoSortedSequences(
        Values & valuesToSort,
        Values & temp,
        unsigned int const low,
        unsigned int const mid,
        unsigned int const high)
{
    std::copy(valuesToSort.cbegin()+low, valuesToSort.cbegin()+high+1, temp.begin()+low);
    unsigned int i=low, j=mid+1;
    for(unsigned int k=low; k<=high; k++)
    {
        if(i > mid)
        {
            valuesToSort[k] = temp.at(j++);
        }
        else if(j > high)
        {
            valuesToSort[k] = temp.at(i++);
        }
        else if(temp.at(j) < temp.at(i))
        {
            valuesToSort[k] = temp.at(j++);
        }
        else
        {
            valuesToSort[k] = temp.at(i++);
        }
    }
}

template <typename Values>
Values mergeTwoSortedSequences(
        Values const& sortedValues1,
        Values const& sortedValues2)
{
    Values result;
    unsigned int i=0, j=0;
    while(i<sortedValues1.size() || j<sortedValues2.size())
    {
        if(i >= sortedValues1.size())
        {
            result.emplace_back(sortedValues2.at(j++));
        }
        else if(j >= sortedValues2.size())
        {
            result.emplace_back(sortedValues1.at(i++));
        }
        else if(sortedValues2.at(j) < sortedValues1.at(i))
        {
            result.emplace_back(sortedValues2.at(j++));
        }
        else
        {
            result.emplace_back(sortedValues1.at(i++));
        }
    }
    return result;
}

}

}
