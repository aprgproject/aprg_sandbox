#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace mathHelper
{

template <typename NumberType> inline bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
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
template <typename NumberType1, typename NumberType2> inline bool isAlmostAnInteger(NumberType1 const value)
{
    return isAlmostEqual(
                value,
                static_cast<NumberType1>(static_cast<NumberType2>(round(value))));
}
template <typename NumberType> bool isValueBeyondLimits(double const value);
template <typename NumberType> NumberType getIntegerAfterRoundingADoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(round(doubleValue));
}
template <typename NumberType> NumberType getIntegerAfterFloorOfDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(floor(doubleValue));
}
template <typename NumberType> NumberType getIntegerAfterCeilingOfDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(ceil(doubleValue));
}
inline bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) <= differenceTolerance;
}
inline bool isAlmostAnInteger(double const value, double const differenceTolerance)
{
    return isAlmostEqual(value, round(value), differenceTolerance);
}
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);
AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value);

}//namespace mathHelper

}//namespace alba
