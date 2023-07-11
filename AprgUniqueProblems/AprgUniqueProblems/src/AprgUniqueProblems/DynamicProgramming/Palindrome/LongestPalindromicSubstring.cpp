#include "LongestPalindromicSubstring.hpp"

using namespace std;

namespace alba {

LongestPalindromicSubstring::LongestPalindromicSubstring(string const& stringParameter) : m_string(stringParameter) {}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingNaiveRecursion() const {
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Index result(0);
    if (!m_string.empty()) {
        result = getLongestLengthUsingNaiveRecursion(0, m_string.length() - 1);
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingMemoizationDP() const {
    // Time Complexity: O(n^2) (should be same as Iterative DP)
    // Auxiliary Space: O(n^2)

    Index result(0);
    if (!m_string.empty()) {
        IndexMatrix lengthMatrix(m_string.length(), m_string.length(), static_cast<Index>(MAX_INDEX));
        result = getLongestLengthUsingMemoizationDP(lengthMatrix, 0, m_string.length() - 1);
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingIterativeDP() const {
    // Time complexity: O(n^2).
    // -> Two nested traversals are needed.
    // Auxiliary Space: O(n^2).
    // -> Matrix of size n*n is needed to store the dp array.

    Index result(0);
    if (!m_string.empty()) {
        result = 1;
        Index const stringLength = m_string.length();
        BoolMatrix isSubstrAPalindrome(stringLength, stringLength, false);

        for (Index index = 0; index < stringLength; index++)  // length = 1
        {
            isSubstrAPalindrome.setEntry(index, index, true);
        }
        for (Index index = 0; index + 1 < stringLength; index++)  // length = 2
        {
            if (m_string[index] == m_string[index + 1]) {
                isSubstrAPalindrome.setEntry(index, index + 1, true);
                result = 2;
            }
        }
        for (Index length = 3; length <= stringLength; length++)  // length >= 3
        {
            for (Index left = 0; left + length <= stringLength; left++) {
                Index right = left + length - 1;
                if (m_string[left] == m_string[right] && isSubstrAPalindrome.getEntry(left + 1, right - 1)) {
                    isSubstrAPalindrome.setEntry(left, right, true);
                    result = max(result, length);
                }
            }
        }
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingIterativeDPAndSpaceEfficient()
    const {
    // Time complexity: O(n^2).
    // Auxiliary Space: O(1).

    Index result(0);
    if (!m_string.empty()) {
        Index const stringLength = m_string.length();
        Index maxLength = 1;
        for (Index centerIndex = 0; centerIndex < stringLength; centerIndex++) {
            Index lowIndex = centerIndex - 1;
            Index highIndex = centerIndex + 1;
            while (highIndex < stringLength && m_string[highIndex] == m_string[centerIndex]) highIndex++;
            while (lowIndex >= 0 && m_string[lowIndex] == m_string[centerIndex]) lowIndex--;
            while (lowIndex >= 0 && highIndex < stringLength && m_string[lowIndex] == m_string[highIndex]) {
                lowIndex--;
                highIndex++;
            }
            maxLength = std::max(maxLength, highIndex - lowIndex - 1);
        }
        result = maxLength;
    }
    return result;
}

string LongestPalindromicSubstring::getLongestStringUsingIterativeDPAndSpaceEfficient() const {
    // Time complexity: O(n^2).
    // Auxiliary Space: O(1).

    if (!m_string.empty()) {
        Index const stringLength = m_string.length();
        Index maxLength = 1;
        Index startIndex = 0;
        for (Index centerIndex = 0; centerIndex < stringLength; centerIndex++) {
            Index lowIndex = centerIndex - 1;
            Index highIndex = centerIndex + 1;
            while (highIndex < stringLength && m_string[highIndex] == m_string[centerIndex]) highIndex++;
            while (lowIndex >= 0 && m_string[lowIndex] == m_string[centerIndex]) lowIndex--;
            while (lowIndex >= 0 && highIndex < stringLength && m_string[lowIndex] == m_string[highIndex]) {
                lowIndex--;
                highIndex++;
            }
            if (maxLength < highIndex - lowIndex - 1) {
                maxLength = highIndex - lowIndex - 1;
                startIndex = lowIndex + 1;
            }
        }
        return m_string.substr(startIndex, maxLength);
    }
    return m_string;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingNaiveRecursion(    Index const left, Index const right) const {
    Index result(0);
    Index length = right - left + 1;
    if (length == 1) {        result = 1;
    } else if (length == 2) {
        result = m_string[left] == m_string[right] ? 2 : 1;
    } else {
        bool isCompletePalindrome(false);
        if (m_string[left] == m_string[right]) {
            Index middleLength = getLongestLengthUsingNaiveRecursion(left + 1, right - 1);
            if (middleLength + 2 == length) {
                isCompletePalindrome = true;
                result = middleLength + 2;
            }
        }

        if (!isCompletePalindrome) {
            result =
                max(getLongestLengthUsingNaiveRecursion(left + 1, right),
                    getLongestLengthUsingNaiveRecursion(left, right - 1));
        }
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingMemoizationDP(
    IndexMatrix& lengthMatrix, Index const left, Index const right) const {
    Index result(lengthMatrix.getEntry(left, right));
    if (MAX_INDEX == result) {
        Index length = right - left + 1;
        if (length == 1) {
            result = 1;
        } else if (length == 2) {
            result = m_string[left] == m_string[right] ? 2 : 1;
        } else {
            bool isCompletePalindrome(false);
            if (m_string[left] == m_string[right]) {
                Index middleLength = getLongestLengthUsingNaiveRecursion(left + 1, right - 1);
                if (middleLength + 2 == length) {
                    isCompletePalindrome = true;
                    result = middleLength + 2;
                }
            }

            if (!isCompletePalindrome) {
                result =
                    max(getLongestLengthUsingMemoizationDP(lengthMatrix, left + 1, right),
                        getLongestLengthUsingMemoizationDP(lengthMatrix, left, right - 1));
            }
        }
        lengthMatrix.setEntry(left, right, result);
    }
    return result;
}

}  // namespace alba
