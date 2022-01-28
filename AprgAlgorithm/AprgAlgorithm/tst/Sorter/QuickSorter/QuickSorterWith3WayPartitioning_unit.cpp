#include <Sorter/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    sortCharactersUsingExample1(make_unique<QuickSorterWith3WayPartitioning<Characters>>());
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    sortCharactersUsingExample2(make_unique<QuickSorterWith3WayPartitioning<Characters>>());
}

}
