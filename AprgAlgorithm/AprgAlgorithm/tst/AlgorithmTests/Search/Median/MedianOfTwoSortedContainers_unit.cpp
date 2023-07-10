#include <Algorithm/Search/Median/MedianOfTwoSortedContainers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = MedianOfTwoSortedContainers<ValuesForTest>;
}  // namespace

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnWhenBothAreEmpty) {
    ValuesForTest empty;
    QueryForTest query(empty, empty);

    EXPECT_EQ(0, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnWhenOneIsEmpty) {
    ValuesForTest empty;
    ValuesForTest notEmpty{1, 2, 3};
    QueryForTest query1(empty, notEmpty);
    QueryForTest query2(notEmpty, empty);

    EXPECT_EQ(2, query1.getMedian());
    EXPECT_EQ(2, query2.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample1) {
    ValuesForTest valuesForTest1{1, 12, 15, 26, 38};
    ValuesForTest valuesForTest2{2, 13, 17, 30, 45};
    QueryForTest query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(15, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample2) {
    ValuesForTest valuesForTest1{1, 12, 17, 26, 38};
    ValuesForTest valuesForTest2{2, 13, 15, 30, 45};
    QueryForTest query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(15, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample3) {
    ValuesForTest valuesForTest1{1, 13, 13, 26, 38};
    ValuesForTest valuesForTest2{2, 12, 17, 30, 45};
    QueryForTest query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(13, query.getMedian());
}

TEST(MedianOfTwoSortedContainersTest, GetMedianWorksOnExample4) {
    ValuesForTest valuesForTest1{1, 12, 13, 26, 38};
    ValuesForTest valuesForTest2{2, 13, 17, 30, 45};
    QueryForTest query(valuesForTest1, valuesForTest2);

    EXPECT_EQ(13, query.getMedian());
}

}  // namespace algorithm

}  // namespace alba
