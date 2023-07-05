#pragma once

#include <cmath>
#include <limits>

namespace alba::AlbaMathConstants {

constexpr double POSITIVE_INFINITY_DOUBLE_VALUE = static_cast<double>(INFINITY);
constexpr double NEGATIVE_INFINITY_DOUBLE_VALUE = static_cast<double>(-INFINITY);
constexpr double NAN_DOUBLE_VALUE = static_cast<double>(NAN);

constexpr double PRECISION_OF_FLOAT = 1E-8;
constexpr double PRECISION_OF_DOUBLE = 1E-15;
constexpr double COMPARISON_TOLERANCE_FOR_FLOAT = 1E-5;
constexpr double COMPARISON_TOLERANCE_FOR_DOUBLE = 1E-12;

constexpr double DOUBLE_EPSILON = std::numeric_limits<double>::epsilon();
// The difference between 1.0 and the next value representable by the floating-point type T.

constexpr double PI_DOUBLE_VALUE = 3.14159265358979323846;
constexpr double E_DOUBLE_VALUE = 2.7182818284590452354;
// Please consider using "variable templates" instead, to define the type of the variable.
// Example:
// -> template <typename ConstType>// -> constexpr ConstType PI_DOUBLE_VALUE(3.14159265358979323846);

}  // namespace alba::AlbaMathConstants
