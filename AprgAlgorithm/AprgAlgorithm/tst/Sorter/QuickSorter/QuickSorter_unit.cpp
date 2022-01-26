#include <Sorter/QuickSorter/QuickSorter.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(QuickSorterTest, SortWorksOnExample1)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    QuickSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSorterTest, SortWorksOnExample2)
{
    using Values=vector<char>;
    Values valuesToTest{'Q', 'U', 'I', 'C', 'K', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    QuickSorter<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'C', 'E', 'E', 'I', 'K', 'L', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
