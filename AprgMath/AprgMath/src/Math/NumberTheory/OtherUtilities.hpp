#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

bool isLagrangeTheoremTrue(UnsignedNumber const number);
bool isZeckendorfTheoremTrue(UnsignedNumber const number);

UnsignedNumber getNthFibonacciNumber(UnsignedNumber const number);
UnsignedNumbers getFibonacciNumbersBelowThisNumber(UnsignedNumber const number);

}

}
