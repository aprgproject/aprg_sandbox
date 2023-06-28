#include "UglyNumbers.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

UglyNumbers::UglyNumbers(Number const nth) : m_nth(nth) {}

UglyNumbers::Number UglyNumbers::getNthUglyNumberByCheckingPreviousUglyNumbersUsingIterativeDP() const {
    // Time Complexity: O(n)
    // Auxiliary Space: O(n)
    // -> where n is the value of the ugly number

    Number result(0);
    if (m_nth > 0) {
        Booleans isUglyNumber{true};

        Number currentNumber = 1;
        for (Number count = 1; count < m_nth;) {
            currentNumber++;
            bool isCurrentNumberUgly = isDivisible(currentNumber, 2)   ? isUglyNumber[(currentNumber / 2) - 1]
                                       : isDivisible(currentNumber, 3) ? isUglyNumber[(currentNumber / 3) - 1]
                                       : isDivisible(currentNumber, 5) ? isUglyNumber[(currentNumber / 5) - 1]
                                                                       : false;
            isUglyNumber.emplace_back(isCurrentNumberUgly);
            count += isCurrentNumberUgly ? 1 : 0;
        }
        result = currentNumber;
    }
    return result;
}

UglyNumbers::Number UglyNumbers::getNthUglyNumberByMultiplesUsingIterativeDP() const {
    // Time Complexity: O(n)
    // Auxiliary Space: O(n)
    // -> where n is the value of the count of the ugly number

    Number result(0);
    if (m_nth > 0) {
        Numbers uglyNumbers{1};
        uglyNumbers.reserve(m_nth);

        Index indexFor2(0), indexFor3(0), indexFor5(0);
        Number next2Multiple(2), next3Multiple(3), next5Multiple(5);
        while (static_cast<Number>(uglyNumbers.size()) < m_nth) {
            Number nextUglyNumber = min(min(next2Multiple, next3Multiple), next5Multiple);
            uglyNumbers.emplace_back(nextUglyNumber);
            next2Multiple = (nextUglyNumber == next2Multiple) ? uglyNumbers[++indexFor2] * 2 : next2Multiple;
            next3Multiple = (nextUglyNumber == next3Multiple) ? uglyNumbers[++indexFor3] * 3 : next3Multiple;
            next5Multiple = (nextUglyNumber == next5Multiple) ? uglyNumbers[++indexFor5] * 5 : next5Multiple;
        }
        result = uglyNumbers.back();
    }
    return result;
}

}  // namespace alba
