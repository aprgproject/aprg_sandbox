#include "LongestIncreasingSubsequenceWithLinearithmicTime.hpp"

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba
{

LongestIncreasingSubsequenceWithLinearithmicTime::LongestIncreasingSubsequenceWithLinearithmicTime(Values const& sequence)
    : m_sequence(sequence)
{}

LongestIncreasingSubsequenceWithLinearithmicTime::Index LongestIncreasingSubsequenceWithLinearithmicTime::getLongestLength() const
{
    Index longestLength(0);
    if(!m_sequence.empty())
    {
        IndexToValue lengthToEndValue(m_sequence.size(), 0); // dynamic programming
        lengthToEndValue[0] = m_sequence.front();
        longestLength = 1;
        for (auto itValue=m_sequence.cbegin()+1; itValue!=m_sequence.cend(); itValue++)
        {
            auto beginIt = lengthToEndValue.begin(), endIt = lengthToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, *itValue);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                lengthToEndValue[longestLength++] = *itValue; // extend
            }
            else
            {
                *lowerBoundItForEndValue = *itValue; // replace
            }
        }
    }
    return longestLength;
}

LongestIncreasingSubsequenceWithLinearithmicTime::Values LongestIncreasingSubsequenceWithLinearithmicTime::getLongestSubsequence() const
{
    Values result;
    if(!m_sequence.empty())
    {
        Index longestLength(1);
        IndexToValue lengthToEndValue(m_sequence.size(), 0); // dynamic programming
        IndexToIndex lengthToEndIndex(m_sequence.size(), 0);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);
        lengthToEndValue[0] = m_sequence.front();
        for (Index i=1; i<m_sequence.size(); i++)
        {
            Value const& value(m_sequence.at(i));
            auto beginIt = lengthToEndValue.begin(), endIt = lengthToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if(lowerBoundItForEndValue == endIt) // if current value is the highest
            {
                indexToPreviousIndex[i] = lengthToEndIndex.at(longestLength-1);
                lengthToEndIndex[longestLength] = i;
                lengthToEndValue[longestLength++] = value; // extend
            }
            else
            {
                Index currentLength = distance(lengthToEndValue.begin(), lowerBoundItForEndValue);
                if(currentLength > 0)
                {
                    indexToPreviousIndex[i] = lengthToEndIndex[currentLength-1];
                }
                lengthToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value; // replace
            }
        }

        // construct longest sequence
        Index traverseIndex=lengthToEndIndex.at(longestLength-1);
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
