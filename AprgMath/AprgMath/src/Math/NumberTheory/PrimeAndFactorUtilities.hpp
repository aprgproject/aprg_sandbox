#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

using FactorsToCountMap = std::map<UnsignedNumber, UnsignedNumber>;

bool isCoPrime(UnsignedNumber const number1, UnsignedNumber const number2);
bool isNumberOfPrimesInfinite();
bool isGoldbachConjectureTrue(UnsignedNumber const evenNumber);
bool isTwinPrimeConjectureTrue(UnsignedNumber const number);
bool isLegendreConjectureTrue(UnsignedNumber const number);
bool isWilsonTheoremTrue(UnsignedNumber const number);

UnsignedNumber getNumberOfFactors(UnsignedNumber const number);
UnsignedNumber getSumOfFactors(UnsignedNumber const number);
UnsignedNumber getProductOfFactors(UnsignedNumber const number);
UnsignedNumber getApproximateDensityOfPrimes(UnsignedNumber const number);
UnsignedNumber getNumberOfCoPrimesBelowThisNumber(UnsignedNumber const number);
UnsignedNumbers getPrimesBelowThisNumber(UnsignedNumber const number);
UnsignedNumbers getPrimeFactorsOfNumber(UnsignedNumber const number);
FactorsToCountMap getPrimeFactorsToCountMap(UnsignedNumber const number);

}

}
