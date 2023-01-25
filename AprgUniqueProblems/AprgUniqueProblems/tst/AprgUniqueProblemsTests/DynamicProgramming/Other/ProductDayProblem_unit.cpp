#include <AprgUniqueProblems/DynamicProgramming/Other/ProductDayProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using PriceMatrix=ProductDayProblem::PriceMatrix;
}

TEST(ProductDayProblemTest, GetMinimumPriceWorksOnExample1)
{
    PriceMatrix pricesInDayByProduct(8U, 3U,
    {6U, 9U, 5U, 2U, 8U, 9U, 1U, 6U,     8U, 2U, 6U, 2U, 7U, 5U, 7U, 2U,
     5U, 3U, 9U, 7U, 3U, 5U, 1U, 4U});
    ProductDayProblem queryForTest(pricesInDayByProduct);

    EXPECT_EQ(5U, queryForTest.getMinimumPriceUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getMinimumPriceUsingTabularDP());
}

}