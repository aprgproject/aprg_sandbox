#include <Algorithm/Search/NearestValue/LinearSearch/LinearNearestValueSearchWithOneIndex.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = LinearNearestValueSearchWithOneIndex<ValuesForTest>;
}  // namespace

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(0, search.getIndexOfNearestValue(33));
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(
    LinearNearestValueSearchWithOneIndexTest,
    GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4, 5, unsortedValues);

    EXPECT_EQ(72, search.getNearestValue(33));
}

TEST(
    LinearNearestValueSearchWithOneIndexTest,
    GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    SearchForTest search(4, 6, unsortedValues);

    EXPECT_EQ(6, search.getNearestValue(33));
}

TEST(LinearNearestValueSearchWithOneIndexTest, GetNearestValueWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest unsortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1, 8, unsortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

}  // namespace algorithm

}  // namespace alba
