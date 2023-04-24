#pragma once

namespace alba
{

namespace StaticOnTranslationUnits
{

constexpr int constInteger=100; // static(internal linkage) by default
static int staticInteger=200; // explicitly static(internal linkage)

// Linking failure if we include things with external linkage in the header:
// -> int integer; // extern(external linkage) by default
// ---> Linking error: multiple definition of `alba::integer'
// -> extern const int externConstInteger; // explicitly extern(external linkage)
// ---> Linking error: undefined reference to `alba::externConstInteger'

// same goes for functions (but there are no free const functions)
int freeFunction(); // extern by default
static int staticFreeFunction(); // explicitly static



// Utilities for tests

struct TranslationUnitValues
{
    int constInteger;
    int staticInteger;
    int integer;
    int externInteger;
    int externConstInteger;
};

TranslationUnitValues getValuesInTranslationUnit1();
TranslationUnitValues getValuesInTranslationUnit2();

}

}

// Notes:

// -> Translation Unit
// ---> According to standard C++ (wayback machine link)
// -----> A translation unit is the basic unit of compilation in C++.
// -----> It consists of the contents of a single source file,
// -------> plus the contents of any header files directly or indirectly included by it,
// -------> minus those lines that were ignored using conditional preprocessing statements.

// -> Linkage
// ---> External linkage refers to things that exist beyond a particular translation unit. In other words, accessible through the whole program.
// ---> Internal linkage means everything in the scope of a translation unit.

// -> By default, an object or variable that is defined in the global namespace has the static duration
// -> and external linkage however when you declare a variable or function at file scope (global and/or namespace scope),
// -> the static keyword specifies that the variable or function has internal linkage (static=internal).

// -> "const" keyword
// ---> "const" variables goes by default internal linkage unless otherwise declared as extern.

// -> "static" keyword
// ---> A "static" variable or function means that when it comes time to link those actual functions or variables to define symbols,
// -----> the linker is not going to look outside of the scope of this translation unit for that symbol definition.
// -----> Static in translation unit also means that symbol is going to be visible ONLY in that translation unit.
// ---> From cppreference:
// -----> The static specifier is only allowed in the declarations of objects (except in function parameter lists),
// -----> declarations of functions (except at block scope), and declarations of anonymous unions.
// -----> When used in a declaration of a class member, it declares a static member.
// -----> When used in a declaration of an object, it specifies static storage duration (except if accompanied by thread_local).
// -----> When used in a declaration at namespace scope, it specifies internal linkage.

// -> "extern" keyword
// ---> "extern" means that its going to look for that variable in an external translation unit.
// ---> From cppreference:
// -----> The extern specifier is only allowed in the declarations of variables and functions (except class members or function parameters).
// -----> It specifies external linkage, and does not technically affect storage duration,
// -----> but it cannot be used in a definition of an automatic storage duration object,
// -----> so all extern objects have static or thread durations.
// -----> In addition, a variable declaration that uses extern and has no initializer is not a definition.

// -> static storage duration
// ---> From cppreference:
// -----> The storage for the object is allocated when the program begins and deallocated when the program ends.
// -----> Only one instance of the object exists (in the translation unit).
// -----> All objects declared at namespace scope (including global namespace) have this storage duration, plus those declared with static or extern.
// ---> If the data is static, it isn't allocated on the heap, and it will be destructed during the shutdown of the process.
// -----> If it is a pointer to the data which is static, e.g.:
// -------> Something* MyClass::aPointer = new Something;
// -----> then like all other dynamically allocated data, it will only be destructed when you delete it. There are two frequent solutions:
// -------> (1) use a smart pointer, which has a destructor which deletes it, or
// -------> (2) don't delete it; in most cases, there's really no reason to call the destructor,
// ---------> and if you happen to use the instance in the destructors of other static objects,
// ---------> you'll run into an order of destruction problem.
// ---> In multi-threaded environment, these objects might have been destructed while some objects are still accessing on it, and then bad things happens.
// -----> Consider std::quick_exit on this case

