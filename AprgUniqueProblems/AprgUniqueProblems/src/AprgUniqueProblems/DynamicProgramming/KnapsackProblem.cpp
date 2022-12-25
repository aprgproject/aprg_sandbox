#include "KnapsackProblem.hpp"

#include <algorithm>
#include <map>

using namespace std;

namespace alba
{

KnapsackProblem::KnapsackProblem(Values const& values)
    : m_inputValues(values)
{}

KnapsackProblem::Values KnapsackProblem::getAllPossiblePartialSums() const
{
    Values result;
    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    vector<bool> isAPossiblePartialSum(sum+1, false); // zero index is for zero value, sum index is for the sum
    isAPossiblePartialSum[0] = true;
    for(unsigned int inputIndex=0; inputIndex<m_inputValues.size(); inputIndex++)
    {
        for(int partialSumIndex=sum; partialSumIndex>=0; partialSumIndex--) // reverse traversal so that the changed values wont be changed again in one iteration
        {
            if(isAPossiblePartialSum.at(partialSumIndex))
            {
                isAPossiblePartialSum[static_cast<Value>(partialSumIndex)+m_inputValues.at(inputIndex)] = true;
            }
        }
    }
    for(unsigned int partialSumIndex=0; partialSumIndex<=sum; partialSumIndex++)
    {
        if(isAPossiblePartialSum.at(partialSumIndex))
        {
            result.emplace_back(partialSumIndex);
        }
    }
    return result;
}

KnapsackProblem::Values KnapsackProblem::getAllPossiblePartialSumsWithSquareRootAlgorithm()
{
    // Some square root algorithms are based on the following observation:
    // if a positive integer n is represented as a sum of positive integers,
    // such a sum always contains at most O(sqrt(n)) distinct numbers.
    // The reason for this is that to construct a sum that contains a maximum number of distinct numbers,
    // we should choose small numbers.
    // If we choose the numbers 1,2,...,k, the resulting sum is (k*(k+1))/2
    // Thus, the maximum amount of distinct numbers is k = O(sqrt(n)).

    // However, we can make the algorithm more efficient by using the fact that there are at most O(sqrt(n)) distinct weights.
    // Thus, we can process the weights in groups that consists of similar weights.
    // We can process each group in O(n) time, which yields an O(sqrt(n))) time algorithm.
    // The idea is to use an array that records the sums of weights that can be formed using the groups processed so far.
    // The array contains n elements: element k is 1 if the sum k can be formed and 0 otherwise.
    // To process a group of weights, we scan the array from left to right
    // and record the new sums of weights that can be formed using this group and the previous groups.

    Values result;

    map<Value, unsigned int> inputValueToCount; // divide into groups of distinct weights and count number of same weights
    for(Value const inputValue : m_inputValues) // n*log(n)
    {
        inputValueToCount.emplace(inputValue, 0U);
        inputValueToCount[inputValue]++;
    }

    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    vector<bool> isAPossiblePartialSum(sum+1, false); // zero index is for zero value, sum index is for the sum
    isAPossiblePartialSum[0] = true;

    for(auto const& inputValueAndCountPair : inputValueToCount) // sqrt(n) distinct numbers
    {
        // reverse traversal so that the changed values wont be changed again in one iteration
        for(int partialSumIndex=sum; partialSumIndex>=0; partialSumIndex--) // O(n) or linear time
        {
            if(isAPossiblePartialSum.at(partialSumIndex))
            {
                for(unsigned int i=1; i<=inputValueAndCountPair.second; i++) // near constant time
                {
                    isAPossiblePartialSum[static_cast<Value>(partialSumIndex)+(i*inputValueAndCountPair.first)] = true;
                }
            }
        }
    }
    for(unsigned int partialSumIndex=0; partialSumIndex<=sum; partialSumIndex++) // O(n) or linear time
    {
        if(isAPossiblePartialSum.at(partialSumIndex))
        {
            result.emplace_back(partialSumIndex);
        }
    }
    return result;
}

}
