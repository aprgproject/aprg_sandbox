#pragma once

#include <type_traits>

namespace alba
{

namespace typeHelper
{

// Source: https://en.cppreference.com/w/cpp/header/type_traits
// NOTE: Value returning meta functions or "TemplateName_v" are not used in this file to make it more readable.
// NOTE: Type returning meta functions or "TemplateName_t" are not used in this file to make it more readable.


// Type relationships:

template <typename Type1, typename Type2>
constexpr bool areSameTypes()
{
    return std::is_same<Type1, Type2>::value;
}

template <typename FromType, typename ToType>
constexpr bool isConvertible()
{
    return std::is_convertible<FromType, ToType>::value;
}

template <typename BaseType, typename DerivedType>
constexpr bool isBaseOf()
{
    return std::is_base_of<BaseType, DerivedType>::value;
}


// Type operations:

template <typename Type>
constexpr bool negateValueInType()
{
    return std::negation<Type>::value;
}

template <typename... Types>
constexpr bool andOperateValuesInTypes()
{
    return std::conjunction<Types...>::value;
}

template <typename... Types>
constexpr bool orOperateValuesInTypes()
{
    return std::disjunction<Types...>::value;
}



// Type checks:

template <typename Type>
constexpr bool isVoidType()
{
    return std::is_void<Type>::value;
}

template <typename Type>
constexpr bool isIntegralType()
{
    return std::is_integral<Type>::value;
}

template <typename Type>
constexpr bool isFloatingPointType()
{
    return std::is_floating_point<Type>::value;
}

template <typename Type>
constexpr bool isArithmeticType()
{
    return std::is_arithmetic<Type>::value;
}

template <typename Type>
constexpr bool isSignedType()
{
    return std::is_signed<Type>::value;
}

template <typename Type>
constexpr bool isUnsignedType()
{
    return std::is_unsigned<Type>::value;
}

template <typename Type>
constexpr bool isFundamentalType()
{
    return std::is_fundamental<Type>::value;
}

template <typename Type>
constexpr bool isAScalarType()
{
    return std::is_scalar<Type>::value;
}

template <typename Type>
constexpr bool canBeAnObject()
{
    return std::is_object<Type>::value;
}

template <typename Type>
constexpr bool isAPointerType()
{
    return std::is_pointer<Type>::value;
}

template <typename Type>
constexpr bool isAnLValueReference()
{
    return std::is_lvalue_reference<Type>::value;
}

template <typename Type>
constexpr bool isAnRValueReference()
{
    return std::is_rvalue_reference<Type>::value;
}

template <typename Type>
constexpr bool isAConstantType()
{
    return std::is_const<Type>::value;
}

template <typename Type>
constexpr bool isAVolatileType()
{
    return std::is_volatile<Type>::value;
}

// template <typename Type>
// constexpr bool isPlainOldData()
// {
//     return std::is_pod<Type>::value; // deprecated in c++20
// }
//
// is_pod is deprecated because:
//
// POD is being replaced with two categories that give more nuances.
// The c++ standard meeting in november 2017 had this to say about it:
// Deprecating the notion of “plain old data” (POD).
// -> It has been replaced with two more nuanced categories of types, “trivial” and “standard-layout”.
// -> “POD” is equivalent to “trivial and standard layout”,
// -> but for many code patterns, a narrower restriction to just “trivial” or just “standard layout” is appropriate;
// -> to encourage such precision, the notion of “POD” was therefore deprecated.
// -> The library trait is_pod has also been deprecated correspondingly.
// For simple data types use the is_standard_layout function, for trivial data types (such as simple structs) use the is_trivial function.

template <typename Type>
constexpr bool isATrivialType()
{
    return std::is_trivial<Type>::value;
}

template <typename Type>
constexpr bool hasStandardLayout()
{
    // Specifies that a type is standard layout type.
    // Standard layout types are useful for communicating with code written in other programming languages.
    // Note: the standard doesn't define a named requirement with this name.
    // This is a type category defined by the core language.
    // It is included here as a named requirement only for consistency.

    // Requirements for standard layout:
    // -> All non-static data members have the same access control
    // -> Has no virtual functions or virtual base classes
    // -> Has no non-static data members of reference type
    // -> All non-static data members and base classes are themselves standard layout types
    // -> Has no two (possibly indirect) base class subobjects of the same type
    // -> None of the base class subobjects has the same type as:
    // ---> for non-union types, as the first non-static data member (see empty base optimization), and, recursively,
    // the first non-static data member of that data member if it has non-union class type,
    // or all non-static data members of that data member if it has union type,
    // or an element of that data member if it has array type, etc.
    // ---> for union types, as any non-static data members, and, recursively,
    // the first non-static data member of every member of non-union class type,
    // and all non-static data members of all members of union type,
    // and element type of all non-static data members of array type, etc.
    // ---> for array types, as the type of the array element, and, recursively,
    // the first non-static data member of the array element if it has non-union class type,
    // or as any non-static data member of the array element if it has union type,
    // or as the element type of the array element if it has array type, etc.

    return std::is_standard_layout<Type>::value;
}

template <typename Type>
constexpr bool isEmpty()
{
    return std::is_empty<Type>::value;
}

template <typename Type>
constexpr bool isAPolymorphicType()
{
    return std::is_polymorphic<Type>::value;
}

template <typename Type>
constexpr bool isAnAbstractType() // isAnInterface
{
    return std::is_abstract<Type>::value;
}

template <typename Type>
constexpr bool isAFinalType()
{
    return std::is_final<Type>::value;
}

template <typename Type>
constexpr bool isAClass()
{
    return std::is_class<Type>::value;
}

template <typename Type>
constexpr bool isAFunction()
{
    return std::is_function<Type>::value;
}

template <typename Type>
constexpr bool isAEnum()
{
    return std::is_enum<Type>::value;
}

template <typename Type>
constexpr bool isAUnion()
{
    return std::is_union<Type>::value;
}

template <typename Type>
constexpr bool isACStyleArray()
{
    return std::is_array<Type>::value;
}

template <typename Type>
constexpr bool isAnAggregate()
{
    // From: https://en.cppreference.com/w/cpp/language/aggregate_initialization
    // An aggregate is one of the following types:
    // 1) array type
    // 2) class type (typically, struct or union), that has:
    // 2.1) no private or protected direct (since C++17)non-static data members
    // 2.2) no user-declared constructors
    // 2.3) etc
    return std::is_aggregate<Type>::value;
}



// Fundamental operations
// NOTE: This list does not include all because we are lazy.

// default construction
template <typename Type>
constexpr bool isDefaultConstructible()
{
    return std::is_default_constructible<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyDefaultConstructible()
{
    return std::is_trivially_default_constructible<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowDefaultConstructible()
{
    return std::is_nothrow_default_constructible<Type>::value;
}

// destructor
template <typename Type>
constexpr bool isDestructible()
{
    return std::is_destructible<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyDestructible()
{
    return std::is_trivially_destructible<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowDestructible()
{
    return std::is_nothrow_destructible<Type>::value;
}

// copy constructor
template <typename Type>
constexpr bool isCopyConstructible()
{
    return std::is_copy_constructible<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyCopyConstructible()
{
    return std::is_trivially_copy_constructible<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowCopyConstructible()
{
    return std::is_nothrow_copy_constructible<Type>::value;
}

// copy assignment
template <typename Type>
constexpr bool isCopyAssignable()
{
    return std::is_copy_assignable<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyCopyAssignable()
{
    return std::is_trivially_copy_assignable<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowCopyAssignable()
{
    return std::is_nothrow_copy_assignable<Type>::value;
}

// move constructor
template <typename Type>
constexpr bool isMoveConstructible()
{
    return std::is_move_constructible<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyMoveConstructible()
{
    return std::is_trivially_move_constructible<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowMoveConstructible()
{
    return std::is_nothrow_move_constructible<Type>::value;
}

// move assignment
template <typename Type>
constexpr bool isMoveAssignable()
{
    return std::is_move_assignable<Type>::value;
}
template <typename Type>
constexpr bool isTriviallyMoveAssignable()
{
    return std::is_trivially_move_assignable<Type>::value;
}
template <typename Type>
constexpr bool isNoThrowMoveAssignable()
{
    return std::is_nothrow_move_assignable<Type>::value;
}



// Get Types

template<typename Type>
using GetPlainType = typename std::decay<Type>::type;


template<typename Type>
using GetTypeWithLValueReference = typename std::add_lvalue_reference<Type>::type;

template<typename Type>
using GetTypeWithRValueReference = typename std::add_rvalue_reference<Type>::type;

template<typename Type>
using GetTypeWithPointer = typename std::add_pointer<Type>::type;

template<typename Type>
using GetTypeWithConstVolatile = typename std::add_cv<Type>::type;

template<typename Type>
using GetTypeWithConst = typename std::add_const<Type>::type;

template<typename Type>
using GetTypeWithVolatile = typename std::add_volatile<Type>::type;


template<typename Type>
using GetTypeWithoutReference = typename std::remove_reference<Type>::type;

template<typename Type>
using GetTypeWithoutPointer = typename std::remove_pointer<Type>::type;

template<typename Type>
using GetTypeWithoutConstVolatile = typename std::remove_cv<Type>::type;

template<typename Type>
using GetTypeWithoutConst = typename std::remove_const<Type>::type;

template<typename Type>
using GetTypeWithoutVolatile = typename std::remove_volatile<Type>::type;


template<typename Type>
using GetSignedType = typename std::make_signed<Type>::type;

template<typename Type>
using GetUnsignedType = typename std::make_unsigned<Type>::type;



// Arrays

template <typename Array>
constexpr std::size_t getDimensions()
{
    return std::rank<Array>::value;
}

template<typename Array>
using RemoveOneDimension = typename std::remove_extent<Array>::type;

template<typename Array>
using RemoveAllDimensions = typename std::remove_all_extents<Array>::type;




// Conditional types

template<bool condition, typename TypeIfTrue, typename TypeIfFalse>
using ConditionalType = typename std::conditional<condition, TypeIfTrue, TypeIfFalse>::type;


}

} // namespace alba
