#include <Sorter/QuickSorter/QuickSorter.hpp>
#include <Sorter/Utilities/CommonTestsWithBaseSorter.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSorter;
using namespace std;

namespace alba
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


