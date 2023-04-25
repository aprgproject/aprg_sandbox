#include <Algorithm/Search/SumSearch/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using SumSearch = SubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
}  // namespace

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1) {
    ValuesForTest valuesToTest{1U, 3U, 2U, 5U, 1U, 1U, 2U, 3U};
    SumSearch search(valuesToTest);

    ValuesForTest valuesToVerify(search.getSubArrayWithSum(8U));

    ValuesForTest valuesToExpect{2U, 5U, 1U};
    EXPECT_EQ(valuesToExpect, valuesToVerify);
}

}  // namespace algorithm

}  // namespace alba
