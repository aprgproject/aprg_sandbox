#include <Sorter/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    QuickSorterWith3WayPartitioning<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    QuickSorterWith3WayPartitioning<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}
