#pragma once

#include <Math/Types.hpp>

namespace alba
{

namespace math
{

UnsignedInteger getNumberOfDerangements(UnsignedInteger const n);
UnsignedInteger getNumberOfDerangementsApproximation(UnsignedInteger const n);
double getDerangementsProbability(UnsignedInteger const n);

}

}
