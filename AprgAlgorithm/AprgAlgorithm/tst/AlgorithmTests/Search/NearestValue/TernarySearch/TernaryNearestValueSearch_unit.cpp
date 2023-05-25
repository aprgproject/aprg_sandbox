#include <Algorithm/Search/NearestValue/TernarySearch/TernaryNearestValueSearch.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = TernaryNearestValueSearch<ValuesForTest>;
}  // namespace

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(33));
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(5, 6, 33));
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(3, 5, 33));
}

TEST(TernaryNearestValueSearchTest, GetIndexOfNearestValueWorksWithndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(1, 8, 33));
}

}  // namespace algorithm

}  // namespace alba
