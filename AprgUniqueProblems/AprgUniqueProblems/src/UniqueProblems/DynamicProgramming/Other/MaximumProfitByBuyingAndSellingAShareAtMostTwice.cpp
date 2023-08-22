#include "MaximumProfitByBuyingAndSellingAShareAtMostTwice.hpp"

#include <queue>

using namespace std;

namespace alba {

MaximumProfitByBuyingAndSellingAShareAtMostTwice::MaximumProfitByBuyingAndSellingAShareAtMostTwice(Values const& prices)
    : m_prices(prices) {}

MaximumProfitByBuyingAndSellingAShareAtMostTwice::Value
MaximumProfitByBuyingAndSellingAShareAtMostTwice::getMaximumProfitUsingIterativeDP() const {
    // Time Complexity: O(prices)
    // Auxiliary Space: O(prices)

    Value result(0);
    if (!m_prices.empty()) {
        Values profit(m_prices.size(), 0);

        Value maxPriceAtTheRight = m_prices.back();
        for (Index right = m_prices.size() - 1; right > 0; right--) {
            Index left = right - 1;
            if (m_prices[left] > maxPriceAtTheRight) {
                maxPriceAtTheRight = m_prices[left];
            }
            profit[left] = max(profit[right], maxPriceAtTheRight - m_prices[left]);
        }

        Value minPriceAtTheLeft = m_prices.front();
        for (Index right = 1; right < static_cast<Index>(m_prices.size()); right++) {
            Index left = right - 1;
            if (m_prices[right] < minPriceAtTheLeft) {
                minPriceAtTheLeft = m_prices[right];
            }
            profit[right] = max(profit[left], profit[right] + m_prices[right] - minPriceAtTheLeft);
        }
        result = profit.back();
    }
    return result;
}

}  // namespace alba
