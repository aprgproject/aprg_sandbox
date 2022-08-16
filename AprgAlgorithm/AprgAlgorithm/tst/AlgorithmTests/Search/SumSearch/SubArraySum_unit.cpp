#include <Algorithm/Search/SumSearch/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using SumSearch = SubArraySum<ValueForTest>;
using ValuesForTest = SumSearch::Values;
}

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1)
{
    SumSearch search({1U, 3U, 2U, 5U, 1U, 1U, 2U, 3U});

    ValuesForTest expectedValues{2U, 5U, 1U};
    EXPECT_EQ(expectedValues, search.getSubArrayWithSum(8));
}

}

}
