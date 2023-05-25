#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithNearestValueSearch {

// getNearestValue

template <typename Search, typename Values>
void testGetNearestValueDoesNotCrashWithEmptyUnsignedInts() {
    Values emptyValues;
    Search search(emptyValues);

    EXPECT_EQ(0, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWithOneUnsignedInt() {
    Values oneValue{10};
    Search search(oneValue);

    EXPECT_EQ(10, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWithDuplicateUnsignedInts() {
    Values duplicateValues{0, 0, 0, 0, 0};
    Search search(duplicateValues);

    EXPECT_EQ(0, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWithMultipleUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(33, search.getNearestValue(34));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(43, search.getNearestValue(42));
}

template <typename Search, typename Values>
void testGetNearestValueWithMultipleSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(33, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(33, search.getNearestValue(34));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(43, search.getNearestValue(42));
}

// getIndexOfNearestValue

template <typename Search, typename Values>
void testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts() {
    Values emptyValues;
    Search search(emptyValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWithOneUnsignedInt() {
    Values oneValue{10};
    Search search(oneValue);

    EXPECT_EQ(0, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWithMultipleUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10, search.getIndexOfNearestValue(34));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts() {
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(0, search.getIndexOfNearestValue(42));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWithMultipleSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4, search.getIndexOfNearestValue(34));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts() {
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(5, search.getIndexOfNearestValue(42));
}

}  // namespace CommonTestsWithNearestValueSearch

}  // namespace algorithm

}  // namespace alba
