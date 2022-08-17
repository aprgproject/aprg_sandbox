#pragma once

#include <map>
#include <vector>

namespace alba
{

namespace math
{

using Number = unsigned long long;
using Numbers = std::vector<Number>;
using FactorsToCountMap = std::map<Number, Number>;

bool canModuloBeDistributedInAddition(Number const number1, Number const number2, Number const modulo);
bool canModuloBeDistributedInSubtraction(Number const number1, Number const number2, Number const modulo);
bool canModuloBeDistributedInMultiplication(Number const number1, Number const number2, Number const modulo);
bool canModuloBeDistributedInPower(Number const number1, Number const exponent, Number const modulo);
bool canModuloBeDistributedInEveryIterationOfFactorial(Number const number, Number const modulo);
bool isFermatTheoremTrue(Number const prime, Number const coPrime);
bool isEulerTheoremTrue(Number const coPrime1, Number const coPrime2);
Number getModularExponentiation(Number const number1, Number const exponent, Number const modulo);
Number getModularInverse(Number const number, Number const modulo);


}

}
