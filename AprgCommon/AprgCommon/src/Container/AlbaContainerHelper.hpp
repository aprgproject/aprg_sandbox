#pragma once

#include <fstream>
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

template <typename ValueType>
std::pair<ValueType,ValueType> getLowerAndUpperValuesInSet(
        std::set<ValueType> const& container,
        ValueType const& value)
{
    std::pair<ValueType,ValueType> result;
    typename std::set<ValueType>::const_iterator itUpper(container.upper_bound(value));
    typename std::set<ValueType>::const_iterator itLower(container.lower_bound(value));
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
    result.first = *itLower;
    result.second = *itUpper;
    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::map<KeyType, ValueType>::const_iterator, typename std::map<KeyType, ValueType>::const_iterator>
getLowerAndUpperConstIteratorsInMap(std::map<KeyType, ValueType> const& container, KeyType const& keyValue)
{
    std::pair<typename std::map<KeyType, ValueType>::const_iterator, typename std::map<KeyType, ValueType>::const_iterator> result;
    typename std::map<KeyType, ValueType>::const_iterator itUpper(container.upper_bound(keyValue));
    typename std::map<KeyType, ValueType>::const_iterator itLower(container.lower_bound(keyValue));
    if(!container.empty())
    {
        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {
                itLower--;
            }
            else if(itLower->first!=keyValue)
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
            else if(itUpper->first!=keyValue)
            {
                itUpper--;
                if(itUpper->first!=keyValue)
                {
                    itUpper++;
                }
            }
        }
    }
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::map<KeyType, ValueType>::iterator, typename std::map<KeyType, ValueType>::iterator>
getLowerAndUpperIteratorsInMap(std::map<KeyType, ValueType> & container, KeyType const& keyValue)
{
    std::pair<typename std::map<KeyType, ValueType>::iterator, typename std::map<KeyType, ValueType>::iterator> result;
    typename std::map<KeyType, ValueType>::iterator itUpper(container.upper_bound(keyValue));
    typename std::map<KeyType, ValueType>::iterator itLower(container.lower_bound(keyValue));
    if(!container.empty())
    {
        if(itLower!=container.begin())
        {
            if(itLower==container.end())
            {
                itLower--;
            }
            else if(itLower->first!=keyValue)
            {
                itLower--;
            }
        }
        if(itUpper!=container.begin())
        {
            if(itUpper==container.end())
            {
                itUpper--;
            }
            else if(itUpper->first!=keyValue)
            {
                itUpper--;
                if(itUpper->first!=keyValue)
                {
                    itUpper++;
                }
            }
        }
    }
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::multimap<KeyType, ValueType>::const_iterator, typename std::multimap<KeyType, ValueType>::const_iterator>
getLowerAndUpperConstIteratorsInMultiMap(std::multimap<KeyType, ValueType> const& container, KeyType const& keyValue)
{
    std::pair<typename std::multimap<KeyType, ValueType>::const_iterator, typename std::multimap<KeyType, ValueType>::const_iterator> result;
    typename std::multimap<KeyType, ValueType>::const_iterator itUpper(container.upper_bound(keyValue));
    typename std::multimap<KeyType, ValueType>::const_iterator itLower(container.lower_bound(keyValue));
    if(!container.empty())
    {
        if(itLower!=container.cbegin())
        {
            if(itLower==container.cend())
            {
                itLower--;
            }
            else if(itLower->first!=keyValue)
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
            else if(itUpper->first!=keyValue)
            {
                itUpper--;
                if(itUpper->first!=keyValue)
                {
                    itUpper++;
                }
            }
        }
    }
    result.first = itLower;
    result.second = itUpper;
    return result;
}

template <typename KeyType, typename ValueType>
std::pair<typename std::multimap<KeyType, ValueType>::iterator, typename std::multimap<KeyType, ValueType>::iterator>
getLowerAndUpperIteratorsInMultiMap(std::multimap<KeyType, ValueType> & container, KeyType const& keyValue)
{
    std::pair<typename std::multimap<KeyType, ValueType>::iterator, typename std::multimap<KeyType, ValueType>::iterator> result;
    typename std::multimap<KeyType, ValueType>::iterator itUpper(container.upper_bound(keyValue));
    typename std::multimap<KeyType, ValueType>::iterator itLower(container.lower_bound(keyValue));
    if(!container.empty())
    {
        if(itLower!=container.begin())
        {
            if(itLower==container.end())
            {
                itLower--;
            }
            else if(itLower->first!=keyValue)
            {
                itLower--;
            }
        }
        if(itUpper!=container.begin())
        {
            if(itUpper==container.end())
            {
                itUpper--;
            }
            else if(itUpper->first!=keyValue)
            {
                itUpper--;
                if(itUpper->first!=keyValue)
                {
                    itUpper++;
                }
            }
        }
    }
    result.first = itLower;
    result.second = itUpper;
    return result;
}

//SaveContentsOfContainerToFile
template <typename ValueType, std::size_t size,
          template<typename, std::size_t> class Container>
void saveContentsOfContainerToFile(std::ofstream & outputFile, Container<ValueType, size> const& container)
{
    //tested on array
    std::ostream_iterator<ValueType> outputIterator (outputFile, "\n");
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType,
          template<typename, typename = std::allocator<ValueType>> class Container>
void saveContentsOfContainerToFile(std::ofstream & outputFile, Container<ValueType> const& container)
{
    //tested on vector
    std::ostream_iterator<ValueType> outputIterator (outputFile, "\n");
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType,
          template<typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void saveContentsOfContainerToFile(std::ofstream & outputFile, Container<ValueType> const& container)
{
    //tested on set
    std::ostream_iterator<ValueType> outputIterator (outputFile, "\n");
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename KeyType, typename ValueType,
          template<typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void saveContentsOfContainerToFile(std::ofstream & outputFile, Container<KeyType, ValueType> const& container)
{
    //tested on map
    for(auto const& content : container)
    {
        outputFile<<content.first<<"\n";
        outputFile<<content.second<<"\n";
    }
}


//RetrieveContentsOfContainerFromFile
template <typename ValueType, std::size_t size,
          template<typename, std::size_t> class Container>
void retrieveContentsOfContainerFromFile(std::ifstream & inputFile, Container<ValueType, size> & container)
{
    //tested on array
    std::istream_iterator<ValueType> inputIterator(inputFile);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, container.begin());
}

template <typename ValueType,
          template<typename, typename = std::allocator<ValueType>> class Container>
void retrieveContentsOfContainerFromFile(std::ifstream & inputFile, Container<ValueType> & container)
{
    //tested on vector
    std::istream_iterator<ValueType> inputIterator(inputFile);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, container.end()));
}

template <typename ValueType,
          template<typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void retrieveContentsOfContainerFromFile(std::ifstream & inputFile, Container<ValueType> & container)
{
    //tested on set
    std::istream_iterator<ValueType> inputIterator(inputFile);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, container.end()));
}

