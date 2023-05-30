#include <AprgUniqueProblems/DynamicProgramming/Grid/MaximumSubMatrixSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using ValueMatrix = MaximumSubMatrixSum::ValueMatrix;
using SubArrayDetails = MaximumSubMatrixSum::SubArrayDetails;
}  // namespace

TEST(MaximumSubMatrixSumTest, GetMaximumSubMatrixSumWorksOnExample1) {
    ValueMatrix pricesInDayByProduct(5, 4, {1, 2, -1, -4, -20, -8, -3, 4, 2, 1, 3, 8, 10, 1, 3, -4, -1, 1, 7, -6});
    MaximumSubMatrixSum queryForTest(pricesInDayByProduct);

    EXPECT_EQ(29, queryForTest.getMaximumSubMatrixSum());
}

TEST(MaximumSubMatrixSumTest, GetMaximumSubMatrixSumWithDetailsWorksOnExample1) {
    ValueMatrix pricesInDayByProduct(5, 4, {1, 2, -1, -4, -20, -8, -3, 4, 2, 1, 3, 8, 10, 1, 3, -4, -1, 1, 7, -6});
    MaximumSubMatrixSum queryForTest(pricesInDayByProduct);

    SubArrayDetails subArrayDetailsToVerify(queryForTest.getMaximumSubMatrixSumWithDetails());

    EXPECT_EQ(1, subArrayDetailsToVerify.left);
    EXPECT_EQ(4, subArrayDetailsToVerify.right);
    EXPECT_EQ(1, subArrayDetailsToVerify.up);
    EXPECT_EQ(3, subArrayDetailsToVerify.down);
    EXPECT_EQ(29, subArrayDetailsToVerify.sum);
}

}  // namespace alba
