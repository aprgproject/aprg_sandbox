#pragma once

#include <string>

namespace alba
{

namespace InlineOnTranslationUnits
{

constexpr int constInteger=100; // implicity inline (external linkage)
inline int inlineIntegerWithDefinition=200; // explicitly inline(external linkage)
inline int inlineIntegerWithDeclaration; // explicitly inline(external linkage)
extern inline int externInlineInteger; // extern so declaration only (incomplete type)
inline std::string inlineString{"700"}; // explicitly inline(external linkage)

// same goes for functions (but there are no free const functions)
constexpr int freeFunction() // implicity inline (external linkage)
{
    return 1;
}
inline int inlineFreeFunction(); // explicitly inline (external linkage)

struct SampleClassWithInline
{
    SampleClassWithInline& operator=(SampleClassWithInline const&) = delete; // implicitly inline (can appear in more than one translation unit)
    static constexpr int constIntegerInClass=1000; // implicity inline (external linkage)
};



// Utilities for tests

struct TranslationUnitValues
{
    int constInteger;
    int inlineIntegerWithDefinition;
    int inlineIntegerWithDeclaration;
    int inlineIntegerAtTranslationUnit;
    int nonInlineAtTranslationUnit;
    int externInlineInteger;
    std::string inlineString;
};

TranslationUnitValues getValuesInTranslationUnit1();
TranslationUnitValues getValuesInTranslationUnit2();

}

}

// Notes:

// From cppreference:

// -> The inline specifier, when used in a function's decl-specifier-seq, declares the function to be an inline function.

// -> A function defined entirely inside a class/struct/union definition,
// ---> whether it's a member function or a non-member friend function,
// ---> is implicitly an inline function if it is attached to the global module (since C++20).

// -> A function declared constexpr is implicitly an inline function.

// -> A deleted function is implicitly an inline function: its (deleted) definition can appear in more than one translation unit. (since C++11)

// -> The inline specifier, when used in a decl-specifier-seq of a variable with static storage duration (static class member or namespace-scope variable),
// ---> declares the variable to be an inline variable.

// -> A static member variable (but not a namespace-scope variable) declared constexpr is implicitly an inline variable. (since C++17)

// Explanation

// -> An inline function or inline variable (since C++17) has the following properties:
// ---> The definition of an inline function or variable (since C++17) must be reachable in the translation unit where it is accessed
// -----> (not necessarily before the point of access).
// ---> An inline function or variable (since C++17) with external linkage (e.g. not declared static) has the following additional properties:
// -----> There may be more than one definition of an inline function or variable (since C++17) in the program
// -------> as long as each definition appears in a different translation unit
// -------> and (for non-static inline functions and variables (since C++17)) all definitions are identical.
// -------> For example, an inline function or an inline variable (since C++17) may be defined in a header file that is #include'd in multiple source files.
// -----> It must be declared inline in every translation unit.
// -----> It has the same address in every translation unit.

// -> In an inline function,
// ---> Function-local static objects in all function definitions are shared across all translation units
// -----> (they all refer to the same object defined in one translation unit)
// ---> Types defined in all function definitions are also the same in all translation units.

// -> Inline const variables at namespace scope have external linkage by default (unlike the non-inline non-volatile const-qualified variables) (since C++17)

// -> The original intent of the inline keyword was to serve as an indicator to the optimizer
// ---> that inline substitution of a function is preferred over function call, that is,
// ---> instead of executing the function call CPU instruction to transfer control to the function body,
// ---> a copy of the function body is executed without generating the call.
// -----> This avoids overhead created by the function call (passing the arguments and retrieving the result)
// -------> but it may result in a larger executable as the code for the function has to be repeated multiple times.

// -> Since this meaning of the keyword inline is non-binding,
// ---> compilers are free to use inline substitution for any function that's not marked inline,
// ---> and are free to generate function calls to any function marked inline.
// -----> Those optimization choices do not change the rules regarding multiple definitions and shared statics listed above.

// -> Because the meaning of the keyword inline for functions came to mean "multiple definitions are permitted" rather than "inlining is preferred",
// ---> that meaning was extended to variables. (since C++17)

// Notes
// -> If an inline function or variable (since C++17) with external linkage is defined differently in different translation units, the behavior is undefined.
// -> The inline specifier cannot be used with a function or variable (since C++17) declaration at block scope (inside another function)
// -> The inline specifier cannot re-declare a function or variable (since C++17) that was already defined in the translation unit as non-inline.
// -> The implicitly-generated member functions and any member function declared as defaulted on its first declaration are inline
// ---> just like any other function defined inside a class definition.
// -> If an inline function is declared in different translation units,
// ---> the accumulated sets of default arguments must be the same at the end of each translation unit.
// -> In C, inline functions do not have to be declared inline in every translation unit (at most one may be non-inline or extern inline),
// ---> the function definitions do not have to be identical (but the behavior of the program is unspecified if it depends on which one is called),
// ---> and the function-local statics are distinct between different definitions of the same function.
// -> See static data members for additional rules about inline static members (on cppreference)
// -> Inline variables eliminate the main obstacle to packaging C++ code as header-only libraries. (since C++17)
// ---> Inlining are Header-only Library Developers Best Friend

// Other discussions:
// -> Inline expansion might be performed regardless of the inline declaration of a function.
// -> Inline functions and variables (with external linkage) may be defined multiple times in the same program, but not compilation unit.
// -> Inline function and variables must be defined in every compilation unit where they are used and declared inline.
// -> All definitions must be identical. Different definitions result in undefined behavior.
// -> constexpr implies inline
// -> inline functions and variables with external linkage share all the same address (exists only once in practice).
