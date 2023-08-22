#include "BranchAndBoundZeroAndOneKnapsack.hpp"

#include <algorithm>
#include <queue>

using namespace std;

namespace alba {

BranchAndBoundZeroAndOneKnapsack::Profit BranchAndBoundZeroAndOneKnapsack::getBestProfit(
    Weight const maximumWeight, Items const& items) const {
    Items sortedItems(items);
    sort(sortedItems.begin(), sortedItems.end(), [](Item const& item1, Item const& item2) {
        return static_cast<double>(item1.first) / item1.second > static_cast<double>(item2.first) / item2.second;
    });

    Index itemSize = items.size();
    Profit bestProfit(0);
    queue<Node> remainingNodes;
    remainingNodes.push(Node{-1, 0, 0, 0});
    while (!remainingNodes.empty()) {
        Node currentNode = remainingNodes.front();
        remainingNodes.pop();

        if (currentNode.level == itemSize - 1) {
            continue;
        }

        Node nextNode;
        nextNode.level = currentNode.level + 1;
        // include item for first possible node
        nextNode.weight = currentNode.weight + items[nextNode.level].first;
        nextNode.profit = currentNode.profit + items[nextNode.level].second;
        if (nextNode.weight <= maximumWeight && nextNode.profit > bestProfit) {
            // update the best profit if possible
            bestProfit = nextNode.profit;
        }
        nextNode.maxPossibleProfit = getMaxPossibleProfit(nextNode, maximumWeight, items);
        if (bestProfit < nextNode.maxPossibleProfit) {
            // branch and bound: only include nodes with higher possible profit
            remainingNodes.push(nextNode);
        }

        // remove item for second possible node
        nextNode.weight = currentNode.weight;
        nextNode.profit = currentNode.profit;
        nextNode.maxPossibleProfit = getMaxPossibleProfit(nextNode, maximumWeight, items);
        if (bestProfit < nextNode.maxPossibleProfit) {
            // branch and bound: only include nodes with higher possible profit
            remainingNodes.push(nextNode);
        }
    }
    return bestProfit;
}

BranchAndBoundZeroAndOneKnapsack::Profit BranchAndBoundZeroAndOneKnapsack::getMaxPossibleProfit(
    Node const& currentNode, Weight const maximumWeight, Items const& items) const {
    if (currentNode.weight < maximumWeight) {
        Index itemIndex = currentNode.level + 1;
        Profit maxPossibleProfit = currentNode.profit;
        Weight totalWeight = currentNode.weight;
        Index itemSize = items.size();
        while (itemIndex < itemSize && totalWeight + items[itemIndex].first <= maximumWeight) {
            totalWeight += items[itemIndex].first;
            maxPossibleProfit += items[itemIndex].second;
            itemIndex++;
        }
        if (itemIndex < itemSize) {
            // for fractional part
            maxPossibleProfit += (maximumWeight - totalWeight) * items[itemIndex].second / items[itemIndex].first;
        }
        return maxPossibleProfit;
    }
    return 0;
}

}  // namespace alba
