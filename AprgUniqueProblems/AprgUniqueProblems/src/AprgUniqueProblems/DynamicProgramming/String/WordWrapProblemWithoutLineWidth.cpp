#include "WordWrapProblemWithoutLineWidth.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

WordWrapProblemWithoutLineWidth::WordWrapProblemWithoutLineWidth(stringHelper::strings const& words)
    : m_words(words)
{}

WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getOptimizedCostUsingNaiveRecursion() const
{
    // Time Complexity: O(2^numberOfWords) (since there are two tries)
    // Auxiliary Space :O(numberOfWords) (RecursionDetails has allocation on stack)

    Cost result(0);
    if(!m_words.empty())
    {
        Index firstWordLength = m_words.front().length();
        RecursionDetails recursionDetails{firstWordLength, Indices{firstWordLength}};
        result = getOptimizedCostUsingNaiveRecursion(recursionDetails, 1U);
    }
    return result;
}

WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getOptimizedCostByTryingAllLengths() const
{
    // Time Complexity: O(totalLength x numberOfWords)
    // Auxiliary Space: O(totalLength)

    Cost result(0);
    Index totalLength(getTotalLength());
    if(totalLength > 0)
    {
        Costs costsAtLength(totalLength, static_cast<Cost>(MAX_COST));
        for(Index targetLineLength=1; targetLineLength<totalLength; targetLineLength++)
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
                    break; // no possible solution try next length
                }
                else if(lineLength+1+wordLength <= targetLineLength)
                {
                    lineLength += 1+wordLength; // plus one for space
                }
                else // does not fit with line so create next line
                {
                    costAtLength += getCostFromExtraSpaces(targetLineLength-lineLength);
                    lineLength=wordLength; // new line
                }
            }
            if(!hasNoSolutions)
            {
                costAtLength += getCostFromExtraSpaces(targetLineLength-lineLength);
                costsAtLength[targetLineLength] = costAtLength;
            }
        }
        result = *min_element(costsAtLength.cbegin(), costsAtLength.cend());
    }
    return result;
}

WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getOptimizedCostUsingNaiveRecursion(
        RecursionDetails const& recursionDetails,
        Index const wordIndex) const
{
    Cost result(0);
    if(wordIndex < m_words.size())
    {
        result = MAX_COST;
        Index wordLength(m_words.at(wordIndex).length());
        {
            RecursionDetails currentDetails(recursionDetails);
            Index & lastLength(currentDetails.lengths.back());
            lastLength+=wordLength+1;
            currentDetails.maxLength = max(currentDetails.maxLength, lastLength);
            result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
        }
        {
            RecursionDetails currentDetails(recursionDetails);
            currentDetails.lengths.emplace_back(wordLength);
            currentDetails.maxLength = max(currentDetails.maxLength, currentDetails.lengths.back());
            result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
        }
    }
    else
    {
        result = getCost(recursionDetails.maxLength, recursionDetails.lengths);
    }
    return result;
}

WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getTotalLength() const
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

WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getCost(Index const maxLength, Indices const& lengths) const
{
    Cost result(0);
    if(lengths.size() == 1)
    {
        result = getCostFromExtraSpaces(lengths.front());
    }
    else
    {
        for(Index const length : lengths)
        {
            result += getCostFromExtraSpaces(maxLength-length);
        }
    }
    return result;
}

// inline optimization can work here because the usage belongs to same translation unit
inline WordWrapProblemWithoutLineWidth::Cost WordWrapProblemWithoutLineWidth::getCostFromExtraSpaces(Index const numberOfExtraSpaces) const
{
    return numberOfExtraSpaces*numberOfExtraSpaces*numberOfExtraSpaces; // sum of cubes is used for cost to avoid single long lengths}


}