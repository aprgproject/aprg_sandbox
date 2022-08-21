#pragma once

#include <Math/NumberTheory/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

using FactorsToCountMap = std::map<Number, Number>;

bool isLagrangeTheoremTrue(Number const number);
bool isZeckendorfTheoremTrue(Number const number);

Numbers getFibonacciNumbersBelowThisNumber(Number const number);

}

}
