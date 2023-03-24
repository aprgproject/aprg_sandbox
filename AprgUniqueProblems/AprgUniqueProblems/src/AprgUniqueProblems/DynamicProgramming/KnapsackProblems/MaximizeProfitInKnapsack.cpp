#include "MaximizeProfitInKnapsack.hpp"

using namespace std;

namespace alba
{

MaximizeProfitInKnapsack::MaximizeProfitInKnapsack(
        Weight const maximumWeight,
        Items const items)
    : m_maximumWeight(maximumWeight)
    , m_items(items)
{}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingNaiveRecursion() const
{
    // Time Complexity: O(2^n)
    // Auxiliary Space: O(1)

    return getBestProfitUsingNaiveRecursion(m_maximumWeight, 0);
}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingMemoizationDP() const
{
    // Time Complexity: O(N*W).
    // -> As redundant calculations of states are avoided.
    // Auxiliary Space: O(N*W).
    // -> The use of 2D array data structure for storing intermediate states.

    Profit result(0);
    if(!m_items.empty())
    {
        ProfitMatrix profitMatrix(m_maximumWeight+1, m_items.size()+1, static_cast<Profit>(UNUSED_VALUE));
        result = getBestProfitUsingMemoizationDP(profitMatrix, m_maximumWeight, 0);
    }
    return result;
}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingIterativeDP() const
{
    // Time Complexity: O(N*W).
    // -> where ‘N’ is the number of weight element and ‘W’ is capacity. As for every weight element we traverse through all weight capacities 1<=w<=W.
    // Auxiliary Space: O(N*W).
    // -> The use of 2-D array of size ‘N*W’.

    Profit result(0);
    if(!m_items.empty())
    {
        ProfitMatrix profitMatrix(m_maximumWeight+1, m_items.size()+1, 0);
        Weight smallestItemWeight(getSmallestItemWeight());
        for(int itemIndex=static_cast<int>(m_items.size())-1; itemIndex>=0; itemIndex--)
        {
            Weight itemWeight(m_items.at(itemIndex).first);
            Profit itemProfit(m_items.at(itemIndex).second);
            for(Weight weight(smallestItemWeight); weight<profitMatrix.getNumberOfColumns(); weight++)
            {
                if(weight >= itemWeight)
                {
                    Profit profit = max(profitMatrix.getEntry(weight, itemIndex+1),
                                        itemProfit + profitMatrix.getEntry(weight-itemWeight, itemIndex+1));
                    profitMatrix.setEntry(weight, itemIndex, profit);
                }
            }
        }
        result = profitMatrix.getEntry(profitMatrix.getNumberOfColumns()-1, 0);
    }
    return result;
}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingIterativeDPAndSpaceEfficient() const
{
    // Complexity Analysis:
    // Time Complexity: O(N*W). As redundant calculations of states are avoided.
    // Auxiliary Space: O(W).  As we are using 1-D array instead of 2-D array.

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one row above and previous column is always to the left,
    // we only really need 1 row (not a matrix) to keep track partial values.

    Profit result(0);
    if(!m_items.empty())
    {
        Profits weightToProfit(m_maximumWeight+1, 0U);
        Weight smallestItemWeight(getSmallestItemWeight());
        for(Item const& item : m_items)
        {
            Weight itemWeight(item.first);
            Profit itemProfit(item.second);

            for(Weight weight=m_maximumWeight; weight>=smallestItemWeight; weight--) // reverse traversal to avoid accessing already computed values
            {
                if(weight >= itemWeight)
                {
                    weightToProfit[weight] = max(weightToProfit.at(weight), weightToProfit.at(weight-itemWeight)+itemProfit);
                }
            }
        }
        result = weightToProfit.back();
    }
    return result;
}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingNaiveRecursion(
        Weight const remainingWeight,
        ItemIndex const itemIndex) const
{
    Profit result(0);
    if(itemIndex < m_items.size())
    {
        Weight itemWeight(m_items.at(itemIndex).first);
        Profit itemProfit(m_items.at(itemIndex).second);
        if(remainingWeight >= itemWeight)
        {
            result = max(getBestProfitUsingNaiveRecursion(remainingWeight, itemIndex+1),
                         itemProfit + getBestProfitUsingNaiveRecursion(remainingWeight-itemWeight, itemIndex+1));
        }
    }
    return result;
}

MaximizeProfitInKnapsack::Profit MaximizeProfitInKnapsack::getBestProfitUsingMemoizationDP(
        ProfitMatrix & profitMatrix,
        Weight const remainingWeight,
        ItemIndex const itemIndex) const
{
    Profit result = profitMatrix.getEntry(remainingWeight, itemIndex);
    if(UNUSED_VALUE == result)
    {
        result = 0;
        if(itemIndex < m_items.size())
        {
            Weight itemWeight(m_items.at(itemIndex).first);
            Profit itemProfit(m_items.at(itemIndex).second);
            if(remainingWeight >= itemWeight)
            {
                result = max(getBestProfitUsingMemoizationDP(profitMatrix, remainingWeight, itemIndex+1),
                             itemProfit + getBestProfitUsingMemoizationDP(profitMatrix, remainingWeight-itemWeight, itemIndex+1));
            }
        }
        profitMatrix.setEntry(remainingWeight, itemIndex, result);
    }
    return result;
}

MaximizeProfitInKnapsack::Weight MaximizeProfitInKnapsack::getSmallestItemWeight() const
{
    Weight result(m_items.front().first);
    for(auto it=m_items.cbegin()+1; it!=m_items.cend(); it++)
    {
        result = min(result, it->first);
    }
    return result;
}

}
