#pragma once

namespace alba
{

namespace mathHelper
{
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value);
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);
double getPi();
double getE();
}

}//namespace alba
