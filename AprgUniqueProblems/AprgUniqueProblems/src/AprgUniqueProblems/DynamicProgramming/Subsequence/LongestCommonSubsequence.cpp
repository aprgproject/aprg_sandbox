#include "LongestCommonSubsequence.hpp"

#include <Common/Math/Matrix/AlbaMatrix.hpp>

using namespace std;

namespace alba
{

LongestCommonSubsequence::LongestCommonSubsequence(Sequence const& sequence1, Sequence const& sequence2)
    : m_sequence1(sequence1)
    , m_sequence2(sequence2)
{}

LongestCommonSubsequence::Index LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingRecursion() const
{
    return getLongestCommonSubsequenceLengthUsingRecursion(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Index LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingDynamicProgramming() const
{
    matrix::AlbaMatrix<Value> lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U);
    for (Index i=0; i<=m_sequence1.size(); i++)    {
        for (Index j=0; j<=m_sequence2.size(); j++)
        {
            if (i == 0 || j == 0)
            {
                continue;
            }
            else if (m_sequence1.at(i-1) == m_sequence2.at(j-1))
            {
                lengthMatrix.setEntry(i, j, lengthMatrix.getEntryConstReference(i-1, j-1)+1);
            }
            else
            {
                lengthMatrix.setEntry(i, j, max(lengthMatrix.getEntryConstReference(i-1, j), lengthMatrix.getEntryConstReference(i, j-1)));
            }
        }
    }
    return lengthMatrix.getEntry(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Index LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingRecursion(
        Index const index1,
        Index const index2) const
{
    if (index1==0 || index2==0)
    {
        return 0;
    }
    else if (m_sequence1.at(index1-1) == m_sequence2.at(index2-1))
    {
        return 1 + getLongestCommonSubsequenceLengthUsingRecursion(index1-1, index2-1);
    }
    else
    {
        return max(getLongestCommonSubsequenceLengthUsingRecursion(index1, index2-1),
                   getLongestCommonSubsequenceLengthUsingRecursion(index1-1, index2));
    }
}

}
