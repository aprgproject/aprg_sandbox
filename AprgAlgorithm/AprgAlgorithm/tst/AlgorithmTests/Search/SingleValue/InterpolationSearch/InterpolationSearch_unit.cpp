#include <Algorithm/Search/SingleValue/InterpolationSearch/InterpolationSearch.hpp>
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
using SearchForTest = InterpolationSearch<ValuesForTest>;
}

TEST(InterpolationSearchTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetNearestValueWorks)
{
    testGetNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfNearestValueWorks)
{
    testGetIndexOfNearestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
