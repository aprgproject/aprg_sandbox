#include "WordWrapProblemWithLineWidth.hpp"

using namespace std;

namespace alba
{

WordWrapProblemWithLineWidth::WordWrapProblemWithLineWidth(
        Index const lineWidth,
        stringHelper::strings const& words)
    : m_maxLineLength(lineWidth)
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
        RecursionDetails recursionDetails{Indices{firstWordLength}}; // bad idea to have structure as argument
        result = getOptimizedCostUsingNaiveRecursion(recursionDetails, 1U);
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostByTryingAllLengths() const
{
    // Time Complexity: O(lineWidth x numberOfWords)
    // Auxiliary Space: O(lineWidth)

    Cost result(0);
    if(!m_words.empty() && m_maxLineLength>0)
    {
        Costs costsAtLength(m_maxLineLength+1, static_cast<Cost>(MAX_COST));
        for(Index targetLineLength=1; targetLineLength<=m_maxLineLength; targetLineLength++)
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
                    costAtLength += getCostFromExtraSpaces(m_maxLineLength-lineLength);
                    lineLength=wordLength; // new line
                }
            }
            if(!hasNoSolutions)
            {
                costAtLength += getCostFromExtraSpaces(m_maxLineLength-lineLength);
                costsAtLength[targetLineLength] = costAtLength;
            }
        }
        result = *min_element(costsAtLength.cbegin(), costsAtLength.cend());
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostByCheckingFirstAndLastWords() const
{
    // Space optimized solution

    // Time Complexity: O(numberOfWords^2)
    // Auxiliary Space: O(numberOfWords)

    Cost result(0);
    if(!m_words.empty())
    {
        Index numberOfWords(m_words.size());
        Costs costsIfFirstWord(numberOfWords, static_cast<Cost>(MAX_COST));
        for(int firstWordIndex=numberOfWords-1; firstWordIndex>=0; firstWordIndex--) // try all first word in lines
        {
            Cost & costIfFirstWord(costsIfFirstWord[firstWordIndex]);
            Index lineLength(0);
            for(Index lastWordIndex=firstWordIndex; lastWordIndex<numberOfWords; lastWordIndex++) // try all last word in lines
            {
                lineLength += m_words.at(lastWordIndex).length();
                lineLength += (static_cast<Index>(firstWordIndex)<lastWordIndex) ? 1 : 0; // add space character
                if(lineLength <= m_maxLineLength)
                {
                    Cost possibleCost = getCostFromExtraSpaces(m_maxLineLength-lineLength);
                    possibleCost += (lastWordIndex+1 < numberOfWords) ? costsIfFirstWord.at(lastWordIndex+1) : 0; // add cost of next lines
                    costIfFirstWord = min(costIfFirstWord, possibleCost);
                }
            }
        }
        result = costsIfFirstWord.front();
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getOptimizedCostUsingNaiveRecursion(
        RecursionDetails const& recursionDetails,
        Index const wordIndex) const
{
    Cost result(0);
    if(wordIndex < m_words.size())
    {
        result = MAX_COST;
        Index wordLength(m_words.at(wordIndex).length());
        if(wordLength <= m_maxLineLength)
        {
            Index lastLength(recursionDetails.lineLengths.back());
            if(lastLength+1+wordLength <= m_maxLineLength)
            {
                // try to put word on last line
                RecursionDetails currentDetails(recursionDetails);
                currentDetails.lineLengths.back() += 1+wordLength;
                result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
            }

            {
                // try to put word on new line
                RecursionDetails currentDetails(recursionDetails);
                currentDetails.lineLengths.emplace_back(wordLength);
                result = min(result, getOptimizedCostUsingNaiveRecursion(currentDetails, wordIndex+1));
            }
        }
    }
    else
    {
        result = getTotalCostOfAllLines(recursionDetails.lineLengths);
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

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getTotalCostOfAllLines(Indices const& lineLengths) const
{
    Cost result(0);
    for(Index const lineLength : lineLengths)
    {
        result += getCostFromExtraSpaces(m_maxLineLength-lineLength);
    }
    return result;
}

WordWrapProblemWithLineWidth::Cost WordWrapProblemWithLineWidth::getCostFromExtraSpaces(Index const numberOfExtraSpaces) const
{
    return numberOfExtraSpaces*numberOfExtraSpaces*numberOfExtraSpaces; // sum of cubes is used for cost to avoid single long lengths
}


}
