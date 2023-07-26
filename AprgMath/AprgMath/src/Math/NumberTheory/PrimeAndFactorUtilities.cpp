#include "PrimeAndFactorUtilities.hpp"

#include <Algorithm/Search/SumSearch/TwoSum.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Math/NumberTheory/ModularArithmetic.hpp>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace math {

bool isCoPrime(UnsignedInteger const number1, UnsignedInteger const number2) {
    return getGreatestCommonFactor(number1, number2) == static_cast<UnsignedInteger>(1);
}

bool isNumberOfPrimesInfinite() {
    // It is easy to show that there is an infinite number of primes.
    // If the number of primes would be finite, we could construct a set P = {p1, p2,..., pn} that would contain all the
    // primes. However, using P, we could form a new prime == p1p2...pn + 1 that is larger than all elements in P. This
    // is a contradiction, and the number of primes has to be infinite.
    return true;
}

// There are many conjectures involving primes.
// Most people think that the conjectures are true, but nobody has been able to prove them.

bool isGoldbachConjectureTrue(UnsignedInteger const evenNumber) {
    // Goldbach’s conjecture: Each even integer n > 2 can be represented as a sum n = a+b so that both a and b are
    // primes.

    bool result(false);  // set as false when input is wrong
    if (evenNumber > 2 && isEven(evenNumber)) {
        UnsignedIntegers numbers(getPrimesBelowThisNumber(evenNumber));
        TwoSum<UnsignedIntegers> twoSum(numbers);
        auto [firstValue, secondValue] = twoSum.getNonDuplicateTwoValuesWithSum(evenNumber);
        result = firstValue != 0 && secondValue != 0;
    }
    return result;
}

bool isTwinPrimeConjectureTrue(UnsignedInteger const number) {
    // Twin prime conjecture: There is an infinite number of pairs of the form {p, p+2}, where both p and p+2 are
    // primes.

    UnsignedIntegers numbers(getPrimesBelowThisNumber(number));
    UnsignedInteger twinPrimeCount = 0;
    for (UnsignedInteger i = 0; i < numbers.size() - 1; i++) {
        if (numbers[i + 1] - numbers[i] == 2) {
            twinPrimeCount++;
        }
    }
    return twinPrimeCount > 0;  // actually we should check if this is infinite (continuously increasing)
}

bool isLegendreConjectureTrue(UnsignedInteger const number) {
    // Legendre’s conjecture: There is always a prime between numbers n^2 and (n+1)^2, where n is any positive integer.

    UnsignedInteger start = getRaiseToPowerForIntegers(number, static_cast<UnsignedInteger>(2));
    UnsignedInteger end = getRaiseToPowerForIntegers(number + 1, static_cast<UnsignedInteger>(2));
    bool result(false);
    for (UnsignedInteger numberToCheck = start + 1; numberToCheck < end; numberToCheck++) {
        if (isPrime(numberToCheck)) {
            result = true;
            break;
        }
    }
    return result;
}

bool isWilsonTheoremTrue(UnsignedInteger const number) {
    // Wilson’s theorem states that a number n is prime exactly when (n-1)! mod n = n-1.

    // For example, the number 11 is prime, because 10! mod 11 = 10
    // and the number 12 is not prime, because 11! mod 12 = 0 (not equal to 11).

    bool result(false);  // false when input is wrong
    if (number >= 2) {
        bool isFormulaSatisfied = getModularFactorial(number - 1, number) == number - 1;
        result = isFormulaSatisfied == isPrime(number);
    }
    return result;
}

UnsignedInteger getNumberOfFactors(UnsignedInteger const number) {
    FactorsToCountMap primeFactorsToCountMap(getPrimeFactorsToCountMap(number));
    UnsignedInteger result(1);
    for (auto const& [primeFactor, count] : primeFactorsToCountMap) {
        result *= count + 1;
    }
    return result;
}

