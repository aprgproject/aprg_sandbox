#include <UniqueProblems/AmortizedAnalysis/TwoPointers/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Value = SubArraySum::Value;
using Values = SubArraySum::Values;
}  // namespace

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1) {
    SubArraySum search({1, 3, 2, 5, 1, 1, 2, 3});

    EXPECT_EQ((Values{2, 5, 1}), search.getSubArrayWithSum(8));
}

}  // namespace alba
