#include "LongestIncreasingSubsequenceWithLinearithmicTime.hpp"

using namespace std;

namespace alba
{

LongestIncreasingSubsequenceWithLinearithmicTime::LongestIncreasingSubsequenceWithLinearithmicTime(Sequence const& sequenceToCheck)
    : m_sequenceToCheck(sequenceToCheck)
{}

LongestIncreasingSubsequenceWithLinearithmicTime::Index LongestIncreasingSubsequenceWithLinearithmicTime::getLongestLength() const
{
    Index longestLength(0U);
    if(!m_sequenceToCheck.empty())
    {
        IndexToValue lengthToEndValue(m_sequenceToCheck.size(), 0U); // dynamic programming
        lengthToEndValue[0] = m_sequenceToCheck.front();        longestLength = 1U;
        for (auto itValue=m_sequenceToCheck.cbegin()+1; itValue!=m_sequenceToCheck.cend(); itValue++)
        {
            auto beginIt = lengthToEndValue.begin(), endIt = lengthToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, *itValue);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                lengthToEndValue[longestLength++] = *itValue; // extend
            }            else
            {
                *lowerBoundItForEndValue = *itValue; // replace
            }        }
    }
    return longestLength;
}

LongestIncreasingSubsequenceWithLinearithmicTime::Sequence LongestIncreasingSubsequenceWithLinearithmicTime::getLongestSubsequence() const
{
    Sequence longestSequence;
    if(!m_sequenceToCheck.empty())
    {
        Index longestLength(1U);
        Value unusedValue(UNUSED_VALUE);        IndexToValue lengthToEndValue(m_sequenceToCheck.size(), 0U); // dynamic programming
        IndexToIndex lengthToEndIndex(m_sequenceToCheck.size(), unusedValue);
        IndexToIndex indexToPreviousIndex(m_sequenceToCheck.size(), unusedValue);
        lengthToEndValue[0] = m_sequenceToCheck.front();        for (Index i=1; i<m_sequenceToCheck.size(); i++)
        {
            Value const& value(m_sequenceToCheck.at(i));
            auto beginIt = lengthToEndValue.begin(), endIt = lengthToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                indexToPreviousIndex[i] = lengthToEndIndex.at(longestLength-1);
                lengthToEndIndex[longestLength] = i;                lengthToEndValue[longestLength++] = value; // extend
            }
            else
            {                Index currentLength = distance(lengthToEndValue.begin(), lowerBoundItForEndValue);
                if(currentLength > 0)
                {
                    indexToPreviousIndex[i] = lengthToEndIndex[currentLength-1];
                }
                lengthToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value; // replace
            }
        }

        // construct longest sequence
        longestSequence.resize(longestLength, Value{});
        Index maxIndex=longestLength-1;
        for(Index inputIndex=lengthToEndIndex.at(maxIndex), outputIndex=0;
            inputIndex!=UNUSED_VALUE && outputIndex<=maxIndex;
            inputIndex=indexToPreviousIndex.at(inputIndex), outputIndex++)
        {
            longestSequence[maxIndex-outputIndex] = m_sequenceToCheck.at(inputIndex); // reverse in output
        }
    }
    return longestSequence;
}

}
