#include <Algorithm/Random/ApproximateMedian.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

using ValuesForTest = vector<int>;
using ApproximateMedianForTest = ApproximateMedian<ValuesForTest>;
using ValueForTest = ApproximateMedianForTest::Value;

TEST(ApproximateMedianTest, GetApproximateMedianWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 0};
    ApproximateMedianForTest approximateMedian;

    EXPECT_NE(0, approximateMedian.getApproximateMedian(values));
}

TEST(ApproximateMedianTest, GetApproximateMedianWorksOnExample2) {
    ValuesForTest values{1, 3, 2, 4, 5, 6, 8, 7};
    ApproximateMedianForTest approximateMedian;

    EXPECT_NE(0, approximateMedian.getApproximateMedian(values));
}

}  // namespace algorithm

}  // namespace alba
