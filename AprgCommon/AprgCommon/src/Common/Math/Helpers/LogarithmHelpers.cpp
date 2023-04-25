#include "LogarithmHelpers.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace std;

namespace alba {

namespace mathHelper {

unsigned int getIterativeLogarithm(double const base, double const inputForLogarithm) {
    // The iterated logarithm of n, written log* n (usually read "log star"),
    // is the number of times the logarithm function must be iteratively applied before the result is less than or equal
    // to 1.

    unsigned int count(0);
    double currentLogarithm = getLogarithm(base, inputForLogarithm);
    while (currentLogarithm >= 0 && !isAlmostEqual(currentLogarithm, 1.0)) {
        count++;
        currentLogarithm = getLogarithm(base, currentLogarithm);
    }
    return count;
}

int getSuperLogarithm(double const base, double const inputForLogarithm) {
    // In mathematics, the super-logarithm is one of the two inverse functions of tetration.
    // On the positive real numbers, the continuous super-logarithm (inverse tetration) is essentially equivalent
    // However, on the negative real numbers, log-star is 0, whereas the superlogarithm = -1

    int result(0);
    if (inputForLogarithm >= 0) {
        result = static_cast<int>(getIterativeLogarithm(base, inputForLogarithm));
    } else {
        result = -1;
    }
    return result;
}

}  // namespace mathHelper

}  // namespace alba
