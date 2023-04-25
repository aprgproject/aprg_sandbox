#include "StatisticsHelpers.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace std;

namespace alba {

namespace mathHelper {

double getCumulativeStandardDistributionApproximation(double const z) { return 0.5 * erfc(-z * pow(0.5, 0.5)); }

double getInverseCumulativeStandardDistributionApproximation(
    double const probability, unsigned int const numberOfIterations) {
    double lowestZ = -10, highestZ = 10, z(0);
    for (unsigned int iterationCount = 0; iterationCount < numberOfIterations; iterationCount++) {
        double middleZ = getAverage<double>(lowestZ, highestZ);
        double probabilityLowest = getCumulativeStandardDistributionApproximation(lowestZ);
        double probabilityMiddle = getCumulativeStandardDistributionApproximation(middleZ);
        double probabilityHighest = getCumulativeStandardDistributionApproximation(highestZ);
        if (isAlmostEqual(probability, probabilityLowest)) {
            z = lowestZ;
            break;
        } else if (isAlmostEqual(probability, probabilityMiddle)) {
            z = middleZ;
            break;
        } else if (isAlmostEqual(probability, probabilityHighest)) {
            z = highestZ;
            break;
        } else if (probability > probabilityLowest && probability < probabilityMiddle) {
            highestZ = middleZ;
            z = getAverage<double>(lowestZ, middleZ);
        } else if (probability > probabilityMiddle && probability < probabilityHighest) {
            lowestZ = middleZ;
            z = getAverage<double>(middleZ, highestZ);
        }
    }
    return z;
}

}  // namespace mathHelper

}  // namespace alba
