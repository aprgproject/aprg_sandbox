#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

bool isLagrangeTheoremTrue(UnsignedInteger const number);
bool isZeckendorfTheoremTrue(UnsignedInteger const number);

UnsignedInteger getNthFibonacciNumber(UnsignedInteger const number);
UnsignedIntegers getFibonacciNumbersBelowThisNumber(UnsignedInteger const number);

}

}
