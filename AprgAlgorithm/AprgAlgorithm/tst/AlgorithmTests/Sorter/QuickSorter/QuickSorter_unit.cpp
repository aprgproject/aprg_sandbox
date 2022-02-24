#include <Algorithm/Sorter/QuickSorter/QuickSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1)
{
    QuickSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2)
{
    QuickSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}

}
