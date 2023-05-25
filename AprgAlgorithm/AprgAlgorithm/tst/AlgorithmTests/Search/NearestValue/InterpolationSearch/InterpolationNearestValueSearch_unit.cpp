#include <Algorithm/Search/NearestValue/InterpolationSearch/InterpolationNearestValueSearch.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = InterpolationNearestValueSearch<ValuesForTest>;
}  // namespace

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(3, search.getIndexOfNearestValue(33));
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWorksWithInitialIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(5, 6, sortedValues);

    EXPECT_EQ(43, search.getNearestValue(33));
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWithInitialIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(3, 5, sortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

TEST(InterpolationNearestValueSearchTest, GetNearestValueWithInitialIndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(1, 8, sortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

}  // namespace algorithm

}  // namespace alba
