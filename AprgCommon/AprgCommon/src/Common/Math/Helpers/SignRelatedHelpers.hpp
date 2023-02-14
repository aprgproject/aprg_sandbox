#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

#include <algorithm>

namespace alba
{
namespace mathHelper
{
template <typename NumberType> inline NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}

template <> inline unsigned int getAbsoluteValue<unsigned int>(unsigned int const value)
{
    return value;
}

template <typename NumberType> inline NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}

template <> inline unsigned int getSign<unsigned int>(unsigned int const)
{
    return 1;
}

template <typename NumberType> inline NumberType getPositiveDelta(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}

template <typename NumberType>
inline
typename std::make_signed<NumberType>::type
convertToSignedThenSubtract(NumberType const number1, NumberType const number2)
{
    using SignedType = typename std::make_signed<NumberType>::type;

    return static_cast<SignedType>(number1) - static_cast<SignedType>(number2);
}

inline AlbaNumber getAbsoluteValue(AlbaNumber const& value) // pass as const reference
{
    return (value<0) ? value*-1 : value;
}

inline AlbaNumber getSign(AlbaNumber const& value) // pass as const reference
{
    return (value<0) ? -1 : 1;
}

inline AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2) // pass as const reference
{
    std::pair<AlbaNumber, AlbaNumber> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}

}//namespace mathHelper

}//namespace alba
