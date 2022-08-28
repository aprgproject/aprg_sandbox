#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

bool canModuloBeDistributedInAddition(UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo);
bool canModuloBeDistributedInSubtraction(UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo);
bool canModuloBeDistributedInMultiplication(UnsignedInteger const number1, UnsignedInteger const number2, UnsignedInteger const modulo);
bool canModuloBeDistributedInPower(UnsignedInteger const number1, UnsignedInteger const exponent, UnsignedInteger const modulo);
bool canModuloBeDistributedInEveryIterationOfFactorial(UnsignedInteger const number, UnsignedInteger const modulo);
bool isFermatTheoremTrue(UnsignedInteger const prime, UnsignedInteger const coPrime);
bool isEulerTheoremTrue(UnsignedInteger const coPrime1, UnsignedInteger const coPrime2);

UnsignedInteger getModularExponentiation(UnsignedInteger const number1, UnsignedInteger const exponent, UnsignedInteger const modulo);
UnsignedInteger getModularInverse(UnsignedInteger const number, UnsignedInteger const modulo);
UnsignedInteger getModularFactorial(UnsignedInteger const number, UnsignedInteger const modulo);


}

}
