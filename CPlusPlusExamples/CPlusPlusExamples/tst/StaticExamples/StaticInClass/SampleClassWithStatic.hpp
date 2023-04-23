#pragma once

namespace alba
{

struct SampleClassWithStatic
{
    int nonStaticData = 100;

    //static int staticData = 200; // Error: non-const static data member must be initialized out of line
    static int staticData; // declaration only (incomplete type and must be defined)

    constexpr static int staticConstData=300;

    inline static int staticInlinedData=400;

    // mutable static int staticMutableData; // Static data members cannot be mutable.

    int nonStaticFunctionWithClassDeclaration();

    static int staticFunctionWithClassDeclaration();

    int nonStaticFunctionWithClassDefinition()
    {
        return nonStaticData;
    }

    static int staticFunctionWithClassDefinition()
    {
        //return this->staticData; // Static member functions are not associated with any object. When called, they have no this pointer.
        return staticData;
    }

    // static int staticFunctionWithConst() const; // Static member functions cannot be const.
    // static virtual int staticFunctionWithConst(); // Static member functions cannot be const.
    // static int staticFunctionWithConst() volatile; // Static member functions cannot be const.
    // static int staticFunctionWithConst() &; // Static member functions cannot be ref-qualified.
    // static int staticFunctionWithConst() &&; // Static member functions cannot be ref-qualified.
};

// int SampleClassWithStatic::staticData = 200; // Linker error: multiple definition of `alba::SampleClassWithStatic::staticData'

}

// Notes:

// -> static members
// ---> Inside a class definition, the keyword static declares members that are not bound to class instances.
// ---> Outside a class definition, it has a different meaning: see storage duration.
// -----> Syntax
// -----> (1) static data_member
// -------> Declares a static data member.
// -----> (2) static member_function
// -------> Declares a static member function.

// Explanation
// -> Static members of a class are not associated with the objects of the class:
// ---> they are independent variables with static or thread (since C++11) storage duration or regular functions.
// -> The static keyword is only used with the declaration of a static member, inside the class definition, but not with the definition of that static member.
// -> The declaration inside the class body is not a definition and may declare the member to be of incomplete type (other than void),
// ---> including the type in which the member is declared.
// -> However, if the declaration uses constexpr or inline (since C++17) specifier, the member must be declared to have complete type.
// -> To refer to a static member m of class T, two forms may be used: qualified name T::m or member access expression E.m or E->m,
// ---> where E is an expression that evaluates to T or T* respectively.
// -> Static members obey the class member access rules (private, protected, public).


// Static member functions
// -> Static member functions are not associated with any object. When called, they have no this pointer.
// -> Static member functions cannot be virtual, const, volatile, or ref-qualified.
// -> The address of a static member function may be stored in a regular pointer to function, but not in a pointer to member function.

// Static data members
// -> Static data members are not associated with any object.
// -> They exist even if no objects of the class have been defined.
// -> There is only one instance of the static data member in the entire program with static storage duration,
// ---> unless the keyword thread_local is used, in which case there is one such object per thread with thread storage duration (since C++11).
// -> Static data members cannot be mutable.
// -> Static data members of a class in namespace scope have external linkage if the class itself has external linkage (is not a member of unnamed namespace).
// ---> Local classes (classes defined inside functions) and unnamed classes, including member classes of unnamed classes, cannot have static data members.
// -> A static data member may be declared inline.
// ---> An inline static data member can be defined in the class definition and may specify an initializer.
// ---> It does not need an out-of-class definition.

// Constant static members
// -> If a static data member of integral or enumeration type is declared const (and not volatile),
// ---> it can be initialized with an initializer in which every expression is a constant expression, right inside the class definition.
// -> If a static data member of LiteralType is declared constexpr,
// ---> it must be initialized with an initializer in which every expression is a constant expression, right inside the class definition.
// -> If a const non-inline (since C++17) static data member or a constexpr static data member (since C++11)(until C++17) is odr-used,
// ---> a definition at namespace scope is still required, but it cannot have an initializer.
// ---> A definition may be provided even though redundant (since C++17).
// -> If a static data member is declared constexpr, it is implicitly inline and does not need to be redeclared at namespace scope.
// ---> This redeclaration without an initializer (formerly required as shown above) is still permitted, but is deprecated.
