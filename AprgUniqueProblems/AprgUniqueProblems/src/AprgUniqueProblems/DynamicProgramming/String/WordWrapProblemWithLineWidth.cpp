#include "WordWrapProblemWithLineWidth.hpp"

using namespace std;

namespace alba
{

WordWrapProblemWithLineWidth::WordWrapProblemWithLineWidth(
        Index const lineWidth,
        stringHelper::strings const& words)
    : m_lineWidth(lineWidth)
    , m_words(words)
{}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostUsingNaiveRecursion() const
{
    // Time Complexity: O(2^numberOfWords) (since there are two tries)
    // Auxiliary Space :O(numberOfWords) (RecursionDetails has allocation on stack)

    Cost result(0);
    if(!m_words.empty())
    {
        Index firstWordLength = m_words.front().length();
        RecursionDetails recursionDetails{Indices{firstWordLength}};
        result = getOptimizedCostUsingNaiveRecursion(recursionDetails, 1U);
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostByTryingAllLengths() const
{
    // Time Complexity: O(lineWidth x numberOfWords)
    // Auxiliary Space: O(lineWidth)

    Cost result(0);
    if(!m_words.empty() && m_lineWidth>0)
    {
        Costs costsAtLength(m_lineWidth+1, static_cast<Cost>(MAX_COST));
        for(Index targetLineLength=1; targetLineLength<=m_lineWidth; targetLineLength++)
        {
            Cost costAtLength(0);
            bool hasNoSolutions(false);
            Index lineLength(m_words.front().length());
            for(auto it=m_words.cbegin()+1; it!=m_words.cend(); it++)
            {
                Index wordLength(it->length());
                if(wordLength > targetLineLength)
                {
                    hasNoSolutions = true;
                    break; // no possible solutions on all lengths
                }
                else if(lineLength+1+wordLength <= targetLineLength)
                {
                    lineLength += 1+wordLength; // plus one for space
                }
                else // does not fit with line so create next line
                {
                    costAtLength += getCostFromExtraSpaces(m_lineWidth-lineLength);
                    lineLength=wordLength; // new line
                }
            }
            if(!hasNoSolutions)
            {
                costAtLength += getCostFromExtraSpaces(m_lineWidth-lineLength);
                costsAtLength[targetLineLength] = costAtLength;
            }
        }
        result = *min_element(costsAtLength.cbegin(), costsAtLength.cend());
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostByCheckingExtraSpaces() const
{
    // Time Complexity: O(numberOfWords^2)
    // Auxiliary Space: O(numberOfWords^2)

    // NOT WORKING: https://www.geeksforgeeks.org/word-wrap-problem-space-optimized-solution/
    Cost result(0);
    if(!m_words.empty())
    {
        int numberOfWords = static_cast<int>(m_words.size());
        vector<int> costs(numberOfWords);
        for(int wordIndex1=numberOfWords-2; wordIndex1>=0; wordIndex1--)
        {
            int currentLength = -1;
            costs[wordIndex1] = numeric_limits<int>::max();
            for(int wordIndex2=wordIndex1; wordIndex2<numberOfWords; wordIndex2++)
            {
                currentLength += m_words.at(wordIndex2).length()+1;
                if(currentLength > static_cast<int>(m_lineWidth))
                {
                    break;
                }
                int cost(0);
                if(wordIndex2+1 != numberOfWords)
                {
                    cost = getCostFromExtraSpaces(m_lineWidth-currentLength) + costs[wordIndex2+1];
                }
                if(cost < costs.at(wordIndex1))
                {
                    costs[wordIndex1] = cost;
                }
            }
        }
        result = costs.front()+1;
    }
    return result;
}
WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostUsingNaiveRecursion(
        RecursionDetails const& recursionDetails,
        Index const wordIndex) const{
    Cost result(0);
    if(wordIndex < m_words.size())
    {
        result = MAX_COST;
        Index wordLength(m_words.at(wordIndex).length());
        if(wordLength <= m_lineWidth)
        {
            Index lastLength(recursionDetails.lengths.back());
            if(lastLength+1+wordLength <= m_lineWidth)
            {
                // try to put word on last line
                RecursionDetails currentDetails(recursionDetails);
                currentDetails.lengths.back() += 1+wordLength;
                result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
            }

            {
                // try to put word on new line
                RecursionDetails currentDetails(recursionDetails);
                currentDetails.lengths.emplace_back(wordLength);
                result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
            }
        }
    }
    else
    {
        result = getCost(recursionDetails.lengths);
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getTotalLength() const
{
    Index result(0);
    if(!m_words.empty())
    {
        result = m_words.front().length();
        for(auto it=m_words.cbegin()+1; it!=m_words.cend(); it++)
        {
            result += it->length()+1; // plus one for space
        }
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getCost(Indices const& lengths) const
{
    Cost result(0);
    for(Index const length : lengths)
    {
        result += getCostFromExtraSpaces(m_lineWidth-length);
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getCostFromExtraSpaces(Index const numberOfExtraSpaces) const
{
    return numberOfExtraSpaces*numberOfExtraSpaces*numberOfExtraSpaces; // sum of cubes is used for cost to avoid single long lengths
}


}
