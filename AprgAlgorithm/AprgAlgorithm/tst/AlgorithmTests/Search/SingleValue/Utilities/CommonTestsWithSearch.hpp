#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithSearch
{

// getIndexOfValue

template <typename Search, typename Values>
void testGetIndexOfValueDoesNotCrashWithEmptyUnsignedInts()
{
    Values emptyValues;
    Search search(emptyValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsNotFoundWithOneUnsignedInt()
{
    Values oneValue{10};
    Search search(oneValue);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsFoundWithOneUnsignedInt()
{
    Values oneValue{10};
    Search search(oneValue);

    EXPECT_EQ(0U, search.getIndexOfValue(10U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithUnsortedUnsignedInts()
{
    Values unsortedValues{96, 96, 53, 53, 53, 72, 72, 72, 72, 14, 33, 33, 33, 13, 13};
    Search search(unsortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(34U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithUnsortedUnsignedInts()
{
    Values unsortedValues{96, 96, 53, 53, 53, 72, 72, 72, 72, 14, 33, 33, 33, 13, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10U, search.getIndexOfValue(33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsNotFoundWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(34U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsFoundWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10U, search.getIndexOfValue(33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsNotFoundWithDuplicatesWithSortedUnsignedInts()
{
    Values sortedValues{13, 13, 14, 33, 33, 33, 53, 53, 53, 72, 72, 72, 72, 96, 96};
    Search search(sortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(34U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsFoundWithDuplicatesWithSortedUnsignedInts()
{
    Values sortedValues{13, 13, 14, 33, 33, 33, 53, 53, 53, 72, 72, 72, 72, 96, 96};
    Search search(sortedValues);

    EXPECT_EQ(3U, search.getIndexOfValue(33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsNotFoundWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(34U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsLessThanTheLowestValueWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(3U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsGreaterThanTheHighestValueWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(100U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWhenValueIsFoundWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfValue(33U));
}


// getIndexOfValue with indices

template <typename Search, typename Values>
void testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(0U, 9U, 33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWithIndicesWhenValueIsFoundWithUnsortedUnsignedInts()
{
    Values unsortedValues{43, 96, 53, 25, 95, 72, 6, 84, 14, 64, 33, 97, 51, 93, 13};
    Search search(unsortedValues);

    EXPECT_EQ(10U, search.getIndexOfValue(0U, 12U, 33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWithIndicesWhenValueIsNotFoundWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);
    auto INVALID_INDEX = Search::INVALID_INDEX;

    EXPECT_EQ(INVALID_INDEX, search.getIndexOfValue(0U, 3U, 33U));
}

template <typename Search, typename Values>
void testGetIndexOfValueWithIndicesWhenValueIsFoundWithSortedUnsignedInts()
{
    Values sortedValues{6, 13, 14, 25, 33, 43, 51, 53, 64, 72, 84, 93, 95, 96, 97};
    Search search(sortedValues);

    EXPECT_EQ(4U, search.getIndexOfValue(0U, 6U, 33U));
}

}

}

}
