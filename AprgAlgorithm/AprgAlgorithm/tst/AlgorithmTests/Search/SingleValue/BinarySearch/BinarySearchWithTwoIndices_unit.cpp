#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithTwoIndices.hpp>
#include <AlgorithmTests/Search/SingleValue/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithTwoIndices<ValuesForTest>;
using IndexForTest = SearchForTest::Index;
IndexForTest INVALID_INDEX = SearchForTest::INVALID_INDEX;
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorks)
{
    testGetNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithOneItem)
{
    ValuesForTest valuesForTest{6};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(6U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithTwoItems)
{
    ValuesForTest valuesForTest{6, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(97U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithFourItems)
{
    ValuesForTest valuesForTest{6, 13, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(97U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithoutGetNearestValue)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(97U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksAfterGetNearestValue)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);
    EXPECT_EQ(33U, binarySearch.getNearestValue(33));

    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksWithoutGetNearestValue)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.getLowerIndex());
    EXPECT_EQ(14U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksAfterGetNearestValue)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);
    EXPECT_EQ(33U, binarySearch.getNearestValue(33));

    EXPECT_EQ(4U, binarySearch.getLowerIndex());
    EXPECT_EQ(5U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(5U, 6U, valuesForTest);

    EXPECT_EQ(43U, binarySearch.getLowerValue());
    EXPECT_EQ(51U, binarySearch.getHigherValue());
    EXPECT_EQ(43U, binarySearch.getNearestValue(33));
    EXPECT_EQ(43U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(3U, 5U, valuesForTest);

    EXPECT_EQ(25U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
    EXPECT_EQ(33U, binarySearch.getNearestValue(33));
    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(33U, binarySearch.getHigherValue());
}

}

}
