#include "ShortestCommonSupersequence.hpp"

using namespace std;

namespace alba {

ShortestCommonSupersequence::ShortestCommonSupersequence(Values const& sequence1, Values const& sequence2)
    : m_sequence1(sequence1), m_sequence2(sequence2) {}

ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingNaiveRecursion() const {
    // Time Complexity: Exponential -> Since there are (m x n) calls per iteration:  O(2^(m x n))
    // Auxiliary Space: Constant

    return getShortestLengthUsingNaiveRecursion(m_sequence1.size(), m_sequence2.size());
}

ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingMemoizationDP() const {
    // Time Complexity: Exponential -> Since there are (m x n) calls per iteration:  O(2^(m x n))
    // Auxiliary Space: O(m x n)

    CountMatrix lengthMatrix(m_sequence1.size() + 1, m_sequence2.size() + 1, static_cast<Count>(UNUSED_COUNT));

    lengthMatrix.setEntry(0, 0, 0);
    for (Index index1 = 1; index1 < static_cast<Index>(lengthMatrix.getNumberOfColumns()); index1++) {
        lengthMatrix.setEntry(index1, 0, index1);
    }
    for (Index index2 = 1; index2 < static_cast<Index>(lengthMatrix.getNumberOfRows()); index2++) {
        lengthMatrix.setEntry(0, index2, index2);
    }
    return getShortestLengthUsingMemoizationDP(lengthMatrix, m_sequence1.size(), m_sequence2.size());
}

ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingIterativeDP() const {
    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m x n)

    CountMatrix lengthMatrix(m_sequence1.size() + 1, m_sequence2.size() + 1, 0);

    for (Index index1 = 1; index1 < static_cast<Index>(lengthMatrix.getNumberOfColumns()); index1++) {
        lengthMatrix.setEntry(index1, 0, index1);
    }
    for (Index index2 = 1; index2 < static_cast<Index>(lengthMatrix.getNumberOfRows()); index2++) {
        lengthMatrix.setEntry(0, index2, index2);
    }
    for (Index index1 = 1; index1 < static_cast<Index>(lengthMatrix.getNumberOfColumns()); index1++) {
        for (Index index2 = 1; index2 < static_cast<Index>(lengthMatrix.getNumberOfRows()); index2++) {
            Count entryResult(0);
            if (m_sequence1[index1 - 1] == m_sequence2[index2 - 1]) {
                entryResult = 1 + lengthMatrix.getEntry(index1 - 1, index2 - 1);
            } else {
                entryResult =                    1 + min(lengthMatrix.getEntry(index1 - 1, index2), lengthMatrix.getEntry(index1, index2 - 1));
            }
            lengthMatrix.setEntry(index1, index2, entryResult);
        }    }
    return lengthMatrix.getEntry(m_sequence1.size(), m_sequence2.size());
}

ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingIterativeDPAndSpaceEfficient()
    const {
    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m)

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one column or one row above,
    // we only really need 2 rows (not a matrix) to keep track partial values.

    // current and previous are the rows in the dynamic programming solution
    vector<Counts> previousAndCurrentCounts(2, Counts(m_sequence1.size() + 1, 0));  // set first row to zero

    {
        Counts& currentCounts(previousAndCurrentCounts[1]);
        for (Index index1 = 0; index1 <= static_cast<Index>(m_sequence1.size()); index1++) {
            currentCounts[index1] = index1;
        }
    }
    for (Index index2 = 1; index2 <= static_cast<Index>(m_sequence2.size()); index2++) {
        Counts& previousCounts(previousAndCurrentCounts[index2 % 2]);
        Counts& currentCounts(previousAndCurrentCounts[(index2 + 1) % 2]);

        currentCounts[0] = index2;
        for (Index index1 = 1; index1 <= static_cast<Index>(m_sequence1.size()); index1++) {
            if (m_sequence1[index1 - 1] == m_sequence2[index2 - 1]) {
                currentCounts[index1] = 1 + previousCounts[index1 - 1];
            } else {
                currentCounts[index1] = 1 + min(currentCounts[index1 - 1], previousCounts[index1]);
            }
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts[(m_sequence2.size() + 1) % 2]);
    return lastCurrent.back();
}
ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingNaiveRecursion(
    Index const index1, Index const index2) const {
    if (index1 == 0) {
        return index2;
    } else if (index2 == 0) {
        return index1;
    } else if (m_sequence1[index1 - 1] == m_sequence2[index2 - 1]) {
        return 1 + getShortestLengthUsingNaiveRecursion(index1 - 1, index2 - 1);
    } else {
        return 1 + min(getShortestLengthUsingNaiveRecursion(index1, index2 - 1),                       getShortestLengthUsingNaiveRecursion(index1 - 1, index2));
    }
}
ShortestCommonSupersequence::Count ShortestCommonSupersequence::getShortestLengthUsingMemoizationDP(
    CountMatrix& lengthMatrix, Index const index1, Index const index2) const {
    Count result(lengthMatrix.getEntry(index1, index2));
    if (UNUSED_COUNT == result) {
        if (index1 == 0) {
            result = index2;
        } else if (index2 == 0) {
            result = index1;
        } else if (m_sequence1[index1 - 1] == m_sequence2[index2 - 1]) {
            result = 1 + getShortestLengthUsingMemoizationDP(lengthMatrix, index1 - 1, index2 - 1);
        } else {
            result = 1 + min(getShortestLengthUsingMemoizationDP(lengthMatrix, index1, index2 - 1),                             getShortestLengthUsingMemoizationDP(lengthMatrix, index1 - 1, index2));
        }
        lengthMatrix.setEntry(index1, index2, result);
    }    return result;
}

}  // namespace alba
