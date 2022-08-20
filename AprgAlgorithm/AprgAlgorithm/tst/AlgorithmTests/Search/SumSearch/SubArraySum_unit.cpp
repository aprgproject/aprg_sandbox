#include <Algorithm/Search/SumSearch/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SumSearch = SubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
}

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1)
{
    SumSearch search;
    ValuesForTest valuesToTest{1U, 3U, 2U, 5U, 1U, 1U, 2U, 3U};

    ValuesForTest valuesToVerify(search.getSubArrayWithSum(8U, valuesToTest));

    ValuesForTest valuesToExpect{2U, 5U, 1U};
    EXPECT_EQ(valuesToExpect, valuesToVerify);
}

}
}