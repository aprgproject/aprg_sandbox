#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithRecursion.hpp>
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
using SearchForTest = BinarySearchWithRecursion<ValuesForTest>;
}

TEST(BinarySearchWithRecursionTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetNearestValueWorks)
{
    testGetNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(5U, 6U, 33U));
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(3U, 5U, 33U));
}

TEST(BinarySearchWithRecursionTest, GetIndexOfNearestValueWorksWithndexesWhenDistanceFromLowerToHigherIsOdd)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(1U, 8U, 33U));
}

}

}