UnsignedInteger getSumOfFactors(UnsignedInteger const number) {
    FactorsToCountMap primeFactorsToCountMap(getPrimeFactorsToCountMap(number));
    UnsignedInteger result(1);
    for (auto const& [primeFactor, count] : primeFactorsToCountMap) {
        UnsignedInteger formulaValue = (getRaiseToPowerForIntegers(primeFactor, count + 1) - 1) / (primeFactor - 1);
        result *= formulaValue;
    }
    return result;
}

UnsignedInteger getProductOfFactors(UnsignedInteger const number) {
    UnsignedInteger numberOfFactors(getNumberOfFactors(number));
    return getRaiseToPowerForIntegers(number, numberOfFactors / 2);
}

UnsignedInteger getApproximateDensityOfPrimes(UnsignedInteger const number) {
    // formula = n/(ln(n))
    return number / log(number);
}

UnsignedInteger getNumberOfCoPrimesBelowThisNumber(UnsignedInteger const number) {
    // Euler’s totient function phi(n) gives the number of coprime numbers to n between 1 and n.

    FactorsToCountMap primeFactorsToCountMap(getPrimeFactorsToCountMap(number));
    UnsignedInteger result(1);
    for (auto const& [primeFactor, count] : primeFactorsToCountMap) {
        UnsignedInteger formulaValue = getRaiseToPowerForIntegers(primeFactor, count - 1) * (primeFactor - 1);
        result *= formulaValue;
    }
    return result;
}

UnsignedIntegers getPrimesBelowThisNumber(UnsignedInteger const number) {
    // The inner loop of the algorithm is executed n/x times for each value of x.
    // Thus, an upper bound for the running time of the algorithm is the harmonic sum
    // -> Summation of n/x = n/2 + n/3 + n/4 + ... + n/n = O(n*log(n))
    // In fact, the algorithm is more efficient, because the inner loop will be executed only if the number x is prime.
    // It can be shown that the running time of the  algorithm is only O(n*log(log(n))), a complexity very near to O(n).

    // This algorithm produces all primes not greater than n.
    // It includes a common optimization, which is to start enumerating the multiples of each prime i from i^2.
    // The time complexity of this algorithm is O(n log log n), provided the array update is an O(1) operation, as is
    // usually the case.

    vector<bool> sieveOfEratosthenes(number, true);
    for (UnsignedInteger candidatePrime = 2; candidatePrime * candidatePrime < number;) {
        for (UnsignedInteger multiple = candidatePrime * candidatePrime; multiple < number;
             multiple += candidatePrime) {
            sieveOfEratosthenes[multiple] = false;
        }
        auto itLowestCandidate =
            find(sieveOfEratosthenes.cbegin() + candidatePrime + 1, sieveOfEratosthenes.cend(), true);
        candidatePrime = distance(sieveOfEratosthenes.cbegin(), itLowestCandidate);
    }
    UnsignedIntegers result;
    for (UnsignedInteger prime = 2; prime < number; prime++) {
        if (sieveOfEratosthenes[prime]) {
            result.emplace_back(prime);
        }
    }
    return result;
}

UnsignedIntegers getPrimeFactorsOfNumber(UnsignedInteger const number) {
    UnsignedIntegers result;
    UnsignedInteger remainingFactor(number);
    for (UnsignedInteger factor = 2; factor * factor <= remainingFactor; factor++) {
        while (remainingFactor % factor == 0) {
            result.emplace_back(factor);
            remainingFactor /= factor;
        }
    }
    if (remainingFactor > 1) {
        result.emplace_back(remainingFactor);
    }
    return result;
}

FactorsToCountMap getPrimeFactorsToCountMap(UnsignedInteger const number) {
    FactorsToCountMap result;
    UnsignedInteger remainingFactor(number);
    for (UnsignedInteger factor = 2; factor * factor <= remainingFactor; factor++) {
        if (remainingFactor % factor == 0) {
            UnsignedInteger count = 0;
            for (; remainingFactor % factor == 0; count++) {
                remainingFactor /= factor;
            }
            result.emplace(factor, count);
        }
    }
    if (remainingFactor > 1) {
        result.emplace(remainingFactor, 1);
    }
    return result;
}

}  // namespace math

}  // namespace alba
