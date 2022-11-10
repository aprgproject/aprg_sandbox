#include <Algorithm/Search/BinarySearch/BinarySearchWithCppFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinarySearchWithCPlusPlusFunctions<ValuesForTest>;
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetNearestValueWorks)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(33U, binarySearch.getNearestValue(33));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.getNearestValue(33));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(33U, binarySearch.getNearestValue(34));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(43U, binarySearch.getNearestValue(42));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetIndexOfNearestValueWorks)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(4U, binarySearch.getIndexOfNearestValue(33));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.getIndexOfNearestValue(33));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(4U, binarySearch.getIndexOfNearestValue(34));
}

TEST(BinarySearchWithCPlusPlusFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);

    EXPECT_EQ(5U, binarySearch.getIndexOfNearestValue(42));
}

}

}
