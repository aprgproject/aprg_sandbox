#include <AprgUniqueProblems/DynamicProgramming/Other/MaximumSubArraySum.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace
{
using SubArrayDetails = MaximumSubArraySum::SubArrayDetails;
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWorksOnExample1)
{
    MaximumSubArraySum queryForTest({-1, 2, 4, -3, 5, 2, -5, 2});

    EXPECT_EQ(10, queryForTest.getMaximumSubArraySum());
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWorksOnExample2)
{
    MaximumSubArraySum queryForTest({-6, -2, -1, -3, -5, -2, -5, -2}); // all negative  numbers

    EXPECT_EQ(-1, queryForTest.getMaximumSubArraySum());
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWithDetailsWorksOnExample1)
{
    MaximumSubArraySum queryForTest({-1, 2, 4, -3, 5, 2, -5, 2});

    SubArrayDetails subArrayDetailsToVerify(queryForTest.getMaximumSubArraySumWithDetails());

    EXPECT_EQ(1U, subArrayDetailsToVerify.lowIndex);
    EXPECT_EQ(5U, subArrayDetailsToVerify.highIndex);
    EXPECT_EQ(10, subArrayDetailsToVerify.sum);
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWithDetailsWorksOnExample2)
{
    MaximumSubArraySum queryForTest({-6, -2, -1, -3, -5, -2, -5, -2}); // all negative  numbers

    SubArrayDetails subArrayDetailsToVerify(queryForTest.getMaximumSubArraySumWithDetails());

    EXPECT_EQ(2U, subArrayDetailsToVerify.lowIndex);
    EXPECT_EQ(2U, subArrayDetailsToVerify.highIndex);
    EXPECT_EQ(-1, subArrayDetailsToVerify.sum);
}

}
