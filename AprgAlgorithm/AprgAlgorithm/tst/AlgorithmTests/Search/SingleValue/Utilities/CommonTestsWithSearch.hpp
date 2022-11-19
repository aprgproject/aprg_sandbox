#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithSearch
{

// getNearestValue

template <typename Search, typename Values>
void testGetNearestValueDoesNotCrashWithEmptyUnsignedInts()
{
    Values emptyValues;
    Search search(emptyValues);

    EXPECT_EQ(0U, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(33U, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(33U, search.getNearestValue(34));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(43U, search.getNearestValue(42));
}

template <typename Search, typename Values>
void testGetNearestValueWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(33U, search.getNearestValue(33));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(33U, search.getNearestValue(34));
}

template <typename Search, typename Values>
void testGetNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(43U, search.getNearestValue(42));
}



// getIndexOfNearestValue

template <typename Search, typename Values>
void testGetIndexOfNearestValueDoesNotCrashWithEmptyUnsignedInts()
{
    Values emptyValues;
    Search search(emptyValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10U, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsLowerWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10U, search.getIndexOfNearestValue(34));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsHigherWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(0U, search.getIndexOfNearestValue(42));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(33));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsLowerWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfNearestValue(34));
}

template <typename Search, typename Values>
void testGetIndexOfNearestValueWhenNearestValueIsHigherWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(5U, search.getIndexOfNearestValue(42));
}

}

}

}
