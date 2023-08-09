#include <Algorithm/Sort/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<char>;
using SorterForTest = QuickSorterWith3WayPartitioning<ValuesForTest>;
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    testSortUsingExample1WithCharacters<SorterForTest, ValuesForTest>();
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    testSortUsingExample2WithCharacters<SorterForTest, ValuesForTest>();
}

}

}
