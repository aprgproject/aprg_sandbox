#include <Algorithm/Search/NearestValue/LinearSearch/LinearSearchWithTwoIndices.hpp>
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
using SearchForTest = LinearNearestValueSearchWithTwoIndices<ValuesForTest>;
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty){
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}
TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereIsOneValue)
{
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreDuplicateValues)
{
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreMultipleValues)
{
    testGetNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower)
{
    testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher)
{
    testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty)
{
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereIsOneValue)
{
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues)
{
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(0U, search.getIndexOfNearestValue(33));
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues)
{
    testGetIndexOfNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower)
{
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher)
{
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne)
{
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4U, 5U, unsortedValues);

    EXPECT_EQ(72U, search.getNearestValue(33));
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo)
{
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4U, 6U, unsortedValues);

    EXPECT_EQ(6U, search.getNearestValue(33));
}

TEST(LinearSearchWithTwoIndicesTest, GetNearestValueWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd)
{
    ValuesForTest unsortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1U, 8U, unsortedValues);

    EXPECT_EQ(33U, search.getNearestValue(33));
}

}

}
