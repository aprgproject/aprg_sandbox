#include <Algorithm/Search/BinarySearch/BinarySearchWithTwoIndices.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithTwoIndices<ValuesForTest>;
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorks)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.findNearestValue(33));
    EXPECT_EQ(0U, binarySearch.getLowerValue());
    EXPECT_EQ(0U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(34));
    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(43U, binarySearch.findNearestValue(42));
    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorksWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(5U, 6U, valuesForTest);

    EXPECT_EQ(43U, binarySearch.findNearestValue(33));
    EXPECT_EQ(43U, binarySearch.getLowerValue());
    EXPECT_EQ(43U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindNearestValueWorksWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(3U, 5U, valuesForTest);

    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
    EXPECT_EQ(33U, binarySearch.getLowerValue());
    EXPECT_EQ(33U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, FindIndexOfNearestValueWorks)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(4U, binarySearch.findIndexOfNearestValue(33));
    EXPECT_EQ(4U, binarySearch.getLowerIndex());
    EXPECT_EQ(5U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, FindIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.findIndexOfNearestValue(33));
    EXPECT_EQ(0U, binarySearch.getLowerIndex());
    EXPECT_EQ(0U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, FindIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(4U, binarySearch.findIndexOfNearestValue(33));
    EXPECT_EQ(4U, binarySearch.getLowerIndex());
    EXPECT_EQ(5U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, FindIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(5U, binarySearch.findIndexOfNearestValue(42));
    EXPECT_EQ(4U, binarySearch.getLowerIndex());
    EXPECT_EQ(5U, binarySearch.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInOneItem)
{
    ValuesForTest valuesForTest{6};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(6U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInTwoItems)
{
    ValuesForTest valuesForTest{6, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(97U, binarySearch.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, HighLowMiddleValuesCanFetchedInFourItems)
{
    ValuesForTest valuesForTest{6, 13, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(6U, binarySearch.getLowerValue());
    EXPECT_EQ(97U, binarySearch.getHigherValue());
}

}

}
