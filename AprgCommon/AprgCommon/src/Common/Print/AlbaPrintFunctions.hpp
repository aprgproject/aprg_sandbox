#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>

#include <ostream>
#include <string>

using namespace alba::containerHelper;

namespace alba
{

// printParameter declaration

template <typename ParameterType>
void printParameter(std::ostream & outputStream, ParameterType const& parameter);
template <typename ValueType1, typename ValueType2>
void printParameter(std::ostream & outputStream, std::pair<ValueType1, ValueType2> const& parameter);
template <typename ValueType, size_t SIZE, template <typename, size_t> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType, SIZE> const& container);
template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType> const& container);
template <typename ValueType, template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType> const& container);
template <typename KeyType, typename ValueType, template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void printParameter(std::ostream & outputStream, Container<KeyType, ValueType> const& container);


// printParameterWithName declaration

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterType const& parameter);
template <typename ParameterPointerType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterPointerType * parameterPointer);
template <>
void printParameterWithName(std::ostream & outputStream, std::string const& , char const*const parameter);
template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::unique_ptr<ParameterType> const& parameterPointer);
template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::shared_ptr<ParameterType> const& parameterPointer);
template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::weak_ptr<ParameterType> const& parameterPointer);
template <typename ValueType1, typename ValueType2>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::pair<ValueType1, ValueType2> const& parameter);
template <typename ValueType, size_t SIZE, template <typename, size_t> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType, SIZE> const& container);
template <typename ValueType, template <typename, typename = std::allocator<ValueType>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container);
template <typename ValueType, template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container);
template <typename KeyType, typename ValueType, template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<KeyType, ValueType> const& container);




// printParameter

template <typename ParameterType>void printParameter(std::ostream & outputStream, ParameterType const& parameter)
{
    outputStream << parameter;
}

template <typename ValueType1, typename ValueType2>
void printParameter(std::ostream & outputStream, std::pair<ValueType1, ValueType2> const& parameter)
{
    outputStream << "(";
    printParameter(outputStream, parameter.first);
    outputStream << ", ";
    printParameter(outputStream, parameter.second);
    outputStream << ")";
}

template <typename ValueType, size_t SIZE,          template <typename, size_t> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType, SIZE> const& container)
{
    outputStream << "{size: " << container.size() << " | ";
    for(auto const& content : container)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType> const& container)
{
    outputStream << "{size: " << container.size() << " | ";
    for(auto const& content : container)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void printParameter(std::ostream & outputStream, Container<ValueType> const& container)
{
    outputStream << "{size: " << container.size() << " | ";
    for(auto const& content : container)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void printParameter(std::ostream & outputStream, Container<KeyType, ValueType> const& container)
{
    outputStream << "{size: " << container.size() << " | ";
    for(auto const& content : container)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}



// printParameterWithName

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterType const& parameter)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, parameter);
    outputStream<< "]";
}

template <typename ParameterPointerType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterPointerType * parameterPointer)
{
    if(parameterPointer == nullptr)
    {
        outputStream << parameterName << " : [nullptr]";
    }
    else
    {
        outputStream << "*" << parameterName << " : [";
        printParameter(outputStream, *parameterPointer);
        outputStream<< "]";
    }
}

template <>
void printParameterWithName(std::ostream & outputStream, std::string const& , char const*const parameter);

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::unique_ptr<ParameterType> const& parameterPointer)
{
    printParameterWithName(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::shared_ptr<ParameterType> const& parameterPointer)
{
    printParameterWithName(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::weak_ptr<ParameterType> const& parameterPointer)
{
    outputStream << parameterName << " has use count: [" << parameterPointer.use_count() << "]";
}

template <typename ValueType1, typename ValueType2>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, std::pair<ValueType1, ValueType2> const& parameter)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, parameter);
    outputStream<< "]";
}

template <typename ValueType, size_t SIZE,
          template <typename, size_t> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType, SIZE> const& container)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, container);
    outputStream<< "]";
}

template <typename ValueType,
          template <typename, typename = std::allocator<ValueType>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, container);
    outputStream<< "]";
}

template <typename ValueType,
          template <typename, typename = std::less<ValueType>, typename = std::allocator<ValueType>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, container);
    outputStream<< "]";
}

template <typename KeyType, typename ValueType,
          template <typename, typename, typename = std::less<KeyType>, typename = std::allocator<std::pair<KeyType const, ValueType>>> class Container>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, Container<KeyType, ValueType> const& container)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, container);
    outputStream<< "]";
}

}//namespace alba
