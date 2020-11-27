#include "AlbaMathHelper.hpp"

namespace alba
{

template <typename NumberType>
NumberType mathHelper::getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template int mathHelper::getAbsoluteValue<int>(int const value);
template double mathHelper::getAbsoluteValue<double>(double const value);

template <typename NumberType>
NumberType mathHelper::clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template int mathHelper::clampLowerBound<int>(int const value, int const limit);
template double mathHelper::clampLowerBound<double>(double const value, double const limit);

template <typename NumberType>
NumberType mathHelper::clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}
template int mathHelper::clampHigherBound<int>(int const value, int const limit);
template double mathHelper::clampHigherBound<double>(double const value, double const limit);

}//namespace alba
