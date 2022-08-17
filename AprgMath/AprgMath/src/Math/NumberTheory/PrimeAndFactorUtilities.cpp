#include "PrimeAndFactorUtilities.hpp"

#include <Algorithm/Search/SumSearch/TwoSum.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

bool isNumberOfPrimesInfinite()
{
    // It is easy to show that there is an infinite number of primes.
    // If the number of primes would be finite, we could construct a set P = {p1, p2,..., pn} that would contain all the primes.
    // However, using P, we could form a new prime == p1p2...pn + 1 that is larger than all elements in P.
    // This is a contradiction, and the number of primes has to be infinite.
    return true;
}

// There are many conjectures involving primes.
// Most people think that the conjectures are true, but nobody has been able to prove them.

bool isGoldbachConjectureTrue(Number const evenNumber)
{
    // Goldbach’s conjecture: Each even integer n > 2 can be represented as a sum n = a+b so that both a and b are primes.

    bool result(false); // set as false when input is wrong
    if(evenNumber > 2 && evenNumber%2 == 0)
    {
        Numbers numbers(getPrimesBeforeThisNumber(evenNumber));
        TwoSum<Number> twoSum(numbers);
        auto primePair(twoSum.getTwoValuesWithSum(evenNumber));
        result = primePair.first != 0 && primePair.second != 0;
    }
    return result;
}

bool isTwinPrimeConjectureTrue(Number const number)
{
    // Twin prime conjecture: There is an infinite number of pairs of the form {p, p+2}, where both p and p+2 are primes.

    Numbers numbers(getPrimesBeforeThisNumber(number));
    Number twinPrimeCount=0;
    for(Number i=0; i<numbers.size()-1; i++)
    {
        if(numbers.at(i+1) - numbers.at(i) == 2)
        {
            twinPrimeCount++;
        }
    }
    return twinPrimeCount>0; // actually we should check if this is infinite (continuously increasing)
}

bool isLegendreConjectureTrue(Number const number)
{
    // Legendre’s conjecture: There is always a prime between numbers n^2 and (n+1)^2, where n is any positive integer.

    Number start(pow(number, 2));
    Number end(pow(number+1, 2));
    bool result(false);
    for(Number numberToCheck=start+1; numberToCheck<end; numberToCheck++)
    {
        if(isPrime(numberToCheck))
        {
            result = true;
            break;
        }
    }
    return result;
}

Number getNumberOfFactors(Number const number)
{
    FactorsToCountMap primeFactorsToCountMap(getPrimeFactorsToCountMap(number));
    Number result=1;
    for(auto const& primeFactorAndCountPair : primeFactorsToCountMap)
    {
        Number count(primeFactorAndCountPair.second);
        result *= count + 1;
    }
    return result;
}

Number getSumOfFactors(Number const number)
{
    FactorsToCountMap primeFactorsToCountMap(getPrimeFactorsToCountMap(number));
    Number result=1;
    for(auto const& primeFactorAndCountPair : primeFactorsToCountMap)
    {
        Number primeFactor(primeFactorAndCountPair.first);
        Number count(primeFactorAndCountPair.second);
        Number formulaValue = static_cast<double>(pow(primeFactor, count+1)-1) / static_cast<double>(primeFactor-1);
        result *= formulaValue;
    }
    return result;
}

Number getProductOfFactors(Number const number)
{
    Number numberOfFactors(getNumberOfFactors(number));
    return pow(number, numberOfFactors/2);
}

Number getApproximateDensityOfPrimes(Number const number)
{
    // formula = n/(ln(n))
    return static_cast<double>(number) / static_cast<double>(log(number));
}

Numbers getPrimesBeforeThisNumber(Number const number)
{
    // The inner loop of the algorithm is executed n/x times for each value of x.
    // Thus, an upper bound for the running time of the algorithm is the harmonic sum
    // -> Summation of n/x = n/2 + n/3 + n/4 + ... + n/n = O(n*log(n))
    // In fact, the algorithm is more efficient, because the inner loop will be executed only if the number x is prime.
    // It can be shown that the running time of the  algorithm is only O(n*log(log(n))), a complexity very near to O(n).

    vector<bool> sieveOfEratosthenes(number, true);
    for(Number possiblePrime=2; possiblePrime<number; possiblePrime++)
    {
        for(Number multiple=2*possiblePrime; multiple<number; multiple+=possiblePrime)
        {
            sieveOfEratosthenes[multiple] = false;
        }
    }
    Numbers result;
    for(Number prime=2; prime<number; prime++)
    {
        if(sieveOfEratosthenes.at(prime))
        {
            result.emplace_back(prime);
        }
    }
    return result;
}

Numbers getPrimeFactorsOfNumber(Number const number)
{
    Numbers result;
    Number remainingFactor(number);
    for(Number factor=2; factor*factor<=remainingFactor; factor++)
    {
        while(remainingFactor % factor == 0)
        {
            result.emplace_back(factor);
            remainingFactor /= factor;
        }
    }
    if(remainingFactor > 1)
    {
        result.emplace_back(remainingFactor);
    }
    return result;
}

FactorsToCountMap getPrimeFactorsToCountMap(Number const number)
{
    FactorsToCountMap result;
    Number remainingFactor(number);
    for(Number factor=2; factor*factor<=remainingFactor; factor++)
    {
        if(remainingFactor % factor == 0)
        {
            Number count=0;
            for(; remainingFactor % factor == 0; count++)
            {
                remainingFactor /= factor;
            }
            result.emplace(factor, count);
        }
    }
    if(remainingFactor > 1)
    {
        result.emplace(remainingFactor, 1);
    }
    return result;
}

}

}
