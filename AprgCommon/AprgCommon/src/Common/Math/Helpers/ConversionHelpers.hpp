#pragma once

#include <Common/Math/Helpers/ConstantHelpers.hpp>

namespace alba::mathHelper {

inline double convertDegreesToRadians(double const valueInDegrees) { return valueInDegrees / 180 * getPi(); }

inline double convertRadiansToDegrees(double const valueInRadians) { return valueInRadians / getPi() * 180; }

}  // namespace alba::mathHelper
