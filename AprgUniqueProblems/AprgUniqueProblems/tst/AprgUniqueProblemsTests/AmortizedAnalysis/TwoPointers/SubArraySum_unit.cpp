#include <AprgUniqueProblems/AmortizedAnalysis/TwoPointers/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Value = SubArraySum::Value;
using Values = SubArraySum::Values;
}

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1)
{
    SubArraySum search({1U, 3U, 2U, 5U, 1U, 1U, 2U, 3U});

    EXPECT_EQ((Values{2U, 5U, 1U}), search.getSubArrayWithSum(8));
}

}
