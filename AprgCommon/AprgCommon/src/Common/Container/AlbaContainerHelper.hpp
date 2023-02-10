#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>

namespace alba
{

namespace containerHelper
{

enum class StreamFormat
{
    String,
    File
};

std::string getDelimeterBasedOnFormat(StreamFormat const streamFormat);

template <typename ValueType, typename Container, typename Iterator>
void adjustLowerAndUpperIterators(
        Container const& container,
        ValueType const& value,
        Iterator & itLower,
        Iterator & itUpper)
{
    if(!container.empty())
    {
        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {
                itLower--;
            }
            else if(*itLower!=value)
            {
                itLower--;
            }
        }
        if(itUpper!=container.cbegin())
        {
            if(itUpper==container.cend())
            {
                itUpper--;
            }
            else if(*itUpper!=value)
            {
                itUpper--;
                if(*itUpper!=value)
                {
                    itUpper++;
                }
            }
        }
    }
}

// Non set

template <typename ValueType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsForNonSet(
        ContainerType const& sortedContainer,
        ValueType const& value)
{
    auto lowerAndUpperItPair(std::equal_range(sortedContainer.cbegin(), sortedContainer.cend(), value));
    adjustLowerAndUpperIterators(sortedContainer, value, lowerAndUpperItPair.first, lowerAndUpperItPair.second);
    return lowerAndUpperItPair;
}

template <typename ValueType, typename ContainerType>
std::pair<ValueType,ValueType> getLowerAndUpperValuesForNonSet(
        ContainerType const& sortedContainer,
        ValueType const& value)
{
    auto lowerAndUpperIteratorPair(getLowerAndUpperConstIteratorsForNonSet(sortedContainer, value));
    return std::pair<ValueType, ValueType>{*(lowerAndUpperIteratorPair.first), *(lowerAndUpperIteratorPair.second)};
}

template <typename ValueType, typename ContainerType>
unsigned int countItemsInBetweenForNonSet(
        ContainerType const& sortedContainer,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range count
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(std::lower_bound(sortedContainer.cbegin(), sortedContainer.cend(), value1));
    ConstIterator itUpper(std::upper_bound(sortedContainer.cbegin(), sortedContainer.cend(), value2));
    return static_cast<unsigned int>(std::distance(itLower, itUpper));
}

template <typename ValueType, typename ContainerType>
ContainerType getItemsInBetweenForNonSet(
        ContainerType const& sortedContainer,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range search
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(std::lower_bound(sortedContainer.cbegin(), sortedContainer.cend(), value1));
    ConstIterator itUpper(std::upper_bound(sortedContainer.cbegin(), sortedContainer.cend(), value2));
    return ContainerType(itLower, itUpper);
}


// set
// needs to differentiate set because according to cppreference:
// The number of comparisons performed is logarithmic in the distance between first and last (At most 2 * log 2(last - first) + O(1) comparisons).
// However, for non-LegacyRandomAccessIterators, the number of iterator increments is linear.
// Notably, std::set and std::multiset iterators are not random access,
// and so their member functions std::set::equal_range (resp. std::multiset::equal_range) should be preferred.

template <typename ValueType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsForSet(
        ContainerType const& setContainer,
        ValueType const& value)
{
    auto lowerAndUpperItPair(setContainer.equal_range(value));
    adjustLowerAndUpperIterators(setContainer, value, lowerAndUpperItPair.first, lowerAndUpperItPair.second);
    return lowerAndUpperItPair;
}

template <typename ValueType, typename ContainerType>
std::pair<ValueType,ValueType> getLowerAndUpperValuesForSet(
        ContainerType const& setContainer,
        ValueType const& value)
{
    auto lowerAndUpperIteratorPair(getLowerAndUpperConstIteratorsForSet(setContainer, value));
    return std::pair<ValueType, ValueType>{*(lowerAndUpperIteratorPair.first), *(lowerAndUpperIteratorPair.second)};
}

template <typename ValueType, typename ContainerType>
unsigned int countItemsInBetweenForSet(
        ContainerType const& setContainer,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range count
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(setContainer.lower_bound(value1));
    ConstIterator itUpper(setContainer.upper_bound(value2));
    return static_cast<unsigned int>(std::distance(itLower, itUpper));
}

template <typename ValueType, typename ContainerType>
ContainerType getItemsInBetweenForSet(
        ContainerType const& setContainer,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range search
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(setContainer.lower_bound(value1));
    ConstIterator itUpper(setContainer.upper_bound(value2));
    return ContainerType(itLower, itUpper);
}


// map

template <typename KeyType, typename Container, typename Iterator>
void adjustLowerAndUpperIteratorsInMap(
        Container const& container,
        KeyType const& keyValue,
        Iterator & itLower,
        Iterator & itUpper)
{
    if(!container.empty())
    {
        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {
                itLower--;
            }
            else if(itLower->first != keyValue)
            {
                itLower--;
            }
        }
        if(itUpper!=container.cbegin())
        {
            if(itUpper==container.cend())
            {
                itUpper--;
            }
            else if(itUpper->first != keyValue)
            {
                itUpper--;
                if(itUpper->first != keyValue)
                {
                    itUpper++;
                }
            }
        }
    }
}

