#include "FindTheMinimumCostToReachDestinationUsingATrain.hpp"

using namespace std;

namespace alba {

FindTheMinimumCostToReachDestinationUsingATrain::FindTheMinimumCostToReachDestinationUsingATrain(
    ValueMatrix const& prices)
    : m_pricesAtEachStation(prices) {
    clearIfInvalid();
}

FindTheMinimumCostToReachDestinationUsingATrain::Value
FindTheMinimumCostToReachDestinationUsingATrain::getMinimumCostUsingNaiveRecursion() const {
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(n^n)
    // Auxiliary Space: O(1)

    Value result(0);
    if (!m_pricesAtEachStation.isEmpty()) {
        result = getMinimumCostUsingNaiveRecursion(m_pricesAtEachStation.getNumberOfColumns() - 1);
    }
    return result;
}

FindTheMinimumCostToReachDestinationUsingATrain::Value
FindTheMinimumCostToReachDestinationUsingATrain::getMinimumCostUsingMemoizationDP() const {
    // Time Complexity: O(n^2) (same as iterative)
    // Auxiliary Space: O(1)

    Value result(0);
    if (!m_pricesAtEachStation.isEmpty()) {
        Values savedCosts(m_pricesAtEachStation.getNumberOfColumns(), static_cast<Value>(UNUSED_VALUE));
        result = getMinimumCostUsingMemoizationDP(savedCosts, m_pricesAtEachStation.getNumberOfColumns() - 1);
    }
    return result;
}

FindTheMinimumCostToReachDestinationUsingATrain::Value
FindTheMinimumCostToReachDestinationUsingATrain::getMinimumCostUsingIterativeDP() const {
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(1)

    Value result(0);
    if (!m_pricesAtEachStation.isEmpty()) {
        Values savedCosts(m_pricesAtEachStation.getNumberOfColumns(), 0);
        for (Index endStation = 1; endStation < static_cast<Index>(savedCosts.size()); endStation++) {
            Value entryResult(MAX_VALUE);
            for (Index immediateStation = 0; immediateStation < endStation; immediateStation++) {
                entryResult =
                    min(entryResult,
                        savedCosts[immediateStation] + m_pricesAtEachStation.getEntry(immediateStation, endStation));
            }
            savedCosts[endStation] = entryResult;
        }        result = savedCosts.back();
    }
    return result;
}
FindTheMinimumCostToReachDestinationUsingATrain::Value
FindTheMinimumCostToReachDestinationUsingATrain::getMinimumCostUsingNaiveRecursion(Index const endStation) const {
    Value result(0);
    if (endStation > 0) {
        result = MAX_VALUE;
        for (int immediateStation = static_cast<int>(endStation) - 1; immediateStation >= 0; immediateStation--) {
            result =
                min(result, getMinimumCostUsingNaiveRecursion(immediateStation) +
                                m_pricesAtEachStation.getEntry(immediateStation, endStation));
        }
    }
    return result;
}

FindTheMinimumCostToReachDestinationUsingATrain::Value
FindTheMinimumCostToReachDestinationUsingATrain::getMinimumCostUsingMemoizationDP(
    Values& savedCosts, Index const endStation) const {
    Value result(savedCosts[endStation]);
    if (UNUSED_VALUE == result) {
        result = 0;
        if (endStation > 0) {            result = MAX_VALUE;
            for (int immediateStation = static_cast<int>(endStation) - 1; immediateStation >= 0; immediateStation--) {
                result =
                    min(result, getMinimumCostUsingNaiveRecursion(immediateStation) +                                    m_pricesAtEachStation.getEntry(immediateStation, endStation));
            }
        }
        savedCosts[endStation] = result;
    }
    return result;
}

void FindTheMinimumCostToReachDestinationUsingATrain::clearIfInvalid() {
    if (m_pricesAtEachStation.getNumberOfColumns() != m_pricesAtEachStation.getNumberOfRows()) {
        m_pricesAtEachStation.clearAndResize(0, 0);
    }
}

}  // namespace alba
