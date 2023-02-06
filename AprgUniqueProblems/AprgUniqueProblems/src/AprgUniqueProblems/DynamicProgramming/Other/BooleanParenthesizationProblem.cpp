#include "BooleanParenthesizationProblem.hpp"

using namespace std;

namespace alba
{

BooleanParenthesizationProblem::BooleanParenthesizationProblem(
        Booleans const& inputValues,
        Operators const& operators)
    : m_inputValues(inputValues)
    , m_operators(operators)
{
    initialize();
}

BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::getNumberOfWaysForTrueUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Count result(0);
    if(!m_inputValues.empty())
    {
        result = getNumberOfWaysUsingNaiveRecursion(true, 0, m_inputValues.size()-1);
    }
    return result;
}

BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::getNumberOfWaysForTrueUsingMemoizationDP() const
{
    // Time Complexity: O(n^3) (should be same as Tabular DP)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_inputValues.empty())
    {
        CountMatrices countMatrices(2U, CountMatrix(m_inputValues.size(), m_inputValues.size(), UNUSED_COUNT));
        result = getNumberOfWaysUsingMemoizationDP(countMatrices, true, 0, m_inputValues.size()-1);
    }
    return result;
}

BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::getNumberOfWaysForTrueUsingTabularDP() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_inputValues.empty())
    {
        CountMatrix countsForFalse(m_inputValues.size(), m_inputValues.size());
        CountMatrix countsForTrue(m_inputValues.size(), m_inputValues.size());

        for(Index index=0; index<m_inputValues.size(); index++) // for length 1
        {
            countsForFalse.setEntry(index, index, convertBoolToCount(!m_inputValues.at(index)));
            countsForTrue.setEntry(index, index, convertBoolToCount(m_inputValues.at(index)));
        }
        for(Index length=2; length<=m_inputValues.size(); length++)
        {
            for(Index leftParenthesis=0; leftParenthesis+length<=m_inputValues.size(); leftParenthesis++)
            {
                Index rightParenthesis = leftParenthesis+length-1;
                Count currentCountForFalse(0);
                Count currentCountForTrue(0);
                for(Index operationIndex=leftParenthesis; operationIndex<rightParenthesis; operationIndex++)
                {
                    Count numberOfFalseInLeft = countsForFalse.getEntry(leftParenthesis, operationIndex);
                    Count numberOfTrueInLeft = countsForTrue.getEntry(leftParenthesis, operationIndex);
                    Count numberOfFalseInRight = countsForFalse.getEntry(operationIndex+1, rightParenthesis);
                    Count numberOfTrueInRight = countsForTrue.getEntry(operationIndex+1, rightParenthesis);

                    if(m_operators.at(operationIndex) == '&')
                    {
                        currentCountForFalse += numberOfFalseInLeft*numberOfFalseInRight + numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
                        currentCountForTrue += numberOfTrueInLeft*numberOfTrueInRight;
                    }
                    else if(m_operators.at(operationIndex) == '|')
                    {
                        currentCountForFalse += numberOfFalseInLeft*numberOfFalseInRight;
                        currentCountForTrue += numberOfFalseInLeft*numberOfTrueInRight + numberOfTrueInLeft*numberOfFalseInRight + numberOfTrueInLeft*numberOfTrueInRight;
                    }
                    else if(m_operators.at(operationIndex) == '^')
                    {
                        currentCountForFalse += numberOfFalseInLeft*numberOfFalseInRight +  numberOfTrueInLeft*numberOfTrueInRight;
                        currentCountForTrue += numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
                    }
                }
                countsForFalse.setEntry(leftParenthesis, rightParenthesis, currentCountForFalse);
                countsForTrue.setEntry(leftParenthesis, rightParenthesis, currentCountForTrue);
            }
        }
        result = countsForTrue.getEntry(0, countsForTrue.getNumberOfRows()-1);
    }
    return result;
}

BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::getNumberOfWaysUsingNaiveRecursion(
        bool const expectedOutput,
        Index const leftParenthesis,
        Index const rightParenthesis) const
{
    Count result(0);
    if(leftParenthesis+1 <= rightParenthesis)  // distance should be one for at least two elements
    {
        for(Index operationIndex=leftParenthesis; operationIndex<rightParenthesis; operationIndex++)
        {
            Count numberOfFalseInLeft = getNumberOfWaysUsingNaiveRecursion(false, leftParenthesis, operationIndex);
            Count numberOfTrueInLeft = getNumberOfWaysUsingNaiveRecursion(true, leftParenthesis, operationIndex);
            Count numberOfFalseInRight = getNumberOfWaysUsingNaiveRecursion(false, operationIndex+1, rightParenthesis);
            Count numberOfTrueInRight = getNumberOfWaysUsingNaiveRecursion(true, operationIndex+1, rightParenthesis);

            if(m_operators.at(operationIndex) == '&' && !expectedOutput)
            {
                result += numberOfFalseInLeft*numberOfFalseInRight + numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
            }
            else if(m_operators.at(operationIndex) == '&' && expectedOutput)
            {
                result += numberOfTrueInLeft*numberOfTrueInRight;
            }
            else if(m_operators.at(operationIndex) == '|' && !expectedOutput)
            {
                result += numberOfFalseInLeft*numberOfFalseInRight;
            }
            else if(m_operators.at(operationIndex) == '|' && expectedOutput)
            {
                result += numberOfFalseInLeft*numberOfTrueInRight + numberOfTrueInLeft*numberOfFalseInRight + numberOfTrueInLeft*numberOfTrueInRight;
            }
            else if(m_operators.at(operationIndex) == '^' && !expectedOutput)
            {
                result += numberOfFalseInLeft*numberOfFalseInRight +  numberOfTrueInLeft*numberOfTrueInRight;
            }
            else if(m_operators.at(operationIndex) == '^' && expectedOutput)
            {
                result += numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
            }
        }
    }
    else if(leftParenthesis == rightParenthesis) // one element
    {
        result = convertBoolToCount(m_inputValues.at(leftParenthesis) == expectedOutput);
    }
    return result;
}

BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::getNumberOfWaysUsingMemoizationDP(
        CountMatrices & countMatrices,
        bool const expectedOutput,
        Index const leftParenthesis,
        Index const rightParenthesis) const
{
    Count expectedOutputIndex = convertBoolToCount(expectedOutput);
    Count result(countMatrices.at(expectedOutputIndex).getEntry(leftParenthesis, rightParenthesis));
    if(UNUSED_COUNT == result)
    {
        result = 0;
        if(leftParenthesis+1 <= rightParenthesis) // distance should be one for at least two elements
        {
            for(Index operationIndex=leftParenthesis; operationIndex<rightParenthesis; operationIndex++)
            {
                Count numberOfFalseInLeft = getNumberOfWaysUsingNaiveRecursion(false, leftParenthesis, operationIndex);
                Count numberOfTrueInLeft = getNumberOfWaysUsingNaiveRecursion(true, leftParenthesis, operationIndex);
                Count numberOfFalseInRight = getNumberOfWaysUsingNaiveRecursion(false, operationIndex+1, rightParenthesis);
                Count numberOfTrueInRight = getNumberOfWaysUsingNaiveRecursion(true, operationIndex+1, rightParenthesis);

                if(m_operators.at(operationIndex) == '&' && !expectedOutput)
                {
                    result += numberOfFalseInLeft*numberOfFalseInRight + numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
                }
                else if(m_operators.at(operationIndex) == '&' && expectedOutput)
                {
                    result += numberOfTrueInLeft*numberOfTrueInRight;
                }
                else if(m_operators.at(operationIndex) == '|' && !expectedOutput)
                {
                    result += numberOfFalseInLeft*numberOfFalseInRight;
                }
                else if(m_operators.at(operationIndex) == '|' && expectedOutput)
                {
                    result += numberOfFalseInLeft*numberOfTrueInRight + numberOfTrueInLeft*numberOfFalseInRight + numberOfTrueInLeft*numberOfTrueInRight;
                }
                else if(m_operators.at(operationIndex) == '^' && !expectedOutput)
                {
                    result += numberOfFalseInLeft*numberOfFalseInRight +  numberOfTrueInLeft*numberOfTrueInRight;
                }
                else if(m_operators.at(operationIndex) == '^' && expectedOutput)
                {
                    result += numberOfFalseInLeft*numberOfTrueInRight +  numberOfTrueInLeft*numberOfFalseInRight;
                }
            }
        }
        else if(leftParenthesis == rightParenthesis) // one element
        {
            result = convertBoolToCount(m_inputValues.at(leftParenthesis) == expectedOutput);
        }
        countMatrices[expectedOutputIndex].setEntry(leftParenthesis, rightParenthesis, result);
    }
    return result;
}

inline BooleanParenthesizationProblem::Count BooleanParenthesizationProblem::convertBoolToCount(bool const booleanValue) const
{
    return booleanValue ? 1U : 0U;
}

bool BooleanParenthesizationProblem::areSizesCorrect() const
{
    return m_operators.size()+1 == m_inputValues.size();
}

void BooleanParenthesizationProblem::initialize()
{
    // clear if invalid
    if(!areSizesCorrect())
    {
        m_inputValues.clear();
        m_operators.clear();
    }
}

}
