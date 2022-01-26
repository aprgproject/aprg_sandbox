#pragma once

#include <utility>

namespace alba
{

template <typename Values>
class ShellSorter
{
public:
    void sort(Values & valuesToSort) const
    {
        unsigned int const size = valuesToSort.size();
        unsigned int skipNumber(getSkipNumber(size));
        while(skipNumber >= 1)
        {
            for(unsigned int i=skipNumber; i<size; i++)
            {
                for(unsigned int j=i; j>=skipNumber && valuesToSort.at(j) < valuesToSort.at(j-skipNumber); j-=skipNumber)
                {
                    std::swap(valuesToSort[j], valuesToSort[j-skipNumber]);
                }
            }
            skipNumber /= 3;
        }
    }

private:
    unsigned int getSkipNumber(unsigned int const size) const
    {
        // This returns: 1, 4, 13, 40, 121, 364, 1093
        unsigned int h(1);
        while(h < size/3)
        {
            h = 3*h + 1;
        }
        return h;
    }
};

}
