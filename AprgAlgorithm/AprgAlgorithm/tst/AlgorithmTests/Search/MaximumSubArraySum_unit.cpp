#include <Algorithm/Search/MaximumSubArraySum.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Values = vector<int>;
using SearchForTest = MaximumSubArraySum<Values>;
using SubArrayDetails = SearchForTest::SubArrayDetails;
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWorksOnExample1)
{
    SearchForTest search;
    Values values{-1, 2, 4, -3, 5, 2, -5, 2};

    EXPECT_EQ(10, search.getMaximumSubArraySum(values));
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWithDetailsWorksOnExample1)
{
    SearchForTest search;
    Values values{-1, 2, 4, -3, 5, 2, -5, 2};

    SubArrayDetails subArrayDetailsToVerify(search.getMaximumSubArraySumWithDetails(values));

    EXPECT_EQ(1U, subArrayDetailsToVerify.lowIndex);
    EXPECT_EQ(5U, subArrayDetailsToVerify.highIndex);
    EXPECT_EQ(10, subArrayDetailsToVerify.sum);
}

}

}
