#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <cmath>

namespace alba
{

namespace mathHelper
{

enum class RootType
{
    RealRootsOnly,
    RealAndImaginaryRoots,
};

template <typename NumberType> inline NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}

template <typename NumberType> inline NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3)
{
    return (value1+value2+value3)/3;
}

template <typename NumberType> inline NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return x*x + y*y;
}

template <typename NumberType> inline NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(x*x + y*y, 0.5));
}

template <typename NumberType> inline NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return static_cast<NumberType>(pow(x*x + y*y + z*z, 0.5));
}

template <typename NumberType> inline NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}

template <typename NumberType> inline NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}

inline AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2)  // pass as const reference
{
    return (value1+value2)/2;
}

AlbaNumbers getQuadraticRoots(RootType const rootType, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

}//namespace mathHelper

}//namespace alba
