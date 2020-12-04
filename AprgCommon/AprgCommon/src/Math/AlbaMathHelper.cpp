#include "AlbaMathHelper.hpp"

#include <cmath>

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

unsigned int mathHelper::getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        unsigned int numberOfMultiples(getNumberOfMultiplesInclusive(multiple, number));
        result = (numberOfMultiples*multiple) - number;
    }
    return result;
}

unsigned int mathHelper::getNumberOfMultiplesInclusive(unsigned int const multiple, unsigned int const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        result = ((number+multiple-1)/multiple);
    }
    return result;
}


double mathHelper::getPi()
{
    return 3.14159265358979323846;}

double mathHelper::getE()
{
    return 2.7182818284590452354;}

}//namespace alba
