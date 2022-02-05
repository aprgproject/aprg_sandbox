#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Macros/AlbaMacros.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace alba::containerHelper;
using namespace std;

namespace alba
{

#pragma warning("The class AlbaDebug is used. Please remove after your done debugging.")


#ifdef ALBA_PRINT_OUTPUT_STREAM_FILE_PATH

static ofstream debugStream(ALBA_PRINT_OUTPUT_STREAM_FILE_PATH);
#define ALBA_PRINT_OUTPUT_STREAM debugStream

#else

#define ALBA_PRINT_OUTPUT_STREAM cout

#endif


// Print parameter functions
template <typename ParameterPointerType>
void printParameter(ostream & outputStream, string const& parameterName, ParameterPointerType const*const parameterPointer)
{
    if(parameterPointer == nullptr)
    {
        outputStream << parameterName << " : [nullptr] ";
    }
    else
    {
        outputStream << "*" << parameterName << " : [" << *parameterPointer << "] ";
    }
}

template <>
void printParameter(ostream & outputStream, string const& , char const*const parameter)
{
    outputStream << R"([")" << parameter << R"("] )";
}

template <typename ParameterType>
void printParameter(ostream & outputStream, string const& parameterName, unique_ptr<ParameterType> const& parameterPointer)
{
    printParameter(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameter(ostream & outputStream, string const& parameterName, shared_ptr<ParameterType> const& parameterPointer)
{
    printParameter(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameter(ostream & outputStream, string const& parameterName, weak_ptr<ParameterType> const& parameterPointer)
{
    printParameter(outputStream, parameterName, parameterPointer.get());
}

template <typename ParameterType>
void printParameter(ostream & outputStream, string const& parameterName, ParameterType const& parameter)
{
    outputStream << parameterName << " : [" << parameter << "] ";
}

template <typename ValueType, size_t SIZE,
          template<typename, size_t> class Container>
void printParameter(ostream & outputStream, string const& parameterName, Container<ValueType, SIZE> const& container)
{
    outputStream << parameterName << "(with size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "} ";
}

template <typename ValueType,
          template<typename, typename = allocator<ValueType>> class Container>
void printParameter(ostream & outputStream, string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << "(with size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "} ";
}

template <typename ValueType,
          template<typename, typename = less<ValueType>, typename = allocator<ValueType>> class Container>
void printParameter(ostream & outputStream, string const& parameterName, Container<ValueType> const& container)
{
    outputStream << parameterName << "(with size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "} ";
}

template <typename KeyType, typename ValueType,
          template<typename, typename, typename = less<KeyType>, typename = allocator<pair<KeyType const, ValueType>>> class Container>
void printParameter(ostream & outputStream, string const& parameterName, Container<KeyType, ValueType> const& container)
{
    outputStream << parameterName << "(with size " << container.size() << "):{";
    saveContentsToStream(outputStream, container, StreamFormat::String);
    outputStream << "} ";
}


// Internal macros
#define Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter)              printParameter(ALBA_PRINT_OUTPUT_STREAM, ALBA_MACROS_GET_STRING_LITERAL(parameter), parameter);
#define Z_ALBA_PRIVATE_PRINT_EXPANSION(printCommands1, printCommands2) printCommands1 printCommands2
#define Z_ALBA_PRIVATE_PRINT1(parameter1)                      Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter1)
#define Z_ALBA_PRIVATE_PRINT2(parameter1, parameter2)          Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter1) Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter2)
#define Z_ALBA_PRIVATE_PRINT3(parameter, ...)                  Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT4(parameter, ...)                  Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT5(parameter, ...)                  Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT6(parameter, ...)                  Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__))


// Macros to use
#define ALBA_PRINT_DETAILS ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT in line:" << setw(4) << __LINE__ << " in " << __FUNCTION__ << "(...): ";
#define ALBA_PRINT1(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT1(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl
#define ALBA_PRINT2(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl
#define ALBA_PRINT3(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl
#define ALBA_PRINT4(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl
#define ALBA_PRINT5(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl
#define ALBA_PRINT6(...) ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT6(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << endl

#define ALBA_PRINT_PRECISION(parameter) ALBA_PRINT_OUTPUT_STREAM.precision(parameter)

#define ALBA_EXIT exit(0)


}//namespace alba
