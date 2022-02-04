#pragma once

#include <Algorithm/Sorter/BaseSorter.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class InsertionSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
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

}
