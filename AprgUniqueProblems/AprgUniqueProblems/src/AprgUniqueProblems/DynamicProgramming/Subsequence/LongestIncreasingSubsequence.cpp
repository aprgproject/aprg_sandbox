#include "LongestIncreasingSubsequence.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

LongestIncreasingSubsequence::LongestIncreasingSubsequence(Values const& sequence)
    : m_sequence(sequence)
{}

LongestIncreasingSubsequence::Index LongestIncreasingSubsequence::getLongestLength()
{
    // Quadratic time because of double loop

    Index result(0U);
    if(!m_sequence.empty())
    {
        IndexToIndex indexToLength(m_sequence.size(), 0U);
        for (Index index=0U; index<m_sequence.size(); index++)
        {
            indexToLength[index]=1U;
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index))
                {
                    indexToLength[index] = max(indexToLength.at(index), indexToLength.at(lowerIndex)+1U); // save maximum
                }
            }
        }        result = *max_element(indexToLength.cbegin(), indexToLength.cend());
    }
    return result;
}

LongestIncreasingSubsequence::Values LongestIncreasingSubsequence::getLongestSubsequence()
{
    // Quadratic time because of double loop

    Values result;
    if(!m_sequence.empty())
    {
        IndexToIndex indexToLength(m_sequence.size(), 0U);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index=0U; index<m_sequence.size(); index++)
        {
            indexToLength[index]=1U;
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index)
                        && indexToLength.at(index) < indexToLength.at(lowerIndex)+1U)
                {
                    indexToPreviousIndex[index] = lowerIndex;                    indexToLength[index] = indexToLength.at(lowerIndex)+1U;
                }
            }
        }

        // construct longest sequence
        auto itMax = max_element(indexToLength.cbegin(), indexToLength.cend());
        Index indexOfLongestLength = distance(indexToLength.cbegin(), itMax);
        Index traverseIndex=indexOfLongestLength;
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