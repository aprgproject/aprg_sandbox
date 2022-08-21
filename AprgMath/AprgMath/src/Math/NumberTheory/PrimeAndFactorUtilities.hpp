#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

using FactorsToCountMap = std::map<Number, Number>;

bool isCoPrime(Number const number1, Number const number2);
bool isNumberOfPrimesInfinite();
bool isGoldbachConjectureTrue(Number const evenNumber);
bool isTwinPrimeConjectureTrue(Number const number);
bool isLegendreConjectureTrue(Number const number);
Number getNumberOfFactors(Number const number);
Number getSumOfFactors(Number const number);
Number getProductOfFactors(Number const number);
Number getApproximateDensityOfPrimes(Number const number);
Number getNumberOfCoPrimesBelowThisNumber(Number const number);
Numbers getPrimesBelowThisNumber(Number const number);
Numbers getPrimeFactorsOfNumber(Number const number);
FactorsToCountMap getPrimeFactorsToCountMap(Number const number);

}

}
