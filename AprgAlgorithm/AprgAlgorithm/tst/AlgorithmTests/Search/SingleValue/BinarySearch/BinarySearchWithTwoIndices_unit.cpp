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

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenThereIsOneValue)
{
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreDuplicateValues)
{
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreMultipleValues)
{
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereIsOneValue)
{
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues)
{
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(33));
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues)
{
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithOneItem)
{
    ValuesForTest sortedValues{6};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(6U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithTwoItems)
{
    ValuesForTest sortedValues{6, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithFourItems)
{
    ValuesForTest sortedValues{6, 13, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithoutGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksAfterGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33U, search.getNearestValue(34));

    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksWithoutGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(0U, search.getLowerIndex());
    EXPECT_EQ(14U, search.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksAfterGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33U, search.getNearestValue(34));

    EXPECT_EQ(4U, search.getLowerIndex());
    EXPECT_EQ(5U, search.getHigherIndex());
}

TEST(BinarySearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(5U, 6U, sortedValues);

    EXPECT_EQ(43U, search.getLowerValue());
    EXPECT_EQ(51U, search.getHigherValue());
    EXPECT_EQ(43U, search.getNearestValue(33));
    EXPECT_EQ(43U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(3U, 5U, sortedValues);

    EXPECT_EQ(25U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
    EXPECT_EQ(33U, search.getNearestValue(33));
    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(33U, search.getHigherValue());
}

TEST(BinarySearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1U, 8U, sortedValues);

    EXPECT_EQ(13U, search.getLowerValue());
    EXPECT_EQ(64U, search.getHigherValue());
    EXPECT_EQ(33U, search.getNearestValue(33));
    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(33U, search.getHigherValue());
}

}

}
