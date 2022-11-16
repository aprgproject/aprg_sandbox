#pragma once

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>

#include <iomanip>

namespace alba
{

#pragma warning("The class AlbaDebug is used. Please remove after your done debugging.")

#ifdef ALBA_PRINT_OUTPUT_STREAM_FILE_PATH
static ofstream debugStream(ALBA_PRINT_OUTPUT_STREAM_FILE_PATH);
#define ALBA_PRINT_OUTPUT_STREAM debugStream
#else
#define ALBA_PRINT_OUTPUT_STREAM std::cout
#endif

// Internal macros
#define Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter)                           printParameterWithName(ALBA_PRINT_OUTPUT_STREAM, ALBA_MACROS_GET_STRING_LITERAL(parameter), parameter);
#define Z_ALBA_PRIVATE_PRINT_SEPARATOR                                      ALBA_PRINT_OUTPUT_STREAM << " ";
#define Z_ALBA_PRIVATE_PRINT_EXPANSION(printCommands1, printCommands2)      printCommands1 Z_ALBA_PRIVATE_PRINT_SEPARATOR printCommands2
#define Z_ALBA_PRIVATE_PRINT1(parameter1)                                   Z_ALBA_PRIVATE_PRINT_PARAMETER(parameter1)
#define Z_ALBA_PRIVATE_PRINT2(parameter1, parameter2)                       Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter1), Z_ALBA_PRIVATE_PRINT1(parameter2))
#define Z_ALBA_PRIVATE_PRINT3(parameter, ...)                               Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT4(parameter, ...)                               Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT5(parameter, ...)                               Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT6(parameter, ...)                               Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__))
#define Z_ALBA_PRIVATE_PRINT7(parameter, ...)                               Z_ALBA_PRIVATE_PRINT_EXPANSION(Z_ALBA_PRIVATE_PRINT1(parameter), Z_ALBA_PRIVATE_PRINT6(__VA_ARGS__))
#define Z_ALBA_PRINT_DETAILS ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT in line:" << std::setw(4) << __LINE__ << " in " << __FUNCTION__ << "(...): ";

// Macros to use#define ALBA_PRINT1(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT1(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT2(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT2(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT3(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT3(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT4(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT4(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT5(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT5(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT6(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT6(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl
#define ALBA_PRINT7(...) Z_ALBA_PRINT_DETAILS Z_ALBA_PRIVATE_PRINT7(__VA_ARGS__) ALBA_PRINT_OUTPUT_STREAM << std::endl

#define ALBA_PRINT_PRECISION(parameter)                                      ALBA_PRINT_OUTPUT_STREAM.precision(parameter)
#define ALBA_PRINT_MANIPULATE_OUTPUT(ioParameter)                            ALBA_PRINT_OUTPUT_STREAM << ioParameter
#define ALBA_EXIT exit(0)

}//namespace alba
