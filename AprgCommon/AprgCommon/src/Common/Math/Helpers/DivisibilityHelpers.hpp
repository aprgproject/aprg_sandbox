#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba::mathHelper {

template <typename NumberType>
inline bool isDivisible(NumberType const dividend, NumberType const divisor) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return (divisor == 0) ? false : (dividend % divisor) == 0;
}

template <typename NumberType>
inline bool isEven(NumberType const number) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return !(static_cast<bool>(number % 2));
}

template <typename NumberType>
inline bool isOdd(NumberType const number) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return static_cast<bool>(number % 2);
}

template <typename NumberType>
inline bool isDivisibleByThree(NumberType const number) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isMultipleOfThree(number);
}

template <typename NumberType>
inline bool isDivisibleByNine(NumberType const number) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isMultipleOfNine(number);
}

}  // namespace alba::mathHelper

// Even or odd discussion:
// -> Bitwise operators might be better because almost all processors supports bitwise operations to take one
// instruction.
// -> But it will not work for negative numbers:
// -> The C standard stipulates that negative numbers can be represented in 3 ways:
// ---> 2's complement
// ---> 1's complement
// ---> sign and magnitude
// -> Checking like this:
// ---> isEven = (x & 1);
// -> will work for 2's complement and sign and magnitude representation, but not for 1's complement.
// So it might be better to use modulo after all.

// From stack overflow (https://stackoverflow.com/questions/160930/how-do-i-check-if-an-integer-is-even-or-odd/161049):
// Use the modulo (%) operator to check if there's a remainder when dividing by 2:
// -> if (x % 2) { /* x is odd */ }
// A few people have criticized my answer above stating that using x & 1 is "faster" or "more efficient".
// I do not believe this to be the case.

// Out of curiosity, I created two trivial test case programs:

// -> #include <stdio.h>
// -> int main(void)
// -> {
// ->     int x;
// ->     for (x = 0; x < 10; x++)
// ->         if (x % 2)
// ->             printf("%d is odd\n", x);
// ->     return 0;
// -> }

// -> #include <stdio.h>
// -> int main(void)
// -> {
// ->     int x;
// ->     for (x = 0; x < 10; x++)
// ->         if (x & 1)
// ->             printf("%d is odd\n", x);
// ->     return 0;
// -> }

// I then compiled these with gcc 4.1.3 on one of my machines 5 different times:
// -> With no optimization flags.
// -> With -O
// -> With -Os
// -> With -O2
// -> With -O3

// I examined the assembly output of each compile (using gcc -S)
// and found that in each case, the output for and.c and modulo.c were identical (they both used the andl $1, %eax
// instruction). I doubt this is a "new" feature, and I suspect it dates back to ancient versions. I also doubt any
// modern (made in the past 20 years) non-arcane compiler, commercial or open source, lacks such optimization. I would
// test on other compilers, but I don't have any available at the moment. If anyone else would care to test other
// compilers and/or platform targets, and gets a different result, I'd be very interested to know.

// Finally, the modulo version is guaranteed by the standard to work whether the integer is positive,
// negative or zero, regardless of the implementation's representation of signed integers.
// The bitwise-and version is not.
// Yes, I realise two's complement is somewhat ubiquitous, so this is not really an issue.
