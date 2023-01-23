#include "MaximumSumIncreasingSubsequence.hpp"

using namespace std;

namespace alba
{

MaximumSumIncreasingSubsequence::MaximumSumIncreasingSubsequence(Values const& sequence)
    : m_sequence(sequence)
{}

MaximumSumIncreasingSubsequence::Value MaximumSumIncreasingSubsequence::getMaximumSum() const
{
    // Quadratic time because of double loop

    Value result(0U);
    if(!m_sequence.empty())
    {
        Values partialSums(m_sequence.size(), 0U);
        for (Index index=0U; index<m_sequence.size(); index++)
        {
            Value maxPartialSum(0);
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index))
                {
                    maxPartialSum = max(maxPartialSum, partialSums.at(lowerIndex));
                }
            }
            maxPartialSum += m_sequence.at(index);
            partialSums[index] = maxPartialSum;
        }
        result = *max_element(partialSums.cbegin(), partialSums.cend());
    }
    return result;
}

MaximumSumIncreasingSubsequence::Values MaximumSumIncreasingSubsequence::getSubsequenceWithMaximumSum() const
{
    // Quadratic time because of double loop

    Values result;
    if(!m_sequence.empty())
    {
        Values partialSums(m_sequence.size(), 0U);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index=0U; index<m_sequence.size(); index++)
        {
            Value maxPartialSum(0);
            Index indexWithMaxPartialSum(0);
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index)
                        && maxPartialSum < partialSums.at(lowerIndex))
                {
                    maxPartialSum = partialSums.at(lowerIndex);
                    indexWithMaxPartialSum = lowerIndex; // save maximum
                }
            }
            maxPartialSum += m_sequence.at(index);
            partialSums[index] = maxPartialSum;
            indexToPreviousIndex[index] = indexWithMaxPartialSum;
        }

        // construct longest sequence
        auto itMax = max_element(partialSums.cbegin(), partialSums.cend());
        Index indexOfMaxSum = distance(partialSums.cbegin(), itMax );
        Index traverseIndex=indexOfMaxSum;
        for(; traverseIndex!=indexToPreviousIndex.at(traverseIndex); traverseIndex=indexToPreviousIndex.at(traverseIndex))
        {
            result.emplace_back(m_sequence.at(traverseIndex));
        }
        result.emplace_back(m_sequence.at(traverseIndex));
        reverse(result.begin(), result.end());
    }
    return result;
}

}
