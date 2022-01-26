#pragma once

#include <utility>

namespace alba
{

template <typename Values>
class SelectionSorter
{
public:
    void sort(Values & valuesToSort) const
    {
        unsigned int const size = valuesToSort.size();
        for(unsigned int i=0; i<size; i++)
        {
            unsigned int indexOfMinimum(i);
            for(unsigned int j=i+1; j<size; j++)
            {
                if(valuesToSort.at(j) < valuesToSort.at(indexOfMinimum))
                {
                    indexOfMinimum = j;
                }
            }
            if(i != indexOfMinimum)
            {
                std::swap(valuesToSort[i], valuesToSort[indexOfMinimum]);
            }
        }
    }
};

}
