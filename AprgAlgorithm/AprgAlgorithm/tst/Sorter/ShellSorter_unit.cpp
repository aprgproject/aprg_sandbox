#include <Sorter/ShellSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(ShellSorterTest, SortWorksOnExample1)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    ShellSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(ShellSorterTest, SortWorksOnExample2)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'H', 'E', 'L', 'L', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    ShellSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'E', 'H', 'L', 'L', 'L', 'M', 'O', 'P', 'R', 'S', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
