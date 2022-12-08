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

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereIsOneValue)
{
    testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreDuplicateValues)
{
    testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsLessThanTheLowestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsLessThanTheHighestValueAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWithIndicesWorksWhenValueIsNotFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithRecursionTest, GetIndexOfValueWithIndicesWorksWhenValueIsFoundAndWhenThereAreMultipleValues)
{
    testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

}

}
