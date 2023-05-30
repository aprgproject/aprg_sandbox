#include "MaximizeProfitInCuttingARod.hpp"

using namespace std;

namespace alba {

MaximizeProfitInCuttingARod::MaximizeProfitInCuttingARod(Length const length, Rods const rods)
    : m_length(length), m_rods(rods) {}

MaximizeProfitInCuttingARod::Profit MaximizeProfitInCuttingARod::getBestProfitUsingNaiveRecursion() const {
    // Time Complexity: O(n^r)
    // Auxiliary Space: O(1)

    return getBestProfitUsingNaiveRecursion(m_length);
}

MaximizeProfitInCuttingARod::Profit MaximizeProfitInCuttingARod::getBestProfitUsingMemoizationDP() const {
    // Time Complexity: O(n^2).
    // Auxiliary Space: O(n).

    Profit result(0);
    if (!m_rods.empty()) {
        Profits partialProfits(m_length + 1, static_cast<Profit>(UNUSED_PROFIT));
        result = getBestProfitUsingMemoizationDP(partialProfits, m_length);
    }
    return result;
}

MaximizeProfitInCuttingARod::Profit MaximizeProfitInCuttingARod::getBestProfitUsingIterativeDP() const {
    // Time Complexity: O(n^2).
    // Auxiliary Space: O(n).

    Profit result(0);
    if (!m_rods.empty()) {
        Profits partialProfits(m_length + 1, 0);
        Length smallestItemLength(getSmallestItemLength());
        for (Length remainingLength = smallestItemLength; remainingLength < static_cast<Length>(partialProfits.size());
             remainingLength++) {
            Profit entryResult(0);
            for (Rod const& rod : m_rods) {
                Length rodLength(rod.first);
                Profit rodProfit(rod.second);
                if (remainingLength >= rodLength) {
                    entryResult = max(entryResult, rodProfit + partialProfits.at(remainingLength - rodLength));
                }
            }
            partialProfits[remainingLength] = entryResult;
        }
        result = partialProfits.back();
    }
    return result;
}

MaximizeProfitInCuttingARod::Profit MaximizeProfitInCuttingARod::getBestProfitUsingNaiveRecursion(
    Length const remainingLength) const {
    Profit result(0);
    for (Rod const& rod : m_rods) {
        Length rodLength(rod.first);
        Profit rodProfit(rod.second);
        if (remainingLength >= rodLength) {
            result = max(result, rodProfit + getBestProfitUsingNaiveRecursion(remainingLength - rodLength));
        }
    }
    return result;
}

MaximizeProfitInCuttingARod::Profit MaximizeProfitInCuttingARod::getBestProfitUsingMemoizationDP(
    Profits& partialProfits, Length const remainingLength) const {
    Profit result = partialProfits.at(remainingLength);
    if (UNUSED_PROFIT == result) {
        result = 0;
        for (Rod const& rod : m_rods) {
            Length rodLength(rod.first);
            Profit rodProfit(rod.second);
            if (remainingLength >= rodLength) {
                result = max(
                    result, rodProfit + getBestProfitUsingMemoizationDP(partialProfits, remainingLength - rodLength));
            }
        }
        partialProfits[remainingLength] = result;
    }
    return result;
}

MaximizeProfitInCuttingARod::Length MaximizeProfitInCuttingARod::getSmallestItemLength() const {
    Length result(m_rods.front().first);
    for (auto it = m_rods.cbegin() + 1; it != m_rods.cend(); it++) {
        result = min(result, it->first);
    }
    return result;
}

}  // namespace alba
