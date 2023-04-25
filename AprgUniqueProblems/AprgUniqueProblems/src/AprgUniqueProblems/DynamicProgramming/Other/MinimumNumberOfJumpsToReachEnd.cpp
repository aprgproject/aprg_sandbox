#include "MinimumNumberOfJumpsToReachEnd.hpp"

#include <numeric>

using namespace std;

namespace alba {

MinimumNumberOfJumpsToReachEnd::MinimumNumberOfJumpsToReachEnd(Counts const& sequence) : m_sequence(sequence) {}

MinimumNumberOfJumpsToReachEnd::Count MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingNaiveRecursion()
    const {
    // Time complexity: O(n^n).
    // -> There are maximum n possible ways to move from a element.
    // -> So maximum number of steps can be N^N so the upperbound of time complexity is O(n^n)
    // Auxiliary Space: O(1).
    // -> There is no space required (if recursive stack space is ignored).

    Count result(0);
    if (!m_sequence.empty()) {
        result = getMinimumNumberOfJumpsUsingNaiveRecursion(0);
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Count MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingMemoizationDP()
    const {
    // Time complexity: O(n^2). (same as iterative DP)
    // Auxiliary Space: O(n).

    Count result(0);
    if (!m_sequence.empty()) {
        Counts indexToCountOfJumps(m_sequence.size(), static_cast<Count>(MAX_COUNT));
        result = getMinimumNumberOfJumpsUsingMemoizationDP(indexToCountOfJumps, 0);
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Count MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingIterativeDP() const {
    // Time complexity: O(n^2).
    // -> Nested traversal of the array is needed.
    // Auxiliary Space: O(n).
    // -> To store the DP array linear space is needed.

    Count result(MAX_COUNT);
    if (!m_sequence.empty()) {
        Counts indexToCountOfJumps(m_sequence.size(), static_cast<Count>(MAX_COUNT));
        indexToCountOfJumps[0] = 0;
        for (Index startOfJumpIndex(0); startOfJumpIndex < m_sequence.size(); startOfJumpIndex++) {
            Count countOfJumps = indexToCountOfJumps.at(startOfJumpIndex) + 1;
            Index maxPossibleJumpIndex =
                min(startOfJumpIndex + m_sequence.at(startOfJumpIndex), static_cast<Index>(m_sequence.size() - 1));
            for (Index endOfJumpIndex = startOfJumpIndex + 1; endOfJumpIndex <= maxPossibleJumpIndex;
                 endOfJumpIndex++) {
                Count& countOfJumpsAtIndex(indexToCountOfJumps[endOfJumpIndex]);
                countOfJumpsAtIndex = min(countOfJumpsAtIndex, countOfJumps);
            }
        }
        result = indexToCountOfJumps.back();
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Count
MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingIterativeDPAndTimeEfficient() const {
    // Time complexity: O(n).
    // -> Only one traversal of the array is needed.
    // Auxiliary Space: O(1).
    // -> There is no space required.

    Count result(MAX_COUNT);
    if (!m_sequence.empty()) {
        Count jumpCount(0);
        Count maxIndexAtNextJump(m_sequence.front());
        Count stepsAtCurrentJump(m_sequence.front());
        for (Index index(1); index <= maxIndexAtNextJump; index++) {
            maxIndexAtNextJump =
                min(max(maxIndexAtNextJump, index + m_sequence.at(index)), static_cast<Index>(m_sequence.size() - 1));
            stepsAtCurrentJump--;
            if (stepsAtCurrentJump == 0) {
                stepsAtCurrentJump = maxIndexAtNextJump - index;
                jumpCount++;
            }
        }
        result = jumpCount;
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Indices MinimumNumberOfJumpsToReachEnd::getPathOfMinimumNumberOfJumps() const {
    // Linear

    Indices result;
    if (!m_sequence.empty()) {
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        Count jumpCount(0);
        Count maxIndexAtNextJump(m_sequence.front());
        Count stepsAtCurrentJump(m_sequence.front());
        Index startOfJump = 0, startOfNextJump = 0;
        for (Index index(1); index <= maxIndexAtNextJump; index++) {
            indexToPreviousIndex[index] = startOfJump;

            Index nextJumpIndex = min(index + m_sequence.at(index), static_cast<Index>(m_sequence.size() - 1));
            if (nextJumpIndex > maxIndexAtNextJump) {
                maxIndexAtNextJump = nextJumpIndex;
                startOfNextJump = index;
            }

            stepsAtCurrentJump--;
            if (stepsAtCurrentJump == 0) {
                stepsAtCurrentJump = maxIndexAtNextJump - index;
                startOfJump = startOfNextJump;
                jumpCount++;
            }
        }

        // construct path
        Index traverseIndex = m_sequence.size() - 1;
        for (; traverseIndex != indexToPreviousIndex.at(traverseIndex);
             traverseIndex = indexToPreviousIndex.at(traverseIndex)) {
            result.emplace_back(m_sequence.at(traverseIndex));
        }
        result.emplace_back(m_sequence.at(traverseIndex));
        reverse(result.begin(), result.end());
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Count MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingNaiveRecursion(
    Index const startOfJumpIndex) const {
    Count result(0);
    if (startOfJumpIndex + 1 < m_sequence.size()) {
        result = MAX_COUNT;
        Index maxPossibleJumpIndex =
            min(startOfJumpIndex + m_sequence.at(startOfJumpIndex), static_cast<Index>(m_sequence.size() - 1));
        for (Index endOfJumpIndex = startOfJumpIndex + 1; endOfJumpIndex <= maxPossibleJumpIndex; endOfJumpIndex++) {
            result = min(result, getMinimumNumberOfJumpsUsingNaiveRecursion(endOfJumpIndex));
        }
        result++;
    }
    return result;
}

MinimumNumberOfJumpsToReachEnd::Count MinimumNumberOfJumpsToReachEnd::getMinimumNumberOfJumpsUsingMemoizationDP(
    Counts& indexToCountOfJumps, Index const startOfJumpIndex) const {
    Count result(indexToCountOfJumps.at(startOfJumpIndex));
    if (MAX_COUNT == result) {
        if (startOfJumpIndex + 1 < m_sequence.size()) {
            // result is already MAX_COUNT
            Index maxPossibleJumpIndex =
                min(startOfJumpIndex + m_sequence.at(startOfJumpIndex), static_cast<Index>(m_sequence.size() - 1));
            for (Index endOfJumpIndex = startOfJumpIndex + 1; endOfJumpIndex <= maxPossibleJumpIndex;
                 endOfJumpIndex++) {
                result = min(result, getMinimumNumberOfJumpsUsingMemoizationDP(indexToCountOfJumps, endOfJumpIndex));
            }
            result++;
        } else {
            result = 0;
        }
        indexToCountOfJumps[startOfJumpIndex] = result;
    }
    return result;
}

}  // namespace alba
