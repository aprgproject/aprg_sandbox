#pragma once

#include <cstddef>

namespace alba {

namespace mathHelper {

double getCumulativeStandardDistributionApproximation(double const z);
double getInverseCumulativeStandardDistributionApproximation(double const p, size_t const numberOfIterations);

}  // namespace mathHelper

}  // namespace alba
