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
    // Naive recursive solution
    return getLongestCommonSubsequenceLengthUsingRecursion(m_sequence1.size(), m_sequence2.size());
}

LongestCommonSubsequence::Index LongestCommonSubsequence::getLongestCommonSubsequenceLengthUsingDynamicProgramming() const
{
    matrix::AlbaMatrix<Value> lengthMatrix(m_sequence1.size()+1U, m_sequence2.size()+1U);

    lengthMatrix.iterateAllThroughYAndThenX([&](unsigned int x, unsigned int y)
    {
        if (x == 0 || y == 0)
        {
            // do nothing
        }
        else if (m_sequence1.at(x-1) == m_sequence2.at(y-1))
        {
            lengthMatrix.setEntry(x, y, lengthMatrix.getEntryConstReference(x-1, y-1)+1);
        }
        else
        {
            lengthMatrix.setEntry(x, y, max(lengthMatrix.getEntryConstReference(x-1, y), lengthMatrix.getEntryConstReference(x, y-1)));
        }
    });
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
