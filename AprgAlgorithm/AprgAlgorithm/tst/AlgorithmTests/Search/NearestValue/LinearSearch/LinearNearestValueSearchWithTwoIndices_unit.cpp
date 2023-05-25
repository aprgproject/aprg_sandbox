#include <Algorithm/Search/NearestValue/LinearSearch/LinearNearestValueSearchWithTwoIndices.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = LinearNearestValueSearchWithTwoIndices<ValuesForTest>;
}  // namespace

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(0, search.getIndexOfNearestValue(33));
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(
    LinearNearestValueSearchWithTwoIndicesTest,
    GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4, 5, unsortedValues);

    EXPECT_EQ(72, search.getNearestValue(33));
}

TEST(
    LinearNearestValueSearchWithTwoIndicesTest,
    GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4, 6, unsortedValues);

    EXPECT_EQ(6, search.getNearestValue(33));
}

TEST(LinearNearestValueSearchWithTwoIndicesTest, GetNearestValueWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest unsortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1, 8, unsortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

}  // namespace algorithm

}  // namespace alba
