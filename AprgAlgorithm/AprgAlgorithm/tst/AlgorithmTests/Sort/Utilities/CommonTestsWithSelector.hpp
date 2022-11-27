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
void testSortUsingExample1WithCharacters(Sorter const& sorter)
{
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortUsingExample2WithCharacters(Sorter const& sorter)
{
    Values valuesToTest{'C', 'O', 'M', 'P', 'L', 'I', 'C', 'A', 'T', 'E', 'D', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'A', 'C', 'C', 'D', 'E', 'E', 'E', 'I', 'L', 'L', 'M', 'M', 'O', 'P', 'P', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortUsingExample1WithPositiveAndNegativeIntegers(Sorter const& sorter)
{
    Values valuesToTest{-5, -10, 0, -3, 8, 5, -1, 10};

    sorter.sort(valuesToTest);

    Values valuesToExpect{-10, -5, -3, -1, 0, 5, 8, 10};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortAsStableUsingExample1WithStabilityCheckObjects(Sorter const& sorter)
{
    Values valuesToTest{{'A',1}, {'C',1}, {'D',1}, {'A',2}, {'B',1}, {'A',3}, {'F',1}, {'E',1}, {'A',4}, {'B',2}, {'D',2}, {'D',3}, {'G',1}};

    sorter.sort(valuesToTest);

    Values valuesToExpect{{'A',1}, {'A',2}, {'A',3}, {'A',4}, {'B',1}, {'B',2}, {'C',1}, {'D',1}, {'D',2}, {'D',3}, {'E',1}, {'F',1}, {'G',1}};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

template <typename Sorter, typename Values>
void testSortAsNotStableUsingExample1WithStabilityCheckObjects(Sorter const& sorter)
{
    Values valuesToTest{{'A',1}, {'C',1}, {'D',1}, {'A',2}, {'B',1}, {'A',3}, {'F',1}, {'E',1}, {'A',4}, {'B',2}, {'D',2}, {'D',3}, {'G',1}};

    sorter.sort(valuesToTest);

    Values valuesToExpect{{'A',1}, {'A',2}, {'A',3}, {'A',4}, {'B',1}, {'B',2}, {'C',1}, {'D',1}, {'D',2}, {'D',3}, {'E',1}, {'F',1}, {'G',1}};
    EXPECT_NE(valuesToExpect, valuesToTest);
}

}

}

}
