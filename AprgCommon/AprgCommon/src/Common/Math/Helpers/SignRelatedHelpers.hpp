#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

#include <algorithm>

namespace alba::mathHelper {

template <typename NumberType>
inline NumberType getAbsoluteValue(NumberType const value) {
    if constexpr (typeHelper::isUnsignedType<NumberType>()) {
        return value;
    } else {
        return (value < 0) ? value * -1 : value;
    }
}

template <typename NumberType>
inline NumberType getSign(NumberType const value) {
    if constexpr (typeHelper::isUnsignedType<NumberType>()) {
        return value / value;  // return 1; has warnings
    } else {
        return (value < 0) ? -1 : 1;
    }
}

template <typename NumberType>
inline NumberType getPositiveDelta(NumberType const value1, NumberType const value2) {
    auto&& [minimum, maximum] = std::minmax(value1, value2);  // C++17, structured bindings
    return maximum - minimum;
}

template <typename NumberType>
inline typename std::make_signed<NumberType>::type convertToSignedThenSubtract(
    NumberType const number1, NumberType const number2) {
    using SignedType = typename std::make_signed<NumberType>::type;

    return static_cast<SignedType>(number1) - static_cast<SignedType>(number2);
}

// pass as const reference
inline AlbaNumber getAbsoluteValue(AlbaNumber const& value) { return (value < 0) ? value * -1 : value; }

// pass as const reference
inline AlbaNumber getSign(AlbaNumber const& value) { return (value < 0) ? -1 : 1; }

// pass as const reference
inline AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2) {
    auto&& [minimum, maximum] = std::minmax(value1, value2);
    return maximum - minimum;
}
}  // namespace alba::mathHelper