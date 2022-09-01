#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <limits>

namespace alba
{
namespace mathHelper
{
template <typename NumberType> inline bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return value1==value2;
}

template <> inline bool isAlmostEqual<float>(float const value1, float const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_FLOAT;
}

template <> inline bool isAlmostEqual<double>(double const value1, double const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_DOUBLE;
}

template <typename FloatingType, typename IntegerType> inline bool isAlmostAnInteger(FloatingType const value)
{
    static_assert(std::is_floating_point<FloatingType>::value, "FloatingType must be an floating type");
    static_assert(std::is_integral<IntegerType>::value, "IntegerType must be an integer");

    return isAlmostEqual(                value,
                static_cast<FloatingType>(static_cast<IntegerType>(round(value))));
}

template <typename NumberType> inline bool isValueBeyondLimits(double const value)
{
    static_assert(std::is_integral<NumberType>::value, "IntegerType must be an integer");

    return value < std::numeric_limits<NumberType>::min()
            || value > std::numeric_limits<NumberType>::max();
}

template <typename NumberType> inline NumberType getIntegerAfterRoundingADoubleValue(double const doubleValue)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    return static_cast<NumberType>(round(doubleValue));
}

template <typename NumberType> inline NumberType getIntegerAfterFloorOfDoubleValue(double const doubleValue)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    return static_cast<NumberType>(floor(doubleValue));
}

template <typename NumberType> inline NumberType getIntegerAfterCeilingOfDoubleValue(double const doubleValue)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    return static_cast<NumberType>(ceil(doubleValue));
}

template <typename NumberType> inline NumberType getIntegerPartOfDoubleValue(double const doubleValue)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    return static_cast<NumberType>(doubleValue);
}
inline bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) <= differenceTolerance;
}

inline bool isAlmostAnInteger(double const value, double const differenceTolerance)
{
    return isAlmostEqual(value, round(value), differenceTolerance);
}

inline double getFractionalPartInDouble(double const doubleValue)
{
    return doubleValue-getIntegerPartOfDoubleValue<long long int>(doubleValue);
}

AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value);

}//namespace mathHelper

}//namespace alba
