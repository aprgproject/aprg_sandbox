#include "LongestIncreasingSubsequenceWithLinearithmicTime.hpp"

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba {

LongestIncreasingSubsequenceWithLinearithmicTime::LongestIncreasingSubsequenceWithLinearithmicTime(
    Values const& sequence)
    : m_sequence(sequence) {}

LongestIncreasingSubsequenceWithLinearithmicTime::Index
LongestIncreasingSubsequenceWithLinearithmicTime::getLongestLength() const {
    Index longestLength(0);
    if (!m_sequence.empty()) {
        IndexToValue lengthMinus1ToEndValue(m_sequence.size(), 0);  // dynamic programming
        lengthMinus1ToEndValue[0] = m_sequence.front();
        longestLength = 1;
        for (auto itValue = m_sequence.cbegin() + 1; itValue != m_sequence.cend(); itValue++) {
            auto beginIt = lengthMinus1ToEndValue.begin(), endIt = lengthMinus1ToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, *itValue);

            if (lowerBoundItForEndValue == endIt)  // if current value is the highest
            {
                lengthMinus1ToEndValue[longestLength++] = *itValue;  // extend
            } else {
                *lowerBoundItForEndValue = *itValue;  // replace
            }
        }
    }
    return longestLength;
}

LongestIncreasingSubsequenceWithLinearithmicTime::Values
LongestIncreasingSubsequenceWithLinearithmicTime::getLongestSubsequence() const {
    Values result;
    if (!m_sequence.empty()) {
        Index longestLength(1);
        IndexToValue lengthMinus1ToEndValue(m_sequence.size(), 0);  // length minus one because its length index
        IndexToIndex lengthMinus1ToEndIndex(m_sequence.size(), 0);
        IndexToIndex indexToPreviousIndex(m_sequence.size());
        iota(indexToPreviousIndex.begin(), indexToPreviousIndex.end(), 0);
        lengthMinus1ToEndValue[0] = m_sequence.front();
        for (Index i = 1; i < static_cast<Index>(m_sequence.size()); i++) {
            Value const& value(m_sequence[i]);
            auto beginIt = lengthMinus1ToEndValue.begin(), endIt = lengthMinus1ToEndValue.begin() + longestLength;
            auto lowerBoundItForEndValue = lower_bound(beginIt, endIt, value);

            if (lowerBoundItForEndValue == endIt)  // if current value is the highest
            {
                indexToPreviousIndex[i] = lengthMinus1ToEndIndex[longestLength - 1];
                lengthMinus1ToEndIndex[longestLength] = i;
                lengthMinus1ToEndValue[longestLength++] = value;  // extend
            } else {
                Index currentLength = distance(lengthMinus1ToEndValue.begin(), lowerBoundItForEndValue);
                if (currentLength > 0) {
                    indexToPreviousIndex[i] = lengthMinus1ToEndIndex[currentLength - 1];
                }
                lengthMinus1ToEndIndex[currentLength] = i;
                *lowerBoundItForEndValue = value;  // replace
            }
        }

        // construct longest sequence
        Index traverseIndex = lengthMinus1ToEndIndex[longestLength - 1];
        for (; traverseIndex != indexToPreviousIndex[traverseIndex];
             traverseIndex = indexToPreviousIndex[traverseIndex]) {
            result.emplace_back(m_sequence[traverseIndex]);
        }
        result.emplace_back(m_sequence[traverseIndex]);
        reverse(result.begin(), result.end());
    }
    return result;
}

}  // namespace alba
