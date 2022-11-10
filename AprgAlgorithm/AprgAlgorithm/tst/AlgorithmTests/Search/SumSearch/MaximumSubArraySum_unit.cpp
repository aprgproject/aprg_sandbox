#include <Algorithm/Search/SumSearch/MaximumSubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<int>;
using SumSearch = MaximumSubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using SubArrayDetailsForTest = SumSearch::SubArrayDetails;
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWorksOnExample1)
{
    ValuesForTest valuesToTest{-1, 2, 4, -3, 5, 2, -5, 2};
    SumSearch search(valuesToTest);

    EXPECT_EQ(10, search.getMaximumSubArraySum());
}

TEST(MaximumSubArraySumTest, GetMaximumSubArraySumWithDetailsWorksOnExample1)
{
    ValuesForTest valuesToTest{-1, 2, 4, -3, 5, 2, -5, 2};
    SumSearch search(valuesToTest);

    SubArrayDetailsForTest subArrayDetailsToVerify(search.getMaximumSubArraySumWithDetails());

    EXPECT_EQ(1U, subArrayDetailsToVerify.lowIndex);
    EXPECT_EQ(5U, subArrayDetailsToVerify.highIndex);
    EXPECT_EQ(10, subArrayDetailsToVerify.sum);
}

}

}
