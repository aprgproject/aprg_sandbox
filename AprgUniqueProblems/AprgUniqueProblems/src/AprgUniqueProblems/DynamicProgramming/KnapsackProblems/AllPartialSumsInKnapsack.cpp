#include "AllPartialSumsInKnapsack.hpp"

#include <algorithm>
#include <map>
#include <numeric>

using namespace std;

namespace alba {

AllPartialSumsInKnapsack::AllPartialSumsInKnapsack(Values const& values) : m_inputValues(values) {}

AllPartialSumsInKnapsack::Values AllPartialSumsInKnapsack::getAllPossiblePartialSums() const {
    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    Booleans isPartialSumPossible(sum + 1, false);  // zero index is for zero value, sum index is for the sum
    isPartialSumPossible[0] = true;
    for (Value const& inputValue : m_inputValues) {
        for (Value partialSum = sum; partialSum > 0;
             partialSum--)  // reverse traversal so that the changed values wont be changed again in one iteration
        {
            if (partialSum >= inputValue && isPartialSumPossible[partialSum - inputValue]) {
                isPartialSumPossible[partialSum] = true;
            }
        }
    }
    return getAllPossiblePartialSums(isPartialSumPossible);
}

AllPartialSumsInKnapsack::Values AllPartialSumsInKnapsack::getAllPossiblePartialSumsBySettingFutureValues() const {
    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    Booleans isPartialSumPossible(sum + 1, false);  // zero index is for zero value, sum index is for the sum
    isPartialSumPossible[0] = true;
    for (Value const& inputValue : m_inputValues) {
        for (int partialSum = sum; partialSum >= 0;
             partialSum--)  // reverse traversal so that the changed values wont be changed again in one iteration
        {
            if (isPartialSumPossible[partialSum]) {
                Value possibleNextValue = static_cast<Value>(partialSum) + inputValue;
                if (possibleNextValue <= sum) {
                    isPartialSumPossible[possibleNextValue] = true;
                }
            }
        }
    }
    return getAllPossiblePartialSums(isPartialSumPossible);
}

AllPartialSumsInKnapsack::Values AllPartialSumsInKnapsack::getAllPossiblePartialSumsWithSquareRootAlgorithm() {
    // Some square root algorithms are based on the following observation:
    // if a positive integer n is represented as a sum of positive integers,
    // such a sum always contains at most O(sqrt(n)) distinct numbers.
    // The reason for this is that to construct a sum that contains a maximum number of distinct numbers,
    // we should choose small numbers.
    // If we choose the numbers 1,2,...,k, the resulting sum is (k*(k+1))/2
    // Thus, the maximum amount of distinct numbers is k = O(sqrt(n)).

    // However, we can make the algorithm more efficient by using the fact that there are at most O(sqrt(n)) distinct
    // weights. Thus, we can process the weights in groups that consists of similar weights. We can process each group
    // in O(n) time, which yields an O(sqrt(n))) time algorithm. The idea is to use an array that records the sums of
    // weights that can be formed using the groups processed so far. The array contains n elements: element k is 1 if
    // the sum k can be formed and 0 otherwise. To process a group of weights, we scan the array from left to right and
    // record the new sums of weights that can be formed using this group and the previous groups.

    map<Value, int> inputValueToCount;  // divide into groups of distinct weights and count number of same weights
    for (Value const inputValue : m_inputValues)  // n*log(n)
    {
        inputValueToCount.emplace(inputValue, 0);
        inputValueToCount[inputValue]++;
    }

    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    Booleans isPartialSumPossible(sum + 1, false);  // zero index is for zero value, sum index is for the sum
    isPartialSumPossible[0] = true;

    for (auto const& inputValueAndCountPair : inputValueToCount)  // sqrt(n) distinct numbers
    {
        // reverse traversal so that the changed values wont be changed again in one iteration
        for (int partialSumIndex = sum; partialSumIndex >= 0; partialSumIndex--)  // O(n) or linear time
        {
            if (isPartialSumPossible[partialSumIndex]) {
                for (int i = 1; i <= inputValueAndCountPair.second; i++)  // near constant time
                {
                    isPartialSumPossible[static_cast<Value>(partialSumIndex) + (i * inputValueAndCountPair.first)] =
                        true;
                }
            }
        }
    }
    return getAllPossiblePartialSums(isPartialSumPossible);
}

AllPartialSumsInKnapsack::Values AllPartialSumsInKnapsack::getAllPossiblePartialSums(
    Booleans const& isPartialSumPossible) const {
    Values result;
    for (int partialSumIndex = 0; partialSumIndex < static_cast<int>(isPartialSumPossible.size());
         partialSumIndex++)  // O(n) or linear time
    {
        if (isPartialSumPossible[partialSumIndex]) {
            result.emplace_back(partialSumIndex);
        }
    }
    return result;
}

}  // namespace alba
