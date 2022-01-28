#pragma once

#include <utility>

namespace alba
{

template <typename Values>
class BaseSorter
{
public:
    virtual ~BaseSorter()
    {}
    virtual void sort(Values & valuesToSort) const = 0;
};

}