template <typename KeyType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsInMap(ContainerType const& container, KeyType const& keyValue)
{
    using ConstIterator = typename ContainerType::const_iterator;
    std::pair<ConstIterator, ConstIterator> result;
    ConstIterator itLower(container.lower_bound(keyValue));
    ConstIterator itUpper(container.upper_bound(keyValue));
    adjustLowerAndUpperIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename KeyType, typename ContainerType>
std::pair<typename ContainerType::iterator, typename ContainerType::iterator>
getLowerAndUpperIteratorsInMap(ContainerType & container, KeyType const& keyValue)
{
    using Iterator = typename ContainerType::iterator;
    std::pair<Iterator, Iterator> result;
    Iterator itLower(container.lower_bound(keyValue));
    Iterator itUpper(container.upper_bound(keyValue));
    adjustLowerAndUpperIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename Adapter>
typename Adapter::container_type const& getUnderlyingContainer(Adapter const& adapter)
{
    struct AdapterParent : Adapter
    {
        static typename Adapter::container_type const& get(Adapter const& adapterAsParameter)
        {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}

template <typename Adapter>
typename Adapter::container_type & getUnderlyingContainerReference(Adapter & adapter)
{
    struct AdapterParent : Adapter
    {
        static typename Adapter::container_type & get(Adapter & adapterAsParameter)
        {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}




//SaveContentsToStream

template <typename ValueType, std::size_t SIZE,
          template <typename, std::size_t> class Container>
void saveContentsToStream(std::ostream & outputStream, Container<ValueType, SIZE> const& container, StreamFormat const streamFormat)
{
    //tested on array
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
void saveContentsToStream(std::ostream & outputStream, Container<ValueType> const& container, StreamFormat const streamFormat)
{
    //tested on vector
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void saveContentsToStream(std::ostream & outputStream, Container<ValueType> const& container, StreamFormat const streamFormat)
{
    //tested on set
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void saveContentsToStream(std::ostream & outputStream, Container<KeyType, ValueType> const& container, StreamFormat const streamFormat)
{
    //tested on map
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    if(StreamFormat::String==streamFormat)
    {
        for(auto const& content : container)
        {
            outputStream << "{"  << content.first << ":" << content.second << "}" << delimeter;
        }
    }
    else
    {
        for(auto const& content : container)
        {
            outputStream << content.first << delimeter;
            outputStream << content.second << delimeter;
        }
    }
}


//RetrieveContentsFromStream
template <typename ValueType, std::size_t SIZE,
          template <typename, std::size_t> class Container>
void retrieveContentsFromStream(std::istream & inputStream, Container<ValueType, SIZE> & container)
{
    //tested on array
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, container.begin());
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
void retrieveContentsFromStream(std::istream & inputStream, Container<ValueType> & container)
{
    //tested on vector
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, container.end()));
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void retrieveContentsFromStream(std::istream & inputStream, Container<ValueType> & container)
{
    //tested on set
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, container.end()));
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void retrieveContentsFromStream(std::istream & inputStream, Container<KeyType, ValueType> & container)
{
    //tested on map
    unsigned int state(0);
    std::pair<KeyType, ValueType> tempPair;
    while(inputStream.good())
    {
        if(0==state)
        {
            inputStream>>tempPair.first;
        }
        else if(1==state)
        {
            inputStream>>tempPair.second;
            container.insert(container.end(), tempPair);
        }
        state = (state+1)%2;
    }
}

//GetStringFromContents
template <typename ValueType, std::size_t SIZE,
          template <typename, std::size_t> class Container>
std::string getStringFromContents(Container<ValueType, SIZE> const& container)
{
    //tested on array
    std::ostringstream result;
    saveContentsToStream(result, container, StreamFormat::String);
    return result.str();
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContents(Container<ValueType> const& container)
{
    //tested on vector
    std::ostringstream result;
    saveContentsToStream(result, container, StreamFormat::String);
    return result.str();
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContents(Container<ValueType> const& container)
{
    //tested on set
    std::ostringstream result;
    saveContentsToStream(result, container, StreamFormat::String);
    return result.str();
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
std::string getStringFromContents(Container<KeyType, ValueType> const& container)
{
    //tested on map
    std::stringstream result;
    saveContentsToStream(result, container, StreamFormat::String);
    return result.str();
}


//GetStringOtherFormats
template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContentsWithNumberFormat(Container<ValueType> const& container)
{
    std::ostringstream result;
    std::string delimeter = getDelimeterBasedOnFormat(StreamFormat::String);
    std::ostream_iterator<unsigned int> outputIterator(result, delimeter.c_str());

    result<<"Decimal values: {"<<std::dec;
    std::copy(container.cbegin(), container.cend(), outputIterator);
    result<<"}\n";

    result<<"Hexadecimal values: {"<<std::hex;
    std::copy(container.cbegin(), container.cend(), outputIterator);
    result<<"}\n";

    return result.str();
}

} //namespace containerHelper

}//namespace alba
