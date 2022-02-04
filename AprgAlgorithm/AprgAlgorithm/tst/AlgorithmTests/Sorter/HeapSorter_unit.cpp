#include <Algorithm/Sorter/HeapSorter.hpp>
#include <AlgorithmTests/Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample1)
{
    HeapSorter<Characters> sorter;
    performSortTestUsingExample1(sorter);
}

TEST(HeapSorterTest, SortWorksOnCharactersUsingExample2)
{
    HeapSorter<Characters> sorter;
    performSortTestUsingExample2(sorter);
}

}

}
