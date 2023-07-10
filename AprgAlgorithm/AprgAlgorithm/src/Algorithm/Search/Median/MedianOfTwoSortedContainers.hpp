#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
class MedianOfTwoSortedContainers {
public:
    using Index = int;
    using Value = typename Values::value_type;
    using ConstIterator = typename Values::const_iterator;

    MedianOfTwoSortedContainers(Values const& sortedValues1, Values const& sortedValues2)
        : m_container1(getContainer1(sortedValues1, sortedValues2)),
          m_container2(getContainer2(sortedValues1, sortedValues2)) {}

    Value getMedian() const {
        if (m_container1.empty() && m_container2.empty()) {
            return Value{};
        } else {
            return getMedianAtLeastOneContainerIsNotEmpty();
        }
    }

private:
    Value getMedianAtLeastOneContainerIsNotEmpty() const {
        // Running time: O(log(container1)*log(container2))

        int medianSize = (m_container1.size() + m_container2.size() + 1) / 2;
        int lowIndexOn1 = 0, highIndexOn1 = m_container1.size() - 1;
        while (lowIndexOn1 < highIndexOn1) {
            int midIndexOn1 = getMidpointOfIndexes(lowIndexOn1, highIndexOn1);
            int totalAtMid = getTotalOnBothContainers(midIndexOn1);
            if (totalAtMid < medianSize) {
                lowIndexOn1 = midIndexOn1 + 1;
            } else if (medianSize < totalAtMid) {
                highIndexOn1 = midIndexOn1 - 1;
            } else {
                lowIndexOn1 = midIndexOn1;
                break;
            }
        }
        int totalCountOnLowerBound = getTotalOnBothContainers(lowIndexOn1);
        if (lowIndexOn1 > 0 && totalCountOnLowerBound > medianSize) {
            --lowIndexOn1;
            totalCountOnLowerBound = getTotalOnBothContainers(lowIndexOn1);
        }

        int indexOn2 = getCorrespondingIndexOn2(lowIndexOn1);
        indexOn2 += medianSize - totalCountOnLowerBound;
        return getValueAtBorder(lowIndexOn1, indexOn2);
    }

    Values const& getContainer1(Values const& container1, Values const& container2) const {
        // Container 1 should be not empty
        return !container1.empty() ? container1 : container2;
    }

    Values const& getContainer2(Values const& container1, Values const& container2) const {
        // Container 2 can be empty
        return !container1.empty() ? container2 : container1;
    }

    int getTotalOnBothContainers(int const indexOn1) const { return indexOn1 + 1 + getCountOn2(indexOn1); }

    int getCorrespondingIndexOn2(int const indexOn1) const { return getCountOn2(indexOn1) - 1; }

    int getCountOn2(int const indexOn1) const {
        // count =  distance + 1 - 1
        // + 1, because its distance and we need to count the first element
        // - 1, since the return of lower bound is the first element that does not satisfy element < value
        auto it = std::lower_bound(m_container2.cbegin(), m_container2.cend(), m_container1[indexOn1]);
        if (it != m_container2.cend()) {
            return std::distance(m_container2.cbegin(), it);
        } else {
            return m_container2.size();
        }
    }

    Value getValueAtBorder(int const indexOn1, int const indexOn2) const {
        if (!m_container2.empty()) {
            return std::max(m_container1[indexOn1], m_container2[indexOn2]);
        } else {
            return m_container1[indexOn1];
        }
    }

    Values const& m_container1;
    Values const& m_container2;
};

}  // namespace algorithm

}  // namespace alba
