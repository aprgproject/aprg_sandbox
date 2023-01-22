#include "LongestCommonSubsequence.hpp"

using namespace std;

namespace alba
{

LongestCommonSubsequence::LongestCommonSubsequence(Sequence const& sequence1, Sequence const& sequence2)
    : m_sequence1(sequence1)
    , m_sequence2(sequence2)
{}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingNaiveRecursion() const
{
    return getLongestCommonSubsequenceLengthUsingNaiveRecursion(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingTabularDP() const
{
    CountMatrix lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U, 0U);

    for(Index index1=1; index1<lengthMatrix.getNumberOfColumns(); index1++)
    {
        for(Index index2=1; index2<lengthMatrix.getNumberOfRows(); index2++)
        {
            if (m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
            {
                lengthMatrix.setEntry(index1, index2, lengthMatrix.getEntryConstReference(index1-1, index2-1)+1);
            }
            else
            {
                lengthMatrix.setEntry(
                            index1, index2,
                            max(lengthMatrix.getEntryConstReference(index1-1, index2),
                                lengthMatrix.getEntryConstReference(index1, index2-1)));
            }
        }
    }
    return lengthMatrix.getEntry(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingTabularDPAndSpaceEfficient() const
{
    // Note this is same implementation in AlbaStringHelper

    // Time Complexity: O(m x n)
    // Auxiliary Space: O(m)

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one column or one row above,
    // we only really need 2 rows (not a matrix) to keep track partial values.

    // current and previous are the rows in the dynamic programming solution
    vector<Counts> previousAndCurrentCounts(2, Counts(m_sequence1.size()+1, 0U)); // set first row to zero
    for(Index index2Minus1=0; index2Minus1<m_sequence2.size(); ++index2Minus1)
    {
        Counts & previousCounts(previousAndCurrentCounts[index2Minus1%2]);
        Counts & currentCounts(previousAndCurrentCounts[(index2Minus1+1)%2]);

        for (Index index1Minus1=0; index1Minus1<m_sequence1.size(); ++index1Minus1)
        {
            if (m_sequence1.at(index1Minus1) == m_sequence2.at(index2Minus1))
            {
                currentCounts[index1Minus1+1] = previousCounts.at(index1Minus1)+1;
            }
            else
            {
                currentCounts[index1Minus1+1] = max(currentCounts.at(index1Minus1), previousCounts.at(index1Minus1+1));
            }
        }
    }

    Counts const& lastPrevious(previousAndCurrentCounts.at(m_sequence1.size()%2));
    return lastPrevious.at(m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingMemoizationDP() const
{
    CountMatrix lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U, static_cast<Count>(UNUSED_COUNT));
    for(Index index1=1; index1<lengthMatrix.getNumberOfColumns(); index1++)
    {
        lengthMatrix.setEntry(index1, 0, 0);
    }
    for(Index index2=1; index2<lengthMatrix.getNumberOfColumns(); index2++)
    {
        lengthMatrix.setEntry(0, index2, 0);
    }

    return getLongestCommonSubsequenceLengthUsingNaiveRecursion(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingNaiveRecursion(
        Index const index1,
        Index const index2) const
{
    if (index1==0 || index2==0)
    {
        return 0;
    }
    else if (m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
    {
        return 1 + getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1-1, index2-1);
    }
    else
    {
        return max(getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1, index2-1),
                   getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1-1, index2));
    }
}

LongestCommonSubsequence::Count LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingMemoizationDP(
        CountMatrix & lengthMatrix,
        Index const index1,
        Index const index2) const
{
    Index result(lengthMatrix.getEntry(index1, index2));
    if(UNUSED_COUNT == result)
    {
        if (m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
        {
            result = 1 + getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1-1, index2-1);
        }
        else
        {
            result = max(getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1, index2-1),
                         getLongestCommonSubsequenceLengthUsingNaiveRecursion(index1-1, index2));
        }
        lengthMatrix.setEntry(index1, index2, result);
    }
    return result;
}

}
