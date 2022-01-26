#include <Sorter/QuickSorter/QuickSorterWith3WayPartitioning.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnExample1)
{
    using Values=vector<char>;
    Values valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    QuickSorterWith3WayPartitioning<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnExample2)
{
    using Values=vector<char>;
    Values valuesToTest{'Q', 'U', 'I', 'C', 'K', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    QuickSorterWith3WayPartitioning<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'A', 'C', 'E', 'E', 'I', 'K', 'L', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'X'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnExample3)
{
    using Values=vector<char>;
    Values valuesToTest{'R', 'B', 'W', 'W', 'R', 'W', 'B', 'R', 'R', 'W', 'B', 'R'};
    QuickSorterWith3WayPartitioning<Values> sorter;

    sorter.sort(valuesToTest);

    Values valuesToExpect{'B', 'B', 'B', 'R', 'R', 'R', 'R', 'R', 'W', 'W', 'W', 'W'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}
