#pragma once

#include <functional>
#include <vector>

namespace alba
{

namespace math
{

using UnsignedInteger = unsigned long long;
using UnsignedIntegers = std::vector<UnsignedInteger>;
using UnsignedIntegerUnaryFunction = std::function<UnsignedInteger(UnsignedInteger const)>;
using UnsignedIntegerBinaryFunction = std::function<UnsignedInteger(UnsignedInteger const, UnsignedInteger const)>;

using SignedInteger = long long;
using SignedIntegers = std::vector<SignedInteger>;

}

}
