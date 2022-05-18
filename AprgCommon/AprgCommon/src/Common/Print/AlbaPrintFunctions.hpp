#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>

#include <ostream>
#include <string>

using namespace alba::containerHelper;

namespace alba
{

// Print parameter functions

template <typename ParameterType>
void printParameter(std::ostream & outputStream, std::string const& parameterName, ParameterType const& parameter)
{
    outputStream << parameterName << " : [" << parameter << "]";
}

template <typename ParameterPointerType>
void printParameter(std::ostream & outputStream, std::string const& parameterName, ParameterPointerType * parameterPointer)
{    if(parameterPointer == nullptr)
    {
        outputStream << parameterName << " : [nullptr]";
    }    else
    {
        outputStream << "*" << parameterName << " : [" << *parameterPointer << "]";
    }
}

template <>
void printParameter(std::ostream & outputStream, std::string const& , char const*const parameter);

template <typename ParameterType>
void printParameter(std::ostream & outputStream, std::string const& parameterName, std::unique_ptr<ParameterType> const& parameterPointer)
{
    printParameter(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameter(std::ostream & outputStream, std::string const& parameterName, std::shared_ptr<ParameterType> const& parameterPointer)
{
    printParameter(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameter(std::ostream & outputStream, std::string const& parameterName, std::weak_ptr<ParameterType> const& parameterPointer)
{
    outputStream << parameterName << " has use count: [" << parameterPointer.use_count() << "]";
}

template <typename ValueType1, typename ValueType2>
void printParameter(std::ostream & outputStream, std::string const& parameterName, std::pair<ValueType1, ValueType2> const& parameter)
{
    outputStream << parameterName << " : [(" << parameter.first << ", " << parameter.second << ")]";
}

template <typename ValueType, size_t SIZE,          template <typename, size_t> class Container>
void printParameter(std::ostream & outputStream, std::string const& parameterName, Container<ValueType, SIZE> const& container)
{
    outputStream << parameterName << " : [(has size " << container.size() << "):{";    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "}]";
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << " : [(has size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "}]";
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << " : [(has size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "}]";
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void printParameter(std::ostream & outputStream, std::string const& parameterName, Container<KeyType, ValueType> const& container)
{
    outputStream << parameterName << " : [(has size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "}]";
}


}//namespace alba
