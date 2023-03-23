#pragma once

// attribute: [[deprecated]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/deprecated
// C++ attribute: deprecated (since C++14)
// -> Indicates that the name or entity declared with this attribute is deprecated, that is, the use is allowed, but discouraged for some reason.
// Syntax:
// -> [[deprecated]] 	(1)
// -> [[deprecated( string-literal )]] 	(2)
// -> string-literal 	- 	text that could be used to explain the rationale for deprecation and/or to suggest a replacing entity
// Explanation:
// -> Indicates that the use of the name or entity declared with this attribute is allowed, but discouraged for some reason.
// -> Compilers typically issue warnings on such uses. The string-literal, if specified, is usually included in the warnings.
// -> This attribute is allowed in declarations of the following names or entities:
// ---> class/struct/union: struct [[deprecated]] S;,
// ---> typedef-name, including those declared by alias declaration: [[deprecated]] typedef S* PS;, using PS [[deprecated]] = S*;,
// ---> variable, including static data member: [[deprecated]] int x;,
// ---> non-static data member: union U { [[deprecated]] int n; };,
// ---> function: [[deprecated]] void f();,
// ---> namespace: namespace [[deprecated]] NS { int x; }
// ---> enumeration: enum [[deprecated]] E {};,
// ---> enumerator: enum { A [[deprecated]], B [[deprecated]] = 42 };.
// ---> template specialization: template<> struct [[deprecated]] X<int> {};
// -> A name declared non-deprecated may be redeclared deprecated. A name declared deprecated cannot be un-deprecated by redeclaring it without this attribute.


// attribute: [[maybe_unused]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/maybe_unused
// C++ attribute: maybe_unused (since C++17)
// -> Suppresses warnings on unused entities.
// Syntax
// -> [[maybe_unused]]
// Explanation
// -> This attribute can appear in the declaration of the following entities:
// ---> class/struct/union: struct [[maybe_unused]] S;,
// ---> typedef, including those declared by alias declaration: [[maybe_unused]] typedef S* PS;, using PS [[maybe_unused]] = S*;,
// ---> variable, including static data member: [[maybe_unused]] int x;,
// ---> non-static data member: union U { [[maybe_unused]] int n; };,
// ---> function: [[maybe_unused]] void f();,
// ---> enumeration: enum [[maybe_unused]] E {};,
// ---> enumerator: enum { A [[maybe_unused]], B [[maybe_unused]] = 42 };.
// -> If the compiler issues warnings on unused entities, that warning is suppressed for any entity declared maybe_unused.


// attribute: [[nodiscard]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/nodiscard
// C++ attribute: nodiscard (since C++17)
// -> If a function declared nodiscard or a function returning an enumeration or class declared nodiscard
// -> by value is called from a discarded-value expression other than a cast to void, the compiler is encouraged to issue a warning.
// Syntax
// -> [[nodiscard]] 	(1)
// -> [[nodiscard( string-literal )]] 	(2) 	(since C++20)
// -> string-literal 	- 	text that could be used to explain the rationale for why the result should not be discarded
// Explanation
// -> Appears in a function declaration, enumeration declaration, or class declaration.
// -> If, from a discarded-value expression other than a cast to void,
// ---> a function declared nodiscard is called, or
// ---> a function returning an enumeration or class declared nodiscard by value is called, or
// ---> a constructor declared nodiscard is called by explicit type conversion or static_cast, or
// ---> an object of an enumeration or class type declared nodiscard is initialized by explicit type conversion or static_cast,
// -> the compiler is encouraged to issue a warning.


// attribute: [[noreturn]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/noreturn
// C++ attribute: noreturn (since C++11)
// -> Indicates that the function does not return.
// Syntax
// -> [[noreturn]]
// Explanation
// -> Indicates that the function does not return.
// -> This attribute applies to the name of the function being declared in function declarations only.
// -> The behavior is undefined if the function with this attribute actually returns.
// -> The first declaration of the function must specify this attribute if any declaration specifies it.
// -> If a function is declared with [[noreturn]] in one translation unit,
// -> and the same function is declared without [[noreturn]] in another translation unit,
// -> the program is ill-formed; no diagnostic required.


// attribute: [[fallthrough]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/fallthrough
// C++ attribute: fallthrough (since C++11)
// -> Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fallthrough.
// Syntax
// -> [[fallthrough]]
// Explanation
// -> May only be applied to a null statement to create a fallthrough statement ([[fallthrough]];).
// -> A fallthrough statement may only be used in a switch statement,
// -> where the next statement to be executed is a statement with a case or default label for that switch statement.
// -> If the fallthrough statement is inside a loop, the next (labeled) statement must be part of the same iteration of that loop.
// -> Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fallthrough.


// attribute: [[carries_dependency]]
// -> Source: https://en.cppreference.com/w/cpp/language/attributes/carries_dependency
// C++ attribute: carries_dependency (since C++11)
// -> Indicates that dependency chain in release-consume std::memory_order propagates in and out of the function,
// -> which allows the compiler to skip unnecessary memory fence instructions.
// Syntax
// -> [[carries_dependency]]
// Explanation
// -> Indicates that dependency chain in release-consume std::memory_order propagates in and out of the function,
// -> which allows the compiler to skip unnecessary memory fence instructions.
// ->
// -> This attribute may appear in two situations:
// -> 1) it may apply to the parameter declarations of a function or lambda-expressions,
// ->    in which case it indicates that initialization of the parameter carries dependency
// ->    into lvalue-to-rvalue conversion of that object.
// -> 2) It may apply to the function declaration as a whole,
// ->     in which case it indicates that the return value carries dependency
// ->     to the evaluation of the function call expression.
// -> This attribute must appear on the first declaration of a function or one of its parameters in any translation unit.
// -> If it is not used on the first declaration of a function or one of its parameters in another translation unit,
// -> the program is ill-formed; no diagnostic required.



// attribute: [[likely]] [[unlikely]]
// -> Source: https://en.unlikely.com/w/cpp/language/attributes/likely
// C++ attribute: likely, unlikely (since C++20)
// -> Allow the compiler to optimize for the case where paths of execution including that statement
// -> are more or less likely than any alternative path of execution that does not include such a statement
// Syntax
// -> [[likely]] 	(1)
// -> [[unlikely]] 	(2)
// -> Explanation
// -> These attributes may be applied to labels and statements (other than declaration-statements).
// -> They may not be simultaneously applied to the same label or statement.
// -> 1) Applies to a statement to allow the compiler to optimize for the case where paths of execution
// ---> including that statement are more likely than any alternative path of execution that does not include such a statement.
// -> 2) Applies to a statement to allow the compiler to optimize for the case where paths of execution
// ---> including that statement are less likely than any alternative path of execution that does not include such a statement.














