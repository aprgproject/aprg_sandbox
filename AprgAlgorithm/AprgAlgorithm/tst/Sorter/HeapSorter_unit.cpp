#include <Sorter/HeapSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(HeapSorterTest, SortWorksOnExample1)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    HeapSorter<char, Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(HeapSorterTest, SortWorksOnExample2)
{
    using Values=vector<char>;
    Values valuesToTest{'H', 'E', 'A', 'P', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    HeapSorter<char, Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'A', 'E', 'E', 'E', 'H', 'L', 'M', 'O', 'P', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
