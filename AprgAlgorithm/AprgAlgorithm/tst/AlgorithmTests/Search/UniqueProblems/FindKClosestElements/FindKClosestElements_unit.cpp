#include <Algorithm/Search/UniqueProblems/FindKClosestElements/FindKClosestElements.hpp>

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
using QueryForTest = FindKClosestElements<ValuesForTest>;
}

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{QueryForTest::INVALID_INDEX, QueryForTest::INVALID_INDEX};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4U, 35U));
}

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnOneValue)
{
    ValuesForTest valuesForTest{12};
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{0U, 0U};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4U, 35U));
}

TEST(FindKClosestElementsTest, GetIndexPairClosestElementsWorksOnExample1)
{
    ValuesForTest valuesForTest{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    QueryForTest query(valuesForTest);

    QueryForTest::IndexPair expectedIndexPair{3U, 6U};
    EXPECT_EQ(expectedIndexPair, query.getIndexPairClosestElements(4U, 35U));
}

}

}
