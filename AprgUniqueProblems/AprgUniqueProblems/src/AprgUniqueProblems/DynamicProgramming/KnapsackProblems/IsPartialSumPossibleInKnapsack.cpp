#include "IsPartialSumPossibleInKnapsack.hpp"

#include <algorithm>

using namespace std;

namespace alba {

IsPartialSumPossibleInKnapsack::IsPartialSumPossibleInKnapsack(Value const targetSum, Values const& values)
    : m_targetSum(targetSum), m_inputValues(values) {}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingNaiveRecursion() const {
    // Time Complexity: O(2^n)
    // -> In the worst case, this solution tries two possibilities (whether to include or exclude) for every element.
    // The problem is in-fact NP-Complete (There is no known polynomial time solution for this problem).
    // Auxiliary Space: O(1)

    bool result(false);
    if (!m_inputValues.empty()) {
        result = isPartialSumPossibleUsingNaiveRecursion(m_targetSum, 0);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingMemoizationDP() const {
    // Time Complexity: O(sum*n) (same as iterative)
    // Auxiliary Space: O(sum*n)

    bool result(false);
    if (!m_inputValues.empty()) {
        StateMatrix stateMatrix(m_targetSum + 1, m_inputValues.size() + 1, State::Unused);
        for (Index valueIndex = 0; valueIndex < stateMatrix.getNumberOfRows(); valueIndex++) {
            stateMatrix.setEntry(0, valueIndex, State::True);
        }
        result = isPartialSumPossibleUsingMemoizationDP(stateMatrix, m_targetSum, 0);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingIterativeDP() const {
    // Time Complexity: O(sum*n)
    // Auxiliary Space: O(sum*n)

    bool result(false);
    if (!m_inputValues.empty()) {
        BooleanMatrix isPossibleMatrix(m_targetSum + 1, m_inputValues.size() + 1, false);
        for (Index valueIndex = 0; valueIndex < isPossibleMatrix.getNumberOfRows(); valueIndex++) {
            isPossibleMatrix.setEntry(0, valueIndex, true);
        }
        for (Value partialSum = 1; partialSum <= m_targetSum; partialSum++) {
            for (Index valueIndex = 1; valueIndex <= m_inputValues.size(); valueIndex++) {
                Value previousValue(m_inputValues.at(valueIndex - 1));
                bool isPossible(isPossibleMatrix.getEntry(partialSum, valueIndex - 1));  // get previous entry result
                if (!isPossible && partialSum >= previousValue) {
                    isPossible =
                        isPossibleMatrix.getEntry(partialSum - previousValue, valueIndex - 1);  // use previous value
                }
                isPossibleMatrix.setEntry(partialSum, valueIndex, isPossible);
            }
        }
        result = isPossibleMatrix.getEntry(
            isPossibleMatrix.getNumberOfColumns() - 1, isPossibleMatrix.getNumberOfRows() - 1);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingIterativeDPAndSpaceEfficient() const {
    // Time Complexity: O(sum * n)
    // Auxiliary Space: O(sum)

    bool result(false);
    if (!m_inputValues.empty()) {
        Booleans isPartialSumPossible(m_targetSum + 1, false);
        isPartialSumPossible[0] = true;
        for (Value const& inputValue : m_inputValues)  // input values are only used values
        {
            for (Value partialSum(m_targetSum); partialSum > 0;
                 partialSum--)  // reverse traversal so that the changed values wont be changed again in one iteration
            {
                if (partialSum >= inputValue && isPartialSumPossible.at(partialSum - inputValue)) {
                    isPartialSumPossible[partialSum] = true;
                }
            }
        }
        result = isPartialSumPossible.at(m_targetSum);
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingNaiveRecursion(
    Value const partialSum, Index const valueIndex) const {
    bool result(false);
    if (valueIndex < m_inputValues.size()) {
        Value currentValue(m_inputValues.at(valueIndex));
        if (partialSum == currentValue) {
            result = true;
        } else if (partialSum > currentValue) {
            result = isPartialSumPossibleUsingNaiveRecursion(partialSum, valueIndex + 1)  // skip value
                     || isPartialSumPossibleUsingNaiveRecursion(
                            partialSum - currentValue, valueIndex + 1);  // reserve value to sum
        } else                                                           // partialSum < currentValue
        {
            result = isPartialSumPossibleUsingNaiveRecursion(partialSum, valueIndex + 1);  // skip value
        }
    }
    return result;
}

bool IsPartialSumPossibleInKnapsack::isPartialSumPossibleUsingMemoizationDP(
    StateMatrix& stateMatrix, Value const partialSum, Index const valueIndex) const {
    State resultState = stateMatrix.getEntry(partialSum, valueIndex);
    if (State::Unused == resultState) {
        bool result(false);
        if (valueIndex < m_inputValues.size()) {
            Value currentValue(m_inputValues.at(valueIndex));
            if (partialSum >= currentValue) {
                result = isPartialSumPossibleUsingMemoizationDP(stateMatrix, partialSum, valueIndex + 1)  // skip value
                         || isPartialSumPossibleUsingMemoizationDP(
                                stateMatrix, partialSum - currentValue, valueIndex + 1);  // reserve value to sum
            } else {
                result = isPartialSumPossibleUsingMemoizationDP(stateMatrix, partialSum, valueIndex + 1);  // skip value
            }
        }
        stateMatrix.setEntry(partialSum, valueIndex, result ? State::True : State::False);
        return result;
    } else {
        return (State::True == resultState) ? true : false;
    }
}

}  // namespace alba
