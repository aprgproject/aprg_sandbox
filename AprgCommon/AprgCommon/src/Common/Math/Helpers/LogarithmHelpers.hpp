#pragma once

#include <cmath>
#include <type_traits>

namespace alba
{
namespace mathHelper
{
inline double getLogarithm(double const base, double const inputForLogarithm)
{
    // change of base formula
    // log a(b) = C
    // -> b = a^C
    // -> log10(b) = log10(a^C)
    // -> log10(b) = C*log10(a)
    // -> C = log10(b)/log10(a)

    // log a(b) = log10(b) / log10(a)
    return log10(inputForLogarithm)/log10(base);
}

template <typename NumberType> NumberType getLogarithmForIntegers(NumberType const base, NumberType const inputForLogarithm)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    // This is always correct and faster than pow (check performance test for comparison)

    NumberType result(0);
    if(base > 1 && inputForLogarithm > 0) // base must be at least 2 and input should be positive
    {
        NumberType currentCount(1), currentBase(base), remainingValue(inputForLogarithm);
        while(remainingValue > 0)
        {
            NumberType nextValue = remainingValue / currentBase;
            if(nextValue > 0)
            {
                result += currentCount;
                currentBase *= base;
                currentCount++;
            }
            else
            {
                nextValue = remainingValue / base;
                if(nextValue > 0)
                {
                    result++;
                    currentBase = base*base;
                    currentCount = 2;
                }
            }
            remainingValue = nextValue;
        }
    }
    return result;
}

unsigned int getIterativeLogarithm(double const base, double const inputForLogarithm);
int getSuperLogarithm(double const base, double const inputForLogarithm);
}//namespace mathHelper

}//namespace alba