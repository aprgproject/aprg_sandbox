#include "ModularArithmetic.hpp"

#include <Common/Math/AlbaMathHelper.hpp>
#include <Math/NumberTheory/PrimeAndFactorUtilities.hpp>



#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

// These formulas are true.

bool canModuloBeDistributedInAddition(
        Number const number1,
        Number const number2,
        Number const modulo)
{
    // (a + b) mod m = (a mod m + b mod m) mod m

    Number undistributed = (number1+number2) % modulo;
    Number distributed = (number1%modulo + number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInSubtraction(
        Number const number1,
        Number const number2,
        Number const modulo)
{
    // (a - b) mod m = (a mod m - b mod m) mod m

    Number undistributed = (number1-number2) % modulo;
    Number distributed = (number1%modulo - number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInMultiplication(
        Number const number1,
        Number const number2,
        Number const modulo)
{
    // (a * b) mod m = ((a mod m) * (b mod m)) mod m

    Number undistributed = (number1*number2) % modulo;
    Number distributed = (number1%modulo * number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInPower(
        Number const number,
        Number const exponent,
        Number const modulo)
{
    // x^n mod m = ((x mod m)^n) mod m

    Number undistributed = getIntegerAfterRoundingADoubleValue<Number>(pow(number, exponent)) % modulo;
    Number distributed = getIntegerAfterRoundingADoubleValue<Number>(pow(number%modulo, exponent)) % modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInEveryIterationOfFactorial(
        Number const number,
        Number const modulo)
{
    // n! mod m = ((n mod m) * (n-1 mod m) * (n-2 mod m) ... (1 mod m)) mod m

    Number undistributed = getFactorial(number) % modulo;
    Number distributed=1;
    for(unsigned int i=2; i<=number; i++)
    {
        distributed = (distributed*i) % modulo;
    }
    distributed %= modulo;
    return undistributed == distributed;
}

bool isFermatTheoremTrue(Number const prime, Number const coPrime)
{
    // Fermat's theorem states that: (x^(m-1)) mod m = 1
    // where m is prime and x and m are coprime.

    bool result(false);
    if(isPrime(prime) && isCoPrime(prime, coPrime))
    {
        Number formula = getIntegerAfterRoundingADoubleValue<Number>(pow(prime, coPrime-1)) % coPrime;
        result = formula == static_cast<Number>(1);
    }
    return result;
}

bool isEulerTheoremTrue(Number const coPrime1, Number const coPrime2)
{
    // Fermat's theorem states that: (x^(phi(m))) mod m = 1
    // where x and m are coprime.

    bool result(false);
    if(isCoPrime(coPrime1, coPrime2))
    {
        Number formula = getIntegerAfterRoundingADoubleValue<Number>(pow(coPrime1, getNumberOfCoPrimesBelowThisNumber(coPrime2))) % coPrime2;
        result = formula == static_cast<Number>(1);
    }
    return result;
}

Number getModularExponentiation(
        Number const number,
        Number const exponent,
        Number const modulo)
{
    // x^n mod m is equal to this

    Number result{};
    if(exponent != 0)
    {
        result = getModularExponentiation(number, exponent/2, modulo);
        result = (result*result) % modulo;
        if(isOdd(exponent))
        {
            result = (result*number) % modulo;
        }
    }
    else
    {
        result = static_cast<Number>(1) % modulo;
    }
    return result;
}

Number getModularInverse(
        Number const number,
        Number const modulo)
{
    // The inverse of x modulo m is a number such that: (x*inverse) mod m = 1
    // Using modular inverses, we can divide numbers modulo m, because division by x corresponds to multiplication by the inverse.
    // However, a modular inverse does not always exist. The inverse can be calculated exactly when x and m are coprime.

    // Formula:  inverse = x^(phi(m)-1)

    Number result{};
    if(isCoPrime(number, modulo))
    {
        result = getModularExponentiation(number, getNumberOfCoPrimesBelowThisNumber(modulo)-1, modulo);
    }
    return result;

    // Note can be derived using Euler's theorem
    // Definition of inverse: (x*inverse) mod m = 1
    // Euler theorem: (x^(phi(m))) mod m = 1
    // (x * x^(phi(m)-1)) mod m = 1
    // inverse = x^(phi(m)-1)
}

}

}
