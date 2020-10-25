#pragma once

#include <set>
#include <utility>

namespace alba
{

namespace ContainerHelper
{

template <typename ValueType> std::pair<ValueType,ValueType> getInclusiveRangeFromSet(std::set<ValueType> const& container, ValueType const& value)
{
    std::pair<ValueType,ValueType> result;
    typename std::set<ValueType>::const_iterator itUpper = container.upper_bound(value);
    typename std::set<ValueType>::const_iterator itLower(itUpper);
    if(itLower != container.cbegin())
    {
        itLower--;
    }
    if(itUpper == container.cend())
    {
        itUpper--;
    }
    result.first = *itLower;
    result.second = *itUpper;
    return result;
}

} //namespace stringHelper

}//namespace alba
