#include "LongestIncreasingSubsequence.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

LongestIncreasingSubsequence::LongestIncreasingSubsequence(Values const& sequence)
    : m_sequence(sequence)
{}

LongestIncreasingSubsequence::Index LongestIncreasingSubsequence::getLongestLength() const
{
    // Quadratic time because of double loop

    Index result(0);
    if(!m_sequence.empty())
    {
        IndexToIndex subLengths(m_sequence.size(), 1);
        for (Index index(0); index<m_sequence.size(); index++)
        {
            Value & subLength(subLengths[index]);
            for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index))
                {
                    subLength = max(subLength, subLengths.at(lowerIndex)+1);
                }
            }
        }
        result = *max_element(subLengths.cbegin(), subLengths.cend());
    }
    return result;
}

LongestIncreasingSubsequence::Values LongestIncreasingSubsequence::getLongestSubsequence() const
{
    // Quadratic time because of double loop

    Values result;
    if(!m_sequence.empty())
    {
        IndexToIndex subLengths(m_sequence.size(), 1);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index(0); index<m_sequence.size(); index++)
        {
            Value & subLength(subLengths[index]);
            Value & previousIndex(indexToPreviousIndex[index]);
            for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index)
                        && subLength < subLengths.at(lowerIndex)+1)
                {
                    subLength = subLengths.at(lowerIndex)+1;
                    previousIndex = lowerIndex;
                }
            }
        }

        // construct longest sequence
        auto itMax = max_element(subLengths.cbegin(), subLengths.cend());
        Index indexOfLongestLength = distance(subLengths.cbegin(), itMax);
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
