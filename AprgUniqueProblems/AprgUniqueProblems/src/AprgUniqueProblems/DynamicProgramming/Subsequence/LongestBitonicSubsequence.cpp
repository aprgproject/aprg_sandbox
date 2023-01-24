#include "LongestBitonicSubsequence.hpp"

#include <algorithm>
#include <list>

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
    if(!m_sequence.empty())    {
        IndexToIndex subIncreasingLengths(m_sequence.size(), 1);
        IndexToIndex subDecreasingLengths(m_sequence.size(), 1);
        for (Index index(0); index<m_sequence.size(); index++)        {
            Value & subIncreasingLength(subIncreasingLengths[index]);
            for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
            {
                if(m_sequence.at(lowerIndex) < m_sequence.at(index))
                {
                    subIncreasingLength = max(subIncreasingLength, subIncreasingLengths.at(lowerIndex)+1);
                }
            }
        }
        for (int index=m_sequence.size()-1; index>=0; index--)
        {
            Value & subDecreasingLength(subDecreasingLengths[index]);
            for (Index higherIndex=index+1; higherIndex<m_sequence.size(); higherIndex++)
            {
                if(m_sequence.at(index) > m_sequence.at(higherIndex))
                {
                    subDecreasingLength = max(subDecreasingLength, subDecreasingLengths.at(higherIndex)+1);
                }
            }
        }

        for (Index index(0); index<m_sequence.size(); index++)
        {
            result = max(result, subIncreasingLengths.at(index)+subDecreasingLengths.at(index)-1);
        }
    }
    return result;
}

LongestBitonicSubsequence::Values LongestBitonicSubsequence::getLongestSubsequence() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Values result;
    if(!m_sequence.empty())    {
        IndexToIndex subIncreasingLengths(m_sequence.size(), 1);
        IndexToIndex subDecreasingLengths(m_sequence.size(), 1);
        IndexToIndex indexToIncreasingPreviousIndex(m_sequence.size());        IndexToIndex indexToDecreasingPreviousIndex(m_sequence.size());
        iota(indexToIncreasingPreviousIndex.begin(), indexToIncreasingPreviousIndex.end(), 0);
        iota(indexToDecreasingPreviousIndex.begin(), indexToDecreasingPreviousIndex.end(), 0);

        computeSubIncreasingLengths(subIncreasingLengths, indexToIncreasingPreviousIndex);
        computeSubDecreasingLengths(subDecreasingLengths, indexToDecreasingPreviousIndex);

        result = getLongestSubsequence(
                    subIncreasingLengths, subDecreasingLengths, indexToIncreasingPreviousIndex, indexToDecreasingPreviousIndex);
    }
    return result;
}

void LongestBitonicSubsequence::computeSubIncreasingLengths(
        IndexToIndex & subIncreasingLengths,
        IndexToIndex & indexToIncreasingPreviousIndex) const
{
    for (Index index(0); index<m_sequence.size(); index++)
    {
        Value & subIncreasingLength(subIncreasingLengths[index]);
        Value & previousIndex(indexToIncreasingPreviousIndex[index]);
        for (Index lowerIndex=0; lowerIndex<index; lowerIndex++)
        {
            if(m_sequence.at(lowerIndex) < m_sequence.at(index)
                    && subIncreasingLength < subIncreasingLengths.at(lowerIndex)+1)
            {
                subIncreasingLength = subIncreasingLengths.at(lowerIndex)+1;
                previousIndex = lowerIndex;
            }
        }
    }
}

void LongestBitonicSubsequence::computeSubDecreasingLengths(
        IndexToIndex & subDecreasingLengths,
        IndexToIndex & indexToDecreasingPreviousIndex) const
{
    for (int index=m_sequence.size()-1; index>=0; index--)
    {
        Value & subDecreasingLength(subDecreasingLengths[index]);
        Value & previousIndex(indexToDecreasingPreviousIndex[index]);
        for (Index higherIndex=index+1; higherIndex<m_sequence.size(); higherIndex++)
        {
            if(m_sequence.at(index) > m_sequence.at(higherIndex)
                    && subDecreasingLength < subDecreasingLengths.at(higherIndex)+1)
            {
                subDecreasingLength = subDecreasingLengths.at(higherIndex)+1;
                previousIndex = higherIndex;
            }
        }
    }
}

LongestBitonicSubsequence::Values LongestBitonicSubsequence::getLongestSubsequence(
        IndexToIndex & subIncreasingLengths,
        IndexToIndex & subDecreasingLengths,
        IndexToIndex & indexToIncreasingPreviousIndex,
        IndexToIndex & indexToDecreasingPreviousIndex) const
{
    Value maxLength(0);
    Index indexOfLongestLength(0);
    for (Index index(0); index<m_sequence.size(); index++)
    {
        Value lengthAtIndex(subIncreasingLengths.at(index)+subDecreasingLengths.at(index)-1);
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
