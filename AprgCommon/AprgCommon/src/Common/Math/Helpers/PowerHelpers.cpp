#include "PowerHelpers.hpp"

using namespace std;

namespace alba {

namespace mathHelper {

bool isPerfectSquare(AlbaNumber const& value) { return isPerfectNthPower(value, 2); }

bool isPerfectCube(AlbaNumber const& value) { return isPerfectNthPower(value, 3); }

bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower) {
    bool result(false);
    if (number.isIntegerType()) {
        int integerValue(static_cast<int>(number.getInteger()));
        result = integerValue >= 0 && isPerfectNthPower(static_cast<unsigned int>(integerValue), nthPower);
    } else if (number.isFractionType()) {
        AlbaNumber::FractionData fractionData(number.getFractionData());
        result = fractionData.numerator >= 0 &&
                 isPerfectNthPower(static_cast<unsigned int>(getAbsoluteValue(fractionData.numerator)), nthPower) &&
                 isPerfectNthPower(fractionData.denominator, nthPower);
    }
    return result;
}

}  // namespace mathHelper

}  // namespace alba
