#include <UniqueProblems/SearchProblems/FindKClosestElements.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindKClosestElements<ValuesForTest>;
}  // namespace

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnEmpty) {
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4, 35));
}

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnOneValue) {
    ValuesForTest valuesForTest{12};
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{0, 0};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4, 35));
}

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnExample1) {
    ValuesForTest valuesForTest{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{3, 6};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4, 35));
}

}  // namespace algorithm

}  // namespace alba
