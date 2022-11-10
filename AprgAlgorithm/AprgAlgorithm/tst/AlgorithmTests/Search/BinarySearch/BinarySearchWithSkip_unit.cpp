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

TEST(BinarySearchWithSkipTest, FindNearestValueWorks)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);
    EXPECT_EQ(33U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchWithSkipTest, FindNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    ValuesForTest valuesForTest;
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(0U, binarySearch.findNearestValue(33));
}

TEST(BinarySearchWithSkipTest, FindNearestValueWorksWhenNearestValueIsLower)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);
    EXPECT_EQ(33U, binarySearch.findNearestValue(34));
}

TEST(BinarySearchWithSkipTest, FindNearestValueWorksWhenNearestValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(sortedValues);
    EXPECT_EQ(43U, binarySearch.findNearestValue(42));
}

TEST(BinarySearchWithSkipTest, FindIndexOfNearestValueWorks)
{
    ValuesForTest valuesForTest{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest binarySearch(valuesForTest);

    EXPECT_EQ(4U, binarySearch.findIndexOfNearestValue(33));
}

}

}