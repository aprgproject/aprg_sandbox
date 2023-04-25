#include "ComputeSumOfDigitsInAllNumbersFrom1ToN.hpp"

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

ComputeSumOfDigitsInAllNumbersFrom1ToN::ComputeSumOfDigitsInAllNumbersFrom1ToN(Value const lastNumber)
    : m_lastNumber(lastNumber) {}

ComputeSumOfDigitsInAllNumbersFrom1ToN::Value ComputeSumOfDigitsInAllNumbersFrom1ToN::getValueUsingNaiveSolution()
    const {
    // Time Complexity: O(number * numberOfDigits)
    // Auxiliary Space: Constant

    Value result(0);
    for (Value number = 1; number <= m_lastNumber; number++) {
        for (Value numberForDigitsSum = number; numberForDigitsSum > 0; numberForDigitsSum /= 10) {
            result += numberForDigitsSum % 10;
        }
    }
    return result;
}

ComputeSumOfDigitsInAllNumbersFrom1ToN::Value ComputeSumOfDigitsInAllNumbersFrom1ToN::getValueUsingMemoizationDP()
    const {
    return getValueUsingMemoizationDP(m_lastNumber);
}

ComputeSumOfDigitsInAllNumbersFrom1ToN::Value ComputeSumOfDigitsInAllNumbersFrom1ToN::getValueUsingSummationValues()
    const {
    // Time Complexity: O(numberOfDigits)
    // Auxiliary Space: Constant

    Value result(0);
    Value digitIndex = 0;
    Value previousPowerOf10 = 0;
    Value powerOf10 = 1;
    Value previousDigits = 0;
    for (Value numberForDigitsSum = m_lastNumber; numberForDigitsSum > 0;
         numberForDigitsSum /= 10, digitIndex++, previousPowerOf10 = powerOf10, powerOf10 *= 10) {
        Value digitValue = numberForDigitsSum % 10;
        Value sumAtDigit = getSummationFrom1ToN(digitValue - 1) * powerOf10 + digitValue * (previousDigits + 1);
        Value numberOf0To9 = digitIndex * previousPowerOf10;
        Value sumAtLessSignificantDigits = digitValue * numberOf0To9 * getSummationFrom1ToN(9);

        result += sumAtDigit + sumAtLessSignificantDigits;
        previousDigits += digitValue * powerOf10;
    }
    return result;
}

ComputeSumOfDigitsInAllNumbersFrom1ToN::Value ComputeSumOfDigitsInAllNumbersFrom1ToN::getValueUsingMemoizationDP(
    Value const number) const {
    // Time Complexity: Even though there are recursion calls the time complexity is O(numberOfDigits)
    // Auxiliary Space: O(numberOfDigits^2)

    Value result(0);
    if (number < 10) {
        result = getSummationFrom1ToN(number);
    } else {
        Value numberOfDigitsMinus1 = getLogarithmForIntegers(10U, number);

        Values sumAtDigitIndex(numberOfDigitsMinus1 + 1);
        // sumAtDigitIndex[0]=0;
        // sumAtDigitIndex[1]=sum of digit from 1 to 9 = 45
        // sumAtDigitIndex[2]=sum of digit from 1 to 99 = a[1]*10 + 45*10^1 = 900
        // sumAtDigitIndex[3]=sum of digit from 1 to 999 = a[2]*10 + 45*10^2 = 13500

        sumAtDigitIndex[0] = 0;
        sumAtDigitIndex[1] = 45;
        for (Value digitIndex = 2; digitIndex <= numberOfDigitsMinus1; digitIndex++) {
            sumAtDigitIndex[digitIndex] =
                10 * sumAtDigitIndex.at(digitIndex - 1) + 45 * getRaiseToPowerForIntegers(10U, digitIndex - 1);
        }

        Value highestPowerOf10 = getRaiseToPowerForIntegers(10U, numberOfDigitsMinus1);
        Value mostSignificantDigit = number / highestPowerOf10;
        Value remainingDigits = number % highestPowerOf10;

        result = mostSignificantDigit * sumAtDigitIndex.at(numberOfDigitsMinus1) +
                 mostSignificantDigit * (mostSignificantDigit - 1) / 2 * highestPowerOf10 +
                 mostSignificantDigit * (1 + remainingDigits) + getValueUsingMemoizationDP(remainingDigits);
    }
    return result;
}

ComputeSumOfDigitsInAllNumbersFrom1ToN::Value ComputeSumOfDigitsInAllNumbersFrom1ToN::getSummationFrom1ToN(
    Value const number) const {
    return number * (number + 1) / 2;
}

}  // namespace alba
