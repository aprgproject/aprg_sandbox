#include <AprgUniqueProblems/SearchProblems/MaximumUnsortedRange/MaximumUnsortedRange.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = MaximumUnsortedRange<ValuesForTest>;
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query;

    QueryForTest::IndexPair expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnOneValue)
{
    ValuesForTest valuesForTest{10U};
    QueryForTest query;

    QueryForTest::IndexPair expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnExample1)
{
    ValuesForTest valuesForTest{10U, 12U, 20U, 30U, 25U, 40U, 32U, 31U, 35U, 50U, 60U};
    QueryForTest query;

    QueryForTest::IndexPair expectedIndexPair{3U, 8U};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

TEST(MaximumUnsortedRangeTest, GetMaximumUnsortedRangeWorksOnExample2)
{
    ValuesForTest valuesForTest{0U, 1U, 15U, 25U, 6U, 7U, 30U, 40U, 50U};
    QueryForTest query;

    QueryForTest::IndexPair expectedIndexPair{2U, 5U};
    EXPECT_EQ(expectedIndexPair, query.getMaximumUnsortedRange(valuesForTest));
}

}

}
