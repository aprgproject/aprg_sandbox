#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithTwoIndices.hpp>
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
using SearchForTest = BinarySearchWithTwoIndices<ValuesForTest>;
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
