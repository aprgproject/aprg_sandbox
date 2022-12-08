#include <Algorithm/Search/SingleValue/TernarySearch/TernarySearch.hpp>
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
using SearchForTest = TernarySearch<ValuesForTest>;
}

TEST(TernarySearchTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues)
{
    ValuesForTest sortedValues{13, 13, 14, 33, 33, 33, 53, 53, 53, 72, 72, 72, 72, 96, 96};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfValue(33U));
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernarySearchTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
