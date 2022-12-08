#include <Algorithm/Search/SingleValue/ExponentialSearch/ExponentialSearch.hpp>
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
using SearchForTest = ExponentialSearch<ValuesForTest>;
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues)
{
    ValuesForTest sortedValues{13, 13, 14, 33, 33, 33, 53, 53, 53, 72, 72, 72, 72, 96, 96};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfValue(33U));
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(ExponentialSearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
