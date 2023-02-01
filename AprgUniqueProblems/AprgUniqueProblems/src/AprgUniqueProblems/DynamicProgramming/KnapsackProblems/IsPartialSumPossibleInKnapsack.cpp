#include "IsPartialSumPossibleInKnapsack.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

IsPartialSumPossibleInKnapsack::IsPartialSumPossibleInKnapsack(
        Value const targetSum,
        Values const& values)
    : m_targetSum(targetSum)
    , m_inputValues(values)
{}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingNaiveRecursion() const
{
    // Time Complexity: O(2^n)
    // -> In the worst case, this solution tries two possibilities (whether to include or exclude) for every element.
    // Auxiliary Space: O(1)

    bool result(false);
    if(!m_inputValues.empty())
    {
        result = isPartialSumPossibleUsingNaiveRecursion(m_targetSum, 0);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingMemoizationDP() const
{
    // Time Complexity: O(sum*n) (same as tabular)
    // Auxiliary Space: O(sum*n)

    bool result(false);
    if(!m_inputValues.empty())
    {
        StateMatrix stateMatrix(m_targetSum+1, m_inputValues.size()+1, State::Unused);
        for(Index valueIndex=0; valueIndex<stateMatrix.getNumberOfRows(); valueIndex++)
        {
            stateMatrix.setEntry(0, valueIndex, State::True);
        }
        result = isPartialSumPossibleUsingMemoizationDP(stateMatrix, m_targetSum, 0);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingTabularDP() const
{
    // Time Complexity: O(sum*n)
    // Auxiliary Space: O(sum*n)

    bool result(false);
    if(!m_inputValues.empty())
    {
        BooleanMatrix isPossibleMatrix(m_targetSum+1, m_inputValues.size()+1, false);
        for(Index valueIndex=0; valueIndex<isPossibleMatrix.getNumberOfRows(); valueIndex++)
        {
            isPossibleMatrix.setEntry(0, valueIndex, true);
        }
        for(Value partialSum=1; partialSum<=m_targetSum; partialSum++)
        {
            for(int valueIndex=static_cast<int>(m_inputValues.size())-1; valueIndex>=0; valueIndex--)
            {
                Value currentValue(m_inputValues.at(valueIndex));
                if(partialSum >= currentValue)
                {
                    bool entryResult = isPossibleMatrix.getEntry(partialSum, valueIndex+1)
                            || isPossibleMatrix.getEntry(partialSum-currentValue, valueIndex+1);
                    isPossibleMatrix.setEntry(partialSum, valueIndex, entryResult);
                }
            }
        }
        result = isPossibleMatrix.getEntry(m_targetSum, 0U);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingTabularDPAndSpaceEfficient() const
{
    // Time Complexity: O(sum * n)
    // Auxiliary Space: O(sum)

    bool result(false);
    if(!m_inputValues.empty())
    {
        Booleans isPartialSumPossible(m_targetSum+1, false);
        isPartialSumPossible[0] = true;
        for(Value const& currentValue : m_inputValues)
        {
            for(Value partialSum(m_targetSum); partialSum>0; partialSum--) // reverse traversal so that the changed values wont be changed again in one iteration
            {
                if(partialSum >= currentValue && isPartialSumPossible.at(partialSum-currentValue))
                {
                    isPartialSumPossible[partialSum] = true;
                }
            }
        }
        result = isPartialSumPossible.at(m_targetSum);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingNaiveRecursion(
        Value const partialSum,
        Index const valueIndex) const
{
    bool result(false);
    if(valueIndex < m_inputValues.size())
    {
        Value currentValue(m_inputValues.at(valueIndex));
        if(partialSum > currentValue)
        {
            result =  isPartialSumPossibleUsingNaiveRecursion(partialSum, valueIndex+1)
                    || isPartialSumPossibleUsingNaiveRecursion(partialSum-currentValue, valueIndex+1);
        }
        else if(partialSum == currentValue)
        {
            result = true;
        }
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingMemoizationDP(
        StateMatrix & stateMatrix,
        Value const partialSum,
        Index const valueIndex) const
{
    State resultState = stateMatrix.getEntry(partialSum, valueIndex);
    if(State::Unused == resultState)
    {
        bool result(false);
        if(valueIndex < m_inputValues.size())
        {
            Value currentValue(m_inputValues.at(valueIndex));
            if(partialSum >= currentValue)
            {
                result = isPartialSumPossibleUsingMemoizationDP(stateMatrix, partialSum, valueIndex+1)
                        || isPartialSumPossibleUsingMemoizationDP(stateMatrix, partialSum-currentValue, valueIndex+1);
            }
        }
        stateMatrix.setEntry(partialSum, valueIndex, result ? State::True : State::False);
        return result;
    }
    else
    {
        return (State::True==resultState) ? true : false;
    }
}

}
