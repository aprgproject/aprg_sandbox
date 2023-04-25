#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

namespace algorithm {

template <typename Value>
class RangeQueryForTwoDimensionsWithAccumulator {
public:
    using Index = unsigned int;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using AccumulatorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryForTwoDimensionsWithAccumulator(
        ValueMatrix const& valueMatrix, AccumulatorFunction const& accumulator,
        AccumulatorFunction const& inverseAccumulator)
        : m_partialResults(valueMatrix.getNumberOfColumns(), valueMatrix.getNumberOfRows()),
          m_accumulator(accumulator),
          m_inverseAccumulator(inverseAccumulator) {
        initialize(valueMatrix);
    }

    Value getAccumulatedValueOn2DInterval(
        Index const topLeftX, Index const topLeftY, Index const bottomRightX, Index const bottomRightY) const {
        // This works on constant time.
        // add outer retangle and inner retangle and subtract incomplete rectangles

        Value positivePart = m_accumulator(
            getPartialResultAt(bottomRightX, bottomRightY), getPartialResultAt(topLeftX - 1, topLeftY - 1));
        Value negativePart = m_accumulator(
            getPartialResultAt(topLeftX - 1, bottomRightY), getPartialResultAt(bottomRightX, topLeftY - 1));
        return m_inverseAccumulator(positivePart, negativePart);
    }

private:
    Value getPartialResultAt(int const x, int const y) const {
        Value result{};
        if (x >= 0 && x < static_cast<int>(m_partialResults.getNumberOfColumns()) && y >= 0 &&
            y < static_cast<int>(m_partialResults.getNumberOfRows())) {
            result =
                m_partialResults.getEntryConstReference(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
        }
        return result;
    }

    void initialize(ValueMatrix const& valueMatrix) {
        // Quadratic time because of the second loop.

        Value partialResultOnFirstRow{};
        for (unsigned int x = 0; x < valueMatrix.getNumberOfColumns(); x++) {
            partialResultOnFirstRow += valueMatrix.getEntryConstReference(x, 0);
            m_partialResults.setEntry(x, 0, partialResultOnFirstRow);
        }

        for (unsigned int y = 1; y < valueMatrix.getNumberOfRows(); y++) {
            Value partialResultOnRow{};
            for (unsigned int x = 0; x < valueMatrix.getNumberOfColumns(); x++) {
                partialResultOnRow += valueMatrix.getEntryConstReference(x, y);
                m_partialResults.setEntry(x, y, partialResultOnRow + m_partialResults.getEntryConstReference(x, y - 1));
            }
        }
    }

    ValueMatrix m_partialResults;
    AccumulatorFunction m_accumulator;
    AccumulatorFunction m_inverseAccumulator;
};

}  // namespace algorithm

}  // namespace alba
