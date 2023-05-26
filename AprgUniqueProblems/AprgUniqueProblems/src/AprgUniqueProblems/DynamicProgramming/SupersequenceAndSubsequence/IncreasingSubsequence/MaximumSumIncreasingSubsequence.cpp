#include "MaximumSumIncreasingSubsequence.hpp"

#include <numeric>

using namespace std;

namespace alba {

MaximumSumIncreasingSubsequence::MaximumSumIncreasingSubsequence(Values const& sequence) : m_sequence(sequence) {}

MaximumSumIncreasingSubsequence::Value MaximumSumIncreasingSubsequence::getMaximumSum() const {
    // Quadratic time because of double loop

    Value result(0);
    if (!m_sequence.empty()) {
        Values partialSums(m_sequence.size(), 0);
        for (Index index(0); index < static_cast<Index>(m_sequence.size()); index++) {
            Value& partialSum(partialSums[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {
                if (m_sequence.at(lowerIndex) < m_sequence.at(index)) {                    partialSum = max(partialSum, partialSums.at(lowerIndex));
                }
            }
            partialSum += m_sequence.at(index);        }
        result = *max_element(partialSums.cbegin(), partialSums.cend());
    }
    return result;
}

MaximumSumIncreasingSubsequence::Values MaximumSumIncreasingSubsequence::getSubsequenceWithMaximumSum() const {
    // Quadratic time because of double loop

    Values result;
    if (!m_sequence.empty()) {
        Values partialSums(m_sequence.size(), 0);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index(0); index < static_cast<Index>(m_sequence.size()); index++) {
            Value& partialSum(partialSums[index]);
            Value& previousIndex(indexToPreviousIndex[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {                if (m_sequence.at(lowerIndex) < m_sequence.at(index) && partialSum < partialSums.at(lowerIndex)) {
                    partialSum = partialSums.at(lowerIndex);
                    previousIndex = lowerIndex;
                }            }
            partialSum += m_sequence.at(index);
        }

        // construct longest sequence
        auto itMax = max_element(partialSums.cbegin(), partialSums.cend());
        Index indexOfMaxSum = distance(partialSums.cbegin(), itMax);
        Index traverseIndex = indexOfMaxSum;
        for (; traverseIndex != indexToPreviousIndex.at(traverseIndex);
             traverseIndex = indexToPreviousIndex.at(traverseIndex)) {
            result.emplace_back(m_sequence.at(traverseIndex));
        }
        result.emplace_back(m_sequence.at(traverseIndex));
        reverse(result.begin(), result.end());
    }
    return result;
}

}  // namespace alba
