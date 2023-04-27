#include "FactorAndMulitplesHelpers.hpp"

using namespace std;

namespace alba::mathHelper {

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber) {
    AlbaNumber result(0);
    if (firstNumber.isDoubleType() || secondNumber.isDoubleType()) {
        result = 1;
    } else {
        AlbaNumber::FractionData firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData secondFractionData(secondNumber.getFractionData());
        uint32_t lcmDenominator = getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        uint32_t firstNumerator = static_cast<uint32_t>(getAbsoluteValue(firstFractionData.numerator)) *
                                  lcmDenominator / firstFractionData.denominator;
        uint32_t secondNumerator = static_cast<uint32_t>(getAbsoluteValue(secondFractionData.numerator)) *
                                   lcmDenominator / secondFractionData.denominator;
        uint32_t gcfNumerator = getGreatestCommonFactor(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(gcfNumerator), lcmDenominator);
    }
    return result;
}

AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber) {
    AlbaNumber result(0);
    if (firstNumber.isDoubleType() || secondNumber.isDoubleType()) {
        result = 1;
    } else {
        AlbaNumber::FractionData firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData secondFractionData(secondNumber.getFractionData());
        uint32_t lcmDenominator = getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        uint32_t firstNumerator = static_cast<uint32_t>(getAbsoluteValue(firstFractionData.numerator)) *
                                  lcmDenominator / firstFractionData.denominator;
        uint32_t secondNumerator = static_cast<uint32_t>(getAbsoluteValue(secondFractionData.numerator)) *
                                   lcmDenominator / secondFractionData.denominator;
        uint32_t lcmNumerator = getLeastCommonMultiple(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(lcmNumerator), lcmDenominator);
    }
    return result;
}

}  // namespace alba::mathHelper
