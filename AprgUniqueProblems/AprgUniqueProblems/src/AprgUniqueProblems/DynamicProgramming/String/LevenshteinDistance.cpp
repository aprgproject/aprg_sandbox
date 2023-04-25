#include "LevenshteinDistance.hpp"

#include <numeric>

using namespace std;

namespace alba {

LevenshteinDistance::LevenshteinDistance(string const& string1, string const& string2)
    : m_string1(string1), m_string2(string2) {}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingNaiveRecursion() const {
    // The time complexity of above solution is exponential.
    // In worst case, we may end up doing O(3m) operations.
    // The worst case happens when none of characters of two strings match.

    return getLevenshteinDistanceUsingNaiveRecursion(m_string1.length(), m_string2.length());
}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingMemoizationDP() const {
    CountGrid indexGrid(m_string1.length() + 1, m_string2.length() + 1, UNUSED_INDEX);
    return getLevenshteinDistanceUsingMemoizationDP(indexGrid, m_string1.length(), m_string2.length());
}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingIterativeDP() const {
    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m x n)

    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)
    // We can calculate values of distance as follows:
    // -> distance(a,b) = min(distance(a,b-1)+1,
    //                     distance(a-1,b)+1,
    //                     distance(a-1,b-1)+cost(a,b)).
    // -> Here cost(a,b) = 0 if x[a] == y[b], and otherwise cost(a,b) == 1.
    // Operation positioning in the grid:
    // ---------------------
    // | replace | insert  |
    // ---------------------
    // | delete  | current |
    // ---------------------
    // Note that first column is for null string and first row is for null string (thats why there is a plus one in
    // column/row size)

    CountGrid indexGrid(m_string1.length() + 1, m_string2.length() + 1);
    indexGrid.iterateAllThroughYAndThenX([&](Index const x, Index const y) {
        Count entryResult(0);
        if (x == 0) {
            entryResult = y;
        } else if (y == 0) {
            entryResult = x;
        } else if (m_string1.at(x - 1) == m_string2.at(y - 1)) {
            entryResult = indexGrid.getEntry(x - 1, y - 1);
        } else {
            Index replaceDistance = indexGrid.getEntry(x - 1, y - 1);
            Index deleteDistance = indexGrid.getEntry(x - 1, y);
            Index insertDistance = indexGrid.getEntry(x, y - 1);
            entryResult = min(min(replaceDistance, deleteDistance), insertDistance) + 1;
        }
        indexGrid.setEntry(x, y, entryResult);
    });

    return indexGrid.getEntry(indexGrid.getNumberOfColumns() - 1, indexGrid.getNumberOfRows() - 1);
}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingIterativeDPAndSpaceEfficient() const {
    // Note this is same implementation in AlbaStringHelper

    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m)

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one column or one row above,
    // we only really need 2 rows (not a matrix) to keep track partial values.

    // Space Complex Solution:
    // In the other solution we require O(m x n) space.
    // This will not be suitable if the length of strings is greater than 2000 as it can only create 2D array of 2000 x
    // 2000. To fill a row in DP array we require only one row the upper row. For example, if we are filling the i = 10
    // rows in DP array we require only values of 9th row. So we simply create a DP array of 2 x str1 length. This
    // approach reduces the space complexity.

    // current and previous are the rows in the dynamic programming solution
    vector<Counts> previousAndCurrentCounts(2, Counts(m_string1.length() + 1));  // string1 as basis
    Counts& firstPrevious(previousAndCurrentCounts[0]);
    iota(firstPrevious.begin(), firstPrevious.end(), 0);  // first row

    for (Index index2 = 1; index2 <= m_string2.length(); index2++) {
        Counts& previousCounts(previousAndCurrentCounts[(index2 - 1) % 2]);
        Counts& currentCounts(previousAndCurrentCounts[index2 % 2]);

        currentCounts[0] = index2;  // first column
        for (Index index1 = 1; index1 <= m_string1.length(); index1++) {
            unsigned int cost = m_string1.at(index1 - 1) == m_string2.at(index2 - 1) ? 0 : 1;
            currentCounts[index1] =
                min(min(currentCounts.at(index1 - 1) + 1, previousCounts.at(index1) + 1),
                    previousCounts.at(index1 - 1) + cost);
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts.at(m_string2.length() % 2));
    return lastCurrent.back();
}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingNaiveRecursion(
    Index const index1, Index const index2) const {
    if (index1 == 0) {
        return index2;
    } else if (index2 == 0) {
        return index1;
    } else if (m_string1.at(index1 - 1) == m_string2.at(index2 - 1)) {
        return getLevenshteinDistanceUsingNaiveRecursion(index1 - 1, index2 - 1);
    } else {
        Index replaceDistance = getLevenshteinDistanceUsingNaiveRecursion(index1 - 1, index2 - 1);
        Index deleteDistance = getLevenshteinDistanceUsingNaiveRecursion(index1 - 1, index2);
        Index insertDistance = getLevenshteinDistanceUsingNaiveRecursion(index1, index2 - 1);
        return min(min(replaceDistance, deleteDistance), insertDistance) + 1;
    }
}

LevenshteinDistance::Count LevenshteinDistance::getLevenshteinDistanceUsingMemoizationDP(
    CountGrid& indexGrid, Index const index1, Index const index2) const {
    // Time Complexity: O(m x n) because of memoization
    // Auxiliary Space: O(m x n)

    Index result = indexGrid.getEntry(index1, index2);
    if (UNUSED_INDEX == result) {
        if (index1 == 0) {
            result = index2;
        } else if (index2 == 0) {
            result = index1;
        } else if (m_string1.at(index1 - 1) == m_string2.at(index2 - 1)) {
            result = getLevenshteinDistanceUsingMemoizationDP(indexGrid, index1 - 1, index2 - 1);
        } else {
            Index replaceDistance = getLevenshteinDistanceUsingMemoizationDP(indexGrid, index1 - 1, index2 - 1);
            Index deleteDistance = getLevenshteinDistanceUsingMemoizationDP(indexGrid, index1 - 1, index2);
            Index insertDistance = getLevenshteinDistanceUsingMemoizationDP(indexGrid, index1, index2 - 1);
            result = min(min(replaceDistance, deleteDistance), insertDistance) + 1;
        }
        indexGrid.setEntry(index1, index2, result);
    }
    return result;
}

}  // namespace alba
