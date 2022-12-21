#include "LevenshteinDistance.hpp"

using namespace std;

namespace alba
{

LevenshteinDistance::LevenshteinDistance(string const& string1, string const& string2)
    : m_string1(string1)
    , m_string2(string2)
{}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingRecursion() const
{
    // The time complexity of above solution is exponential.
    // In worst case, we may end up doing O(3m) operations.
    // The worst case happens when none of characters of two strings match.

    return getLevenshteinDistanceUsingRecursion(m_string1.length(), m_string2.length());
}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingTabularDP() const
{
    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m x n)

    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)    // -> modify a character (e.g. ABC ! ADC)
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
    // Note that first column is for null string and first row is for null string (thats why there is a plus one in column/row size)

    IndexGrid indexGrid(m_string1.length()+1, m_string2.length()+1);
    indexGrid.iterateAllThroughYAndThenX([&](Index const x, Index const y)
    {
        if(x==0)
        {
            indexGrid.setEntry(x, y, y);
        }
        else if(y==0)
        {
            indexGrid.setEntry(x, y, x);
        }
        else if(m_string1.at(x-1) ==  m_string2.at(y-1))
        {
            indexGrid.setEntry(x, y, indexGrid.getEntry(x-1, y-1));
        }
        else
        {
            Index replaceDistance = indexGrid.getEntry(x-1, y-1);
            Index deleteDistance = indexGrid.getEntry(x-1, y);
            Index insertDistance = indexGrid.getEntry(x, y-1);
            indexGrid.setEntry(x, y, min(min(replaceDistance, deleteDistance), insertDistance)+1);
        }
    });

    return indexGrid.getEntry(indexGrid.getNumberOfColumns()-1, indexGrid.getNumberOfRows()-1);
}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingEfficientSpaceDP() const
{
    // Note this is same implementation in AlbaStringHelper

    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m)

    // Space Complex Solution:
    // In the other solution we require O(m x n) space.
    // This will not be suitable if the length of strings is greater than 2000 as it can only create 2D array of 2000 x 2000.
    // To fill a row in DP array we require only one row the upper row.
    // For example, if we are filling the i = 10 rows in DP array we require only values of 9th row.
    // So we simply create a DP array of 2 x str1 length.
    // This approach reduces the space complexity.

    string otherString(m_string1), basisString(m_string2); // use string2 as basis
    Indices current(basisString.length() + 1);
    Indices previous(basisString.length() + 1);
    iota(previous.begin(), previous.end(), 0);

    // current and previous are the rows in the dynamic programming solution
    for(Index otherIndex=0; otherIndex<otherString.length(); ++otherIndex)
    {
        current[0] = otherIndex+1;
        for (unsigned int basisIndex=0; basisIndex<basisString.length(); ++basisIndex)
        {
            // next value is the minimum of
            // 1) index-1 in current // remove operation
            // 2) index in previous // insert operation
            // 2) index-1 in previous // modify operation (if characters are different)
            unsigned int cost = otherString.at(otherIndex)==basisString.at(basisIndex) ? 0 : 1;
            current[basisIndex+1] = min(min(current.at(basisIndex)+1, previous.at(basisIndex+1)+1), previous.at(basisIndex)+cost);
        }
        current.swap(previous);
    }
    return previous.at(basisString.length());
}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingMemoizationDP() const
{
    IndexGrid indexGrid(m_string1.length()+1, m_string2.length()+1, UNUSED_INDEX);
    return getLevenshteinDistanceUsingMemoizationDP(indexGrid, m_string1.length(), m_string2.length());
}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingRecursion(        Index const index1,
        Index const index2) const
{
    if (index1==0)
    {
        return index2;
    }
    else if (index2==0)
    {
        return index1;
    }
    else if (m_string1.at(index1-1) == m_string2.at(index2-1))
    {
        return getLevenshteinDistanceUsingRecursion(index1-1, index2-1);
    }
    else
    {
        Index replaceDistance = getLevenshteinDistanceUsingRecursion(index1-1, index2-1);
        Index deleteDistance = getLevenshteinDistanceUsingRecursion(index1-1, index2);
        Index insertDistance = getLevenshteinDistanceUsingRecursion(index1, index2-1);
        return min(min(replaceDistance, deleteDistance), insertDistance)+1;
    }
}

LevenshteinDistance::Index LevenshteinDistance::getLevenshteinDistanceUsingMemoizationDP(
        IndexGrid & indexGrid,
        Index const index1,
        Index const index2) const{
    // Time Complexity: O(m x n) because of memoization
    // Auxiliary Space: O(m x n)

    Index result = indexGrid.getEntryConstReference(index1, index2);
    if(UNUSED_INDEX == result)
    {
        if (index1==0)
        {
            result = index2;
        }
        else if (index2==0)
        {
            result = index1;
        }
        else if (m_string1.at(index1-1) == m_string2.at(index2-1))
        {
            result = getLevenshteinDistanceUsingRecursion(index1-1, index2-1);
        }
        else
        {
            Index replaceDistance = getLevenshteinDistanceUsingRecursion(index1-1, index2-1);
            Index deleteDistance = getLevenshteinDistanceUsingRecursion(index1-1, index2);
            Index insertDistance = getLevenshteinDistanceUsingRecursion(index1, index2-1);
            result = min(min(replaceDistance, deleteDistance), insertDistance)+1;
        }
        indexGrid.setEntry(index1, index2, result);
    }
    return result;
}


}