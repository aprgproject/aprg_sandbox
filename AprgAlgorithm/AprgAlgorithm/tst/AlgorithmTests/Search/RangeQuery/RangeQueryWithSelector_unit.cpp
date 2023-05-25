#include <Algorithm/Search/RangeQuery/RangeQueryWithSelector.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithSelector<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::SelectorFunction minimumSelector = [](ValueForTest const& value1, ValueForTest const& value2) {
    return min(value1, value2);
};

RangeQueryForTest::SelectorFunction maximumSelector = [](ValueForTest const& value1, ValueForTest const& value2) {
    return max(value1, value2);
};
}  // namespace

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(0, minimumRangeQuery.getSelectedValueOnInterval(0, 0));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksWithOneValue) {
    ValuesForTest values{5};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5, minimumRangeQuery.getSelectedValueOnInterval(0, 0));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksWithTwoValues) {
    ValuesForTest values{5, 9};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5, minimumRangeQuery.getSelectedValueOnInterval(0, 0));
    EXPECT_EQ(5, minimumRangeQuery.getSelectedValueOnInterval(0, 1));
    EXPECT_EQ(9, minimumRangeQuery.getSelectedValueOnInterval(1, 1));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 0};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5, minimumRangeQuery.getSelectedValueOnInterval(0, 0));
    EXPECT_EQ(5, minimumRangeQuery.getSelectedValueOnInterval(0, 1));
    EXPECT_EQ(4, minimumRangeQuery.getSelectedValueOnInterval(0, 2));
    EXPECT_EQ(4, minimumRangeQuery.getSelectedValueOnInterval(0, 3));
    EXPECT_EQ(4, minimumRangeQuery.getSelectedValueOnInterval(0, 4));
    EXPECT_EQ(1, minimumRangeQuery.getSelectedValueOnInterval(0, 5));
    EXPECT_EQ(1, minimumRangeQuery.getSelectedValueOnInterval(0, 6));
    EXPECT_EQ(1, minimumRangeQuery.getSelectedValueOnInterval(0, 7));
    EXPECT_EQ(0, minimumRangeQuery.getSelectedValueOnInterval(0, 8));
    EXPECT_EQ(0, minimumRangeQuery.getSelectedValueOnInterval(0, 9));
    EXPECT_EQ(1, minimumRangeQuery.getSelectedValueOnInterval(3, 6));
    EXPECT_EQ(4, minimumRangeQuery.getSelectedValueOnInterval(2, 4));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMaximumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 10};
    RangeQueryForTest maximumRangeQuery(values, maximumSelector);

    EXPECT_EQ(5, maximumRangeQuery.getSelectedValueOnInterval(0, 0));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 1));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 2));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 3));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 4));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 5));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 6));
    EXPECT_EQ(9, maximumRangeQuery.getSelectedValueOnInterval(0, 7));
    EXPECT_EQ(10, maximumRangeQuery.getSelectedValueOnInterval(0, 8));
    EXPECT_EQ(0, maximumRangeQuery.getSelectedValueOnInterval(0, 9));
    EXPECT_EQ(8, maximumRangeQuery.getSelectedValueOnInterval(3, 6));
    EXPECT_EQ(8, maximumRangeQuery.getSelectedValueOnInterval(2, 4));
}

}  // namespace algorithm

}  // namespace alba
