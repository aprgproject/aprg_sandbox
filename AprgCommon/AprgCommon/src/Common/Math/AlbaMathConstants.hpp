#pragma once

#include <cmath>
#include <limits>

namespace alba::AlbaMathConstants {

constexpr double POSITIVE_INFINITY_DOUBLE_VALUE = static_cast<double>(INFINITY);
constexpr double NEGATIVE_INFINITY_DOUBLE_VALUE = static_cast<double>(-INFINITY);
constexpr double NAN_DOUBLE_VALUE = static_cast<double>(NAN);

// Check C++ Primer for minimum number of significant digits
// minimum number of significant digits for float is 6 (normally its ~7.2)
// minimum number of significant digits for double is 10 (normally its ~15.9)
constexpr double MININUM_SIGNIFICANT_DIGITS_FOR_FLOAT = 1E-6;
constexpr double MININUM_SIGNIFICANT_DIGITS_FOR_DOUBLE = 1E-10;

// Best values according by tests
constexpr double COMPARISON_TOLERANCE_FOR_FLOAT = 1E-5;
constexpr double COMPARISON_TOLERANCE_FOR_DOUBLE = 1E-12;

constexpr double DOUBLE_EPSILON = std::numeric_limits<double>::epsilon();
// The difference between 1.0 and the next value representable by the floating-point type T.

constexpr double PI_DOUBLE_VALUE = 3.14159265358979323846;
constexpr double E_DOUBLE_VALUE = 2.7182818284590452354;

// Please consider using "variable templates" instead, to define the type of the variable.
// Example:
// -> template <typename ConstType>
// -> constexpr ConstType PI_DOUBLE_VALUE(3.14159265358979323846);

}  // namespace alba::AlbaMathConstants

// From: https://en.wikipedia.org/wiki/Floating-point_arithmetic#Internal_representation
// Floating point formats:
//              |           Number of Bits           |                    Other Details                           |
//              | Sign | Exponent | Mantissa | Total | Exponent bias | Bits precision | Significant Digits        |
// Half         |  1   |    5     |    10    |   16  |        15     |       11       |         3-4 (~3.3)        |
// Single       |  1   |    8     |    23    |   32  |       127     |       24       |         6-9 (~7.2)        |
// Double       |  1   |    11    |    52    |   64  |      1023     |       53       |       15-17 (~15.9)       |
// x86 extended |  1   |    15    |    64    |   80  |     16383     |       64       |       18-21 (~19.2)       |
// Quad         |  1   |    15    |   112    |  128  |     16383     |      113       |       33-36 (~34.0)       |
