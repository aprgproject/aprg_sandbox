#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

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
