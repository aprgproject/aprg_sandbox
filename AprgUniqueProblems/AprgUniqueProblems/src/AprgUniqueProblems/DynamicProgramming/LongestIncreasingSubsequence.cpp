#include "LongestIncreasingSubsequence.hpp"

using namespace std;

namespace alba
{

LongestIncreasingSubsequence::LongestIncreasingSubsequence(Sequence const& sequenceToCheck)
    : m_sequenceToCheck(sequenceToCheck)
{}

LongestIncreasingSubsequence::Length LongestIncreasingSubsequence::getLongestIncreasingSubsequenceLength()
{
    LengthToIndexMap lengthToIndexMap;
    for (Length index=0; index<m_sequenceToCheck.size(); index++)
    {
        bool isLongestPartialFound(false);
        for(auto itWithMaxLength = lengthToIndexMap.crbegin(); itWithMaxLength!=lengthToIndexMap.crend(); itWithMaxLength++)
        {
            if(m_sequenceToCheck.at(itWithMaxLength->second) < m_sequenceToCheck.at(index))
            {
                lengthToIndexMap.emplace(itWithMaxLength->first + 1U, index);
                isLongestPartialFound = true;
                break;
            }
        }
        if(!isLongestPartialFound)
        {
            lengthToIndexMap.emplace(1U, index);
        }
    }
    Length result{};
    if(!lengthToIndexMap.empty())
    {
        auto it = lengthToIndexMap.crbegin();
        result = it->first;
    }
    return result;
}

LongestIncreasingSubsequence::Sequence LongestIncreasingSubsequence::getLongestIncreasingSubsequence()
{
    Sequences savedSequences;
    LengthToIndexMap lengthToIndexMap;
    for (Length index=0; index<m_sequenceToCheck.size(); index++)
    {
        bool isLongestPartialFound(false);
        for(auto it = lengthToIndexMap.crbegin(); it!=lengthToIndexMap.crend(); it++)
        {
            if(m_sequenceToCheck.at(it->second) < m_sequenceToCheck.at(index))
            {
                Sequence longestPartial(savedSequences.at(it->second));
                longestPartial.emplace_back(m_sequenceToCheck.at(index));
                savedSequences.emplace_back(longestPartial);
                lengthToIndexMap.emplace(it->first + 1U, index);
                isLongestPartialFound = true;
                break;
            }
        }
        if(!isLongestPartialFound)
        {
            lengthToIndexMap.emplace(1U, index);
            savedSequences.emplace_back(Sequence{m_sequenceToCheck.at(index)});
        }
    }
    Sequence result{};
    if(!lengthToIndexMap.empty())
    {
        auto it = lengthToIndexMap.crbegin();
        if(it->second < savedSequences.size())
        {
            result = savedSequences.at(it->second);
        }
    }
    return result;
}

}
