#pragma once

namespace alba
{

namespace algorithm
{

template <typename Values>
class BaseSorter
{public:
    virtual ~BaseSorter()
    {}
    virtual void sort(Values & valuesToSort) const = 0;
};

}

}