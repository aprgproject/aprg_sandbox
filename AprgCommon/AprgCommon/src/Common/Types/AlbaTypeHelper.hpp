#pragma once

#include <type_traits>

namespace alba
{

namespace typeHelper
{

// Source: https://en.cppreference.com/w/cpp/header/type_traits
// NOTE: "_v" variant functions are not used in this file to make it more readable.



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

template <typename Type>
constexpr bool isPlainOldData()
{
    return std::is_pod<Type>::value;
}

template <typename Type>
constexpr bool isATrivialType()
{
    return std::is_trivial<Type>::value;
}

template <typename Type>
constexpr bool hasStandardLayout()
{
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


// Conditional types

template<bool condition, typename TypeIfTrue, typename TypeIfFalse>
using ConditionalType = typename std::conditional<condition, TypeIfTrue, TypeIfFalse>::type;


}

} // namespace alba
