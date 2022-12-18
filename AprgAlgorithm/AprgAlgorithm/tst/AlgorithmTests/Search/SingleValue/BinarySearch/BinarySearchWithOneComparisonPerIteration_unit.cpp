#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithOneComparisonPerIteration.hpp>
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
using SearchForTest = BinarySearchWithOneComparisonPerIteration<ValuesForTest>;
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithOneComparisonPerIterationTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
