#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryWithSelector {
public:
    // Example for "range query with selector" is minimum queries
    // Minimum queries are more difficult to process than sum queries.

    // Still, there is a quite simple O(nlogn) time preprocessing method after which we can answer any minimum query in
    // O(1) time.
    // Note that since minimum and maximum queries can be processed similarly, we can focus on minimum queries.

    using Index = int;
    using Value = typename Values::value_type;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using SelectorFunction = std::function<Value(Value const&, Value const&)>;

    RangeQueryWithSelector(Values const& valuesToCheck, SelectorFunction const& selector)
        : m_selectedValueMatrix(), m_selector(selector) {
        initialize(valuesToCheck);
    }

    Value getSelectedValueOnInterval(Index const start, Index const end) const {
        // This is on constant time
        Value result{};
        if (start < static_cast<Index>(m_selectedValueMatrix.getNumberOfColumns()) &&
            end < static_cast<Index>(m_selectedValueMatrix.getNumberOfColumns()))  // this condition is correct
        {
            if (start < end) {
                Index exponentOfDelta = getCeilOfLogarithmWithBase2Of(end + 1 - start) - 1;
                Index delta = get2ToThePowerOf(exponentOfDelta);  // Half of the distance that would fit
                result = m_selector(
                    m_selectedValueMatrix.getEntry(start, exponentOfDelta),
                    m_selectedValueMatrix.getEntry(end + 1 - delta, exponentOfDelta));
            } else if (start == end) {
                result = m_selectedValueMatrix.getEntry(start, 0);
            }
        }
        return result;
    }

private:
    void initialize(Values const& valuesToCheck) {
        if (!valuesToCheck.empty()) {
            Index maxExponentOf2(getCeilOfLogarithmWithBase2Of(valuesToCheck.size()));
            Index lastExponentOf2 = maxExponentOf2 > 0
                                        ? maxExponentOf2 - 1
                                        : 0;  // half (reason for minus1) of min exponent in power of 2 that would fit
            m_selectedValueMatrix = ValueMatrix(
                valuesToCheck.size(), lastExponentOf2 + 1);  // column is index, row is exponent of size with base 2
            for (Index index = 0; index < static_cast<Index>(valuesToCheck.size());
                 index++)  // put values in first column
            {
                m_selectedValueMatrix.setEntry(index, 0, valuesToCheck.at(index));
            }
            for (Index subExponentOf2 = 0; subExponentOf2 < lastExponentOf2;
                 subExponentOf2++)  // put remaining values with "powers of 2 sized" ranges
            {
                Index offset = get2ToThePowerOf(subExponentOf2);
                Index limit = valuesToCheck.size() - offset;
                for (Index index = 0; index < limit; index++) {
                    Value selectedValue(m_selector(
                        m_selectedValueMatrix.getEntry(index, subExponentOf2),
                        m_selectedValueMatrix.getEntry(index + offset, subExponentOf2)));
                    m_selectedValueMatrix.setEntry(index, subExponentOf2 + 1, selectedValue);
                }
            }
        }
    }

    Index getCeilOfLogarithmWithBase2Of(Index const size) const {
        return AlbaBitValueUtilities<Index>::getCeilOfLogarithmWithBase2Of(size);
    }

    Index get2ToThePowerOf(Index const exponent) const {
        return AlbaBitValueUtilities<Index>::get2ToThePowerOf(exponent);
    }
    ValueMatrix m_selectedValueMatrix;  // index by exponent matrix
    SelectorFunction m_selector;
};

}  // namespace algorithm

}  // namespace alba
