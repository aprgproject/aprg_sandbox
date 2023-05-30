#include <Algorithm/Search/SumSearch/SubArraySum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = SubArraySum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
}  // namespace

TEST(SubArraySumTest, GetSubArrayWithSumWorksOnExample1) {
    ValuesForTest valuesToSearch{1, 3, 2, 5, 1, 1, 2, 3};
    SumSearch search(valuesToSearch);

    ValuesForTest valuesToVerify(search.getSubArrayWithSum(8));
    ValuesForTest valuesToExpect{2, 5, 1};
    EXPECT_EQ(valuesToExpect, valuesToVerify);
}
}  // namespace algorithm

}  // namespace alba
