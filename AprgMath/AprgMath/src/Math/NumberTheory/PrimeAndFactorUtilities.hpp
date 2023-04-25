#pragma once

#include <Math/Types.hpp>

#include <map>

namespace alba {

namespace math {

using FactorsToCountMap = std::map<UnsignedInteger, UnsignedInteger>;

bool isCoPrime(UnsignedInteger const number1, UnsignedInteger const number2);
bool isNumberOfPrimesInfinite();
bool isGoldbachConjectureTrue(UnsignedInteger const evenNumber);
bool isTwinPrimeConjectureTrue(UnsignedInteger const number);
bool isLegendreConjectureTrue(UnsignedInteger const number);
bool isWilsonTheoremTrue(UnsignedInteger const number);

UnsignedInteger getNumberOfFactors(UnsignedInteger const number);
UnsignedInteger getSumOfFactors(UnsignedInteger const number);
UnsignedInteger getProductOfFactors(UnsignedInteger const number);
UnsignedInteger getApproximateDensityOfPrimes(UnsignedInteger const number);
UnsignedInteger getNumberOfCoPrimesBelowThisNumber(UnsignedInteger const number);
UnsignedIntegers getPrimesBelowThisNumber(UnsignedInteger const number);
UnsignedIntegers getPrimeFactorsOfNumber(UnsignedInteger const number);
FactorsToCountMap getPrimeFactorsToCountMap(UnsignedInteger const number);

}  // namespace math

}  // namespace alba
