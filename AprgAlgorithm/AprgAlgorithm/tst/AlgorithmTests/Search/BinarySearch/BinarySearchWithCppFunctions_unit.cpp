#include <Algorithm/Search/BinarySearch/BinarySearchWithCppFunctions.hpp>
#include <AlgorithmTests/Search/Utilities/CommonTestsWithSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSearch;
using namespace std;

namespace alba{

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

}
}