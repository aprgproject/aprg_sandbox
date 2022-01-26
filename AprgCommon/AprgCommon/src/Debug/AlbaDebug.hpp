#pragma once

#include <Container/AlbaSingleton.hpp>
#include <Macros/AlbaMacros.hpp>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace alba
{

#pragma warning("The class AlbaDebug is used. Please remove after your done debugging.")

#ifdef ALBA_PRINT_OUTPUT_STREAM_FILE_PATH

static std::ofstream debugStream(ALBA_PRINT_OUTPUT_STREAM_FILE_PATH);
#define ALBA_PRINT_OUTPUT_STREAM debugStream

#else

#define ALBA_PRINT_OUTPUT_STREAM cout

#endif


#define Z_ALBA_PRIVATE_GET_STRING_LITERALS_EXPANSION(parameter1, parameter2) ALBA_MACROS_GET_STRING_LITERAL(parameter1) + parameter2
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS1(parameter1)                      ALBA_MACROS_GET_STRING_LITERAL(parameter1)
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS2(parameter1, parameter2)          ALBA_MACROS_GET_STRING_LITERAL(parameter1) + ALBA_MACROS_GET_STRING_LITERAL(parameter2)
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS3(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_LITERALS_EXPANSION(parameter, Z_ALBA_PRIVATE_GET_STRING_LITERALS2(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS4(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_LITERALS_EXPANSION(parameter, Z_ALBA_PRIVATE_GET_STRING_LITERALS3(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS5(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_LITERALS_EXPANSION(parameter, Z_ALBA_PRIVATE_GET_STRING_LITERALS4(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_LITERALS6(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_LITERALS_EXPANSION(parameter, Z_ALBA_PRIVATE_GET_STRING_LITERALS4(__VA_ARGS__))

#define Z_ALBA_PRIVATE_GET_STRING_PRINT_EXPANSION(parameter1, parameter2) parameter1 << parameter2
#define Z_ALBA_PRIVATE_GET_STRING_PRINT1(parameter1)                      ALBA_MACROS_GET_STRING_LITERAL(parameter1) << " : [" << parameter1 << "] "
#define Z_ALBA_PRIVATE_GET_STRING_PRINT2(parameter1, parameter2)          ALBA_MACROS_GET_STRING_LITERAL(parameter1) << " : [" << parameter1 << "] " << ALBA_MACROS_GET_STRING_LITERAL(parameter2) << " : [" << parameter2 << "] "
#define Z_ALBA_PRIVATE_GET_STRING_PRINT3(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_PRINT_EXPANSION(Z_ALBA_PRIVATE_GET_STRING_PRINT1(parameter), Z_ALBA_PRIVATE_GET_STRING_PRINT2(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_PRINT4(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_PRINT_EXPANSION(Z_ALBA_PRIVATE_GET_STRING_PRINT1(parameter), Z_ALBA_PRIVATE_GET_STRING_PRINT3(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_PRINT5(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_PRINT_EXPANSION(Z_ALBA_PRIVATE_GET_STRING_PRINT1(parameter), Z_ALBA_PRIVATE_GET_STRING_PRINT4(__VA_ARGS__))
#define Z_ALBA_PRIVATE_GET_STRING_PRINT6(parameter, ...)                  Z_ALBA_PRIVATE_GET_STRING_PRINT_EXPANSION(Z_ALBA_PRIVATE_GET_STRING_PRINT1(parameter), Z_ALBA_PRIVATE_GET_STRING_PRINT5(__VA_ARGS__))

#define ALBA_PRINT_PRECISION(parameter) ALBA_PRINT_OUTPUT_STREAM.precision(parameter)
#define ALBA_EXIT exit(0)
#define ALBA_PRINT0(parameter) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT0 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << parameter << endl
#define ALBA_PRINT1(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT1 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT1(__VA_ARGS__) << endl
#define ALBA_PRINT2(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT2 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT2(__VA_ARGS__) << endl
#define ALBA_PRINT3(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT3 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT3(__VA_ARGS__) << endl
#define ALBA_PRINT4(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT4 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT4(__VA_ARGS__) << endl
#define ALBA_PRINT5(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT5 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT5(__VA_ARGS__) << endl
#define ALBA_PRINT6(...) ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT6 in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " << Z_ALBA_PRIVATE_GET_STRING_PRINT6(__VA_ARGS__) << endl

#define ALBA_PRINT_CONTAINER(container)  \
    ALBA_PRINT_OUTPUT_STREAM << "ALBA_PRINT_CONTAINER in " << __FUNCTION__ << "(...) in line:" << __LINE__ << " || " \
    << ALBA_MACROS_GET_STRING_LITERAL(container) \
    << " (with size " << container.size() <<")" \
    << " : {"; \    for(auto const& item : container) \
{ \
    ALBA_PRINT_OUTPUT_STREAM << "[" << item << "], "; \
} \    ALBA_PRINT_OUTPUT_STREAM << "}" << endl;


}//namespace alba
