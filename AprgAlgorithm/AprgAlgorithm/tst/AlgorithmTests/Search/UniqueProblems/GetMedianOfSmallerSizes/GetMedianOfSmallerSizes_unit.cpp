#include <Algorithm/Search/UniqueProblems/GetMedianOfSmallerSizes/GetMedianOfSmallerSizes.hpp>

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
using QueryForTest = GetMedianOfSmallerSizes<ValuesForTest>;
}

TEST(GetMedianOfSmallerSizesTest, GetGetMedianOfSmallerSizesWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    EXPECT_EQ(0U, query.getMedian());
    EXPECT_EQ(0U, query.getSmallerMedian());
    EXPECT_EQ(0U, query.getLargerMedian());
}

TEST(GetMedianOfSmallerSizesTest, GetGetMedianOfSmallerSizesWorksOnOneValue)
{
    ValuesForTest valuesForTest{10U};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(10U, query.getMedian());
    EXPECT_EQ(10U, query.getSmallerMedian());
    EXPECT_EQ(10U, query.getLargerMedian());
}

TEST(GetMedianOfSmallerSizesTest, GetGetMedianOfSmallerSizesWorksOnExample1)
{
    ValuesForTest valuesForTest{10U, 12U, 20U, 30U, 25U, 40U, 32U, 31U, 35U, 50U, 60U};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(31U, query.getMedian());
    EXPECT_EQ(31U, query.getSmallerMedian());
    EXPECT_EQ(31U, query.getLargerMedian());
}

TEST(GetMedianOfSmallerSizesTest, GetGetMedianOfSmallerSizesWorksOnExample2)
{
    ValuesForTest valuesForTest{0U, 1U, 15U, 25U, 6U, 7U, 30U, 40U};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(11U, query.getMedian());
    EXPECT_EQ(7U, query.getSmallerMedian());
    EXPECT_EQ(15U, query.getLargerMedian());
}

}

}
