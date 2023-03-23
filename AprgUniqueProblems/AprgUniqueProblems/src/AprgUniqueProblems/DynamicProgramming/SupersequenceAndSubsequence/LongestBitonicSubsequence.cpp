#include "LongestBitonicSubsequence.hpp"

#include <algorithm>
#include <list>
#include <numeric>

using namespace std;

namespace alba
{

LongestBitonicSubsequence::LongestBitonicSubsequence(Values const& sequence)
    : m_sequence(sequence)
{}

LongestBitonicSubsequence::Index LongestBitonicSubsequence::getLongestLength() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Index result(0);
    if(!m_sequence.empty())
    {
        IndexToIndex increasingPartialLengths(m_sequence.size(), 1);
        IndexToIndex decreasingPartialLengths(m_sequence.size(), 1);

        computeIncreasingPartialLengths(increasingPartialLengths);
        computeDecreasingPartialLengths(decreasingPartialLengths);

        for (Index index(0); index<m_sequence.size(); index++)
        {
            result = max(result, increasingPartialLengths.at(index)+decreasingPartialLengths.at(index)-1);
        }
    }
    return result;
}

LongestBitonicSubsequence::Values LongestBitonicSubsequence::getLongestSubsequence() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Values result;
    if(!m_sequence.empty())
    {
        IndexToIndex increasingPartialLengths(m_sequence.size(), 1);
        IndexToIndex decreasingPartialLengths(m_sequence.size(), 1);
        IndexToIndex indexToIncreasingPreviousIndex(m_sequence.size());
        IndexToIndex indexToDecreasingPreviousIndex(m_sequence.size());
        iota(indexToIncreasingPreviousIndex.begin(), indexToIncreasingPreviousIndex.end(), 0);
        iota(indexToDecreasingPreviousIndex.begin(), indexToDecreasingPreviousIndex.end(), 0);

        computeIncreasingPartialLengths(increasingPartialLengths, indexToIncreasingPreviousIndex);
        computeDecreasingPartialLengths(decreasingPartialLengths, indexToDecreasingPreviousIndex);

        result = getLongestSubsequence(
                    increasingPartialLengths, decreasingPartialLengths, indexToIncreasingPreviousIndex, indexToDecreasingPreviousIndex);
    }
    return result;
}

void LongestBitonicSubsequence::computeIncreasingPartialLengths(
        IndexToIndex & increasingPartialLengths) const
{
    for (Index index(0); index<m_sequence.size(); index++)
    {
        Value & subIncreasingLength(increasingPartialLengths[index]);
        for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
        {
            if(m_sequence.at(lowerIndex) < m_sequence.at(index))
            {
                subIncreasingLength = max(subIncreasingLength, increasingPartialLengths.at(lowerIndex)+1);
            }
        }
    }
}

void LongestBitonicSubsequence::computeDecreasingPartialLengths(
        IndexToIndex & decreasingPartialLengths) const
{
    for (int index=m_sequence.size()-1; index>=0; index--)
    {
        Value & decreasingPartialLength(decreasingPartialLengths[index]);
        for (Index higherIndex=index+1; higherIndex<m_sequence.size(); higherIndex++)
        {
            if(m_sequence.at(index) > m_sequence.at(higherIndex))
            {
                decreasingPartialLength = max(decreasingPartialLength, decreasingPartialLengths.at(higherIndex)+1);
            }
        }
    }
}

void LongestBitonicSubsequence::computeIncreasingPartialLengths(
        IndexToIndex & increasingPartialLengths,
        IndexToIndex & indexToIncreasingPreviousIndex) const
{
    for (Index index(0); index<m_sequence.size(); index++)
    {
        Value & subIncreasingLength(increasingPartialLengths[index]);
        Value & previousIndex(indexToIncreasingPreviousIndex[index]);
        for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
        {
            if(m_sequence.at(lowerIndex) < m_sequence.at(index)
                    && subIncreasingLength < increasingPartialLengths.at(lowerIndex)+1)
            {
                subIncreasingLength = increasingPartialLengths.at(lowerIndex)+1;
                previousIndex = lowerIndex;
            }
        }
    }
}

void LongestBitonicSubsequence::computeDecreasingPartialLengths(
        IndexToIndex & decreasingPartialLengths,
        IndexToIndex & indexToDecreasingPreviousIndex) const
{
    for (int index=m_sequence.size()-1; index>=0; index--)
    {
        Value & decreasingPartialLength(decreasingPartialLengths[index]);
        Value & previousIndex(indexToDecreasingPreviousIndex[index]);
        for (Index higherIndex=index+1; higherIndex<m_sequence.size(); higherIndex++)
        {
            if(m_sequence.at(index) > m_sequence.at(higherIndex)
                    && decreasingPartialLength < decreasingPartialLengths.at(higherIndex)+1)
            {
                decreasingPartialLength = decreasingPartialLengths.at(higherIndex)+1;
                previousIndex = higherIndex;
            }
        }
    }
}

LongestBitonicSubsequence::Values LongestBitonicSubsequence::getLongestSubsequence(
        IndexToIndex & increasingPartialLengths,
        IndexToIndex & decreasingPartialLengths,
        IndexToIndex & indexToIncreasingPreviousIndex,
        IndexToIndex & indexToDecreasingPreviousIndex) const
{
    Value maxLength(0);
    Index indexOfLongestLength(0);
    for (Index index(0); index<m_sequence.size(); index++)
    {
        Value lengthAtIndex(increasingPartialLengths.at(index)+decreasingPartialLengths.at(index)-1);
        if(maxLength < lengthAtIndex)
        {
            maxLength = lengthAtIndex;
            indexOfLongestLength = index;
        }
    }

    list<Value> sequenceInDeque;

    Index traverseIndex=indexOfLongestLength;
    for(; traverseIndex!=indexToIncreasingPreviousIndex.at(traverseIndex); traverseIndex=indexToIncreasingPreviousIndex.at(traverseIndex))
    {
        sequenceInDeque.emplace_front(m_sequence.at(traverseIndex));
    }
    sequenceInDeque.emplace_front(m_sequence.at(traverseIndex));

    traverseIndex=indexToDecreasingPreviousIndex.at(indexOfLongestLength);
    for(; traverseIndex!=indexToDecreasingPreviousIndex.at(traverseIndex); traverseIndex=indexToDecreasingPreviousIndex.at(traverseIndex))
    {
        sequenceInDeque.emplace_back(m_sequence.at(traverseIndex));
    }
    sequenceInDeque.emplace_back(m_sequence.at(traverseIndex));

    return Values(sequenceInDeque.cbegin(), sequenceInDeque.cend());
}

}
