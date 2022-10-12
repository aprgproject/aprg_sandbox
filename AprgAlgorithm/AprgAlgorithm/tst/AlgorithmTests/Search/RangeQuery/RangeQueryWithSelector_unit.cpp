#include <Algorithm/Search/RangeQuery/RangeQueryWithSelector.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithSelector<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::SelectorFunction minimumSelector = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return min(value1, value2);
};

RangeQueryForTest::SelectorFunction maximumSelector = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return max(value1, value2);
};
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(0U, minimumRangeQuery.getSelectedValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMinimumWorksInExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5U, minimumRangeQuery.getSelectedValueOnInterval(0U, 0U));
    EXPECT_EQ(5U, minimumRangeQuery.getSelectedValueOnInterval(0U, 1U));
    EXPECT_EQ(4U, minimumRangeQuery.getSelectedValueOnInterval(0U, 2U));    EXPECT_EQ(4U, minimumRangeQuery.getSelectedValueOnInterval(0U, 3U));
    EXPECT_EQ(4U, minimumRangeQuery.getSelectedValueOnInterval(0U, 4U));
    EXPECT_EQ(1U, minimumRangeQuery.getSelectedValueOnInterval(0U, 5U));
    EXPECT_EQ(1U, minimumRangeQuery.getSelectedValueOnInterval(0U, 6U));
    EXPECT_EQ(1U, minimumRangeQuery.getSelectedValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getSelectedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getSelectedValueOnInterval(0U, 9U));
    EXPECT_EQ(1U, minimumRangeQuery.getSelectedValueOnInterval(3U, 6U));
    EXPECT_EQ(4U, minimumRangeQuery.getSelectedValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithSelectorTest, GetSelectedValueOnIntervalWithMaximumWorksInExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 10U};
    RangeQueryForTest maximumRangeQuery(values, maximumSelector);

    EXPECT_EQ(5U, maximumRangeQuery.getSelectedValueOnInterval(0U, 0U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 1U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 2U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 3U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 4U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 5U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 6U));
    EXPECT_EQ(9U, maximumRangeQuery.getSelectedValueOnInterval(0U, 7U));
    EXPECT_EQ(10U, maximumRangeQuery.getSelectedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getSelectedValueOnInterval(0U, 9U));
    EXPECT_EQ(8U, maximumRangeQuery.getSelectedValueOnInterval(3U, 6U));
    EXPECT_EQ(8U, maximumRangeQuery.getSelectedValueOnInterval(2U, 4U));
}

}

}
