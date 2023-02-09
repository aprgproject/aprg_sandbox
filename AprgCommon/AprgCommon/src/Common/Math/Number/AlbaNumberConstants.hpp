#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/AlbaMathConstants.hpp>

namespace alba
{

namespace AlbaNumberConstants
{

constexpr AlbaNumber ALBA_NUMBER_POSITIVE_INFINITY = AlbaNumber(AlbaMathConstants::POSITIVE_INFINITY_DOUBLE_VALUE);
constexpr AlbaNumber ALBA_NUMBER_NEGATIVE_INFINITY = AlbaNumber(AlbaMathConstants::NEGATIVE_INFINITY_DOUBLE_VALUE);
constexpr AlbaNumber ALBA_NUMBER_NOT_A_NUMBER = AlbaNumber(AlbaMathConstants::NAN_DOUBLE_VALUE);
constexpr AlbaNumber ALBA_NUMBER_PI = AlbaNumber(AlbaMathConstants::PI_DOUBLE_VALUE);
constexpr AlbaNumber ALBA_NUMBER_E = AlbaNumber(AlbaMathConstants::E_DOUBLE_VALUE);

}

}
