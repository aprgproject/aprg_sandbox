#pragma once

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

template <typename ValueType, typename Iterator, typename Container>
void adjustUpperAndLowerIteratorsInSet(
        Container const& container,
        ValueType const& value,
        Iterator & itLower,
        Iterator & itUpper)
{
    if(!container.empty())
    {        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {                itLower--;
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

template <typename ValueType>
std::pair<typename std::set<ValueType>::const_iterator, typename std::set<ValueType>::const_iterator>
getLowerAndUpperConstIteratorsInSet(
        std::set<ValueType> const& container,
        ValueType const& value)
{
    using ConstIterator = typename std::set<ValueType>::const_iterator;
    std::pair<ConstIterator, ConstIterator> result;
    ConstIterator itUpper(container.upper_bound(value));
    ConstIterator itLower(container.lower_bound(value));
    adjustUpperAndLowerIteratorsInSet(container, value, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename ValueType>
std::pair<ValueType,ValueType> getLowerAndUpperValuesInSet(
        std::set<ValueType> const& container,
        ValueType const& value)
{
    using ConstIterator = typename std::set<ValueType>::const_iterator;
    std::pair<ValueType, ValueType> result;
    ConstIterator itUpper(container.upper_bound(value));
    ConstIterator itLower(container.lower_bound(value));
    adjustUpperAndLowerIteratorsInSet(container, value, itLower, itUpper);
    result.first = *itLower;
    result.second = *itUpper;    return result;
}

template <typename ValueType>
unsigned int countItemsInBetween(
        std::set<ValueType> const& container,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range count
    using ConstIterator = typename std::set<ValueType>::const_iterator;
    ConstIterator itLower(container.lower_bound(value1));
    ConstIterator itUpper(container.upper_bound(value2));
    return static_cast<unsigned int>(std::distance(itLower, itUpper));
}

template <typename ValueType>
std::set<ValueType> getItemsInBetween(
        std::set<ValueType> const& container,
        ValueType const& value1,
        ValueType const& value2)
{
    // 1D range search
    using ConstIterator = typename std::set<ValueType>::const_iterator;
    ConstIterator itLower(container.lower_bound(value1));
    ConstIterator itUpper(container.upper_bound(value2));
    return std::set<ValueType>(itLower, itUpper);
}

template <typename KeyType, typename Iterator, typename Container>
void adjustUpperAndLowerIteratorsInMap(
        Container const& container,
        KeyType const& keyValue,
        Iterator & itLower,
        Iterator & itUpper)
{
    if(!container.empty())
    {        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {                itLower--;
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

template <typename KeyType, typename ValueType>
std::pair<typename std::map<KeyType, ValueType>::const_iterator, typename std::map<KeyType, ValueType>::const_iterator>
getLowerAndUpperConstIteratorsInMap(std::map<KeyType, ValueType> const& container, KeyType const& keyValue)
{
    using ConstIterator = typename std::map<KeyType, ValueType>::const_iterator;
    std::pair<ConstIterator, ConstIterator> result;
    ConstIterator itUpper(container.upper_bound(keyValue));
    ConstIterator itLower(container.lower_bound(keyValue));
    adjustUpperAndLowerIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::map<KeyType, ValueType>::iterator, typename std::map<KeyType, ValueType>::iterator>
getLowerAndUpperIteratorsInMap(std::map<KeyType, ValueType> & container, KeyType const& keyValue)
{
    using Iterator = typename std::map<KeyType, ValueType>::iterator;
    std::pair<Iterator, Iterator> result;
    Iterator itUpper(container.upper_bound(keyValue));
    Iterator itLower(container.lower_bound(keyValue));
    adjustUpperAndLowerIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::multimap<KeyType, ValueType>::const_iterator, typename std::multimap<KeyType, ValueType>::const_iterator>
getLowerAndUpperConstIteratorsInMultiMap(std::multimap<KeyType, ValueType> const& container, KeyType const& keyValue)
{
    using ConstIterator = typename std::multimap<KeyType, ValueType>::const_iterator;
    std::pair<ConstIterator, ConstIterator> result;
    ConstIterator itUpper(container.upper_bound(keyValue));
    ConstIterator itLower(container.lower_bound(keyValue));
    adjustUpperAndLowerIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::multimap<KeyType, ValueType>::iterator, typename std::multimap<KeyType, ValueType>::iterator>
getLowerAndUpperIteratorsInMultiMap(std::multimap<KeyType, ValueType> & container, KeyType const& keyValue)
{
    using Iterator = typename std::multimap<KeyType, ValueType>::iterator;
    std::pair<Iterator, Iterator> result;
    Iterator itUpper(container.upper_bound(keyValue));
    Iterator itLower(container.lower_bound(keyValue));
    adjustUpperAndLowerIteratorsInMap(container, keyValue, itLower, itUpper);
    result.first = itLower;
    result.second = itUpper;    return result;
}

//SaveContentsToStreamtemplate <typename ValueType, std::size_t SIZE,
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
    std::ostream_iterator<unsigned int> outputIterator(result, getDelimeterBasedOnFormat(StreamFormat::String).c_str());

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
