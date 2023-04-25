#pragma once

namespace alba {

namespace mathHelper {

double getCumulativeStandardDistributionApproximation(double const z);
double getInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);

}  // namespace mathHelper

}  // namespace alba
