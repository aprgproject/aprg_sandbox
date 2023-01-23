#include "LongestCommonSubsequence.hpp"

using namespace std;

namespace alba
{

LongestCommonSubsequence::LongestCommonSubsequence(Sequence const& sequence1, Sequence const& sequence2)
    : m_sequence1(sequence1)
    , m_sequence2(sequence2)
{}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingNaiveRecursion() const
{
    return getLongestLengthUsingNaiveRecursion(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingMemoizationDP() const
{
    CountMatrix lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U, static_cast<Count>(UNUSED_COUNT));
    for(Index index1=1; index1<lengthMatrix.getNumberOfColumns(); index1++)    {
        lengthMatrix.setEntry(index1, 0, 0);
    }
    for(Index index2=1; index2<lengthMatrix.getNumberOfColumns(); index2++)    {
        lengthMatrix.setEntry(0, index2, 0);
    }

    return getLongestLengthUsingMemoizationDP(lengthMatrix, m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingTabularDP() const
{
    CountMatrix lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U, 0U);
    for(Index index1=1; index1<lengthMatrix.getNumberOfColumns(); index1++)
    {
        for(Index index2=1; index2<lengthMatrix.getNumberOfRows(); index2++)
        {
            Count entryResult(0);
            if(m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
            {
                entryResult = 1 + lengthMatrix.getEntryConstReference(index1-1, index2-1);
            }
            else
            {
                entryResult = max(lengthMatrix.getEntryConstReference(index1-1, index2),
                                  lengthMatrix.getEntryConstReference(index1, index2-1));

            }
            lengthMatrix.setEntry(index1, index2, entryResult);
        }
    }
    return lengthMatrix.getEntry(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingTabularDPAndSpaceEfficient() const
{
    // Note this is same implementation in AlbaStringHelper
    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m)
    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one column or one row above,
    // we only really need 2 rows (not a matrix) to keep track partial values.

    // current and previous are the rows in the dynamic programming solution
    vector<Counts> previousAndCurrentCounts(2, Counts(m_sequence1.size()+1, 0U)); // set first row to zero
    for(Index index2=1; index2<=m_sequence2.size(); index2++)
    {
        Counts & previousCounts(previousAndCurrentCounts[index2%2]);
        Counts & currentCounts(previousAndCurrentCounts[(index2+1)%2]);

        for (Index index1=1; index1<=m_sequence1.size(); index1++)
        {
            if(m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
            {
                currentCounts[index1] = previousCounts.at(index1-1)+1;
            }
            else
            {
                currentCounts[index1] = max(currentCounts.at(index1-1), previousCounts.at(index1));
            }
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts.at((m_sequence1.size()+1)%2));
    return lastCurrent.back();
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingNaiveRecursion(
        Index const index1,
        Index const index2) const
{
    if(index1==0 || index2==0)
    {
        return 0;
    }
    else if(m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
    {
        return 1 + getLongestLengthUsingNaiveRecursion(index1-1, index2-1);
    }
    else
    {
        return max(getLongestLengthUsingNaiveRecursion(index1, index2-1),
                   getLongestLengthUsingNaiveRecursion(index1-1, index2));
    }
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestLengthUsingMemoizationDP(
        CountMatrix & lengthMatrix,
        Index const index1,
        Index const index2) const
{
    Count result(lengthMatrix.getEntry(index1, index2));
    if(UNUSED_COUNT == result)
    {
        result = 0;
        if(index1 > 0 && index2 > 0)
        {
            if(m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
            {
                result = 1 + getLongestLengthUsingMemoizationDP(lengthMatrix, index1-1, index2-1);
            }
            else
            {
                result = max(getLongestLengthUsingMemoizationDP(lengthMatrix, index1, index2-1),
                             getLongestLengthUsingMemoizationDP(lengthMatrix, index1-1, index2));
            }
        }
        lengthMatrix.setEntry(index1, index2, result);
    }    return result;
}

}