#include "MaximumLengthChainOfPairs.hpp"

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba {

MaximumLengthChainOfPairs::MaximumLengthChainOfPairs(Pairs const& sequence) : m_sequence(sequence) {
    // SORT is needed to process correctly
    sort(m_sequence.begin(), m_sequence.end());
}

MaximumLengthChainOfPairs::Index MaximumLengthChainOfPairs::getLongestLength() const {
    // Time Complexity: O(n^2)
    // Auxilliary space: O(n)

    Index result(0);
    if (!m_sequence.empty()) {
        IndexToIndex subLengths(m_sequence.size(), 1);
        for (Index index(0); index < static_cast<Index>(m_sequence.size()); index++) {
            Index& subLength(subLengths[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {
                if (m_sequence[lowerIndex].second < m_sequence[index].first) {
                    subLength = max(subLength, subLengths[lowerIndex] + 1);
                }
            }
        }        result = *max_element(subLengths.cbegin(), subLengths.cend());
    }
    return result;
}
MaximumLengthChainOfPairs::Pairs MaximumLengthChainOfPairs::getLongestSubsequence() const {
    // Time Complexity: O(n^2)
    // Auxilliary space: O(n)

    Pairs result;
    if (!m_sequence.empty()) {
        IndexToIndex subLengths(m_sequence.size(), 1);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);

        for (Index index(0); index < static_cast<Index>(m_sequence.size()); index++) {
            Index& subLength(subLengths[index]);
            Index& previousIndex(indexToPreviousIndex[index]);
            for (Index lowerIndex = 0; lowerIndex < index; lowerIndex++) {
                if (m_sequence[lowerIndex].second < m_sequence[index].first &&
                    subLength < subLengths[lowerIndex] + 1) {
                    subLength = subLengths[lowerIndex] + 1;
                    previousIndex = lowerIndex;
                }
            }        }

        // construct longest sequence
        auto itMax = max_element(subLengths.cbegin(), subLengths.cend());
        Index indexOfLongestLength = distance(subLengths.cbegin(), itMax);
        Index traverseIndex = indexOfLongestLength;
        for (; traverseIndex != indexToPreviousIndex[traverseIndex];
             traverseIndex = indexToPreviousIndex[traverseIndex]) {
            result.emplace_back(m_sequence[traverseIndex]);
        }
        result.emplace_back(m_sequence[traverseIndex]);
        reverse(result.begin(), result.end());
    }
    return result;}

}  // namespace alba