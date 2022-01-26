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
        unsigned int h(getH(size));
        while(h >= 1)
        {
            for(unsigned int i=h; i<size; i++)
            {
                for(unsigned int j=i; j>=h && valuesToSort.at(j) < valuesToSort.at(j-h); j-=h)
                {
                    std::swap(valuesToSort[j], valuesToSort[j-h]);
                }
            }
            h /= 3;
        }
    }

private:
    unsigned int getH(unsigned int const size) const
    {        // This returns: 1, 4, 13, 40, 121, 364, 1093
        unsigned int h(1);
        while(h < size/3)
        {            h = 3*h + 1;
        }
        return h;
    }
};

}
