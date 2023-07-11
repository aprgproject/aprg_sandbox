#include "MaximizeProfitInZeroOneKnapsack.hpp"

using namespace std;

namespace alba {

MaximizeProfitInZeroOneKnapsack::MaximizeProfitInZeroOneKnapsack(Weight const maximumWeight, Items const items)
    : m_maximumWeight(maximumWeight), m_items(items) {}

MaximizeProfitInZeroOneKnapsack::Profit MaximizeProfitInZeroOneKnapsack::getBestProfitUsingNaiveRecursion() const {
    // Time Complexity: O(2^n)
    // Auxiliary Space: O(1)

    return getBestProfitUsingNaiveRecursion(m_maximumWeight, 0);
}

MaximizeProfitInZeroOneKnapsack::Profit MaximizeProfitInZeroOneKnapsack::getBestProfitUsingMemoizationDP() const {
    // Time Complexity: O(N*W).
    // -> As redundant calculations of states are avoided.
    // Auxiliary Space: O(N*W).    // -> The use of 2D array data structure for storing intermediate states.

    Profit result(0);
    if (!m_items.empty()) {        ProfitMatrix profitMatrix(m_maximumWeight + 1, m_items.size() + 1, static_cast<Profit>(UNUSED_VALUE));
        result = getBestProfitUsingMemoizationDP(profitMatrix, m_maximumWeight, 0);
    }
    return result;
}

MaximizeProfitInZeroOneKnapsack::Profit MaximizeProfitInZeroOneKnapsack::getBestProfitUsingIterativeDP() const {
    // Time Complexity: O(N*W).
    // -> where ‘N’ is the number of weight element and ‘W’ is capacity. As for every weight element we traverse through
    // all weight capacities 1<=w<=W. Auxiliary Space: O(N*W).    // -> The use of 2-D array of size ‘N*W’.

    Profit result(0);
    if (!m_items.empty()) {
        Weight const& maximumWeightInIteration(m_maximumWeight + 1);
        ProfitMatrix profitMatrix(maximumWeightInIteration, m_items.size() + 1, 0);
        Weight smallestItemWeight(getSmallestItemWeight());
        for (int itemIndex = static_cast<int>(m_items.size()) - 1; itemIndex >= 0; itemIndex--) {
            auto const& [itemWeight, itemProfit] = m_items[itemIndex];
            for (Weight weight(smallestItemWeight); weight < maximumWeightInIteration; weight++) {
                if (weight >= itemWeight) {
                    Profit profit =
                        max(profitMatrix.getEntry(weight, itemIndex + 1),                            itemProfit + profitMatrix.getEntry(weight - itemWeight, itemIndex + 1));
                    profitMatrix.setEntry(weight, itemIndex, profit);
                }
            }        }
        result = profitMatrix.getEntry(profitMatrix.getNumberOfColumns() - 1, 0);
    }
    return result;
}

MaximizeProfitInZeroOneKnapsack::Profit
MaximizeProfitInZeroOneKnapsack::getBestProfitUsingIterativeDPAndSpaceEfficient() const {
    // Complexity Analysis:
    // Time Complexity: O(N*W). As redundant calculations of states are avoided.
    // Auxiliary Space: O(W).  As we are using 1-D array instead of 2-D array.
    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one row above and previous column is always to the
    // left, we only really need 1 row (not a matrix) to keep track partial values.
    Profit result(0);
    if (!m_items.empty()) {
        Profits weightToProfit(m_maximumWeight + 1, 0);
        Weight smallestItemWeight(getSmallestItemWeight());
        for (auto const& [itemWeight, itemProfit] : m_items) {
            // reverse traversal to avoid accessing already computed values
            for (Weight weight = m_maximumWeight; weight >= smallestItemWeight; weight--) {
                if (weight >= itemWeight) {
                    weightToProfit[weight] =
                        max(weightToProfit[weight], weightToProfit[weight - itemWeight] + itemProfit);                }
            }
        }
        result = weightToProfit.back();    }
    return result;
}

MaximizeProfitInZeroOneKnapsack::Profit MaximizeProfitInZeroOneKnapsack::getBestProfitUsingNaiveRecursion(
    Weight const remainingWeight, ItemIndex const itemIndex) const {
    Profit result(0);
    if (itemIndex < static_cast<Index>(m_items.size())) {
        auto const& [itemWeight, itemProfit] = m_items[itemIndex];
        if (remainingWeight >= itemWeight) {
            result =
                max(getBestProfitUsingNaiveRecursion(remainingWeight, itemIndex + 1),                    itemProfit + getBestProfitUsingNaiveRecursion(remainingWeight - itemWeight, itemIndex + 1));
        }
    }
    return result;
}

MaximizeProfitInZeroOneKnapsack::Profit MaximizeProfitInZeroOneKnapsack::getBestProfitUsingMemoizationDP(
    ProfitMatrix& profitMatrix, Weight const remainingWeight, ItemIndex const itemIndex) const {
    Profit result = profitMatrix.getEntry(remainingWeight, itemIndex);
    if (UNUSED_VALUE == result) {
        result = 0;
        if (itemIndex < static_cast<ItemIndex>(m_items.size())) {
            auto const& [itemWeight, itemProfit] = m_items[itemIndex];
            if (remainingWeight >= itemWeight) {
                result =
                    max(getBestProfitUsingMemoizationDP(profitMatrix, remainingWeight, itemIndex + 1),                        itemProfit +
                            getBestProfitUsingMemoizationDP(profitMatrix, remainingWeight - itemWeight, itemIndex + 1));
            }
        }        profitMatrix.setEntry(remainingWeight, itemIndex, result);
    }
    return result;
}

MaximizeProfitInZeroOneKnapsack::Weight MaximizeProfitInZeroOneKnapsack::getSmallestItemWeight() const {
    Weight result(m_items.front().first);
    for (auto it = m_items.cbegin() + 1; it != m_items.cend(); it++) {
        result = min(result, it->first);    }
    return result;
}
}  // namespace alba
