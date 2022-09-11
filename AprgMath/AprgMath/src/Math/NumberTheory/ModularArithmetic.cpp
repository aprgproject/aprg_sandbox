#include "ModularArithmetic.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Math/NumberTheory/PrimeAndFactorUtilities.hpp>

using namespace alba::mathHelper;using namespace std;

namespace alba
{
namespace math
{

// These formulas are true.

bool canModuloBeDistributedInAddition(
        UnsignedInteger const number1,
        UnsignedInteger const number2,
        UnsignedInteger const modulo)
{
    // (a + b) mod m = (a mod m + b mod m) mod m

    UnsignedInteger undistributed = (number1+number2) % modulo;
    UnsignedInteger distributed = (number1%modulo + number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInSubtraction(
        UnsignedInteger const number1,
        UnsignedInteger const number2,
        UnsignedInteger const modulo)
{
    // (a - b) mod m = (a mod m - b mod m) mod m

    UnsignedInteger undistributed = (number1-number2) % modulo;
    UnsignedInteger distributed = (number1%modulo - number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInMultiplication(
        UnsignedInteger const number1,
        UnsignedInteger const number2,
        UnsignedInteger const modulo)
{
    // (a * b) mod m = ((a mod m) * (b mod m)) mod m

    UnsignedInteger undistributed = (number1*number2) % modulo;
    UnsignedInteger distributed = (number1%modulo * number2%modulo)%modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInPower(
        UnsignedInteger const number,
        UnsignedInteger const exponent,
        UnsignedInteger const modulo)
{
    // x^n mod m = ((x mod m)^n) mod m

    UnsignedInteger undistributed = getRaiseToPowerForIntegers(number, exponent) % modulo;
    UnsignedInteger distributed = getRaiseToPowerForIntegers(number%modulo, exponent) % modulo;
    return undistributed == distributed;
}
bool canModuloBeDistributedInEveryIterationOfFactorial(
        UnsignedInteger const number,
        UnsignedInteger const modulo){
    // n! mod m = ((n mod m) * (n-1 mod m) * (n-2 mod m) ... (1 mod m)) mod m

    UnsignedInteger undistributed = getFactorial(number) % modulo;
    UnsignedInteger distributed=1;
    for(unsigned int i=2; i<=number; i++)
    {
        distributed = (distributed*i) % modulo;
    }
    distributed %= modulo;
    return undistributed == distributed;
}

bool isFermatTheoremTrue(UnsignedInteger const prime, UnsignedInteger const coPrime)
{
    // Fermat's theorem states that: (x^(m-1)) mod m = 1
    // where m is prime and x and m are coprime.

    bool result(false);
    if(isPrime(prime) && isCoPrime(prime, coPrime))
    {
        UnsignedInteger formula = getRaiseToPowerForIntegers(prime, coPrime-1) % coPrime;
        result = formula == static_cast<UnsignedInteger>(1);
    }
    return result;}

bool isEulerTheoremTrue(UnsignedInteger const coPrime1, UnsignedInteger const coPrime2)
{    // Fermat's theorem states that: (x^(phi(m))) mod m = 1
    // where x and m are coprime.

    bool result(false);
    if(isCoPrime(coPrime1, coPrime2))
    {
        UnsignedInteger formula = getRaiseToPowerForIntegers(coPrime1, getNumberOfCoPrimesBelowThisNumber(coPrime2)) % coPrime2;
        result = formula == static_cast<UnsignedInteger>(1);
    }
    return result;}

UnsignedInteger getModularExponentiation(
        UnsignedInteger const number,        UnsignedInteger const exponent,
        UnsignedInteger const modulo)
{
    // x^n mod m is equal to this

    UnsignedInteger result{};
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
        result = static_cast<UnsignedInteger>(1) % modulo;
    }
    return result;
}

UnsignedInteger getModularInverse(
        UnsignedInteger const number,
        UnsignedInteger const modulo)
{
    // The inverse of x modulo m is a number such that: (x*inverse) mod m = 1
    // Using modular inverses, we can divide numbers modulo m, because division by x corresponds to multiplication by the inverse.
    // However, a modular inverse does not always exist. The inverse can be calculated exactly when x and m are coprime.

    // Formula:  inverse = x^(phi(m)-1)

    UnsignedInteger result{};
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

UnsignedInteger getModularFactorial(
        UnsignedInteger const number,
        UnsignedInteger const modulo)
{
    // n! mod m = ((n mod m) * (n-1 mod m) * (n-2 mod m) ... (1 mod m)) mod m

    UnsignedInteger result=1;
    for(unsigned int i=2; i<=number; i++)
    {
        result = (result*i) % modulo;
    }
    result %= modulo;
    return result;
}

}

}
