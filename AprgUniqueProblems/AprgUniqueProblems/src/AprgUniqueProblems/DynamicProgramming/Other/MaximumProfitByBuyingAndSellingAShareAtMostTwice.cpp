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
        Values profit(m_prices.size(), 0U);

        Value maxPriceAtTheRight = m_prices.back();
        for (Index right = m_prices.size() - 1; right > 0; right--) {
            Index left = right - 1;
            if (m_prices.at(left) > maxPriceAtTheRight) {
                maxPriceAtTheRight = m_prices.at(left);
            }
            profit[left] = max(profit.at(right), maxPriceAtTheRight - m_prices.at(left));
        }

        Value minPriceAtTheLeft = m_prices.front();
        for (Index right = 1; right < m_prices.size(); right++) {
            Index left = right - 1;
            if (m_prices.at(right) < minPriceAtTheLeft) {
                minPriceAtTheLeft = m_prices.at(right);
            }
            profit[right] = max(profit.at(left), profit.at(right) + m_prices.at(right) - minPriceAtTheLeft);
        }
        result = profit.back();
    }
    return result;
}

}  // namespace alba
