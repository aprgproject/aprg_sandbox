#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

bool canModuloBeDistributedInAddition(UnsignedNumber const number1, UnsignedNumber const number2, UnsignedNumber const modulo);
bool canModuloBeDistributedInSubtraction(UnsignedNumber const number1, UnsignedNumber const number2, UnsignedNumber const modulo);
bool canModuloBeDistributedInMultiplication(UnsignedNumber const number1, UnsignedNumber const number2, UnsignedNumber const modulo);
bool canModuloBeDistributedInPower(UnsignedNumber const number1, UnsignedNumber const exponent, UnsignedNumber const modulo);
bool canModuloBeDistributedInEveryIterationOfFactorial(UnsignedNumber const number, UnsignedNumber const modulo);
bool isFermatTheoremTrue(UnsignedNumber const prime, UnsignedNumber const coPrime);
bool isEulerTheoremTrue(UnsignedNumber const coPrime1, UnsignedNumber const coPrime2);

UnsignedNumber getModularExponentiation(UnsignedNumber const number1, UnsignedNumber const exponent, UnsignedNumber const modulo);
UnsignedNumber getModularInverse(UnsignedNumber const number, UnsignedNumber const modulo);
UnsignedNumber getModularFactorial(UnsignedNumber const number, UnsignedNumber const modulo);


}

}
