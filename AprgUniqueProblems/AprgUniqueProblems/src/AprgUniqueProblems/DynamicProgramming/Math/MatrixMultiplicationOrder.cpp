#include "MatrixMultiplicationOrder.hpp"

using namespace std;

namespace alba
{

MatrixMultiplicationOrder::MatrixMultiplicationOrder(Dimensions const& dimensions)
    : m_dimensions(dimensions)
{}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    Count result(0);
    if(!m_dimensions.empty())
    {
        result = getMinimumNumberOfOperationsUsingNaiveRecursion(0, m_dimensions.size()-1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingTabularDP() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_dimensions.empty())
    {
        CountMatrix countMatrix(m_dimensions.size(), m_dimensions.size());

        for(Index length=2; length<m_dimensions.size(); length++)
        {
            for(Index leftParenthesis=0; leftParenthesis+length<countMatrix.getNumberOfColumns(); leftParenthesis++)
            {
                Index rightParenthesis = leftParenthesis+length;
                Count minimumCount(MAX_COUNT);
                for(Index inBetween=leftParenthesis+1; inBetween<rightParenthesis; inBetween++)
                {
                    Count currentCount = countMatrix.getEntry(leftParenthesis, inBetween)
                            + countMatrix.getEntry(inBetween, rightParenthesis)
                            + m_dimensions.at(leftParenthesis) * m_dimensions.at(inBetween) * m_dimensions.at(rightParenthesis);
                    minimumCount = min(minimumCount, currentCount);
                }
                countMatrix.setEntry(leftParenthesis, rightParenthesis, minimumCount);
            }
        }
        result = countMatrix.getEntry(0, countMatrix.getNumberOfRows()-1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingMemoizationDP() const
{
    // Time Complexity: O(n^3) (should be same as Tabular DP)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_dimensions.empty())
    {
        CountMatrix countMatrix(m_dimensions.size(), m_dimensions.size(), MAX_COUNT);
        result = getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, 0, m_dimensions.size()-1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingNaiveRecursion(
        Index const leftParenthesis,
        Index const rightParenthesis) const
{
    Count result(0);
    if(leftParenthesis+2 <= rightParenthesis) // distance should be two for at least three elements
    {
        result = MAX_COUNT;
        for(Index inBetween=leftParenthesis+1; inBetween<rightParenthesis; inBetween++)
        {
            Count currentCount = getMinimumNumberOfOperationsUsingNaiveRecursion(leftParenthesis, inBetween)
                    + getMinimumNumberOfOperationsUsingNaiveRecursion(inBetween, rightParenthesis)
                    + m_dimensions.at(leftParenthesis) * m_dimensions.at(inBetween) * m_dimensions.at(rightParenthesis);
            result = min(result, currentCount);
        }
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingMemoizationDP(
        CountMatrix & countMatrix,
        Index const leftParenthesis,
        Index const rightParenthesis) const
{
    Count result(countMatrix.getEntry(leftParenthesis, rightParenthesis));
    if(MAX_COUNT == result)
    {
        if(leftParenthesis+2 <= rightParenthesis) // distance should be two for at least three elements
        {
            // result is already set to MAX_COUNT so we can proceed on using min
            for(Index inBetween=leftParenthesis+1; inBetween<rightParenthesis; inBetween++)            {
                Count currentCount = getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, leftParenthesis, inBetween)
                        + getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, inBetween, rightParenthesis)
                        + m_dimensions.at(leftParenthesis) * m_dimensions.at(inBetween) * m_dimensions.at(rightParenthesis);
                result = min(result, currentCount);
            }
        }
        else
        {
            result = 0;
        }
        countMatrix.setEntry(leftParenthesis, rightParenthesis, result);
    }
    return result;
}
}