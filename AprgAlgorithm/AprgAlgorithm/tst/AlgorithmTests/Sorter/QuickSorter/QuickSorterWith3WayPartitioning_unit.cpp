#include <Algorithm/Sorter/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
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

}
