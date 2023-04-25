#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>
#include <set>
#include <vector>

namespace alba {

namespace math {

using UnsignedInteger = unsigned long long;
using UnsignedIntegerPair = std::pair<UnsignedInteger, UnsignedInteger>;
using UnsignedIntegerTriplet = std::tuple<UnsignedInteger, UnsignedInteger, UnsignedInteger>;
using UnsignedIntegers = std::vector<UnsignedInteger>;
using SetOfUnsignedIntegers = std::set<UnsignedInteger>;
using UnsignedIntegerUnaryFunction = std::function<UnsignedInteger(UnsignedInteger const)>;
using UnsignedIntegerBinaryFunction = std::function<UnsignedInteger(UnsignedInteger const, UnsignedInteger const)>;
using UnsignedIntegerMatrix = alba::matrix::AlbaMatrix<UnsignedInteger>;

using SignedInteger = long long;
using SignedIntegers = std::vector<SignedInteger>;

}  // namespace math

}  // namespace alba
