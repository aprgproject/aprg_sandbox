#include "LongestPalindromicSubsequence.hpp"

using namespace std;

namespace alba {

LongestPalindromicSubsequence::LongestPalindromicSubsequence(string const& stringParameter)
    : m_string(stringParameter) {}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingNaiveRecursion() const {
    Count result(0);
    if (!m_string.empty()) {
        result = getLongestLengthUsingNaiveRecursion(0, m_string.length() - 1);
    }
    return result;
}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingMemoizationDP() const {
    Count result(0);
    if (!m_string.empty()) {
        CountMatrix lengthMatrix(m_string.length(), m_string.length(), static_cast<Count>(UNUSED_COUNT));
        result = getLongestLengthUsingMemoizationDP(lengthMatrix, 0, m_string.length() - 1);
    }
    return result;
}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingIterativeDP() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if (!m_string.empty()) {
        Index stringLength = m_string.length();
        CountMatrix lengthMatrix(stringLength, stringLength, 0);

        for (Index index2 = 0; index2 < stringLength; index2++) {
            lengthMatrix.setEntry(index2, index2, 1);
            for (int index1 = static_cast<int>(index2) - 1; index1 >= 0;
                 index1--)  // reverse traversal to get previous values
            {
                Count entryResult(0);
                if (m_string.at(index1) == m_string.at(index2)) {
                    entryResult = 2 + lengthMatrix.getEntry(index1 + 1, index2 - 1);
                } else {
                    entryResult =
                        max(lengthMatrix.getEntry(index1, index2 - 1), lengthMatrix.getEntry(index1 + 1, index2));
                }
                lengthMatrix.setEntry(index1, index2, entryResult);
            }
        }
        result = lengthMatrix.getEntry(0, stringLength - 1);
    }
    return result;
}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingIterativeDPAndSpaceEfficient()
    const {
    // Note this is same implementation in AlbaStringHelper

    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one column or one row above,
    // we only really need 2 rows (not a matrix) to keep track partial values.

    // current and previous are the rows in the dynamic programming solution
    Index stringLength = m_string.length();
    vector<Counts> previousAndCurrentCounts(2, Counts(stringLength, 0));  // set first row to zero
    for (Index index2 = 0; index2 < stringLength; index2++) {
        Counts& previousCounts(previousAndCurrentCounts[index2 % 2]);
        Counts& currentCounts(previousAndCurrentCounts[(index2 + 1) % 2]);

        currentCounts[index2] = 1;
        for (int index1 = static_cast<int>(index2) - 1; index1 >= 0;
             index1--)  // reverse traversal to get previous values
        {
            if (m_string.at(index1) == m_string.at(index2)) {
                currentCounts[index1] = 2 + previousCounts.at(index1 + 1);
            } else {
                currentCounts[index1] = max(previousCounts.at(index1), currentCounts.at(index1 + 1));
            }
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts.at(stringLength % 2));
    return lastCurrent.front();
}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingNaiveRecursion(
    Index const index1, Index const index2) const {
    Count result(0);
    if (index1 == index2) {
        result = 1;  // one character is considered a palindrome
    } else if (index1 < index2) {
        if (m_string.at(index1) == m_string.at(index2)) {
            result = 2 + getLongestLengthUsingNaiveRecursion(index1 + 1, index2 - 1);
        } else {
            result =
                max(getLongestLengthUsingNaiveRecursion(index1, index2 - 1),
                    getLongestLengthUsingNaiveRecursion(index1 + 1, index2));
        }
    }
    return result;
}

LongestPalindromicSubsequence::Count LongestPalindromicSubsequence::getLongestLengthUsingMemoizationDP(
    CountMatrix& lengthMatrix, Index const index1, Index const index2) const {
    Count result(lengthMatrix.getEntry(index1, index2));
    if (UNUSED_COUNT == result) {
        result = 0;
        if (index1 == index2) {
            result = 1;  // one character is considered a palindrome
        } else if (index1 < index2) {
            if (m_string.at(index1) == m_string.at(index2)) {
                result = 2 + getLongestLengthUsingNaiveRecursion(index1 + 1, index2 - 1);
            } else {
                result =
                    max(getLongestLengthUsingNaiveRecursion(index1, index2 - 1),
                        getLongestLengthUsingNaiveRecursion(index1 + 1, index2));
            }
        }
        lengthMatrix.setEntry(index1, index2, result);
    }
    return result;
}

}  // namespace alba
