#include "TotalNumberOfNonDecreasingNumbersWithNDigits.hpp"

#include <numeric>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

TotalNumberOfNonDecreasingNumbersWithNDigits::TotalNumberOfNonDecreasingNumbersWithNDigits(Count const numberOfDigits)
    : m_numberOfDigits(numberOfDigits) {}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingNaiveRecursion() const {
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    Count result(0);
    if (m_numberOfDigits > 0) {
        for (Value digitValue = 0; digitValue <= 9; digitValue++) {
            result += getCountUsingNaiveRecursion(digitValue, m_numberOfDigits - 1);
        }
    }
    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingMemoizationDP() const {
    // Time Complexity: O(numberOfDigits) (same as iterative)
    // Auxiliary Space: O(numberOfDigits)

    Count result(0);
    if (m_numberOfDigits > 0) {
        CountMatrix countMatrix(10, m_numberOfDigits, UNUSED_COUNT);
        for (Value digitValue = 0; digitValue <= 9; digitValue++) {
            result += getCountUsingMemoizationDP(countMatrix, digitValue, m_numberOfDigits - 1);
        }
    }
    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingIterativeDP() const {
    // Time Complexity: O(numberOfDigits)
    // Auxiliary Space: O(numberOfDigits)

    Count result(0);
    if (m_numberOfDigits > 0) {
        CountMatrix countMatrix(10, m_numberOfDigits);
        for (Value digitValue = 0; digitValue <= 9; digitValue++) {
            countMatrix.setEntry(digitValue, 0, 1);
        }
        for (Count digitIndex = 1; digitIndex < m_numberOfDigits; digitIndex++) {
            for (Value digitValue = 0; digitValue <= 9; digitValue++) {
                Count entryResult(0);
                for (Value beforeDigitValue = 0; beforeDigitValue <= digitValue; beforeDigitValue++) {
                    entryResult += countMatrix.getEntry(beforeDigitValue, digitIndex - 1);
                }
                countMatrix.setEntry(digitValue, digitIndex, entryResult);
            }
        }

        for (Value digitValue = 0; digitValue <= 9; digitValue++) {
            result += countMatrix.getEntry(digitValue, m_numberOfDigits - 1);
        }
    }
    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingIterativeDPAndSpaceEfficient() const {
    // Time Complexity: O(numberOfDigits)
    // Auxiliary Space: O(1)

    Count result(0);
    if (m_numberOfDigits > 0) {
        Counts digitValueToCount(10, 1);
        for (Count digitIndex = 1; digitIndex < m_numberOfDigits; digitIndex++) {
            for (int digitValue = 9; digitValue >= 0; digitValue--) {
                Count entryResult(0);
                for (Value beforeDigitValue = 0; beforeDigitValue <= static_cast<Value>(digitValue);
                     beforeDigitValue++) {
                    entryResult += digitValueToCount[beforeDigitValue];
                }
                digitValueToCount[digitValue] = entryResult;
            }        }

        result = accumulate(digitValueToCount.cbegin(), digitValueToCount.cend(), 0);
    }    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingSummationFormula() const {
    // Using integration for finite calculus:
    // When length=1, then formula=1.
    // When length=2, then formula=(x+1).
    // When length=3, then formula=(x+1)*(x+2)/2.
    // When length=4, then formula=(x+1)*(x+2)*(x+3)/2/3.
    // Based from this, we can have this algorithm.

    Count result(0);
    if (m_numberOfDigits > 0) {
        result = 1;
        for (Count digitCount = 1; digitCount <= m_numberOfDigits; digitCount++) {
            result *= (9 + digitCount);
            result /= digitCount;
        }
    }
    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingNaiveRecursion(
    Value const digitValue, Count const digitIndex) const {
    Count result(0);
    if (digitIndex > 0) {
        for (Value beforeDigitValue = 0; beforeDigitValue <= digitValue; beforeDigitValue++) {
            result += getCountUsingNaiveRecursion(beforeDigitValue, digitIndex - 1);
        }
    } else {
        result = 1;
    }
    return result;
}

TotalNumberOfNonDecreasingNumbersWithNDigits::Count
TotalNumberOfNonDecreasingNumbersWithNDigits::getCountUsingMemoizationDP(
    CountMatrix& countMatrix, Value const digitValue, Count const digitIndex) const {
    Count result(countMatrix.getEntry(digitValue, digitIndex));
    if (UNUSED_COUNT == result) {
        if (digitIndex > 0) {
            result = 0;
            for (Value beforeDigitValue = 0; beforeDigitValue <= digitValue; beforeDigitValue++) {
                result += getCountUsingNaiveRecursion(beforeDigitValue, digitIndex - 1);
            }
        } else {
            result = 1;
        }
        countMatrix.setEntry(digitValue, digitIndex, result);
    }
    return result;
}

}  // namespace alba
