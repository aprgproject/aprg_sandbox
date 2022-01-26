#pragma once

#include <utility>

namespace alba
{

template <typename Values>
class InsertionSorter
{
public:
    void sort(Values & valuesToSort) const
    {
        unsigned int const size = valuesToSort.size();
        for(unsigned int i=0; i<size; i++)
        {
            for(unsigned int j=i; j>0 && valuesToSort.at(j) < valuesToSort.at(j-1); j--)
            {
                std::swap(valuesToSort[j], valuesToSort[j-1]);
            }
        }
    }
};

}
