#pragma once

#include <Macros/AlbaMacros.hpp>

#include <iostream>
#include <string>

using namespace std;

namespace alba
{

#pragma warning("The class AlbaDebug is used. Please remove after your done debugging.")

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

#define ALBA_PRECISION(parameter) cout.precision(parameter)
#define ALBA_EXIT exit(0)
#define ALBA_PRINT0(parameter) cout << "ALBA_PRINT0:" << parameter << endl
#define ALBA_PRINT1(...) cout << "ALBA_PRINT1:" << Z_ALBA_PRIVATE_GET_STRING_PRINT1(__VA_ARGS__) << endl
#define ALBA_PRINT2(...) cout << "ALBA_PRINT2:" << Z_ALBA_PRIVATE_GET_STRING_PRINT2(__VA_ARGS__) << endl
#define ALBA_PRINT3(...) cout << "ALBA_PRINT3:" << Z_ALBA_PRIVATE_GET_STRING_PRINT3(__VA_ARGS__) << endl
#define ALBA_PRINT4(...) cout << "ALBA_PRINT4:" << Z_ALBA_PRIVATE_GET_STRING_PRINT4(__VA_ARGS__) << endl
#define ALBA_PRINT5(...) cout << "ALBA_PRINT5:" << Z_ALBA_PRIVATE_GET_STRING_PRINT5(__VA_ARGS__) << endl
#define ALBA_PRINT6(...) cout << "ALBA_PRINT6:" << Z_ALBA_PRIVATE_GET_STRING_PRINT6(__VA_ARGS__) << endl


}//namespace alba
