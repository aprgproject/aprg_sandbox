#pragma once

#include <limits>
#include <type_traits>

namespace alba
{

namespace algorithm
{

template <typename Index>
constexpr Index getInvalidIndex()
{
    static_assert(std::is_integral<Index>::value, "Index must an integer.");
    if(std::is_signed<Index>::value)
    {
        return std::numeric_limits<Index>::min();
    }
    else
    {
        return std::numeric_limits<Index>::max();
    }
}

}

}
