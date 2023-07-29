#pragma once

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <iomanip>
#include <iostream>

namespace alba {

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#warning("The class AlbaDebug is used. Please remove after your done debugging.") // GCC extension
#elif defined(_MSC_VER)
#pragma message("The class AlbaDebug is used. Please remove after your done debugging.")  // MSVC extension
#endif

#if defined(ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH)
#include <ofstream>
inline std::ofstream debugStream(ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH);
#define ALBA_PRINT_OUTPUT_STREAM debugStream
#elif defined(ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT)
#define ALBA_PRINT_OUTPUT_STREAM ALBA_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT
#else
#define ALBA_PRINT_OUTPUT_STREAM std::cout
#endif

// Internal macros
#define Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter) \
    printParameterWithName(ALBA_PRINT_OUTPUT_STREAM, ALBA_MACROS_GET_STRING_LITERAL(parameter), parameter);
#define Z_ALBA_PRIVATE_PRINT_SEPARATOR ALBA_PRINT_OUTPUT_STREAM << " ";
#define Z_ALBA_PRIVATE_PRINT_EXPANSION(printCommands1, printCommands2) \
    printCommands1 Z_ALBA_PRIVATE_PRINT_SEPARATOR printCommands2
#define Z_ALBA_PRIVATE_PRINT1(parameter1) Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter1)
#define Z_ALBA_PRIVATE_PRINT2(parameter1, parameter2) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter1), Z_ALBA_PRIVATE_PRINT1(parameter2))
#define Z_ALBA_PRIVATE_PRINT3(parameter, ...) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT4(parameter, ...) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT5(parameter, ...) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT6(parameter, ...) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT7(parameter, ...) \
    Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT6(__VA_ARGS__))
#define Z_ALBA_PRINT_DETAILS                                                                            \
    ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT in line:" << std::setw(4) << ALBA_MACROS_GET_LINE << " in " \
                             << ALBA_MACROS_GET_FUNCTION << "(...): ";
// For PRETTY_FUNCTIONS
//#define Z_ALBA_PRINT_DETAILS ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT in line:" << std::setw(4) << ALBA_MACROS_GET_LINE
//<< " in " << ALBA_MACROS_GET_PRETTY_FUNCTION << ": ";

// Print macros to use
#define ALBA_PRINT1(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT1(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT2(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT3(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT4(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT5(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT6(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT6(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT7(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT7(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl

#define ALBA_PRINT_PRECISION(parameter) ALBA_PRINT_OUTPUT_STREAM.precision(parameter)
#define ALBA_PRINT_MANIPULATE_OUTPUT(ioParameter) ALBA_PRINT_OUTPUT_STREAM << ioParameter

// Macros for debug scope
#define ALBA_DEBUG_SCOPE_START {
#define ALBA_DEBUG_SCOPE_END }

// Macros for output operator
// Note: Dont include "friend" keyword in macro just include in the class.
#define ALBA_DEBUG_CLASS_OUTPUT_OPERATOR_DECLARATION(ParameterSignature) \
    std::ostream& operator<<(std::ostream& out, ParameterSignature);

#define ALBA_DEBUG_CLASS_OUTPUT_OPERATOR_DEFINITION(ParameterSignature, OutputOperation) \
    std::ostream& operator<<(std::ostream& out, ParameterSignature) {                    \
        out << OutputOperation;                                                          \
        return out;                                                                      \
    }

//#define ALBA_DEBUG_COMMENTED_LINE #warning("Uncomment this line after your done debugging.");

}  // namespace alba
