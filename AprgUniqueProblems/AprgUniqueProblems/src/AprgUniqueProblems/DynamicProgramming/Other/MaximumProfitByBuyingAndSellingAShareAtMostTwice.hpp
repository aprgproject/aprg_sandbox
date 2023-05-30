#pragma once

#include <limits>
#include <vector>

namespace alba {

class MaximumProfitByBuyingAndSellingAShareAtMostTwice  // the largest possible sum of a sequence of consecutive values
                                                        // in the array
{
public:
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    static constexpr Index MAX_NUMBER_OF_TRANSACTIONS = 2;

    MaximumProfitByBuyingAndSellingAShareAtMostTwice(Values const& prices);

    Value getMaximumProfitUsingIterativeDP() const;

private:
    Values const m_prices;
};

}  // namespace alba

// Maximum profit by buying and selling a share at most twice

// In daily share trading, a buyer buys shares in the morning and sells them on the same day.
// If the trader is allowed to make at most 2 transactions in a day,
// whereas the second transaction can only start after the first one is complete (Buy->sell->Buy->sell).
// Given stock prices throughout the day, find out the maximum profit that a share trader could have made.

// Examples:
// Input:   price[] = {10, 22, 5, 75, 65, 80}
// -> Output:  87
// -> Trader earns 87 as sum of 12, 75
// -> Buy at 10, sell at 22,
// -> Buy at 5 and sell at 80
// Input:   price[] = {2, 30, 15, 10, 8, 25, 80}
// -> Output:  100
// -> Trader earns 100 as sum of 28 and 72
// -> Buy at price 2, sell at 30, buy at 8 and sell at 80
// -> Input:   price[] = {100, 30, 15, 10, 8, 25, 80};
// Output:  72
// -> Buy at price 8 and sell at 80.
// -> Input:   price[] = {90, 80, 70, 60, 50}
// -> Output:  0
// -> Not possible to earn.
