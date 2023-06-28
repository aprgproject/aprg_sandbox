#include "LongestEqualLengthSubArraysWithSameSum.hpp"

#include <Algorithm/Search/RangeQuery/RangeQueryWithAccumulator.hpp>

#include <functional>

using namespace alba::algorithm;
using namespace std;

namespace alba {

LongestEqualLengthSubArraysWithSameSum::LongestEqualLengthSubArraysWithSameSum(Values const& values)
    : m_values(values) {}

LongestEqualLengthSubArraysWithSameSum::Index
LongestEqualLengthSubArraysWithSameSum::getLongestTotalLengthOfSubArraysUsingPartialSums() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n)

    Index result(0);

    RangeQueryWithAccumulator<Values> partialSumsQuery(m_values, plus<>(), minus<>());
    for (Index subArrayLength = m_values.size() / 2; subArrayLength > 0;
         subArrayLength--)  // starts with highest length
    {
        for (Index startOfSubArray1 = 0; startOfSubArray1 + (2 * subArrayLength) <= static_cast<Index>(m_values.size());
             startOfSubArray1++) {
            Index startOfSubArray2 = startOfSubArray1 + subArrayLength;
            Value sum1 =
                partialSumsQuery.getAccumulatedValueOnInterval(startOfSubArray1, startOfSubArray1 + subArrayLength - 1);
            Value sum2 =
                partialSumsQuery.getAccumulatedValueOnInterval(startOfSubArray2, startOfSubArray2 + subArrayLength - 1);
            if (sum1 == sum2) {
                result = subArrayLength * 2;
            }
        }
    }
    return result;
}

LongestEqualLengthSubArraysWithSameSum::Index
LongestEqualLengthSubArraysWithSameSum::getLongestTotalLengthOfSubArraysByAccumulatingSum() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(1)

    Index result(0);
    for (Index startOfSubArray2 = 1; startOfSubArray2 < static_cast<Index>(m_values.size()); startOfSubArray2++) {
        Index endOfSubArray1 = startOfSubArray2 - 1;
        Index subArrayLength = 0;
        Value sum1(0), sum2(0);
        while (endOfSubArray1 >= subArrayLength &&
               startOfSubArray2 + subArrayLength < static_cast<Index>(m_values.size())) {
            sum1 += m_values[endOfSubArray1 - subArrayLength];
            sum2 += m_values[startOfSubArray2 + subArrayLength];
            ++subArrayLength;
            if (sum1 == sum2) {
                result = max(result, subArrayLength * 2);
            }
        }
    }
    return result;
}

}  // namespace alba
