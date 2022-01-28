#include <Sorter/HeapSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
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