template <typename KeyType, typename ValueType,
          template<typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void retrieveContentsOfContainerFromFile(std::ifstream & inputFile, Container<KeyType, ValueType> & container)
{
    //tested on map
    int state(0);
    std::pair<KeyType, ValueType> tempPair;
    while(inputFile.good())
    {
        if(0==state)
        {
            inputFile>>tempPair.first;
            state=1;
        }
        else if(1==state)
        {
            inputFile>>tempPair.second;
            container.insert(container.end(), tempPair);
            state=0;
        }
    }
}

//GetStringFromContentsOfContainer
template <typename ValueType, std::size_t size,
          template<typename, std::size_t> class Container>
std::string getStringFromContentsOfContainer(Container<ValueType, size> const& container, std::string const& delimiter)
{
    //tested on array
    std::ostringstream result;
    std::ostream_iterator<ValueType> outputIterator(result, delimiter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
    return result.str();
}

template <typename ValueType,
          template<typename, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContentsOfContainer(Container<ValueType> const& container, std::string const& delimiter)
{
    //tested on vector
    std::ostringstream result;
    std::ostream_iterator<ValueType> outputIterator(result, delimiter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
    return result.str();
}

template <typename ValueType,
          template<typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContentsOfContainer(Container<ValueType> const& container, std::string const& delimiter)
{
    //tested on set
    std::ostringstream result;
    std::ostream_iterator<ValueType> outputIterator(result, delimiter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
    return result.str();
}

template <typename KeyType, typename ValueType,
          template<typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
std::string getStringFromContentsOfContainer(Container<KeyType, ValueType> const& container, std::string const& delimiter)
{
    //tested on map
    std::stringstream result;
    for(auto const& content : container)
    {
        result << "[" << content.first << ":" << content.second << "]" << delimiter;
    }
    return result.str();
}


//GetStringOtherFormats
template <typename ValueType,
          template<typename, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContentsOfContainerWithNumberFormat(Container<ValueType> const& container, std::string const& delimiter)
{
    std::ostringstream result;
    std::ostream_iterator<unsigned int> outputIterator(result, delimiter.c_str());

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
