#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithCppFunctions.hpp>
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
using SearchForTest = BinarySearchWithCppFunctions<ValuesForTest>;
}

TEST(BinarySearchWithCppFunctionsTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetNearestValueWorks)
{
    testGetNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithCppFunctionsTest, GetLowerBoundAndGetHigherBoundWorks)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(43U, search.getLowerBound(34));
    EXPECT_EQ(43U, search.getHigherBound(34));
}

}

}
