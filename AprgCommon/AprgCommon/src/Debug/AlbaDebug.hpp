#pragma once

#include <Macros/AlbaMacros.hpp>

#include <iostream>
#include <string>

using namespace std;

namespace alba
{

#pragma warning("The class AlbaDebug is used. Please remove after your done debugging.")

#define ALBA_DEBUG_GET_STRING_LITERALS_EXPANSION(parameter1, parameter2) ALBA_MACROS_GET_STRING_LITERAL(parameter1) + parameter2
#define ALBA_DEBUG_GET_STRING_LITERALS1(parameter1)                      ALBA_MACROS_GET_STRING_LITERAL(parameter1)
#define ALBA_DEBUG_GET_STRING_LITERALS2(parameter1, parameter2)          ALBA_MACROS_GET_STRING_LITERAL(parameter1) + ALBA_MACROS_GET_STRING_LITERAL(parameter2)
#define ALBA_DEBUG_GET_STRING_LITERALS3(parameter, ...)                  ALBA_DEBUG_GET_STRING_LITERALS_EXPANSION(parameter, ALBA_DEBUG_GET_STRING_LITERALS2(__VA_ARGS__))
#define ALBA_DEBUG_GET_STRING_LITERALS4(parameter, ...)                  ALBA_DEBUG_GET_STRING_LITERALS_EXPANSION(parameter, ALBA_DEBUG_GET_STRING_LITERALS2(__VA_ARGS__))
#define ALBA_DEBUG_GET_STRING_LITERALS5(parameter, ...)                  ALBA_DEBUG_GET_STRING_LITERALS_EXPANSION(parameter, ALBA_DEBUG_GET_STRING_LITERALS2(__VA_ARGS__))

#define ALBA_DEBUG_GET_STRING_PRINT_EXPANSION(parameter1, parameter2) parameter1 << parameter2
#define ALBA_DEBUG_GET_STRING_PRINT1(parameter1)                      ALBA_MACROS_GET_STRING_LITERAL(parameter1) << ":[" << parameter1 << "] "
#define ALBA_DEBUG_GET_STRING_PRINT2(parameter1, parameter2)          ALBA_MACROS_GET_STRING_LITERAL(parameter1) << ":[" << parameter1 << "] " << ALBA_MACROS_GET_STRING_LITERAL(parameter2) << ":[" << parameter2 << "] "
#define ALBA_DEBUG_GET_STRING_PRINT3(parameter, ...)                  ALBA_DEBUG_GET_STRING_PRINT_EXPANSION(ALBA_DEBUG_GET_STRING_PRINT1(parameter), ALBA_DEBUG_GET_STRING_PRINT2(__VA_ARGS__))
#define ALBA_DEBUG_GET_STRING_PRINT4(parameter, ...)                  ALBA_DEBUG_GET_STRING_PRINT_EXPANSION(ALBA_DEBUG_GET_STRING_PRINT1(parameter), ALBA_DEBUG_GET_STRING_PRINT3(__VA_ARGS__))
#define ALBA_DEBUG_GET_STRING_PRINT5(parameter, ...)                  ALBA_DEBUG_GET_STRING_PRINT_EXPANSION(ALBA_DEBUG_GET_STRING_PRINT1(parameter), ALBA_DEBUG_GET_STRING_PRINT4(__VA_ARGS__))

#define ALBA_DEBUG_PRINT1(...) cout << ALBA_DEBUG_GET_STRING_PRINT1(__VA_ARGS__) << endl
#define ALBA_DEBUG_PRINT2(...) cout << ALBA_DEBUG_GET_STRING_PRINT2(__VA_ARGS__) << endl
#define ALBA_DEBUG_PRINT3(...) cout << ALBA_DEBUG_GET_STRING_PRINT3(__VA_ARGS__) << endl
#define ALBA_DEBUG_PRINT4(...) cout << ALBA_DEBUG_GET_STRING_PRINT4(__VA_ARGS__) << endl
#define ALBA_DEBUG_PRINT5(...) cout << ALBA_DEBUG_GET_STRING_PRINT5(__VA_ARGS__) << endl


}//namespace alba
