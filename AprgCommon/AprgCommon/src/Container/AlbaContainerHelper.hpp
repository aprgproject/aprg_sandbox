#pragma once

#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <string>

namespace alba
{

namespace containerHelper
{

template <typename ValueType>
std::pair<ValueType,ValueType> getRangeFromSetBasedFromValue(std::set<ValueType> const& container, ValueType const& value)
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

template <typename ValueType, template<typename, typename = std::allocator<ValueType>> class Container>
void saveContentsOfContainerToFile(std::ofstream& outputFile, Container<ValueType> const& container)
{
    std::ostream_iterator<ValueType> outputIterator (outputFile,"\n");
    std::copy (container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType, template<typename, typename = std::allocator<ValueType>> class Container>
void retrieveContentsOfContainerToFile(std::ifstream& outputFile, Container<ValueType> const& container)
{
    std::istream_iterator<ValueType> inputIterator (outputFile,"\n");
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::back_inserter(container));
}

} //namespace containerHelper

}//namespace alba
