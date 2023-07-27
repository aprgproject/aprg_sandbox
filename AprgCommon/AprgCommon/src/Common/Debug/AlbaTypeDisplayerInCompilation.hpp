#pragma once

namespace alba {

// NOTES on approach:
// 1) To know the real type, DONT use std::type_info::name,
// because its required by the standard to change what is displayed.
// 2) Boost.TypeIndex (.pretty_name()) provide accurate information in runtime, but we dont use boost.
// 3) Print __PRETTY_FUNCTION__ or ALBA_MACROS_GET_PRETTY_FUNCTION it works!

// Examples taken from Scott Meyers lecture.
// NOTES on type deduction:
// 1) auto type deduction is the same with template type deduction, except for brace initializer list (automatically
// converts to std::initializer_list type) (ill-formed in C++17)
// 2) lambda capture type deduction
// 2.1) capture by reference -> same with template type deduction
// 2.2) init capture in c++14 -> same with auto type deduction
// 2.3) capture by value -> same with template type deduction, except cv qualifiers are retained
// 3) Deduced return type specifiers
// 3.1) auto: Uses template type deduction rules (NOT AUTO!)
// 3.2) decltype(auto) -> Uses decltype type deduction rules
// 4) decltype(something) mean the "declared type of something"
// 4.1) decltype of a name is different from a decltype of an expression (check tests for details)

template <typename TypeToDisplay>
class DisplayThisType;

template <typename TypeInTemplate>
void displayTypeInTemplateByValue(TypeInTemplate parameter) {
    DisplayThisType<TypeInTemplate> objectWithTypeInTemplate;
    DisplayThisType<decltype(parameter)> objectWithParameterType;
}

template <typename TypeInTemplate>
void displayTypeInTemplateByReference(TypeInTemplate& parameter) {
    DisplayThisType<TypeInTemplate> objectWithTypeInTemplate;
    DisplayThisType<decltype(parameter)> objectWithParameterType;
}

template <typename TypeInTemplate>
void displayTypeInTemplateByConstReference(TypeInTemplate const& parameter) {
    DisplayThisType<TypeInTemplate> objectWithTypeInTemplate;
    DisplayThisType<decltype(parameter)> objectWithParameterType;
}

template <typename TypeInTemplate>
void displayTypeInTemplateByUniversalReference(TypeInTemplate&& parameter) {
    DisplayThisType<TypeInTemplate> objectWithTypeInTemplate;
    DisplayThisType<decltype(parameter)> objectWithParameterType;
}

template <typename TypeInTemplate>
void displayTypeInTemplateByPointer(TypeInTemplate* parameter) {
    DisplayThisType<TypeInTemplate> objectWithTypeInTemplate;
    DisplayThisType<decltype(parameter)> objectWithParameterType;
}

}  // namespace alba
