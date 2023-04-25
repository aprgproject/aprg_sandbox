#pragma once

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryWithBinaryIndexedTree {
public:
    // This supports "accumulator" type queries.
    // Example for "range query with accumulator" is sum queries
    // We can easily process sum queries on a static array by constructing a prefix sum array.
    // Each value in the prefix sum array equals the sum of values in the original array up to that position, i.e., the
    // value at position k is sumq(0,k).

    // A binary indexed tree or a Fenwick tree can be seen as a dynamic variant of a prefix sum array.
    // It supports two O(logn) time operations on an array: processing a range sum query and updating a value.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using AccumulatorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithBinaryIndexedTree(
        Values const& valuesToCheck, AccumulatorFunction const& accumulator,
        AccumulatorFunction const& inverseAccumulator)
        : m_values(valuesToCheck),
          m_partialTreeSums(),
          m_accumulator(accumulator),
          m_inverseAccumulator(inverseAccumulator) {
        initializePartialSums();
    }

    Value getAccumulatedValueOnInterval(Index const start, Index const end) const {
        // This has log(N) running time
        Value result{};
        if (start <= end && start < m_partialTreeSums.size() && end < m_partialTreeSums.size()) {
            // No possibility to find a partial sum because binary index tree does not guarantee a common index when
            // traversing from different two indexes.
            if (0 < start) {
                result = m_inverseAccumulator(
                    getAccumulatedValueFrom0ToIndex(end), getAccumulatedValueFrom0ToIndex(start - 1));
            } else if (0 == start) {
                result = getAccumulatedValueFrom0ToIndex(end);
            }
        }
        return result;
    }

    Value getAccumulatedValueFrom0ToIndex(Index const index) const {
        // This has log(N) running time
        Value result{};
        if (index < m_partialTreeSums.size()) {
            // Indexes here have plus one (for easier end loop conditions)
            Index indexPlusOne(index + 1);
            result = m_partialTreeSums.at(indexPlusOne - 1);
            indexPlusOne -= getGreatestPowerOf2Factor(indexPlusOne);
            while (0 < indexPlusOne) {
                result = m_accumulator(result, m_partialTreeSums.at(indexPlusOne - 1));
                indexPlusOne -= getGreatestPowerOf2Factor(indexPlusOne);
            }
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has log(N) running time
        if (index < m_values.size()) {
            // Indexes here have plus one (for easier end loop conditions)
            Value delta = m_inverseAccumulator(newValue, m_values.at(index));
            Index indexPlusOne(index + 1);
            while (indexPlusOne <= m_partialTreeSums.size())  // update partial sums
            {
                m_partialTreeSums[indexPlusOne - 1] = m_accumulator(m_partialTreeSums.at(indexPlusOne - 1), delta);
                indexPlusOne += getGreatestPowerOf2Factor(indexPlusOne);
            }
            m_values[index] = newValue;
        }
    }

private:
    void initializePartialSums() {
        // This has N*log(N) running time
        m_partialTreeSums.reserve(m_values.size());
        // Indexes here have plus one (for easier end loop conditions)
        for (Index indexPlusOne = 1; indexPlusOne <= m_values.size(); indexPlusOne++) {
            Index powerOf2Factor(getGreatestPowerOf2Factor(indexPlusOne));
            m_partialTreeSums.emplace_back(getPartialTreeSum(powerOf2Factor, indexPlusOne));
        }
        m_partialTreeSums.shrink_to_fit();
    }

    Value getPartialTreeSum(unsigned int const powerOf2Factor, unsigned int const indexPlusOne) const {
        // This has log(N) running time
        Value result(m_values.at(indexPlusOne - 1));
        unsigned int powerOf2FactorForPartialSum = powerOf2Factor / 2;
        for (unsigned int indexPlusOneForPartialSum = indexPlusOne - powerOf2FactorForPartialSum;
             powerOf2FactorForPartialSum > 0;
             powerOf2FactorForPartialSum /= 2, indexPlusOneForPartialSum += powerOf2FactorForPartialSum) {
            // continuously accumulate partial sums (located at power of 2 distances) to get new partial sum
            result = m_accumulator(result, m_partialTreeSums.at(indexPlusOneForPartialSum - 1));
        }
        return result;
    }

    Index getGreatestPowerOf2Factor(Index const index) const { return mathHelper::getGreatestPowerOf2Factor(index); }

    Values m_values;
    Values m_partialTreeSums;
    AccumulatorFunction m_accumulator;
    AccumulatorFunction m_inverseAccumulator;
};

}  // namespace algorithm

}  // namespace alba
