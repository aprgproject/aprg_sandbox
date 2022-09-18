#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

// A linear recurrence is a function f (n) whose initial values are f (0), f (1),..., f (k-1)
// and larger values are calculated recursively using the formula:
// f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)

UnsignedIntegerPair getNextFibonacciNumbersUsingLinearRecurrence(
        UnsignedIntegerPair const integerPair);

UnsignedIntegerPair getNextNumberOfDerangementsUsingLinearRecurrence(
        UnsignedInteger const nthValue,
        UnsignedIntegerPair const integerPair);

}

}
