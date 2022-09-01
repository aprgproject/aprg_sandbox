#pragma once

namespace alba
{

namespace mathHelper
{

template <typename NumberType> inline bool isDivisible(NumberType const dividend, NumberType const divisor)
{
    bool result(false);
    if(divisor != 0)    {
        result = (dividend % divisor)==0;
    }
    return result;
}

template <typename NumberType> inline bool isEven(NumberType const number)
{
    return isDivisible(number, static_cast<NumberType>(2));
}

template <typename NumberType> inline bool isOdd(NumberType const number)
{
    return !isDivisible(number, static_cast<NumberType>(2));
}
}//namespace mathHelper

}//namespace alba