#include "LongestIncreasingSubsequence.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

LongestIncreasingSubsequence::LongestIncreasingSubsequence(Sequence const& sequenceToCheck)
    : m_sequenceToCheck(sequenceToCheck)
{}

LongestIncreasingSubsequence::Index LongestIncreasingSubsequence::getLongestIncreasingSubsequenceLength()
{
    Index result(0U);
    if(!m_sequenceToCheck.empty())
    {        IndexToIndex indexToLength(m_sequenceToCheck.size(), 0U);
        indexToLength[0U]=1U;

        // Quadratic time because of double loop        for (Index index=1U; index<m_sequenceToCheck.size(); index++)
        {
            indexToLength[index]=1U;
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequenceToCheck.at(lowerIndex) < m_sequenceToCheck.at(index)
                        && indexToLength.at(index) < indexToLength.at(lowerIndex)+1U)
                {
                    indexToLength[index] = indexToLength.at(lowerIndex)+1U; // save maximum
                }
            }
        }        result = *max_element(indexToLength.cbegin(), indexToLength.cend());
    }
    return result;
}

LongestIncreasingSubsequence::Sequence LongestIncreasingSubsequence::getLongestIncreasingSubsequence()
{
    Sequence longestSequence;
    if(!m_sequenceToCheck.empty())
    {        Value unusedValue(UNUSED_VALUE);
        IndexToIndex indexToPreviousIndex(m_sequenceToCheck.size(), unusedValue);
        IndexToIndex indexToLength(m_sequenceToCheck.size(), 0U);
        indexToLength[0U]=1U;
        // Quadratic time because of double loop
        for (Index index=1U; index<m_sequenceToCheck.size(); index++)
        {
            indexToLength[index]=1U;
            for (Index lowerIndex=0U; lowerIndex<index; lowerIndex++)
            {
                if(m_sequenceToCheck.at(lowerIndex) < m_sequenceToCheck.at(index)
                        && indexToLength.at(index) < indexToLength.at(lowerIndex)+1U)
                {
                    indexToPreviousIndex[index] = lowerIndex;
                    indexToLength[index] = indexToLength.at(lowerIndex)+1U;
                }
            }
        }

        // construct longest sequence
        auto it=max_element(indexToLength.cbegin(), indexToLength.cend());
        Index indexOfLongestLength = distance(indexToLength.cbegin(), it);
        Index longestLength = *it;
        longestSequence.resize(longestLength, Value{});
        Index maxIndex=longestLength-1;
        for(Index inputIndex=indexOfLongestLength, outputIndex=0;
            inputIndex!=UNUSED_VALUE && outputIndex<=maxIndex;
            inputIndex=indexToPreviousIndex.at(inputIndex), outputIndex++)
        {
            longestSequence[maxIndex-outputIndex] = m_sequenceToCheck.at(inputIndex); // reverse in output
        }
    }
    return longestSequence;
}

}
