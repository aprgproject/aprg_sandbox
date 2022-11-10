#include <Algorithm/Search/BinarySearch/BinarySearchWithSkip.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithSkip<ValuesForTest>;
}

TEST(BinarySearchWithSkipTest, GetNearestValueWorks)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(33U, binarySearch.getNearestValue(33));
}

TEST(BinarySearchWithSkipTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.getNearestValue(33));
}

TEST(BinarySearchWithSkipTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(33U, binarySearch.getNearestValue(34));
}

TEST(BinarySearchWithSkipTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(43U, binarySearch.getNearestValue(42));
}

TEST(BinarySearchWithSkipTest, GetIndexOfNearestValueWorks)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(4U, binarySearch.getIndexOfNearestValue(33));
}

TEST(BinarySearchWithSkipTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.getIndexOfNearestValue(33));
}

TEST(BinarySearchWithSkipTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(4U, binarySearch.getIndexOfNearestValue(34));
}

TEST(BinarySearchWithSkipTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(5U, binarySearch.getIndexOfNearestValue(42));
}

}

}
