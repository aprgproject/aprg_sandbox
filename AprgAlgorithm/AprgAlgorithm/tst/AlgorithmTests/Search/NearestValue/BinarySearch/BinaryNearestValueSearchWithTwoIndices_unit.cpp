#include <Algorithm/Search/NearestValue/BinarySearch/BinaryNearestValueSearchWithTwoIndices.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SearchForTest = BinaryNearestValueSearchWithTwoIndices<ValuesForTest>;
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereIsOneValue)
{
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreDuplicateValues)
{
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreMultipleValues)
{
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereIsOneValue)
{
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues)
{
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(33));
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues)
{
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithOneItem)
{
    ValuesForTest sortedValues{6};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(6U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithTwoItems)
{
    ValuesForTest sortedValues{6, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithFourItems)
{
    ValuesForTest sortedValues{6, 13, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksWithoutGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(6U, search.getLowerValue());
    EXPECT_EQ(97U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerValueAndGetHigherValueWorksAfterGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33U, search.getNearestValue(34));

    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksWithoutGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(0U, search.getLowerIndex());
    EXPECT_EQ(14U, search.getHigherIndex());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, GetLowerIndexAndGetHigherIndexWorksAfterGetNearestValue)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);
    EXPECT_EQ(33U, search.getNearestValue(34));

    EXPECT_EQ(4U, search.getLowerIndex());
    EXPECT_EQ(5U, search.getHigherIndex());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(5U, 6U, sortedValues);

    EXPECT_EQ(43U, search.getLowerValue());
    EXPECT_EQ(51U, search.getHigherValue());
    EXPECT_EQ(43U, search.getNearestValue(33));
    EXPECT_EQ(43U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(3U, 5U, sortedValues);

    EXPECT_EQ(25U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
    EXPECT_EQ(33U, search.getNearestValue(33));
    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(33U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1U, 8U, sortedValues);

    EXPECT_EQ(13U, search.getLowerValue());
    EXPECT_EQ(64U, search.getHigherValue());
    EXPECT_EQ(33U, search.getNearestValue(33));
    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(33U, search.getHigherValue());
}

TEST(BinaryNearestValueSearchWithTwoIndicesTest, SearchWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOddAndValueIsHigher)
{
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1U, 8U, sortedValues);

    EXPECT_EQ(13U, search.getLowerValue());
    EXPECT_EQ(64U, search.getHigherValue());
    EXPECT_EQ(33U, search.getNearestValue(34));
    EXPECT_EQ(33U, search.getLowerValue());
    EXPECT_EQ(43U, search.getHigherValue());
}

}

}
