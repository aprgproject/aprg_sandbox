#include "LongestCommonSubstring.hpp"

#include <numeric>

using namespace std;

namespace alba {

LongestCommonSubstring::LongestCommonSubstring(string const& string1, string const& string2)
    : m_string1(string1), m_string2(string2) {}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingNaiveRecursion() const {
    Index maxLength = 0;
    for (Index index2 = 0; index2 < static_cast<int>(m_string2.length()); index2++) {
        for (Index index1 = 0; index1 < static_cast<int>(m_string1.length()); index1++) {
            if (m_string1[index1] == m_string2[index2]) {
                Index length = getLongestCommonSubstringLengthUsingNaiveRecursion(index1, index2);
                maxLength = max(maxLength, length);
            }
        }
    }
    return maxLength;
}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingMemoizationDP() const {
    Index maxLength = 0;
    CountGrid lengthGrid(m_string1.length(), m_string2.length(), UNUSED_INDEX);
    for (Index index2 = 0; index2 < static_cast<int>(m_string2.length()); index2++) {
        for (Index index1 = 0; index1 < static_cast<int>(m_string1.length()); index1++) {
            if (m_string1[index1] == m_string2[index2]) {
                Index length = getLongestCommonSubstringLengthUsingMemoizationDP(lengthGrid, index1, index2);
                maxLength = max(maxLength, length);
            }
        }
    }
    return maxLength;
}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingIterativeDP() const {
    Index maxLength = 0;
    CountGrid lengthGrid(m_string1.length(), m_string2.length(), 0);
    for (Index index2 = 0; index2 < static_cast<int>(m_string2.length()); index2++) {
        for (Index index1 = 0; index1 < static_cast<int>(m_string1.length()); index1++) {
            if (m_string1[index1] == m_string2[index2]) {
                Index length = 0;
                if (index1 == 0 || index2 == 0) {
                    length = 1;
                } else {
                    length = 1 + lengthGrid.getEntry(index1 - 1, index2 - 1);
                }
                lengthGrid.setEntry(index1, index2, length);
                maxLength = max(maxLength, length);
            }
        }
    }
    return maxLength;
}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingIterativeDPAndSpaceEfficient()
    const {
    Index maxLength = 0;
    Counts previousLengths(m_string1.length(), 0);
    for (Index index2 = 0; index2 < static_cast<int>(m_string2.length()); index2++) {
        for (Index index1 = static_cast<int>(m_string1.length()) - 1; index1 >= 0; index1--) {
            if (m_string1[index1] == m_string2[index2]) {
                Index length = 0;
                if (index1 == 0 || index2 == 0) {
                    length = 1;
                } else {
                    length = 1 + previousLengths[index1 - 1];
                }
                previousLengths[index1] = length;
                maxLength = max(maxLength, length);
            } else {
                previousLengths[index1] = 0;
            }
        }
    }
    return maxLength;
}

string LongestCommonSubstring::getLongestCommonSubstringUsingIterativeDPAndSpaceEfficient() const {
    Index maxLength = 0;
    Index endIndexWithMaxLength = 0;
    Counts previousLengths(m_string1.length(), 0);
    for (Index index2 = 0; index2 < static_cast<int>(m_string2.length()); index2++) {
        for (Index index1 = static_cast<int>(m_string1.length()) - 1; index1 >= 0; index1--) {
            if (m_string1[index1] == m_string2[index2]) {
                Index length = 0;
                if (index1 == 0 || index2 == 0) {
                    length = 1;
                } else {
                    length = 1 + previousLengths[index1 - 1];
                }
                previousLengths[index1] = length;
                if (maxLength < length) {
                    maxLength = length;
                    endIndexWithMaxLength = index1;
                }
            } else {
                previousLengths[index1] = 0;
            }
        }
    }
    return string(
        m_string1.cbegin() + endIndexWithMaxLength - maxLength + 1, m_string1.cbegin() + endIndexWithMaxLength + 1);
}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingNaiveRecursion(
    Index const index1, Index const index2) const {
    Index result = 0;
    if (m_string1[index1] == m_string2[index2]) {
        if (index1 == 0 || index2 == 0) {
            result = 1;
        } else {
            result = 1 + getLongestCommonSubstringLengthUsingNaiveRecursion(index1 - 1, index2 - 1);
        }
    }
    return result;
}

LongestCommonSubstring::Count LongestCommonSubstring::getLongestCommonSubstringLengthUsingMemoizationDP(
    CountGrid& lengthGrid, Index const index1, Index const index2) const {
    // Time Complexity: O(m x n) because of memoization
    // Auxiliary Space: O(m x n)

    Index result = lengthGrid.getEntry(index1, index2);
    if (UNUSED_INDEX == result) {
        result = 0;
        if (m_string1[index1] == m_string2[index2]) {
            if (index1 == 0 || index2 == 0) {
                result = 1;
            } else {
                result = 1 + getLongestCommonSubstringLengthUsingNaiveRecursion(index1 - 1, index2 - 1);
            }
        }
        lengthGrid.setEntry(index1, index2, result);
    }
    return result;
}

}  // namespace alba
