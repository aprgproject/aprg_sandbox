#pragma once

#include <algorithm>

namespace alba
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

}
