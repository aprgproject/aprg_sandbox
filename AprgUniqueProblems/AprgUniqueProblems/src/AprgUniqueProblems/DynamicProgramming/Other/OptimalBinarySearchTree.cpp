#include "OptimalBinarySearchTree.hpp"

#include <Algorithm/Search/RangeQuery/RangeQueryWithAccumulator.hpp>

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

OptimalBinarySearchTree::OptimalBinarySearchTree(ValueAndFrequencyPairs const& valueAndFrequencyPairs)
    : m_valueAndFrequencyPairs(valueAndFrequencyPairs)
{
    initialize();
}

OptimalBinarySearchTree::Cost OptimalBinarySearchTree::getMinimumCostUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Cost result(0);
    if(!m_valueAndFrequencyPairs.empty())
    {
        result = getMinimumCostUsingNaiveRecursion(1, 0, m_valueAndFrequencyPairs.size()-1);
    }
    return result;
}

OptimalBinarySearchTree::Cost OptimalBinarySearchTree::getMinimumCostUsingIterativeDP() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Cost result(0);
    if(!m_valueAndFrequencyPairs.empty())
    {        Index numberOfPairs = m_valueAndFrequencyPairs.size();
        CostMatrix costMatrix(numberOfPairs, numberOfPairs);

        Frequencies frequencies;
        frequencies.reserve(numberOfPairs);
        transform(m_valueAndFrequencyPairs.cbegin(), m_valueAndFrequencyPairs.cend(), back_inserter(frequencies), [](ValueAndFrequencyPair const& pair)
        {
            return pair.second;
        });
        RangeQueryWithAccumulator<Frequencies> frequencyRange(frequencies, plus<Frequency>(), minus<Frequency>());


        for(Index index=0; index<numberOfPairs; index++) // length = 1
        {
            costMatrix.setEntry(index, index, m_valueAndFrequencyPairs.at(index).second);
        }
        for(Index length=2; length<=numberOfPairs; length++) // length >= 2
        {
            for(Index left=0; left+length<=costMatrix.getNumberOfColumns(); left++)
            {
                Index right = left+length-1;
                Cost entryResult(MAX_COUNT);
                Cost offsetCost(frequencyRange.getAccumulatedValueOnInterval(left, right)); // pattern when going down with depth
                for(Index possibleParent=left; possibleParent<=right; possibleParent++)
                {
                    Cost costOfPossibleParent(offsetCost);
                    if(left<possibleParent)
                    {
                        costOfPossibleParent += costMatrix.getEntry(left, possibleParent-1); // left child
                    }
                    if(possibleParent<right)
                    {
                        costOfPossibleParent += costMatrix.getEntry(possibleParent+1, right); // right child
                    }
                    entryResult = min(entryResult, costOfPossibleParent);
                }
                costMatrix.setEntry(left, right, entryResult);
            }
        }
        result = costMatrix.getEntry(0, costMatrix.getNumberOfRows()-1);
    }
    return result;
}

OptimalBinarySearchTree::Cost OptimalBinarySearchTree::getMinimumCostUsingNaiveRecursion(
        Cost const depth,
        Index const left,
        Index const right) const
{
    Cost result(0);
    if(left <= right)
    {
        result = MAX_COUNT;
        for(Index possibleParent=left; possibleParent<=right; possibleParent++)
        {
            Cost costOfPossibleParent(getCost(depth, m_valueAndFrequencyPairs.at(possibleParent).second));
            if(left<possibleParent)
            {
                costOfPossibleParent += getMinimumCostUsingNaiveRecursion(depth+1, left, possibleParent-1); // left child
            }
            if(possibleParent<right)
            {
                costOfPossibleParent += getMinimumCostUsingNaiveRecursion(depth+1, possibleParent+1, right); // right child
            }
            result = min(result, costOfPossibleParent);
        }
    }
    return result;
}

// inline optimization can work here because the usage belongs to same translation unit
inline OptimalBinarySearchTree::Cost OptimalBinarySearchTree::getCost(
        Cost const depth,
        Cost const frequency) const
{
    return depth*frequency;
}

void OptimalBinarySearchTree::initialize()
{
    sortByValue();
}

void OptimalBinarySearchTree::sortByValue()
{
    sort(m_valueAndFrequencyPairs.begin(), m_valueAndFrequencyPairs.end(), [](
         ValueAndFrequencyPair const& pair1,
         ValueAndFrequencyPair const& pair2)
    {
        return pair1.first < pair2.first;
    });
}

}
