#include <Algorithm/Search/SingleValue/JumpSearch/JumpSearch.hpp>
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
using SearchForTest = JumpSearch<ValuesForTest>;
}

TEST(JumpSearchTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetNearestValueWorks)
{
    testGetNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(JumpSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
