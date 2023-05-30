#include "ModularArithmetic.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Math/NumberTheory/PrimeAndFactorUtilities.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace math {

// These formulas are true.

bool canModuloBeDistributedInAddition(
    UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo) {
    // (a + b) mod m = (a mod m + b mod m) mod m

    UnsignedInteger undistributed = (number1 + number2) % modulo;
    UnsignedInteger distributed = (number1 % modulo + number2 % modulo) % modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInSubtraction(
    UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo) {
    // (a - b) mod m = (a mod m - b mod m) mod m

    UnsignedInteger undistributed = (number1 - number2) % modulo;
    UnsignedInteger distributed = (number1 % modulo - number2 % modulo) % modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInMultiplication(
    UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo) {
    // (a * b) mod m = ((a mod m) * (b mod m)) mod m

    UnsignedInteger undistributed = (number1 * number2) % modulo;
    UnsignedInteger distributed = (number1 % modulo * number2 % modulo) % modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInPower(
    UnsignedInteger const number, UnsignedInteger const exponent, UnsignedInteger const modulo) {
    // x^n mod m = ((x mod m)^n) mod m

    UnsignedInteger undistributed = getRaiseToPowerForIntegers(number, exponent) % modulo;
    UnsignedInteger distributed = getRaiseToPowerForIntegers(number % modulo, exponent) % modulo;
    return undistributed == distributed;
}

bool canModuloBeDistributedInEveryIterationOfFactorial(UnsignedInteger const number, UnsignedInteger const modulo) {
    // n! mod m = ((n mod m) * (n-1 mod m) * (n-2 mod m) ... (1 mod m)) mod m

    UnsignedInteger undistributed = getFactorial(number) % modulo;
    UnsignedInteger distributed = 1;
    for (int i = 2; i <= static_cast<int>(number); i++) {
        distributed = (distributed * i) % modulo;
    }
    distributed %= modulo;
    return undistributed == distributed;
}

bool isFermatTheoremTrue(UnsignedInteger const prime, UnsignedInteger const coPrime) {
    // Fermat's theorem states that: (x^(m-1)) mod m = 1
    // where m is prime and x and m are coprime.

    bool result(false);
    if (isPrime(prime) && isCoPrime(prime, coPrime)) {
        UnsignedInteger formula = getRaiseToPowerForIntegers(prime, coPrime - 1) % coPrime;
        result = formula == static_cast<UnsignedInteger>(1);
    }
    return result;
}

bool isEulerTheoremTrue(UnsignedInteger const coPrime1, UnsignedInteger const coPrime2) {
    // Fermat's theorem states that: (x^(phi(m))) mod m = 1
    // where x and m are coprime.

    bool result(false);
    if (isCoPrime(coPrime1, coPrime2)) {
        UnsignedInteger formula =
            getRaiseToPowerForIntegers(coPrime1, getNumberOfCoPrimesBelowThisNumber(coPrime2)) % coPrime2;
        result = formula == static_cast<UnsignedInteger>(1);
    }
    return result;
}

UnsignedInteger getModularExponentiation(
    UnsignedInteger const number, UnsignedInteger const exponent, UnsignedInteger const modulo) {
    // x^n mod m is equal to this

    UnsignedInteger result{};
    if (exponent != 0) {
        result = getModularExponentiation(number, exponent / 2, modulo);
        result = (result * result) % modulo;
        if (isOdd(exponent)) {
            result = (result * number) % modulo;
        }
    } else {
        result = static_cast<UnsignedInteger>(1) % modulo;
    }
    return result;
}

// Modular Inverse:

// The inverse of x modulo m is a number such that: (x*inverse) mod m = 1
// Using modular inverses, we can divide numbers modulo m, because division by x corresponds to multiplication by the
// inverse. However, a modular inverse does not always exist.

UnsignedInteger getModularInverseByIteratingPossibleValues(UnsignedInteger const number, UnsignedInteger const modulo) {
    // Time Complexity: O(m)

    UnsignedInteger result{};
    for (UnsignedInteger possibleInverse = 1; possibleInverse < modulo; possibleInverse++) {
        if (((number % modulo) * (possibleInverse % modulo)) % modulo == 1) {
            result = possibleInverse;
            break;
        }
    }
    return result;
}

UnsignedInteger getModularInverseByGcfEuclidAlgorithm(UnsignedInteger const number, UnsignedInteger const modulo) {
    // Time Complexity: O(log(m)) (because of gcf)

    // The inverse can be calculated exactly when x and m are coprime using Extended Euclid Algorithm.

    // The idea is to use Extended Euclidean algorithms that takes two integers ‘a’ and ‘b’, finds their gcd and also
    // find ‘x’ and ‘y’ such that
    // -> ax + by = gcd(a, b)
    // To find multiplicative inverse of ‘a’ under ‘m’, we put b = m in above formula.
    // Since we know that a and m are relatively prime, we can put value of gcd as 1.
    // -> ax + my = 1
    // If we take modulo m on both sides, we get
    // -> ax + my = 1 (mod m)
    // We can remove the second term on left side as ‘my (mod m)’ would always be 0 for an integer y.
    // -> ax = 1 (mod m)
    // So the 'x' is the multiplicative inverse of 'a'
    // Note: getGreatestCommonFactorWithLastValues in AprgCommon already implements GCF with last values.

    UnsignedInteger result{};
    UnsignedInteger x, y;
    UnsignedInteger gcf = getGreatestCommonFactorWithLastValues(number, modulo, x, y);
    if (1 == gcf)  // is coprime
    {
        result = (x % modulo + modulo) % modulo;
    }
    return result;
}

UnsignedInteger getModularInverseByEulersTheorem(UnsignedInteger const number, UnsignedInteger const modulo) {
    // Time Complexity: O(log(m)) (because of exponentiation)

    // The inverse can be calculated exactly when x and m are coprime using Euler's theorem.

    // Formula:  inverse = x^(phi(m)-1)

    UnsignedInteger result{};
    if (isCoPrime(number, modulo)) {
        result = getModularExponentiation(number, getNumberOfCoPrimesBelowThisNumber(modulo) - 1, modulo);
    }
    return result;

    // Note can be derived using Euler's theorem
    // Definition of inverse: (x*inverse) mod m = 1
    // Euler theorem: (x^(phi(m))) mod m = 1
    // (x * x^(phi(m)-1)) mod m = 1
    // inverse = x^(phi(m)-1)
}

UnsignedInteger getModularInverseByFermatsLittleTheorem(UnsignedInteger const number, UnsignedInteger const modulo) {
    // Time Complexity: O(log(m)) (because of exponentiation)

    // If we know m is prime, then we can also use Fermats’s little theorem to find the inverse.

    // Fermat's little theorem states that if p is a prime number, then for any integer a, the number ap − a is an
    // integer multiple of p. In the notation of modular arithmetic, a^p ~= a (mod p)

    // Thus:
    // -> a^(m-1) ~= 1 (mod m)
    // If we multiply both sides with a-1, we get:
    // -> a^(-1) != a^(m-2) (mod m)

    UnsignedInteger result{};
    if (isPrime(modulo)) {
        result = getModularExponentiation(number, modulo - 2, modulo);
    }
    return result;
}

UnsignedInteger getModularFactorial(UnsignedInteger const number, UnsignedInteger const modulo) {
    // n! mod m = ((n mod m) * (n-1 mod m) * (n-2 mod m) ... (1 mod m)) mod m

    UnsignedInteger result = 1;
    for (int i = 2; i <= static_cast<int>(number); i++) {
        result = (result * i) % modulo;
    }
    result %= modulo;
    return result;
}

}  // namespace math

}  // namespace alba
