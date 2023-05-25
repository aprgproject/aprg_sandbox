#include <Algorithm/Search/NearestValue/BinarySearch/BinaryNearestValueSearchWithRecursion.hpp>
#include <AlgorithmTests/Search/NearestValue/Utilities/CommonTestsWithNearestValueSearch.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithNearestValueSearch;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SearchForTest = BinaryNearestValueSearchWithRecursion<ValuesForTest>;
}  // namespace

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksWhenThereIsOneValue) {
    testGetNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksWhenThereAreDuplicateValues) {
    testGetNearestValueWithDuplicateUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    testGetNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksWhenNearestValueIsLower) {
    testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetNearestValueWorksWhenNearestValueIsHigher) {
    testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksAndDoesNotCrashWhenEmpty) {
    testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksWhenThereIsOneValue) {
    testGetIndexOfNearestValueWithOneUnsignedInt<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksWhenThereAreDuplicateValues) {
    ValuesForTest duplicateValues{0, 0, 0, 0, 0};
    SearchForTest search(duplicateValues);

    EXPECT_EQ(3, search.getIndexOfNearestValue(33));
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksWhenThereAreMultipleValues) {
    testGetIndexOfNearestValueWithMultipleSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksWhenNearestValueIsLower) {
    testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(BinaryNearestValueSearchWithRecursionTest, GetIndexOfNearestValueWorksWhenNearestValueIsHigher) {
    testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts<SearchForTest, ValuesForTest>();
}

TEST(
    BinaryNearestValueSearchWithRecursionTest,
    GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsOne) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfNearestValue(5, 6, 33));
}

TEST(
    BinaryNearestValueSearchWithRecursionTest,
    GetIndexOfNearestValueWorksWithIndexesWhenDistanceFromLowerToHigherIsTwo) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(3, 5, 33));
}

TEST(
    BinaryNearestValueSearchWithRecursionTest,
    GetIndexOfNearestValueWorksWithndexesWhenDistanceFromLowerToHigherIsOdd) {
    ValuesForTest sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    SearchForTest search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(1, 8, 33));
}

}  // namespace algorithm

}  // namespace alba
