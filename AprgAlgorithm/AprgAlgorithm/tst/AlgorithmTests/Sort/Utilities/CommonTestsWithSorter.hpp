#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithSorter
{

template <typename Sorter, typename Values>
void testSortUsingExample1WithCharacters()
{
    Sorter sorter;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortUsingExample2WithCharacters()
{
    Sorter sorter;
    Values valuesToTest{'C', 'O', 'M', 'P', 'L', 'I', 'C', 'A', 'T', 'E', 'D', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'A', 'C', 'C', 'D', 'E', 'E', 'E', 'I', 'L', 'L', 'M', 'M', 'O', 'P', 'P', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithPositiveAndNegativeIntegers()
{
    Sorter sorter;
    Values valuesToTest{-5, -10, 0, -3, 8, 5, -1, 10};

    sorter.sort(valuesToTest);

    Values valuesToExpect{-10, -5, -3, -1, 0, 5, 8, 10};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}

}

}