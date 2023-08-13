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
// This is a revised approach in printing because of MSVC limitation on macros.
#define Z_ALBA_PRINT_START                                                                              \
    ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT in line:" << std::setw(4) << ALBA_MACROS_GET_LINE << " in " \
                             << ALBA_MACROS_GET_FUNCTION << "(...): ";
#define Z_ALBA_PRINT_END ALBA_PRINT_OUTPUT_STREAM << std::endl
#define Z_ALBA_PRINT_PARAMETER_ONLY(parameter) \
    printParameterWithName(ALBA_PRINT_OUTPUT_STREAM, ALBA_MACROS_GET_STRING_LITERAL(parameter), parameter);
#define Z_ALBA_PRINT_SEPARATOR ALBA_PRINT_OUTPUT_STREAM << " ";
#define Z_ALBA_PRINT_PARAMETER(parameter) Z_ALBA_PRINT_PARAMETER_ONLY(parameter) Z_ALBA_PRINT_SEPARATOR
#define Z_ALBA_PRINT_7(p1, p2, p3, p4, p5, p6, p7) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_6(p2, p3, p4, p5, p6, p7)
#define Z_ALBA_PRINT_6(p1, p2, p3, p4, p5, p6) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_5(p2, p3, p4, p5, p6)
#define Z_ALBA_PRINT_5(p1, p2, p3, p4, p5) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_4(p2, p3, p4, p5)
#define Z_ALBA_PRINT_4(p1, p2, p3, p4) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_3(p2, p3, p4)
#define Z_ALBA_PRINT_3(p1, p2, p3) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_2(p2, p3)
#define Z_ALBA_PRINT_2(p1, p2) Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_PARAMETER(p2)

// Print macros to use
#define ALBA_PRINT1(p1) Z_ALBA_PRINT_START Z_ALBA_PRINT_PARAMETER(p1) Z_ALBA_PRINT_END
#define ALBA_PRINT2(p1, p2) Z_ALBA_PRINT_START Z_ALBA_PRINT_2(p1, p2) Z_ALBA_PRINT_END
#define ALBA_PRINT3(p1, p2, p3) Z_ALBA_PRINT_START Z_ALBA_PRINT_3(p1, p2, p3) Z_ALBA_PRINT_END
#define ALBA_PRINT4(p1, p2, p3, p4) Z_ALBA_PRINT_START Z_ALBA_PRINT_4(p1, p2, p3, p4) Z_ALBA_PRINT_END
#define ALBA_PRINT5(p1, p2, p3, p4, p5) Z_ALBA_PRINT_START Z_ALBA_PRINT_5(p1, p2, p3, p4, p5) Z_ALBA_PRINT_END
#define ALBA_PRINT6(p1, p2, p3, p4, p5, p6) Z_ALBA_PRINT_START Z_ALBA_PRINT_6(p1, p2, p3, p4, p5, p6) Z_ALBA_PRINT_END
#define ALBA_PRINT7(p1, p2, p3, p4, p5, p6, p7) \
    Z_ALBA_PRINT_START Z_ALBA_PRINT_7(p1, p2, p3, p4, p5, p6, p7) Z_ALBA_PRINT_END

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define ALBA_PRINT_ALL(...) ALBA_MACROS_CONCATENATE(ALBA_PRINT, ALBA_MACROS_COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__)
#endif

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

// #define ALBA_DEBUG_COMMENTED_LINE #warning("Uncomment this line after your done debugging.");

}  // namespace alba