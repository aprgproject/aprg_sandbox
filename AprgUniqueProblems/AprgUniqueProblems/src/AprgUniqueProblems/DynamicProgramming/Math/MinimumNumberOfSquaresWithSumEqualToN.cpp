#include "MinimumNumberOfSquaresWithSumEqualToN.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <AprgUniqueProblems/DynamicProgramming/Other/CoinProblem.hpp>

#include <queue>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

MinimumNumberOfSquaresWithSumEqualToN::MinimumNumberOfSquaresWithSumEqualToN(
        Count const sumOfSquares)
    : m_sumOfSquares(sumOfSquares)
{}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are n calls per iteration:  O(n^n)
    // Auxiliary Space: Constant

    return getMinimumCountUsingNaiveRecursion(m_sumOfSquares);
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingMemoizationDP() const
{
    // Time Complexity: Exponential -> Since there are n calls per iteration:  O(n^n)
    // Auxiliary Space: O(n)

    Counts savedMinimumCounts(m_sumOfSquares+1, MAX_COUNT); // plus one so no more conversion
    return getMinimumCountUsingMemoizationDP(savedMinimumCounts, m_sumOfSquares);
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingIterativeDP() const
{
    // Time Complexity: O(n^(3/2))
    // Auxiliary Space: O(n)

    Counts minimumCounts(m_sumOfSquares+1, MAX_COUNT); // plus one so no more conversion
    minimumCounts[0] = 0;
    for(Count previousSumOfSquares=1; previousSumOfSquares<=m_sumOfSquares; previousSumOfSquares++)
    {
        Count entryResult(MAX_COUNT);        for(Count base=1; base*base<=previousSumOfSquares; base++)
        {
            entryResult = min(entryResult, minimumCounts.at(previousSumOfSquares-base*base)); // if difference is zero then its a perfect square
        }
        minimumCounts[previousSumOfSquares] = ++entryResult;
    }
    return minimumCounts.back();
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingBfs() const
{
    // Time Complexity: O(n^(3/2))
    // Auxiliary Space: O(n)

    Count result(MAX_COUNT);
    vector<bool> isProcessed(m_sumOfSquares+1, false);
    struct NodeDetails    {
        Count sum;
        Count count;
    };
    queue<NodeDetails> immediateNodes;
    immediateNodes.emplace(NodeDetails{m_sumOfSquares, 0});

    while(!immediateNodes.empty())
    {
        NodeDetails immediateNode(immediateNodes.front());
        immediateNodes.pop();
        if(immediateNode.sum==0)
        {
            result = min(result, immediateNode.count);
        }
        for(Count base=1; base*base<=immediateNode.sum; base++)
        {
            Count newSum = immediateNode.sum-base*base;
            if(newSum==0 || !isProcessed.at(newSum))
            {
                isProcessed[newSum] = 1;
                immediateNodes.emplace(NodeDetails{newSum, immediateNode.count+1});
            }
        }
    }
    return result;
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingFewestCoins() const
{
    CoinProblem::Coins squaredValues;
    Count highestBase = getIntegerAfterFloorOfDoubleValue<Count>(pow(m_sumOfSquares, 0.5));
    squaredValues.reserve(highestBase);
    for(Count base=1; base<=highestBase; base++)
    {
        squaredValues.emplace_back(base*base);
    }

    CoinProblem coinProblem(squaredValues);
    return coinProblem.getNumberOfFewestCoinsIterativeDP(m_sumOfSquares);
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingNaiveRecursion(
        Count const sumOfSquares) const
{
    Count result(MAX_COUNT);
    Count highestBase = getIntegerAfterFloorOfDoubleValue<Count>(pow(sumOfSquares, 0.5));
    if(sumOfSquares == highestBase*highestBase)
    {
        result = sumOfSquares>0 ? 1 : 0;
    }
    else
    {
        for(Count base=highestBase; base>=1 && result!=1; base--)
        {
            result = min(result, getMinimumCountUsingNaiveRecursion(sumOfSquares - base*base));
        }
        ++result;
    }
    return result;
}

MinimumNumberOfSquaresWithSumEqualToN::Count MinimumNumberOfSquaresWithSumEqualToN::getMinimumCountUsingMemoizationDP(
        Counts & savedMinimumCounts,
        Count const sumOfSquares) const
{
    Count result(savedMinimumCounts.at(sumOfSquares));
    if(MAX_COUNT == result)
    {
        Count highestBase = getIntegerAfterFloorOfDoubleValue<Count>(pow(sumOfSquares, 0.5));
        if(sumOfSquares == highestBase*highestBase)
        {
            result = sumOfSquares>0 ? 1 : 0;
        }
        else
        {
            for(Count base=highestBase; base>=1 && result!=1; base--)
            {
                result = min(result, getMinimumCountUsingMemoizationDP(savedMinimumCounts, sumOfSquares - base*base));
            }
            ++result;
        }        savedMinimumCounts[sumOfSquares] = result;
    }
    return result;
}

}
