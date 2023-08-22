#include <UniqueProblems/DynamicProgramming/Other/ProductDayProblem.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using PriceMatrix = ProductDayProblem::PriceMatrix;
}

TEST(ProductDayProblemTest, GetMinimumPriceWorksOnExample1) {
    PriceMatrix pricesInDayByProduct(8, 3, {6, 9, 5, 2, 8, 9, 1, 6, 8, 2, 6, 2, 7, 5, 7, 2, 5, 3, 9, 7, 3, 5, 1, 4});
    ProductDayProblem queryForTest(pricesInDayByProduct);

    EXPECT_EQ(5, queryForTest.getMinimumPriceUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getMinimumPriceUsingIterativeDP());
}

}  // namespace alba
