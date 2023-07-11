#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>

namespace alba::containerHelper {

enum class StreamFormat { String, File };

std::string getDelimeterBasedOnFormat(StreamFormat const streamFormat);

template <typename ValueType, typename Container, typename Iterator>
void adjustLowerAndUpperIterators(
    Container const& container, ValueType const& value, Iterator& itLower, Iterator& itUpper) {
    if (!container.empty()) {
        if (itLower != container.cbegin()) {
            if (itLower == container.cend()) {
                itLower--;
            } else if (*itLower != value) {
                itLower--;
            }
        }
        if (itUpper != container.cbegin()) {
            if (itUpper == container.cend()) {
                itUpper--;
            } else if (*itUpper != value) {
                itUpper--;
                if (*itUpper != value) {
                    itUpper++;
                }
            }
        }
    }
}

// Non set

template <typename ValueType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsForNonSet(ContainerType const& sortedContainer, ValueType const& value) {
    auto&& [lowerIt, upperIt] = std::equal_range(sortedContainer.cbegin(), sortedContainer.cend(), value);
    adjustLowerAndUpperIterators(sortedContainer, value, lowerIt, upperIt);
    return std::make_pair(lowerIt, upperIt);
}

template <typename ValueType, typename ContainerType>
std::pair<ValueType, ValueType> getLowerAndUpperValuesForNonSet(
    ContainerType const& sortedContainer, ValueType const& value) {
    auto&& [lowerIt, upperIt] = getLowerAndUpperConstIteratorsForNonSet(sortedContainer, value);
    return std::make_pair(*lowerIt, *upperIt);
}

template <typename ValueType, typename ContainerType>
size_t countItemsInBetweenForNonSet(
    ContainerType const& sortedContainer, ValueType const& value1, ValueType const& value2) {
    // 1D range count
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(std::lower_bound(sortedContainer.cbegin(), sortedContainer.cend(), value1));
    ConstIterator itUpper(std::upper_bound(sortedContainer.cbegin(), sortedContainer.cend(), value2));
    return static_cast<size_t>(std::distance(itLower, itUpper));
}

template <typename ValueType, typename ContainerType>
ContainerType getItemsInBetweenForNonSet(
    ContainerType const& sortedContainer, ValueType const& value1, ValueType const& value2) {
    // 1D range search
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(std::lower_bound(sortedContainer.cbegin(), sortedContainer.cend(), value1));
    ConstIterator itUpper(std::upper_bound(sortedContainer.cbegin(), sortedContainer.cend(), value2));
    return ContainerType(itLower, itUpper);
}

// set
// needs to differentiate set because according to cppreference:
// The number of comparisons performed is logarithmic in the distance between first and last (At most 2 * log 2(last -
// first) + O(1) comparisons). However, for non-LegacyRandomAccessIterators, the number of iterator increments is
// linear. Notably, std::set and std::multiset iterators are not random access, and so their member functions
// std::set::equal_range (resp. std::multiset::equal_range) should be preferred.

template <typename ValueType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsForSet(ContainerType const& setContainer, ValueType const& value) {
    auto&& [lowerIt, upperIt] = setContainer.equal_range(value);
    adjustLowerAndUpperIterators(setContainer, value, lowerIt, upperIt);
    return std::make_pair(lowerIt, upperIt);
}

template <typename ValueType, typename ContainerType>
std::pair<ValueType, ValueType> getLowerAndUpperValuesForSet(
    ContainerType const& setContainer, ValueType const& value) {
    auto&& [lowerIt, upperIt] = getLowerAndUpperConstIteratorsForSet(setContainer, value);
    return std::make_pair(*lowerIt, *upperIt);
}

template <typename ValueType, typename ContainerType>
size_t countItemsInBetweenForSet(ContainerType const& setContainer, ValueType const& value1, ValueType const& value2) {
    // 1D range count
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(setContainer.lower_bound(value1));
    ConstIterator itUpper(setContainer.upper_bound(value2));
    return static_cast<size_t>(std::distance(itLower, itUpper));
}

template <typename ValueType, typename ContainerType>
ContainerType getItemsInBetweenForSet(
    ContainerType const& setContainer, ValueType const& value1, ValueType const& value2) {
    // 1D range search
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(setContainer.lower_bound(value1));
    ConstIterator itUpper(setContainer.upper_bound(value2));
    return ContainerType(itLower, itUpper);
}

// map

template <typename KeyType, typename Container, typename Iterator>
void adjustLowerAndUpperIteratorsInMap(
    Container const& container, KeyType const& keyValue, Iterator& itLower, Iterator& itUpper) {
    if (!container.empty()) {
        if (itLower != container.cbegin()) {
            if (itLower == container.cend()) {
                itLower--;
            } else if (itLower->first != keyValue) {
                itLower--;
            }
        }
        if (itUpper != container.cbegin()) {
            if (itUpper == container.cend()) {
                itUpper--;
            } else if (itUpper->first != keyValue) {
                itUpper--;
                if (itUpper->first != keyValue) {
                    itUpper++;
                }
            }
        }
    }
}

template <typename KeyType, typename ContainerType>
std::pair<typename ContainerType::const_iterator, typename ContainerType::const_iterator>
getLowerAndUpperConstIteratorsInMap(ContainerType const& container, KeyType const& keyValue) {
    using ConstIterator = typename ContainerType::const_iterator;
    ConstIterator itLower(container.lower_bound(keyValue));
    ConstIterator itUpper(container.upper_bound(keyValue));
    adjustLowerAndUpperIteratorsInMap(container, keyValue, itLower, itUpper);
    return std::pair<ConstIterator, ConstIterator>(itLower, itUpper);
}

template <typename KeyType, typename ContainerType>
std::pair<typename ContainerType::iterator, typename ContainerType::iterator> getLowerAndUpperIteratorsInMap(
    ContainerType& container, KeyType const& keyValue) {
    using Iterator = typename ContainerType::iterator;
    Iterator itLower(container.lower_bound(keyValue));
    Iterator itUpper(container.upper_bound(keyValue));
    adjustLowerAndUpperIteratorsInMap(container, keyValue, itLower, itUpper);
    return std::pair<Iterator, Iterator>(itLower, itUpper);
}

template <typename Adapter>
typename Adapter::container_type const& getUnderlyingContainer(Adapter const& adapter) {
    struct AdapterParent : Adapter {
        static typename Adapter::container_type const& get(Adapter const& adapterAsParameter) {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}

template <typename Adapter>
typename Adapter::container_type& getUnderlyingContainerReference(Adapter& adapter) {
    struct AdapterParent : Adapter {
        static typename Adapter::container_type& get(Adapter& adapterAsParameter) {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}

// SaveContentsToStream

template <typename ValueType, std::size_t SIZE, template <typename, std::size_t> class Container>
void saveContentsToStream(
    std::ostream& outputStream, Container<ValueType, SIZE> const& container, StreamFormat const streamFormat) {
    // tested on array
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
void saveContentsToStream(
    std::ostream& outputStream, Container<ValueType> const& container, StreamFormat const streamFormat) {
    // tested on vector
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <
    typename ValueType,
    template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void saveContentsToStream(
    std::ostream& outputStream, Container<ValueType> const& container, StreamFormat const streamFormat) {
    // tested on set
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    std::ostream_iterator<ValueType> outputIterator(outputStream, delimeter.c_str());
    std::copy(container.cbegin(), container.cend(), outputIterator);
}

template <
    typename KeyType, typename ValueType,
    template <
        typename, typename, typename = std::less<KeyType>,
        typename = std::allocator<std::pair<KeyType const, ValueType>>>
    class Container>
void saveContentsToStream(
    std::ostream& outputStream, Container<KeyType, ValueType> const& container, StreamFormat const streamFormat) {
    // tested on map
    std::string delimeter(getDelimeterBasedOnFormat(streamFormat));
    if (StreamFormat::String == streamFormat) {
        for (auto const& [key, value] : container)  // C++17, structured bindings
        {
            outputStream << "{" << key << ":" << value << "}" << delimeter;
        }
    } else {
        for (auto const& [key, value] : container) {
            outputStream << key << delimeter;
            outputStream << value << delimeter;
        }
    }
}

template <
    typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container,
    typename DisplayType = ValueType>
void saveContentsInDecimalAndHexadecimalFormat(std::ostream& outputStream, Container<ValueType> const& container) {
    std::string delimeter = getDelimeterBasedOnFormat(StreamFormat::String);
    std::ostream_iterator<DisplayType> outputIterator(outputStream, delimeter.c_str());

    outputStream << "Decimal values: {" << std::dec;
    std::copy(container.cbegin(), container.cend(), outputIterator);
    outputStream << "}\n";

    outputStream << "Hexadecimal values: {" << std::hex;
    std::copy(container.cbegin(), container.cend(), outputIterator);
    outputStream << "}\n";
}

// RetrieveContentsFromStream
template <typename ValueType, std::size_t SIZE, template <typename, std::size_t> class Container>
void retrieveContentsFromStream(std::istream& inputStream, Container<ValueType, SIZE>& container) {
    // tested on array
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, begin(container));
}

template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
void retrieveContentsFromStream(std::istream& inputStream, Container<ValueType>& container) {
    // tested on vector
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, end(container)));
}

template <
    typename ValueType,
    template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void retrieveContentsFromStream(std::istream& inputStream, Container<ValueType>& container) {
    // tested on set
    std::istream_iterator<ValueType> inputIterator(inputStream);
    std::istream_iterator<ValueType> inputIteratorEnd;
    std::copy(inputIterator, inputIteratorEnd, std::inserter(container, end(container)));
}

template <
    typename KeyType, typename ValueType,
    template <
        typename, typename, typename = std::less<KeyType>,
        typename = std::allocator<std::pair<KeyType const, ValueType>>>
    class Container>
void retrieveContentsFromStream(std::istream& inputStream, Container<KeyType, ValueType>& container) {
    // tested on map
    enum class StreamState { SendFirst, SendSecond };

    StreamState state(StreamState::SendFirst);
    std::pair<KeyType, ValueType> tempPair;
    while (inputStream.good()) {
        if (StreamState::SendFirst == state) {
            inputStream >> tempPair.first;
            state = StreamState::SendSecond;
        } else if (StreamState::SendSecond == state) {
            inputStream >> tempPair.second;
            container.insert(end(container), tempPair);
            state = StreamState::SendFirst;
        }
    }
}

// GetStringFromContents
template <typename ValueType, std::size_t SIZE, template <typename, std::size_t> class Container>
std::string getStringFromContents(Container<ValueType, SIZE> const& container) {
    // tested on array
    std::ostringstream oss;
    saveContentsToStream(oss, container, StreamFormat::String);
    return oss.str();
}

template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContents(Container<ValueType> const& container) {
    // tested on vector
    std::ostringstream oss;
    saveContentsToStream(oss, container, StreamFormat::String);
    return oss.str();
}

template <
    typename ValueType,
    template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
std::string getStringFromContents(Container<ValueType> const& container) {
    // tested on set
    std::ostringstream oss;
    saveContentsToStream(oss, container, StreamFormat::String);
    return oss.str();
}

template <
    typename KeyType, typename ValueType,
    template <
        typename, typename, typename = std::less<KeyType>,
        typename = std::allocator<std::pair<KeyType const, ValueType>>>
    class Container>
std::string getStringFromContents(Container<KeyType, ValueType> const& container) {
    // tested on map
    std::stringstream oss;
    saveContentsToStream(oss, container, StreamFormat::String);
    return oss.str();
}

// GetStringOtherFormats

template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
std::string getStringInDecimalAndHexadecimalFormat(Container<ValueType> const& container) {
    std::ostringstream oss;
    saveContentsInDecimalAndHexadecimalFormat(oss, container);
    return oss.str();
}

}  // namespace alba::containerHelper
