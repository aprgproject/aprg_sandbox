#include <UniqueProblems/DynamicProgramming/Other/MaximumProfitByBuyingAndSellingAShareAtMostTwice.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(
    MaximumProfitByBuyingAndSellingAShareAtMostTwiceTest,
    GetMaximumProfitByBuyingAndSellingAShareAtMostTwiceWorksOnExample1) {
    MaximumProfitByBuyingAndSellingAShareAtMostTwice queryForTest({10, 22, 5, 75, 65, 80});

    EXPECT_EQ(87, queryForTest.getMaximumProfitUsingIterativeDP());
}

TEST(
    MaximumProfitByBuyingAndSellingAShareAtMostTwiceTest,
    GetMaximumProfitByBuyingAndSellingAShareAtMostTwiceWorksOnExample2) {
    MaximumProfitByBuyingAndSellingAShareAtMostTwice queryForTest({2, 30, 15, 10, 8, 25, 80});

    EXPECT_EQ(100, queryForTest.getMaximumProfitUsingIterativeDP());
}

TEST(
    MaximumProfitByBuyingAndSellingAShareAtMostTwiceTest,
    GetMaximumProfitByBuyingAndSellingAShareAtMostTwiceWorksOnExample3) {
    MaximumProfitByBuyingAndSellingAShareAtMostTwice queryForTest({100, 30, 15, 10, 8, 25, 80});

    EXPECT_EQ(72, queryForTest.getMaximumProfitUsingIterativeDP());
}

TEST(
    MaximumProfitByBuyingAndSellingAShareAtMostTwiceTest,
    GetMaximumProfitByBuyingAndSellingAShareAtMostTwiceWorksOnExample4) {
    MaximumProfitByBuyingAndSellingAShareAtMostTwice queryForTest({90, 80, 70, 60, 50});

    EXPECT_EQ(0, queryForTest.getMaximumProfitUsingIterativeDP());
}

}  // namespace alba
