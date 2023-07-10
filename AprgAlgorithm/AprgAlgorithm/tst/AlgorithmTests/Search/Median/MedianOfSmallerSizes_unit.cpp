#include <Algorithm/Search/Median/MedianOfSmallerSizes.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = MedianOfSmallerSizes<ValuesForTest>;
}  // namespace

TEST(MedianOfSmallerSizesTest, GetMedianOfSmallerSizesWorksOnEmpty) {
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    EXPECT_EQ(0, query.getSmallerMedian());
    EXPECT_EQ(0, query.getLargerMedian());
    EXPECT_EQ(0, query.getMedian());
}

TEST(MedianOfSmallerSizesTest, GetMedianOfSmallerSizesWorksOnOneValue) {
    ValuesForTest valuesForTest{10};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(10, query.getSmallerMedian());
    EXPECT_EQ(10, query.getLargerMedian());
    EXPECT_EQ(10, query.getMedian());
}

TEST(MedianOfSmallerSizesTest, GetMedianOfSmallerSizesWorksOnExample1) {
    ValuesForTest valuesForTest{10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(31, query.getSmallerMedian());
    EXPECT_EQ(31, query.getLargerMedian());
    EXPECT_EQ(31, query.getMedian());
}

TEST(MedianOfSmallerSizesTest, GetMedianOfSmallerSizesWorksOnExample2) {
    ValuesForTest valuesForTest{0, 1, 15, 25, 6, 7, 30, 40};
    QueryForTest query(valuesForTest);

    EXPECT_EQ(7, query.getSmallerMedian());
    EXPECT_EQ(15, query.getLargerMedian());
    EXPECT_EQ(11, query.getMedian());
}

}  // namespace algorithm

}  // namespace alba
