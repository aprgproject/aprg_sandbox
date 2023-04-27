#pragma once

#include <cstddef>

namespace alba::mathHelper {

double getCumulativeStandardDistributionApproximation(double const z);
double getInverseCumulativeStandardDistributionApproximation(double const p, size_t const numberOfIterations);

}  // namespace alba::mathHelper
